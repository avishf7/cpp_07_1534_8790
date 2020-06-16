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
		throw  "ERROR:faild to open file";

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

const char* Manage::getCourses(int id)
{
	char courses[26];
	if (!(_file->is_open()))
		_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "ERROR:faild to open file";

	_file->seekg(sizeof(int) + (id - 1) * sizeof(Student) + (sizeof(int) + 2 * sizeof(char[21])));
	_file->read((char*)&courses, sizeof(char[6]));

	_file->close();

	return courses;
}

Manage::Manage(string fileName) : _file(new fstream), _fileName(nullptr)
{
	_file->open(fileName, ios::binary, ios::in);
	if (!_file)
		throw"ERROR:file not exists";
	_fileName = fileName;
}

Manage::Manage(Manage&& manage) : _file(manage._file), _fileName(manage._fileName)
{
	// Avoid temp object DTOR removing the dynamic data which is now used in our object
	manage._file = nullptr;
}



void Manage::allocate(std::string fileName)
{

	if (!_file)
		_file = new fstream;
	_file->open(fileName, ios::binary, ios::in);
	if (!_file)
		throw"ERROR: file not exists";
	_fileName = fileName;
}

void Manage::addStudent(const Student& st)
{
	errorCheck();

	int max;

	if (isExists(st._id))
		throw "the student already exists";

	//because isExists close the file i need to open again
	_file->open(_fileName, ios::binary | ios::in);

	_file->read((char*)&max, sizeof(int));
	if (st._id > max)
	{
		_file->seekp(0, ios::end);
		if (_file->eof())
			cout << "WHYYYYYY!!!!";
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
	errorCheck();

	//check if the student exists
	if (!isExists(id))
		throw "ERROR:student not found";

	Student st;
	//because isExists close the file i need to open again
	_file->open(_fileName, ios::binary | ios::out);

	//replace the del student with empty student
	_file->seekp((id - 1) * sizeof(Student) + sizeof(int));
	_file->write((char*)&Student::emptyStudent, sizeof(Student));

	_file->close();

}

void Manage::updateCurse(const int id, const int courseNum)
{
	errorCheck();

	//delCourses is parameter to delete the pointer that get form getCourses()
	const char* delCourses = getCourses(id);
	char courses[6];

	if (!isExists(id))
		throw "ERROR:student not found";

	if (isRegistered(id, courseNum))
		throw "the student already Registered to this course";

	strcpy(courses, delCourses);
	courses[courseNum] = 'Y';

	_file->open(_fileName, ios::binary | ios::out);

	if (!_file)
		throw  "faild to open file";

	_file->seekp((id - 1) * sizeof(Student) + sizeof(int) + (sizeof(int) + 2 * sizeof(char[21])));
	_file->write((char*)&courses, sizeof(char[6]));

	_file->close();
}

bool Manage::isRegistered(const int id, const int courseNum)
{
	errorCheck();

	return isExists(id) && getCourses(id)[courseNum] == 'Y';

}

void Manage::printStudent(const int id)
{
	errorCheck();

	if (!isExists(id))
		throw "ERROR:student not found";


	Student st;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->seekg((id - 1) * (int)sizeof(Student) + sizeof(int));
	_file->read((char*)&st, sizeof(Student));

	cout << st;

	_file->close();
}

void Manage::printRgisteredStudent()
{
	errorCheck();

	int max;
	//courses is parameter to delete the pointer that get form getCourses()
	const char* courses;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i , delete[] courses)
		if (strcmp(courses = getCourses(i + 1), "NNNNN"))
		{
			cout << j++ << "." << endl;
			printStudent(i + 1);
		}
}

void Manage::printCurse(const int courseNum)
{
	errorCheck();

	//courses is parameter to delete the pointer that get form getCourses()
	const char* courses;
	int max;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i , delete[] courses)
		if (((courses = getCourses(i + 1))[courseNum]) == 'Y')
		{
			cout << j++ << "." << endl;
			printStudent(i);
		}
}

void Manage::errorCheck()
{
	//check if there is a file name in object
	if (_fileName == "")
		throw "ERROR:there is no file name";

	//check if the file exists:
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "ERROR:file not exists";
}

bool Manage::operator!() const
{
	return _file->fail();
}

Manage Manage::operator+(Manage& manageFile)
{
	Student st;
	int max,tempMax;
	Manage mergeFile;


	if ((*this)._fileName == "" || manageFile._fileName == "")
	{
		openF("Empty.dat");
		mergeFile.allocate("Empty.dat");
		return mergeFile;
	}

	string fName = _fileName;
	fName.replace(fName.find("."), fName.size() - fName.find("."), " & ");
	fName += manageFile._fileName;
	openF(fName);
	mergeFile.allocate(fName);

	_file->open(_fileName, ios::binary | ios::in);

	if (!(*this))
		return mergeFile;

	manageFile._file->open(_fileName, ios::binary | ios::in);

	if (!manageFile)
	{
		_file->close;
		return mergeFile;
	}

	_file->read((char*)&max, sizeof(int));

	manageFile._file->read((char*)&tempMax, sizeof(int));

	if (tempMax > max)
		max = tempMax;

	for (int i = 0; i < max; ++i)
	{
		if (isExists(i + 1) && manageFile.isExists(i + 1))
		{
			_file->open(_fileName, ios::binary | ios::in);
			_file->seekg((i * sizeof(Student)) + sizeof(int));
			_file->read((char*)&st, sizeof(Student));

			for (int j = 0; j < 5; ++j)
				if (manageFile.isRegistered(i + 1, j))
					st._courses[j] = 'Y';


			mergeFile.addStudent(st);
		}
		else if (isExists(i + 1))
		{
			_file->open(_fileName, ios::binary | ios::in);
			_file->seekg((i) * sizeof(Student) + sizeof(int));
			_file->read((char*)&st, sizeof(Student));


			mergeFile.addStudent(st);
		}
		else if (manageFile.isExists(i + 1))
		{
			manageFile._file->open(_fileName, ios::binary | ios::in);
			manageFile._file->seekg((i) * sizeof(Student) + sizeof(int));
			manageFile._file->read((char*)&st, sizeof(Student));


			mergeFile.addStudent(st);
		}
	}
	return mergeFile;
}

Manage& Manage::operator=(Manage&& manage)
{
	if (manage._file != _file)
	{
		if (_file != nullptr)
			delete _file;
		_file = manage._file;
		manage._file = nullptr;
	}
	_fileName = manage._fileName;

	return *this;
}


Manage::~Manage()
{
	if (_file->is_open())
		_file->close();
	delete _file;
}

Manage& operator<<(Manage& out, const Student& st)
{
	out.addStudent(st);
	return out;
}
