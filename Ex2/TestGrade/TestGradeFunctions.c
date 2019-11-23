
#include "TestGradeFunctions.h"


int ReadAllGrades(char *folder_path, int* grades_array)
{
	// variables
	HANDLE p_thread_handles[NUM_THREADS];
	DWORD p_thread_ids[NUM_THREADS];
	DWORD wait_code;

	int change_diractory_err = 0, exit_code = 0;

	// create constant string array of all grades text filenames
	const char filenames[NUM_GRADES][MAX_FILNAME_LENGTH] = {
	"ex01.txt",
	"ex02.txt",
	"ex03.txt",
	"ex04.txt",
	"ex05.txt",
	"ex06.txt",
	"ex07.txt",
	"ex08.txt",
	"ex09.txt",
	"ex10.txt",
	"midterm.txt",
	"moedA.txt",
	"moedB.txt" };

	// change directory to the student grades folder
	change_diractory_err = chdir(folder_path);

	// create all ex threads in a loop
	for (int i = 0; i < NUM_THREADS - 1; i++)
	{
		p_thread_handles[i] = CreateThreadSimple(ReadGrade, &p_thread_ids[i], (void*)filenames[i]);
		

	}
	// check if thread creation failed

	// wait for all thread to finish
	wait_code = WaitForMultipleObjects(NUM_THREADS, p_thread_handles, TRUE, INFINITE);
	
	if ((WAIT_FAILED == wait_code) || (WAIT_TIMEOUT == wait_code))
	{
		printf("Error when waiting");
		return ERROR_CODE;
	}

	// get the exit codes
	for (int i = 0; i < NUM_THREADS - 1; i++)
	{
		// get exit code into a temporary variable
		GetExitCodeThread(p_thread_handles[i], &exit_code);
		// check if thread error
		if (exit_code == -1)
		{
			// print error and exit
			return ERROR_CODE;
		}
		else
		{
			grades_array[i] = exit_code;
		}
	}

}

