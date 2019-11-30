#pragma once
#ifndef __PROCESSFUNCTIONS_H__
#define __PROCESSFUNCTIONS_H___

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "HardCodedData.h"

//--------------------------------------------------------------------------//
/**
* CreateProcessSimple uses the win32 API to create a process that runs the
* command in 'CommandLine'. it uses the win32 API function CreateProcess()
* using default values for most parameters.
* (c) This function was taken from recitation 3.
*
* Accepts:
* --------
* CommandLine - a windows generic string containing the command that the new
*               process performs. ( See CreateProcess( documentation for more ).
* ProcessInfoPtr - an output parameter, used to return a PROCESS_INFORMATION
*					structure containing data about the process that was created.
*					( See CreateProcess() documentation for more ).
*
* Returns:
* --------
* the output of CreateProcess().
*/
//--------------------------------------------------------------------------//

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr);

//--------------------------------------------------------------------------//
/**
* CreateProcessTestGrade call CreateProcessSimple, wait for the process to run and
* gets the exit code from the son process.
* (c) This function was taken from recitation 3.
*
* Accepts:
* --------
* input_path - the main folder path that we recieved from the main function.
* id_string  - the id of the student.
*
* Returns:
* --------
* The exit code of the TestGrade process, the final grafe of the student. will 
* return -1 if there is an error.
*/
//--------------------------------------------------------------------------//

int CreateProcessTestGrade(char *input_path, char *id_string);
#endif // __PROCESSFUNCTIONS_H__