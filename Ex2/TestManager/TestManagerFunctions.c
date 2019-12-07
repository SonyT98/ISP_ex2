// Authors - Tomer Segal 207133646, Nadav Nave 209365725.
// Exercise 2 in the Course Introduction to system programming.
// This C file contains all the function related to the manager process include:
// getting the list of ids from the file, get the students grade, and write the grade 
// the output file.
// 

#include "TestManagerFunctions.h"
#include "ProcessFunctions.h"

int GetIdsFromFile(char *path, char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH])
{
	// variables
	int number_of_students = 0;
	FILE *idsFile = NULL;
	char* filename = NULL;
	char current_id[ID_STR_LENGTH + 1] = "";
	int error_flag = -1,ret = 0;

	// create filename 
	filename = (char*)malloc(sizeof(char)*(strlen(path) + ID_FILE_EXTENSION));
	if (filename == NULL)
	{
		printf("Error allocating memory\n");
		ret = ERROR_CODE;
		goto err1;
	}
	
	error_flag = sprintf_s(filename, strlen(path) + 18,"%s\\studentIds.txt", path);

	if (error_flag == ERROR_CODE)
	{
		fprintf(stderr, "Error: sprintf has failed\n");
		ret = ERROR_CODE;
		goto err2;
	}

	// open file
	error_flag = fopen_s(&idsFile,filename,"r");

	// check fopen failure 
	if (idsFile == NULL)
	{
		printf("Error opening File - %s\n", filename);
		ret = ERROR_CODE;
		goto err2;
	}
	
	// while loop until reach end of file & read one line
	while (fgets(current_id, ID_STR_LENGTH + 1, idsFile) != NULL)
	{

		current_id[ID_STR_LENGTH - 1] = '\0';
		error_flag = strcpy_s(ids[number_of_students], ID_STR_LENGTH, current_id);
		// fill the ids table
		if (error_flag) 
		{
			printf("error using strcpy\n");
			ret = ERROR_CODE;
			goto err3;
		}
		number_of_students++;
	}
	ret = number_of_students;

err3:
	fclose(idsFile);
err2:	
	free(filename);
err1:
	return ret;
}

int GetStudentsFinalGrades(char *path, char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH], int number_of_students, int *grades)
{
	//varibales
	int i = 0, process_exit_code = 0;

	//create each process
	for (i = 0; i < number_of_students; i++)
	{
 		process_exit_code = CreateProcessTestGrade(path, ids[i]);
		if (process_exit_code == ERROR_CODE)
		{
			//if the process number i failed
			fprintf(stderr, "Captain, we were unable to calculate %s\n", ids[i]);
			return ERROR_CODE;
		}
		//final grade of the i's students
		grades[i] = process_exit_code;
	}
	return 0;
}

int WriteFinalGradesFile(char *path, char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH], int number_of_students, int *grades)
{
	char* filename = NULL;
	int error_flag = -1, i = 0,ret = 0;
	FILE* gradesFile = NULL;

	filename = (char*)malloc(sizeof(char)*(strlen(path) + FINAL_GRADES_FILE_EXTENSION));
	if (filename == NULL) // check malloc error
	{
		printf("Error allocating memory\n");
		ret = ERROR_CODE;
		goto err1;
	}

	error_flag = sprintf_s(filename, strlen(path) + 19, "%s\\final_grades.txt", path);
	if (error_flag == ERROR_CODE) // check sprintf error
	{
		fprintf(stderr, "Error: sprintf has failed\n");
		ret = ERROR_CODE;
		goto err2;
	}

	// open the file
	error_flag = fopen_s(&gradesFile, filename, "w");
	if (gradesFile == NULL)// check fopen error 
	{
		printf("Error opening File - %s\n", filename);
		ret = ERROR_CODE;
		goto err2;
	}

	for (i = 0; i < number_of_students; i++)
	{
		error_flag = fprintf_s(gradesFile, "%s %d\n", ids[i], grades[i]);
		if (error_flag < 0)//check fprintf error
		{
			printf("fprintf failed\n");
			ret = ERROR_CODE;
			goto err3;
		}
	}

	// if the function succeed
	ret = 0;

err3:
	fclose(gradesFile);
err2:
	free(filename);
err1:
	return ret;
}