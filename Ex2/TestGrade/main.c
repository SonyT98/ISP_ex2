#include "ThreadFunctions.h"
#include "HardCodedData.h"
#include "TestGradeFunctions.h"

int main()
{
	char folder_dir[] = "C:\\Users\\user\\source\\repos\\SonyT98\\ISP_ex2\\Ex2\\TestGrade\\test1\\grades_853453571";
	int grades_array[NUM_GRADES];
	int a = 0;
	ReadAllGrades(folder_dir, grades_array);
	a = CalculateFinalGrade(grades_array);
	return a;
}