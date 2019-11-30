
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
	filename = (char*)malloc(sizeof(char)*(strlen(path) + 18));
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
	
	// while loop until reach end of file
	while (!feof(idsFile))
	{

		// read one line
		fgets(current_id, ID_STR_LENGTH +1, idsFile);
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
	return 0;
}


















int WriteFinalGradesFile(char *path, char **ids, int number_of_students, int **grades)
{
	char* filename = NULL;
	int error_flag = -1, i = 0;
	FILE* gradesFile = NULL;
	filename = (char*)malloc(sizeof(char)*(strlen(path) + 19));
	
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

	for (i = 0, i < number_of_students, i++)
	{
		error_flag = fprintf_s(gradesFile, "%s %s\n", ids[i], grades[i]);

	}


}