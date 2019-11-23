#include "ThreadFunctions.h"
#include "HardCodedData.h"
#include "TestGradeFunctions.h"

int main()
{
	char folder_dir[] = ".\\test1\\grades_122369710";
	int grades_array[NUM_GRADES];
	int a = 0;
	a =ReadAllGrades(folder_dir, grades_array);
	a++;
	return a;
}