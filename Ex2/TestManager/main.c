#pragma once

#include "HardCodedData.h"
#include "ProcessFunctions.h"
#include "TestManagerFunctions.h"


int main()
{
	char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH] = { "" };
	char *path = "C:\\Users\\user\\Documents\\MyDocs\\input";
	int grades[10] = { 0 };
	int err = 0, num = 0;

	num = GetIdsFromFile(path, ids);
	if (num == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	err = GetStudentsFinalGrades(path, ids, num, grades);
	if (err == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	err = WriteFinalGradesFile(path, ids, num, grades);
	if (err == ERROR_CODE)
	{
		return ERROR_CODE;
	}
	return 1;
}





