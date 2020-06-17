/*
File: Student.cpp
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include "Student.h"
#pragma warning(disable:4996)
using namespace std;

const Student Student::emptyStudent;

std::istream& operator>>(std::istream& in, Student& st)
{
	cout << "Enter student details:" << endl;
	cout << "\nid(1 - 999) - ";
	in >> st._id;

	if (st._id < 1 || st._id > 999)
		throw "ERROR: id out of range\n";

	cout << "first name - ";
	in >> setw(21) >> st._name;

	cout << "last name - ";
	in>> setw(21) >> st._lastName;

	cout << "curses(Y or N):" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << "[" << i + 1 << "] - ";
		in >> st._courses[i];
		if (st._courses[i] != 'Y' && st._courses[i] != 'N')
			throw "ERROR: invalid choice\n";
	}

	return in;
}

ostream& operator<<(ostream& out, const Student& st)
{
	out << "id: " << st._id << endl
		<< "first name: " << st._name << endl
		<< "last name: " << st._lastName << endl
		<< "curses:" << endl;
	for (int i = 0; i < 5; ++i)
		out << "[" << i + 1 << "] - " << st._courses[i] << endl;

	return out;
}

Student::Student(int id, const char name[], const char lastName[]) :_id(id)
{
	//puts in all curses the character 'N'
	strcpy(_courses, "NNNNN");

	if (strlen(name) > 21 || strlen(lastName) > 21)
		throw "the name is out of range";

	strcpy(_name, name);
	strcpy(_lastName, lastName);
}
