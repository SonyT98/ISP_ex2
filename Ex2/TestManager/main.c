// Authors - Tomer Segal 207133646, Nadav Nave 209365725
// Exercise 2 in the Course Introduction to system programming
// This is the main function of TestManager project

#include "HardCodedData.h"
#include "ProcessFunctions.h"
#include "TestManagerFunctions.h"


int main(int argc,char **argv)
{
	char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH] = { "" };
	char *path = NULL;
	int grades[MAX_NUM_STUDENTS] = { 0 };
	int err = 0, number_of_students = 0;

	// check number of input arguments
	if (argc != 2)
	{
		if (argc > 2) printf("Error: Too many arguments for TestManager\n");
		else printf("Error: Too few arguments for TestManager\n");
		return ERROR_CODE;
	}

	path = argv[1];

	// get the Ids from the file to an array 
	number_of_students = GetIdsFromFile(path, ids);
	if (number_of_students == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	
	// calculate and get the final grades
	err = GetStudentsFinalGrades(path, ids, number_of_students, grades);
	if (err == ERROR_CODE)
	{
		return ERROR_CODE;
	}

	// write the grades to final_grades.txt
	err = WriteFinalGradesFile(path, ids, number_of_students, grades);
	
	if (err == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	printf("The grades have arrived, captain\n");

	return 1;
}





