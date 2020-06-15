#include "Management.h"
#pragma warning(disable:4996)
using namespace std;

bool Manage::isExists(int id) const
{
	int max, idF;
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	if (id > max)
		return false;

	_file->seekg((id - 1) * sizeof(Student) + sizeof(int));
	_file->read((char*)&idF, sizeof(int));

	if (idF != id && idF != 0)
		throw "ERROR:the id in the file is illegal";
	return idF;
}

char* Manage::getCourses(int id) const
{
	char* courses = new char[6];
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->seekg(id * sizeof(Student) - sizeof(char*));
	_file->read((char*)&courses, sizeof(char*));

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
	fstream newFile(fName, ios::binary | ios::out);
	int capacity = 10;

	if (!newFile)
		throw "faild to open file";

	newFile.write((char*)&capacity, sizeof(int));
	for (int i = 0; i < 10; ++i)
		newFile.write((char*)&Student::emptyStudent, sizeof(Student));
	newFile.close();
}

void Manage::allocate(std::string fileName)
{
	if (_file != nullptr)
		_file = new fstream;
	OpenF(fileName);
	_fileName = fileName;
}

void Manage::addStudent(const Student& st)
{
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
		_file->seekp(st._id - 1 * sizeof(Student) + sizeof(int));
		_file->write((char*)&st, sizeof(Student));
	}

	_file->close();
}

void Manage::delStudent(const int id)
{

	if (isExists(id))
		throw "the student already exists";

	_file->open(_fileName, ios::binary | ios::out);

	if (!_file)
		throw  "faild to open file";

	_file->seekp((id - 1) * sizeof(Student) + sizeof(int));
	_file->write((char*)&Student::emptyStudent, sizeof(Student));

	_file->close();
}

void Manage::updateCurse(const int id, const int courseNum)
{
	char* courses;
	if (isExists(id))
		throw "the student already exists";

	if (isRegistered(id, courseNum))
		throw "the student already Registered to this course";

	courses = getCourses(id);
	courses[courseNum] = 'Y';
	_file->open(_fileName, ios::binary | ios::out);
	_file->seekp(id * sizeof(Student) + sizeof(int) - sizeof(char*));
	_file->write((char*)&courses, sizeof(char*));

	delete[] courses;
	_file->close();
}

bool Manage::isRegistered(const int id, const int courseNum)
{
	return isExists(id) && getCourses(id)[courseNum] == 'Y';
}

void Manage::printStudent(const int id)
{
	Student st;
	if (isExists(id))
		throw "the student already exists";

	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->seekg((id - 1) * sizeof(Student));
	_file->read((char*)&st, sizeof(Student));

	cout << st;

	_file->close();
}

void Manage::printRgisteredStudent()
{
	int max;
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 0; i < max; ++i)
		if (strcmp(getCourses(i), "NNNNN"))
		{
			cout << j++ << "." << endl;
			printStudent(i);
		}
}

void Manage::printCurse(const int courseNum)
{
	int max;
	_file->open(_fileName, ios::binary | ios::in);

	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max, sizeof(int));
	_file->close();

	for (int i = 0, j = 0; i < max; ++i)
		if (getCourses(i)[courseNum] == 'Y')
		{
			cout << j++ << "." << endl;
			printStudent(i);
		}
}

void Manage::clear()
{
	if (_file->is_open())
		_file->close();
	delete _file;
}

bool Manage::operator!() const
{
	return (!_file);
}

Manage Manage::operator+(Manage& manageFile)
{
	Student st;
	char* coursesMerge;
	int max1, max2, max;
	Manage mergeFile;
	string fName = _fileName;

	fName.replace(fName.find("."), fName.size() - fName.find("."), " & ");
	fName += manageFile._fileName;

	mergeFile.allocate(fName);

	if (!(*this) || !manageFile)
		return mergeFile;

	_file->open(_fileName, ios::binary | ios::in);
	
	if (!_file)
		throw  "faild to open file";

	manageFile._file->open(_fileName, ios::binary | ios::in);
	
	if (!_file)
		throw  "faild to open file";

	_file->read((char*)&max1, sizeof(int));

	mergeFile._file->read((char*)&max2, sizeof(int));

	if (max1 > max2)
		max = max2;
	else
		max = max1;

	for (int i = 0; i < max; ++i)
		if (isExists(i) && manageFile.isExists(i))
		{
			_file->seekg((i - 1) * sizeof(Student));
			_file->read((char*)&st, sizeof(Student));

			for (int j = 0; j < 5; ++j)
				if (manageFile.isRegistered(i, j))
					st._courses[j] = 'Y';

			mergeFile.addStudent(st);
		}
		else if(isExists(i))
		{
			_file->seekg((i - 1) * sizeof(Student));
			_file->read((char*)&st, sizeof(Student));

			mergeFile.addStudent(st);
		}
		else if (manageFile.isExists(i))
		{
			manageFile._file->seekg((i - 1) * sizeof(Student));
			manageFile._file->read((char*)&st, sizeof(Student));

			mergeFile.addStudent(st);
		}

	return mergeFile;
}

Manage& Manage::operator=(Manage&& manage)
{
	if (manage._file != _file)
	{
		if (_file != nullptr)
			_file->clear();
		_file = manage._file;
		manage._file = nullptr;
	}
	_fileName = manage._fileName;
	
	return *this;
}

void Manage::operator<<(const Student& st)
{
	addStudent(st);
}

Manage::~Manage()
{
	clear();
}

