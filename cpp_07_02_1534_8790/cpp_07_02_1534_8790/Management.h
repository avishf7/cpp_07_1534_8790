#ifndef _MANAGEMENT
#define _MANAGEMENT

#include <iostream>
#include <string>
#include "Student.h"
#include "fstream"

class Manage {
private:
	std::string _fileName;
	std::fstream* _file;

	bool isExists(const int id) const;
	char* getCourses(const int id) const;
public:
	Manage():_file(nullptr){}
	Manage(std::string fileName);

	Manage(const Manage&) = delete;
	Manage(Manage&& manage);

	void OpenF(const std::string fName);
	void allocate(const std::string fileName);
	void addStudent(const Student& st);
	void delStudent(const int id);
	void updateCurse(const int id,const int courseNum);
	bool isRegistered(const int id,const int courseNum);
	void printStudent(const int id);
	void printRgisteredStudent();
	void printCurse(const int courseNum);
	void clear();


	bool operator !() const;
	Manage operator +(Manage& manageFile);
	Manage& operator = (const Manage& other) = delete;
	Manage& operator = (Manage&& manage);
	void operator << (const Student& st);
	~Manage();

};

std::ofstream& operator << (std::ofstream& out, const Student& st);
#endif // !_MANAGEMENT

