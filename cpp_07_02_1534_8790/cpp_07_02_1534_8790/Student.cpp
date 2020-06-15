#include "Student.h"
#pragma warning(disable:4996)
using namespace std;

const Student Student::emptyStudent;

Student::Student(int id, const char* name, const char* lastName) :_id(0), _name(new char[21]), _lastName(new char[21]), _courses(new char[6])
{
	//puts in all curses the character 'N'
	strcpy(_courses, "NNNNN");

	if (strlen(name) > 21 || strlen(lastName) > 21)
		throw "the name is out of range";

	strcpy(_name, name);
	strcpy(_lastName, lastName);

}

Student::~Student()
{
	delete[] _name;
	delete[] _lastName;
	delete[] _courses;
	_name = _lastName = _courses = nullptr;
}

ostream& operator<<(ostream& out, const Student& st)
{
	out << "id: " << st._id << endl
		<< "first name: " << st._name << endl
		<< "last name: " << st._lastName << endl
		<< "curses:" << endl;
	for (int i = 0; i < 5; ++i)
		out << "[" << i << "] - " << st._courses[i] << endl;

	return out;
}
