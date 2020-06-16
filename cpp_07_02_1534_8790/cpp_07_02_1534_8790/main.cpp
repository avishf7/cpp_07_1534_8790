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

int main(void) {
	char fileChoice;
	int sNum, cNum, chosen;
	string fileName;
	Student* st;
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

			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 'A':
				try { fileA.allocate(fileName); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.allocate(fileName); }
				catch (const char* msg) { cout << msg; }
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case ADD://add to the file
			bool isSuccess;
			st = new Student();
			do
			{
				isSuccess = true;
				try { cin >> *st; }
				catch (const char* msg)
				{
					cout << endl << msg << endl;
					isSuccess = false;
					cin.clear();
				}
			} while (!isSuccess);
			cout << "\nEnter on which file to execute(A or B): ";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 'A':
				try { fileA << *st; }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB << *st; }
				catch (const char* msg) { cout << msg; }
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
				try { fileA.delStudent(sNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.delStudent(sNum); }
				catch (const char* msg) { cout << msg; }
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
				try { fileA.updateCurse(sNum, cNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.updateCurse(sNum, cNum); }
				catch (const char* msg) { cout << msg; }
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

			switch (fileChoice)
			{
			case 'A':
				try {
					cout << "The student is"
						<< (fileA.isRegistered(sNum, cNum) ? " " : " not ")
						<< "taking the course\n";
				}
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try {
					cout << "The student is"
						<< (fileB.isRegistered(sNum, cNum) ? " " : " not ")
						<< "taking the course\n";
				}
				catch (const char* msg) { cout << msg; }
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		case ADD_TWO_ELEMENTS://put the sum of File A and File B in File C
			try { fileC = fileA + fileB; }
			catch (const char* msg) { cout << msg; }
			break;
		case PRINT://print the details of a specific student in specific file
			cout << "enter number of student to print:\n";
			cin >> sNum;

			cout << "\nEnter on which file to execute(A or B or C): ";
			cin >> fileChoice;

			switch (fileChoice)
			{
			case 'A':
				try { fileA.printStudent(sNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.printStudent(sNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'C':
				try { fileC.printStudent(sNum); }
				catch (const char* msg) { cout << msg; }
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
				try { fileA.printRgisteredStudent(); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.printRgisteredStudent(); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'C':
				try { fileC.printRgisteredStudent(); }
				catch (const char* msg) { cout << msg; }
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
				try { fileA.printCurse(cNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'B':
				try { fileB.printCurse(cNum); }
				catch (const char* msg) { cout << msg; }
				break;
			case 'C':
				try { fileC.printCurse(cNum); }
				catch (const char* msg) { cout << msg; }
				break;
			default:
				cout << "ERROR: invalid choice\n";
				break;
			}
			break;
		default:
			cout << "ERROR: invalid choice\n";
		}
		if (!(!fileA))
			fileA.clear();
		if (!(!fileB))
			fileB.clear();
		if (!(!fileC))
			fileC.clear();
	} while (chosen != EXIT_MENU);

	return 0;
}
