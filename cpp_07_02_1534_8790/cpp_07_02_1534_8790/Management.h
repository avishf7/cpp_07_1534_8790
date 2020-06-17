/*
File: management.h
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef _MANAGEMENT
#define _MANAGEMENT

#include <iostream>
#include <string>
#include "Student.h"
#include "fstream"



class Manage {

public:
	std::string _fileName;
	std::fstream* _file;
	bool success = true;;

	Manage():_file(nullptr){}
	Manage(std::string fileName);

	Manage(const Manage&) = delete;
	Manage(Manage&& manage);

	void allocate(const std::string fileName);
	void addStudent(const Student& st);
	void delStudent(const int id);
	void updateCurse(const int id,const int courseNum);
	bool isRegistered(const int id,const int courseNum);
	void printStudent(const int id);
	void printRgisteredStudent();
	void printCurse(const int courseNum);
	bool errorCheck();
	void clear();

	bool operator !() const;
	Manage operator +(Manage& manageFile);
	Manage& operator = (const Manage& other) = delete;
	Manage& operator = (Manage&& manage);
	friend Manage& operator << (Manage& out, const Student& st);
	~Manage();

private:
	bool isExists(const int id);
	const char* getCourses(const int id);

};

Manage& operator << (Manage& out, const Student& st);

extern void openF(std::string fName);
#endif // !_MANAGEMENT

