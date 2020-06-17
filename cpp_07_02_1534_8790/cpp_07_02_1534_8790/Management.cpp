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
	success = false;
	int max, idF;
	if (_file->is_open())
		_file->seekg(0);
	else
		_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return false;

	_file->read((char*)&max, sizeof(int));
	if (id > max)
	{
		_file->close();
		success = _file->good();
		return  false;
	}

	_file->seekg((id - 1) * sizeof(Student) + sizeof(int));
	_file->read((char*)&idF, sizeof(int));

	_file->close();

	if (idF != id && idF != 0)
		throw "ERROR:the id in the file is illegal";



	return (success = _file->good()) && idF;
}

const char* Manage::getCourses(int id)
{
	success = false;
	char* courses = new char[6];
	if (!(_file->is_open()))
		_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return nullptr;

	_file->seekg(sizeof(int) + (id - 1) * sizeof(Student) + (sizeof(int) + 2 * sizeof(char[21])));
	_file->read((char*)courses, sizeof(char[6]));

	_file->close();

	success = _file->good();
	return courses;
}

Manage::Manage(string fileName) : _file(new fstream), _fileName(nullptr)
{
	_file->open(fileName, ios::binary, ios::in);
	if (success = _file->good())
		return;
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
	_file->open(fileName, ios::binary | ios::in);

	if (!(success = _file))
	{
		_file->close();
		return;
	}

	_file->close();
	_fileName = fileName;
}

void Manage::addStudent(const Student& st)
{
	if (!errorCheck())
		return;

	if (isExists(st._id))
	{
		success = false;
		return;
	}

	if (!(*this))
		return;

	success = false;
	int max;

	//because isExists close the file i need to open again
	_file->open(_fileName, ios::binary | ios::in | ios::out);

	if (!_file)
		return;

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
	success = _file->good();
}

void Manage::delStudent(const int id)
{
	if (!errorCheck())
		return;

	//check if the student exists
	if (!isExists(id))
	{
		success = false;
		return;
	}

	if (!(*this))
		return;

	success = false;
	Student st;
	//because isExists close the file i need to open again
	_file->open(_fileName, ios::binary | ios::out | ios::in);

	if (!_file)
		return;

	//replace the del student with empty student
	_file->seekp((id - 1) * sizeof(Student) + sizeof(int));
	_file->write((char*)&Student::emptyStudent, sizeof(Student));

	_file->close();
	success = _file->good();
}

void Manage::updateCurse(const int id, const int courseNum)
{
	if (!errorCheck())
		return;

	//check if the student exists
	if (!isExists(id))
	{
		success = false;
		return;
	}

	if (isRegistered(id, courseNum - 1))
	{
		success = false;
		return;
	 }

	if (!(*this))
		return;
	char courses[6];
	//delCourses is parameter to delete the pointer that get form getCourses()
	const char* delCourses = getCourses(id);

	if (!(*this))
	{
		delete[] delCourses;
		return;
	}

	success = false;
	strcpy(courses, delCourses);
	courses[courseNum - 1] = 'Y';

	_file->open(_fileName, ios::binary | ios::out | ios::in);

	if (!_file)
		return;

	_file->seekp((id - 1) * sizeof(Student) + sizeof(int) + (sizeof(int) + 2 * sizeof(char[21])));
	_file->write((char*)&courses, sizeof(char[6]));

	_file->close();
	success = _file->good();
}

bool Manage::isRegistered(const int id, const int courseNum)
{
	if (!errorCheck())
		return false;

	bool isTrue;
	//Courses is parameter to delete the pointer that get form getCourses()
	const char* Courses = getCourses(id);

	isTrue = isExists(id) && Courses[courseNum] == 'Y';

	delete[] Courses;
	return isTrue;
}

void Manage::printStudent(const int id)
{
	if (!errorCheck())
		return;

	if (!isExists(id))
	{
		success = false;
		return;
	}

	if (!(*this))
		return;

	success = false;
	Student st;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return;

	_file->seekg((id - 1) * (int)sizeof(Student) + sizeof(int));
	_file->read((char*)&st, sizeof(Student));

	cout << st;

	_file->close();
	success = _file->good();
}

void Manage::printRgisteredStudent()
{
	if (!errorCheck())
		return;

	success = false;
	int max;
	//courses is parameter to delete the pointer that get form getCourses()
	const char* courses;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return;

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i)
		if (isExists(i + 1))
		{

			if (!(*this))
				return;

			courses = getCourses(i + 1);

			if (!(*this))
				return;
			if (strcmp(courses, "NNNNN"))
			{
				cout << j++ << "." << endl;
				printStudent(i + 1);

				if (!(*this))
					return;
			}

			delete[] courses;
		}
}

void Manage::printCurse(const int courseNum)
{
	if (!errorCheck())
		return;

	success = false;
	//courses is parameter to delete the pointer that get form getCourses()
	const char* courses;
	int max;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return;

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 1; i < max; ++i)
		if (isExists(i + 1))
		{

			if (!(*this))
				return;
			courses = getCourses(i + 1);

			if (!(*this))
				return;
			if (courses[courseNum - 1] == 'Y')
			{
				cout << j++ << "." << endl;
				printStudent(i + 1);

				if (!(*this))
					return;
			}
			delete[] courses;
		}
}

bool Manage::errorCheck()
{
	success = false;
	//check if there is a file name in object
	if (_fileName == "")
		return success;

	//check if the file exists:
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		return success;

	_file->close();

	return (success = true);
}

void Manage::clear()
{
	if (_file)
		_file->clear();
}

bool Manage::operator!() const
{
	return !success;;
}

Manage Manage::operator+(Manage& manageFile)
{
	Student st;
	int max, tempMax;
	Manage mergeFile;

	if (!errorCheck() || !(manageFile.errorCheck()))
		return mergeFile;

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
	{
		_file->close();
		return mergeFile;
	}

	manageFile._file->open(manageFile._fileName, ios::binary | ios::in);

	if (!manageFile._file)
	{
		_file->close();
		return mergeFile;
	}

	string fName = _fileName;
	fName.replace(fName.find("."), fName.size() - fName.find("."), " & ");
	fName += manageFile._fileName;
	openF(fName);
	mergeFile.allocate(fName);

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
	manageFile._file->close();
	_file->close();
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

	if (_file && _file->is_open())
		_file->close();
	delete _file;
}

Manage& operator<<(Manage& out, const Student& st)
{
	out.addStudent(st);
	return out;
}
