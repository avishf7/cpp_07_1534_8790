#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

struct Student
{
	int _id;
	char _name[21];
	char _lastName[21];
	char _courses[6];
	static const Student emptyStudent;

	friend std::ostream& operator << (std::ostream& out,const Student& st);
	Student(int id = 0, const char name[] = "", const char lastName[] = "");
};

std::ostream& operator << (std::ostream& out,const Student& st);

#endif // !STUDENT_H

