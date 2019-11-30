#include "TestGradeFunctions.h"


int ReadAllGrades(char *folder_path, int* grades_array)
{
	// variables
	HANDLE p_thread_handles[NUM_THREADS] = { NULL };
	DWORD p_thread_ids[NUM_THREADS] = {0};
	DWORD wait_code = 0;

	int change_diractory_err = 0, exit_code = 0, i = 0, error_val = 0;

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



	// create all ex threads in a loop
	for (i = 0; i < NUM_THREADS; i++)
	{
		p_thread_handles[i] = CreateThreadSimple(ReadGrade, &p_thread_ids[i], (void*)filenames[i]);
		if (p_thread_handles[i] == NULL)
		{
			error_val = CloseThreads(p_thread_handles, i);
			return ERROR_CODE;
		}
	}
	


	// wait for all thread to finish
	wait_code = WaitForMultipleObjects(NUM_THREADS, p_thread_handles, TRUE, INFINITE);
	
	if ((WAIT_FAILED == wait_code) || (WAIT_TIMEOUT == wait_code))
	{
		printf("Error when waiting\n");
		error_val = CloseThreads(p_thread_handles, NUM_THREADS);
		return ERROR_CODE;
	}

	// get the exit codes
	for (i = 0; i < NUM_THREADS; i++)
	{
		// get exit code into a temporary variable
		error_val = GetExitCodeThread(p_thread_handles[i], &exit_code);
		// check if GetExitCodeThread error
		if (error_val == 0)
		{
			printf("Error getting exit code from thread\n");
			error_val = CloseThreads(p_thread_handles,NUM_THREADS);
			return ERROR_CODE;
		}
		// check if thread error
		else if (exit_code == -1)
		{
			error_val = CloseThreads(p_thread_handles, NUM_THREADS);
			return ERROR_CODE;
		}
		else
		{
			grades_array[i] = exit_code;
		}
	}
	//close all the threads
	if (CloseThreads(p_thread_handles, NUM_THREADS) == ERROR_CODE)
		return ERROR_CODE;
	return 0;
}

int CalculateFinalGrade(int* grades_array)
{
	//variables
	int i = 0, exam_grade = 0, midterm_grade = 0;
	double ex_avg = 0, final_grade = 0;

	// zeroing the grades if less then 60.
	for (i = EX1; i <= MOED_A; i++)
	{
		if (grades_array[i] < 60)
			grades_array[i] = 0;
	}
	// calculate the average of the best 8 exercise 
	ex_avg = CalculateBestExercisesAvg(grades_array);

	// check if the student took to MoedB and change
	// the exam grade to the last exam that was taken.
	if (grades_array[MOED_B] == 0)
		exam_grade = grades_array[MOED_A];
	else if (grades_array[MOED_B] < 60)
		exam_grade = 0;
	else
		exam_grade = grades_array[MOED_B];

	// extract the midterm grade to separate variable
	midterm_grade = grades_array[MIDTERM];
	//calculate the final grade
	final_grade = 0.2*(ex_avg + midterm_grade) + 0.6*exam_grade;
	// round the result up
	final_grade = ceil(final_grade);

	return final_grade;
}

double CalculateBestExercisesAvg(int *grades_array)
{
	int i = 0, min1 = 0, min2 = 0, sum_exercises = 0;
	if (grades_array[EX1] < grades_array[EX2])
	{
		min1 = grades_array[EX1];
		min2 = grades_array[EX2];
	}
	else
	{
		min1 = grades_array[EX2];
		min2 = grades_array[EX1];
	}
	//checking the two lowest grades of exercises and calculate the sum
	for (i = EX3; i < NUM_EXERCISES; i++)
	{
		//if the grade is lower then the two minimum grades
		if (grades_array[i] < min1)
		{
			sum_exercises = sum_exercises + min2;
			min2 = min1;
			min1 = grades_array[i];
		}
		// if the grade is higher then one grade but lower than the other one
		else if (grades_array[i] < min2)
		{
			sum_exercises = sum_exercises + min2;
			min2 = grades_array[i];
		}
		else
			sum_exercises = sum_exercises + grades_array[i];
	}
	return (sum_exercises / 8);
}

int PrintFinalGradeToFile(char *folder_path, int final_grade)
{
	FILE* fp = NULL;
	char *id_str = NULL;
	char filename[FINAL_FILENAME_LENGTH] = "";
	int path_length = strlen(folder_path);
	errno_t err = 0;
	// Create the file name with the correct id
	id_str = folder_path + path_length - 9;
	err = sprintf_s(filename, FINAL_FILENAME_LENGTH, "final_%s.txt", id_str);
	if (err == ERROR_CODE)
	{
		printf("Error: sprintf has failed\n");
		return ERROR_CODE;
	}
	// Open the file and check for opening errors
	err = fopen_s(&fp, filename, "w");
	if (fp == NULL)
	{
		printf("Error: couldn't open the file %s\n", filename);
		return ERROR_CODE;
	}
	
	fprintf(fp, "%d", final_grade);
	fclose(fp);

	return 0;
}