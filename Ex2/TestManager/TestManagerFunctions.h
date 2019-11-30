#pragma once
#ifndef __TESTMANAGERFUNCTIONS_H__
#define __TESTMANAGERFUNCTIONS_H___

// Includes --------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "HardCodedData.h"
#include "ProcessFunctions.h"

// Function Declarations -------------------------------------------------------


/*
* getIdsFromFile extract all ids from the file studentIds.txt into an array of string.
* Input Arguments:
*	path	- Full path to the main folder containing studentIds.txt
*	ids		- array of string to be filled by the function with the student id's.
* Return:
*	the number of students in the list. return -1 if failed.
*/

int GetIdsFromFile(char *path, char **ids);

/*
* getStudentsFinalGrades gets all students final grades by calling the TestGrade process.
* Input Arguments:
*	path					- Full path to the main folder containing studentIds.txt
*	ids						- array of string containing students ids.
*	number_of_students		- the number of students in ids array.
*	grades					- array of integers to be filled with the students grades.
* Return:
*	 return -1 if failed.
*/

int GetStudentsFinalGrades(char *path, char **ids,int number_of_students, int **grades);


/*
* WriteFinalGradesFile gets all students final grades by calling the TestGrade process.
* Input Arguments:
*	path					- Full path to the main folder containing studentIds.txt
*	ids						- array of string containing students ids.
*	number_of_students		- the number of students in ids array.
*	grades					- array of integers to be filled with the students grades.
* Return:
*	 return -1 if failed.
*/


int WriteFinalGradesFile(char **ids, int number_of_students, int **grades);

#endif // __TESTMANAGERFUNCTIONS_H___