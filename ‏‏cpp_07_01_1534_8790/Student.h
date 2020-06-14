#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

struct Student
{
	int _id;
	char* _name;
	char* _lastName;
	char* _curses;
	static const Student emptyStudent;

	Student(int id = 0, const char* name = "", const char* lastName = "");
	~Student();
};


#endif // !STUDENT_H

