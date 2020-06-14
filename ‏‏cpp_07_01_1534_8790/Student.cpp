#include "Student.h"
#pragma warning(disable:4996)

const Student Student::emptyStudent;

Student::Student(int id, const char* name, const char* lastName):_id(0),_name(new char[21]),_lastName(new char[21]),_curses(new char[6])
{
	//puts in all curses the character 'N'
	strcpy(_curses, "NNNNN");

	if (strlen(name) > 21 || strlen(lastName) > 21)
		throw "the name is out of range";

	strcpy(_name, name);
	strcpy(_lastName, lastName);

}

Student::~Student()
{
	delete[] _name;
	delete[] _lastName;
	delete[] _curses;
	_name = _lastName = _curses = nullptr;
}
