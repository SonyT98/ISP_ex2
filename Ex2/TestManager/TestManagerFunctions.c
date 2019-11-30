
#include "TestManagerFunctions.h"
#include "ProcessFunctions.h"

int GetIdsFromFile(char *path, char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH])
{
	// variables
	int number_of_students = 0;
	FILE *idsFile = NULL;
	char* filename = NULL;
	char current_id[ID_STR_LENGTH + 1] = "";
	int error_flag = -1;
	// create filename 
	filename = (char*)malloc(sizeof(char)*(strlen(path) + ID_FILE_EXTENSION));
	if (filename == NULL)
	{
		printf("Error allocating memory\n");
		return ERROR_CODE;
	}
	
	error_flag = sprintf_s(filename, strlen(path) + 18,"%s\\studentIds.txt", path);

	if (error_flag == ERROR_CODE)
	{
		fprintf(stderr, "Error: sprintf has failed");
		return ERROR_CODE;
	}

	// open file
	error_flag = fopen_s(&idsFile,filename,"r");

	// check fopen failure 
	if (idsFile == NULL)
	{
		printf("Error opening File - %s\n", filename);
		return ERROR_CODE;
	}
	
	// while loop until reach end of file & read one line
	while (fgets(current_id, ID_STR_LENGTH + 1, idsFile) != NULL)
	{

		current_id[ID_STR_LENGTH - 1] = '\0';
		error_flag = strcpy_s(ids[number_of_students], ID_STR_LENGTH + 1, current_id);
		// fill the ids table
		if (error_flag) 
		{
			printf("error using strcpy");
			fclose(idsFile);
			return ERROR_CODE;
		}
		number_of_students++;
	}
	return number_of_students;
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
	int error_flag = -1, i = 0;
	FILE* gradesFile = NULL;
	filename = (char*)malloc(sizeof(char)*(strlen(path) + FINAL_GRADES_FILE_EXTENSION));
	
	if (filename == NULL)
	{
		printf("Error allocating memory\n");
		return ERROR_CODE;
	}

	error_flag = sprintf_s(filename, strlen(path) + 19, "%s\\final_grades.txt", path);
	
	if (error_flag == ERROR_CODE)
	{
		fprintf(stderr, "Error: sprintf has failed");
		return ERROR_CODE;
	}

	// open the file
	error_flag = fopen_s(&gradesFile, filename, "w");

	// check fopen failure 
	if (gradesFile == NULL)
	{
		printf("Error opening File - %s\n", filename);
		return ERROR_CODE;
	}

	for (i = 0; i < number_of_students; i++)
	{
		error_flag = fprintf_s(gradesFile, "%s %d\n", ids[i], grades[i]);
		if (error_flag < 0)//if the fprintf failed
		{
			fprintf(stderr, "fprintf failed");
			return ERROR_CODE;
		}
	}
	fclose(gradesFile);
	return 0;
}