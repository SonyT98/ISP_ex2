#pragma once

#include "HardCodedData.h"
#include "ProcessFunctions.h"
#include "TestManagerFunctions.h"


int main()
{
	char ids[MAX_NUM_STUDENTS][ID_STR_LENGTH] = { "1", "2", "3","4","5","6","7","8","9","10"};
	char *path = "C:\\Users\\User\\source\\repos\\SonyT98\\ISP_ex2\\Ex2\\TestGrade\\test1";

	GetIdsFromFile(path, ids);



}





