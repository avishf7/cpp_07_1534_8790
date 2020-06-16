/*
File: management.cpp
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include "Management.h"
#pragma warning(disable:4996)
using namespace std;

bool Manage::isExists(int id)
{
	int max, idF;
	if (_file->is_open())
		_file->seekg(0);
	else
		_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	if (id > max)
		return false;

	_file->seekg((id - 1) * sizeof(Student) + sizeof(int));
	_file->read((char*)&idF, sizeof(int));

	_file->close();

	if (idF != id && idF != 0)
		throw "ERROR:the id in the file is illegal";
	return idF;
}

char* Manage::getCourses(int id)
{
	char* courses;
	if(!(_file->is_open()))
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->seekg(sizeof(int) + id * sizeof(Student) - sizeof(char*));
	_file->read((char*)&courses, sizeof(char*));

	_file->close();

	return courses;
}

Manage::Manage(string fileName) : _file(new fstream), _fileName(fileName)
{
	OpenF(fileName);
}

Manage::Manage(Manage&& manage) : _file(manage._file), _fileName(manage._fileName)
{
	// Avoid temp object DTOR removing the dynamic data which is now used in our object
	manage._file = nullptr;
}

void Manage::OpenF(string fName)
{
	_file->open(fName, ios::binary | ios::out);
	int capacity = 10;

	if (!_file)
		throw "faild to open file";

	_file->write((char*)&capacity, sizeof(int));
	for (int i = 0; i < 10; ++i)
		_file->write((char*)&Student::emptyStudent, sizeof(Student));
	_file->close();
}

void Manage::allocate(std::string fileName)
{
	if (!_file)
		_file = new fstream;
	OpenF(fileName);
	_fileName = fileName;
}

void Manage::addStudent(const Student& st)
{
	if (!(*this))
		throw "ERROR: file not found";

	int max;
	if (isExists(st._id))
		throw "the student already exists";

	_file->open(_fileName, ios::binary | ios::in | ios::out);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	if (st._id > max)
	{
		_file->seekp(0, ios::end);
		//fill the binary file with empty student:
		for (int i = 0; i < st._id - max - 1; ++i)
			_file->write((char*)&Student::emptyStudent, sizeof(Student));
		_file->write((char*)&st, sizeof(Student));

		_file->seekp(0);
		//update the higher student in the binary file
		_file->write((char*)&st._id, sizeof(int));
	}
	else
	{
		unsigned int g = st._id - 1;
		_file->seekp((g) * sizeof(Student) + sizeof(int));
		_file->write((char*)&st, sizeof(Student));
	}

	_file->close();
}

void Manage::delStudent(const int id)
{
	if (!(*this))
		throw "ERROR: file not found";

	if (isExists(id))
	{

		Student st;

		_file->open(_fileName, ios::binary | ios::out | ios::in);

		if (!_file)
			throw  "faild to open file";
		//activate the DTOR on the del student:
		unsigned int g = id - 1;
		_file->seekg((g) * sizeof(Student) + sizeof(int));
		_file->read((char*)&st, sizeof(Student));
		st.clear();
		//replace the del student with empty student
		_file->seekp(-((int)sizeof(Student)), ios::cur);
		_file->write((char*)&Student::emptyStudent, sizeof(Student));

		_file->close();
	}
}

void Manage::updateCurse(const int id, const int courseNum)
{
	if (!(*this))
		throw "ERROR: file not found";

	char* courses;
	if (isExists(id))
		throw "the student already exists";

	if (isRegistered(id, courseNum))
		throw "the student already Registered to this course";

	courses = getCourses(id);
	courses[courseNum] = 'Y';

	_file->open(_fileName, ios::binary | ios::out);

	if (!_file)
		throw  "faild to open file";

	_file->seekp(id * sizeof(Student) + sizeof(int) - sizeof(char*));
	_file->write((char*)&courses, sizeof(char*));

	_file->close();
}

bool Manage::isRegistered(const int id, const int courseNum)
{
	if (!(*this))
		throw "ERROR: file not found";

	return isExists(id) && getCourses(id)[courseNum] == 'Y';

}

void Manage::printStudent(const int id)
{
	if (!(*this))
		throw "ERROR: file not found";

	Student st;
	if (isExists(id))
	{

		_file->open(_fileName, ios::binary | ios::in);

		if (!_file)
			throw  "faild to open file";

		_file->seekg((id - 1) * (int)sizeof(Student) + sizeof(int));
		_file->read((char*)&st, sizeof(Student));

		cout << st;

		_file->close();
	}
}

void Manage::printRgisteredStudent()
{
	if (!(*this))
		throw "ERROR: file not found";

	int max;
	char* courses;
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";
	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i)
		if (strcmp(courses = getCourses(i + 1), "NNNNN"))
		{
			cout << j++ << "." << endl;
			printStudent(i + 1);

			courses = nullptr;
		}
}

void Manage::printCurse(const int courseNum)
{
	if (!(*this))
		throw "ERROR: file not found";

	int max;
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i)
		if (getCourses(i + 1)[courseNum] == 'Y')
		{
			cout << j++ << "." << endl;
			printStudent(i);
		}
}

void Manage::clean()
{
	int max;
	if (_file)
	{
		if (!(_file->is_open()))
			_file->open(_fileName, ios::binary | ios::in);
		_file->seekg(0);
		_file->read((char*)&max, sizeof(int));
		for (int i = 0; i < max; ++i)
			try { delStudent(i + 1); }
		catch (const char* msg) { cout << msg << endl; }
		_file->close();
	}
	delete _file;
}

void Manage::clear()
{
	_file->clear();
}

bool Manage::operator!() const
{
	return (!_file || _file->fail());
}

Manage Manage::operator+(Manage& manageFile)
{
	Student* st;
	int max1, max2, max;
	char* courses = new char[6];
	Manage mergeFile;
	

	if (!(*this) || !manageFile)
	{
		mergeFile.allocate("Empty.dat");
		return mergeFile;
	}

	string fName = _fileName;
	fName.replace(fName.find("."), fName.size() - fName.find("."), " & ");
	fName += manageFile._fileName;
	mergeFile.allocate(fName);

	_file->open(_fileName, ios::binary | ios::in);

	if (!(*this))
		throw  "faild to open file";

	manageFile._file->open(_fileName, ios::binary | ios::in);

	if (!manageFile)
		throw  "faild to open file";

	_file->read((char*)&max1, sizeof(int));

	manageFile._file->read((char*)&max2, sizeof(int));

	if (max1 > max2)
		max = max1;
	else
		max = max2;

	for (int i = 0; i < max; ++i)
	{
		st = new Student;
		if (isExists(i + 1) && manageFile.isExists(i + 1))
		{
			_file->open(_fileName, ios::binary | ios::in);
			_file->seekg((i * sizeof(Student)) + sizeof(int));
			_file->read((char*)st, sizeof(Student));

			strcpy(courses, st->_courses);
			for (int j = 0; j < 5; ++j)
				if (manageFile.isRegistered(i + 1, j))
					courses[j] = 'Y';


			mergeFile.addStudent(*(new Student((*st)._id, (const char*)(*st)._name, (const char*)(*st)._lastName, courses)));
		}
		else if (isExists(i + 1))
		{
			_file->open(_fileName, ios::binary | ios::in);
			_file->seekg((i) * sizeof(Student) + sizeof(int));
			_file->read((char*)st, sizeof(Student));


			mergeFile.addStudent(*(new Student((*st)._id, (const char*)(*st)._name, (const char*)(*st)._lastName, (const char*)(*st)._courses)));
		}
		else if (manageFile.isExists(i + 1))
		{
			manageFile._file->open(_fileName, ios::binary | ios::in);
			manageFile._file->seekg((i) * sizeof(Student) + sizeof(int));
			manageFile._file->read((char*)st, sizeof(Student));


			mergeFile.addStudent(*(new Student((*st)._id, (const char*)(*st)._name, (const char*)(*st)._lastName, (const char*)(*st)._courses)));
		}
	}
	st = nullptr;
	return mergeFile;
}

Manage& Manage::operator=(Manage&& manage)
{
	if (manage._file != _file)
	{
		if (_file != nullptr)
			this->clean();
		_file = manage._file;
		manage._file = nullptr;
	}
	_fileName = manage._fileName;

	return *this;
}


Manage::~Manage()
{
	clean();
}

Manage& operator<<(Manage& out, const Student& st)
{
	out.addStudent(st);
	return out;
}
