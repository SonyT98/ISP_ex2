
#include <stdlib.h>

#include "ThreadFunctions.h"
#include "HardCodedData.h"
#include "TestGradeFunctions.h"

int main()
{
	char folder_path[] = "C:\\Users\\user\\source\\repos\\SonyT98\\ISP_ex2\\Ex2\\TestGrade\\test6\\grades_673938188";
	int grades_array[NUM_GRADES];
	int final_grade = 0;

	// change directory to the student grades folder
	if (chdir(folder_path) == ERROR_CODE)
	{
		printf("ERROR: %s directory wasn't found", folder_path);
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