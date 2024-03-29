// Authors - Tomer Segal 207133646, Nadav Nave 209365725
// Exercise 2 in the Course Introduction to system programming
// This C file contains all the function related to the process creation,
// waiting for the end of the process and get the process exit code.

#include "ProcessFunctions.h"


int CreateProcessTestGrade(char *input_path, char *id_string)
{
	CHAR *commandstring = NULL;
	int path_length = strlen(id_string) + strlen(input_path) + COMMAND_LINE_EXTENSION;
	int return_num = 0, sprintf_err = 0, exitcode_err = 0;

	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;

	commandstring = (char*)malloc(sizeof(char)*(path_length));
	if (commandstring == NULL)// Check malloc error
	{
		fprintf(stderr, "Memory Not Allocated\n");
		return ERROR_CODE;
	}

	// the string that we send to the command line, the folder path
	sprintf_err = sprintf_s(commandstring, path_length, "TestGrade.exe %s\\grades_%s", input_path, id_string);
	if (sprintf_err == ERROR_CODE)// Check sprintf error
	{
		fprintf(stderr, "Error: sprintf has failed\n");
		free(commandstring);
		return ERROR_CODE;
	}
	

	//create the process with the create process simple function
	retVal = CreateProcessSimple(commandstring, &procinfo);

	// we will get 0 if the creation failed
	if (retVal == 0)
	{
		fprintf(stderr, "Process Creation Failed!\n");
		free(commandstring);
		return ERROR_CODE;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */


	if (waitcode != WAIT_OBJECT_0) /* Process is still alive */
	{
		fprintf(stderr, "Process was not terminated before timeout!\n");
		return_num = ERROR_CODE;
	}
	else
	{
		// if there is no timeout, we will get the exit code
		exitcode_err = GetExitCodeProcess(procinfo.hProcess, &exitcode);
		// check if GetExitCodeProcess error
		if (exitcode_err == 0)
		{
			fprintf(stderr, "Error getting exit code from process\n");
			CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
			CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
			free(commandstring);
			return ERROR_CODE;
		}
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