/*
File: main.cpp
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#include "main.h"
using namespace std;

int main() {
	char fileChoice;
	int sNum, cNum, chosen;
	bool isSuccess;
	string fileName;
	Student st;
	Manage fileA, fileB, fileC;

	// Everything happens inside of this do-while loop, until the user
	//     has decided to exit (or an error occurs).
	do {
		cout << endl << "Menu options:" << endl << endl;

		const int menuIndent = 10;

		// The user will see:
		//
		//           0 -- exit
		//           1 -- add Student to a file(A OR B).
		//           2 -- delete student from file(A OR B).
		//           etc.
		//
		// The casts are for doing the "++" as an int type since
		// they are not allowed as a MenuOption type.
		for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION;
			chosen = (MenuOption)((int)chosen + 1)) {
			cout << setw(menuIndent) << " " << chosen << " -- ";
			cout << menuOptionStrings[chosen] << endl;
		}
		cout << endl;


		cout << "Please choose a menu option: ";
		cin >> chosen;
		// After the user has input an int, it is cast to a
		//   MenuOption variable.



		cout << endl;
		switch (chosen)
		{
		case EXIT_MENU:
			break;
		case CREATE:
			cout << "Enter file name: ";
			cin >> fileName;
			
			openF(fileName);

			cout << "\nEnter in which element allocate the new file:(A or B): ";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 'A':
				fileA.allocate(fileName);

				if (!fileA)
					cout << "Failad to allocate." << endl;
				break;
			case 'B':
				fileB.allocate(fileName);

				if (!fileB)
					cout << "Failad to allocate." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case ADD://add to the file
			do
			{
				isSuccess = true;
				try { cin >> st; }
				catch (const char* msg)
				{
					cout << endl << msg << endl;
					isSuccess = false;
					cin.clear();
					char tempStr[1000000];
					cin.getline(tempStr, 1000000);
				}
			} while (!isSuccess);
			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 'A':
				fileA << st;

				if (!fileA)
					cout << "Failad to add the student." << endl;
				break;
			case 'B':
				fileB << st;

				if (!fileB)
					cout << "Failad to add the student." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case DEL://delete from file
			cout << "enter number of student to delete:\n";
			cin >> sNum;

			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				fileA.delStudent(sNum);

				if (!fileA)
					cout << "Failad to delete the student." << endl;
				break;
			case 'B':
				fileB.delStudent(sNum);

				if (!fileB)
					cout << "Failad to delete the student." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case UPDATE://update the list of courses of a student
			cout << "enter number of student:\n";
			cin >> sNum;
			cout << "enter number of course:\n";
			cin >> cNum;

			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				fileA.updateCurse(sNum, cNum);

				if (!fileA)
					cout << "Failad to uptate the student course." << endl;
				break;
			case 'B':
				fileB.updateCurse(sNum, cNum);

				if (!fileB)
					cout << "Failad to uptate the student course." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case REGISTERED://check registered to a specific course
			cout << "enter number of student:\n";
			cin >> sNum;
			cout << "enter number of course:\n";
			cin >> cNum;

			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;

			bool isTrue;
			switch (fileChoice)
			{
			case 'A':
				isTrue = fileA.isRegistered(sNum, cNum);

				if (!fileA)
					cout << "Failad to check." << endl;
				else
					cout << endl << "The student is"
					<< (isTrue ? " " : " not ")
					<< "taking the course\n";
				break;
			case 'B':
				isTrue = fileB.isRegistered(sNum, cNum);

				if (!fileB)
					cout << "Failad to check." << endl;
				else
					cout << "The student is"
					<< (isTrue ? " " : " not ")
					<< "taking the course\n";
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case ADD_TWO_ELEMENTS://put the sum of File A and File B in File C
			fileC = fileA + fileB;
			if (!fileC)
			{
				cout << "Failed to merge the files";
				fileA.clear();
				fileB.clear();
			}
			else
				cout << "name of C(A + B) - " << fileC._fileName;
			break;
		case PRINT://print the details of a specific student in specific file
			cout << "enter number of student to print:\n";
			cin >> sNum;

			cout << "\nEnter on which file to execute(A or B or C): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				fileA.printStudent(sNum);

				if (!fileA)
					cout << "Failad to print." << endl;
				break;
			case 'B':
				fileB.printStudent(sNum);

				if (!fileB)
					cout << "Failad to print." << endl;
				break;
			case 'C':
				fileC.printStudent(sNum);

				if (!fileB)
					cout << "Failad to print." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case PRINT_REGISTERED://print the details of all students that are registered in specific file
			cout << "\nEnter on which file to execute(A or B or C): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				fileA.printRgisteredStudent();

				if (!fileA)
					cout << "Failad to print." << endl;
				break;
			case 'B':
				fileB.printRgisteredStudent();

				if (!fileB)
					cout << "Failad to print." << endl;
				break;
			case 'C':
				fileC.printRgisteredStudent();

				if (!fileC)
					cout << "Failad to print." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case PRINT_COURSE://print the details of all the students that are taking a specific course in specific file
			cout << "enter number of course:\n";
			cin >> cNum;

			cout << "\nEnter on which file to execute(A or B or C): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				fileA.printCurse(cNum);

				if (!fileA)
					cout << "Failad to print." << endl;
				break;
			case 'B':
				fileB.printCurse(cNum);

				if (!fileB)
					cout << "Failad to print." << endl;
				break;
			case 'C':
				fileC.printCurse(cNum);

				if (!fileC)
					cout << "Failad to print." << endl;
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		default:
			cout << "ERROR: invalid choice\n";
			cin.clear();
			cin.get();
		}
	} while (chosen != EXIT_MENU);

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
