/*
File: Student.h
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>
#include <iomanip>

struct Student
{
	int _id;
	char* _name;
	char* _lastName;
	char* _courses;
	static const Student emptyStudent;

	void clear();

	friend std::ostream& operator << (std::ostream& out, const Student& st);
	friend std::istream& operator >> (std::istream& in, Student& st);
	Student(int id = 0, const char* name = " ", const char* lastName = " ", const char* courses = "NNNNN");
	~Student();
};

std::istream& operator >> (std::istream& in, Student& st);
std::ostream& operator << (std::ostream& out, const Student& st);

#endif // !STUDENT_H

