#include <stdlib.h>

#include "ThreadFunctions.h"
#include "HardCodedData.h"
#include "TestGradeFunctions.h"

int main(int argc,char **argv)
{
	char *folder_path = NULL;
	int grades_array[NUM_GRADES] = {0};
	int final_grade = 0;

	if (argc != 2)
	{
		printf("Error: not enough arguments for TestGrade\n");
		return ERROR_CODE;
	}
	
	folder_path = argv[1];

	// change directory to the student grades folder
	if (chdir(folder_path) == ERROR_CODE)
	{
		printf("ERROR: %s directory wasn't found\n", folder_path);
		return ERROR_CODE;
	}

	// Read all grades
	if (ReadAllGrades(folder_path, grades_array) == ERROR_CODE)
		return ERROR_CODE;

	// Calculate the final grade
	final_grade = CalculateFinalGrade(grades_array);
	
	// Write the final grade to final_id.txt
	if(PrintFinalGradeToFile(folder_path,final_grade) == ERROR_CODE)
		return ERROR_CODE;

	return final_grade;
}