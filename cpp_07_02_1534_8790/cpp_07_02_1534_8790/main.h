/*
File: main.h
Description:
Course: 150018 C++ Workshop, Exercise 7, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Management.h"
#include "Student.h"


// These are all of the main menu options.  Note that the numbers:
// 0, 1, 2, etc., show up /nowhere/ in the code, even though the
// user will see them on the screen, and will input them for
// choosing a menu option.
// Add your menu options according the the exercise requirements
enum MenuOption {
	EXIT_MENU,
	CREATE,
	ADD,
	DEL,
	UPDATE,
	REGISTERED,
	ADD_TWO_ELEMENTS,
	PRINT,
	PRINT_REGISTERED,
	PRINT_COURSE,
	// a neat trick for for-loop initial and final values
	FIRST_MENU_OPTION = EXIT_MENU,
	LAST_MENU_OPTION = PRINT_COURSE	
};

// These strings will be seen by the user, on the main menu.  They
// must be kept consistent with the operations of menu_option
// above.
const char* const menuOptionStrings[] = {
	"exit the program",
	"create file(to A or B).",
	"add Student to a file(A OR B).",
	"delete student from file(A OR B).",
	"update the student courses in spcific file(A or B).",
	"Check if student is registered to spcific course in spcific file(A or B).",
	"put the sum of File A and File B in File C.",
	"print the details of a specific student in specific file(A or B or C).",
	"print the details of all students that are registered in specific file(A or B or C).",
	"print the details of all the students that are taking a specific course in specific file(A or B or C)."
};


void openF(std::string fName);

#endif // !MAIN_H

