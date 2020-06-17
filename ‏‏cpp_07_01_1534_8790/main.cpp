/*
File: main.cpp
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#include "main.h"
using namespace std;

int main()
{
	string fileName;
	char* f;

	cout << "Enter the file name:" << endl;
	cin >> fileName;

	openF(fileName);

	return 0;
}
void openF(string fName)
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
