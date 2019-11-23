#pragma once
#ifndef __TESTGRADEFUNCTIONS_H__
#define __TESTGRADEFUNCTIONS_H___

// Includes --------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <limits.h>
#include <string.h>
#include "HardCodedData.h"
#include "ThreadFunctions.h"

// Function Declarations -------------------------------------------------------

/*
* create threads to all grades possible for student, and fill the grade array.
* Input Arguments:
*	folder_path: string name of the full/relative folder path of the specific student.
*	grades_array: empty array of grades of the student. the function will fill the 
*	grades_array with the correct grades from the file.
* Return:
*	returns -1 if there was an error. 
*/
int ReadAllGrades(char *folder_path, int* grades_array);

/*
* calculate the final grade.
* Input Arguments:
*	grades_array: the array of grades of the student.
* Return:
*	returns the final grade.
*/
int CalculateFinalGrade(int* grades_array);

/*
* Print the final grade to the txt file of the student
* Input Arguments:
*	folder_path: string name of the full/relative folder path of the specific student.
*	final_grade: the final grade of the student.
* Return:
*	returns -1 if the file operations fail.
*/
int PrintFinalGradeToFile(char *folder_path, int final_grade);

#endif // __HARDCODEDDATA_H___