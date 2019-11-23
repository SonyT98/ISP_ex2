// Includes --------------------------------------------------------------------

#include "ThreadFunctions.h"
#include "HardCodedData.h"

// Function Definitions --------------------------------------------------------

HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPDWORD p_thread_id, void *arg_pointer)
{
	HANDLE thread_handle;

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	thread_handle = CreateThread(
		NULL,            /*  default security attributes */
		0,               /*  use default stack size */
		p_start_routine, /*  thread function */
		arg_pointer,     /*  argument to thread function */
		0,               /*  use default creation flags */
		p_thread_id);    /*  returns the thread identifier */

	if (NULL == thread_handle)
	{
		printf("Couldn't create thread\n");
		exit(ERROR_CODE);
	}

	return thread_handle;
}


DWORD WINAPI ReadGrade(LPVOID lpParam)
{
	//variables
	FILE* grade_file = NULL;
	char grade_string[4] = "";
	int length = 0, grade_num = 0;
	errno_t err;

	//casting of the void* parameter to a string
	char *filepath = (char*)lpParam;

	//opening the file in read mode
	err = fopen_s(&grade_file,filepath, "r");
	if (grade_file == NULL)
	{
		printf("Couldn't open the file: %s\n", filepath);
		exit(ERROR_CODE);
	}

	//extract the string from the file
	fgets(grade_string, 4, grade_file);
	length = strlen(grade_string) - 1;
	if (grade_string[length] == '\n')
		grade_string[length] = '\0';

	//convert the string to int
	grade_num = atoi(grade_string);

	//close file
	fclose(grade_file);

	return grade_num;
}
