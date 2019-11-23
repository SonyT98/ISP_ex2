#include "ThreadFunctions.h"
#include "HardCodedData.h"

int main()
{
	char filename1[11] = "grade.txt";
	char filename2[11] = "grade2.txt";
	HANDLE p_thread_handles[NUM_THREADS];
	DWORD p_thread_ids[NUM_THREADS];
	DWORD wait_code;
	int exit_code = 0, i =0, ret_val =0;

	p_thread_handles[0] = CreateThreadSimple(ReadGrade, &p_thread_ids[0], (void*)filename1);
	p_thread_handles[1] = CreateThreadSimple(ReadGrade, &p_thread_ids[1], (void*)filename2);


	wait_code = WaitForMultipleObjects(NUM_THREADS,p_thread_handles,TRUE, INFINITE);
	/*if (WAIT_OBJECT_0 != wait_code)
	{
		printf("Error when waiting");
		return ERROR_CODE;
	}*/

	DWORD exit1 = 0, exit2 = 0;
	GetExitCodeThread(p_thread_handles[0],&exit1);
	GetExitCodeThread(p_thread_handles[1], &exit2);
	exit_code = (int)exit1+(int)exit2;

	for (i = 0; i < NUM_THREADS; i++)
	{
		ret_val = CloseHandle(p_thread_handles[i]);
		if (false == ret_val)
		{
			printf("Error when closing\n");
			return ERROR_CODE;
		}
	}
	return exit_code;
}