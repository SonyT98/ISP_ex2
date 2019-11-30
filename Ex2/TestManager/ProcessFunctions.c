// Authors - Tomer Segal 207133646, Nadav Nave 209365725
// Exercise 2 in the Course Introduction to system programming
// This code create the TestGrade process and wait for it result
// The code gets from the main function the parameters that the process needs

#include "ProcessFunctions.h"


int CreateProcessTestGrade(char *input_path, char *id_string)
{
	CHAR *commandstring = NULL;
	commandstring = (char*)malloc(sizeof(char)*(strlen(input_string) + 9));
	if (commandstring == NULL)
	{
		fprintf(stderr, "Memory Not Allocated");
		return ERROR_CODE;
	}
	int return_num = 0;

	// the string that we send to the command line, including the program name and the equation
	strcpy(commandstring, "son.exe ");
	strcat(commandstring, input_string);

	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;

	//create the process with the create process simple function
	retVal = CreateProcessSimple(commandstring, &procinfo);

	// we will get 0 if the creation failed
	if (retVal == 0)
	{
		fprintf(stderr, "Process Creation Failed!\n");
		free(commandstring);
		return PROCESS_CREATION_FAILED;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */


	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		fprintf(stderr, "Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate */
		return_num = PROCESS_ACCEDED_TIMEOUT;
	}
	else
	{
		// if there is no timeout, we will get the exit code
		GetExitCodeProcess(procinfo.hProcess, &exitcode);
		return_num = (int)exitcode;
	}

	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
	free(commandstring);
	return return_num;
}



BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}