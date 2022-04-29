#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int getTimeDetail(int index)
{
	time_t timeNow;
	struct tm *timeType;
	int year, month, day, hour, min, sec;

	/*
	Get time from local system.
	*/
	time(&timeNow);					//	get time return seconds
	timeType = localtime(&timeNow); //	into struct
	year = timeType->tm_year + 1900;
	month = timeType->tm_mon;
	day = timeType->tm_mday;
	hour = timeType->tm_hour;
	min = timeType->tm_min;
	sec = timeType->tm_sec;
	//	add time to second (ignored date)
	int time[6] = {year, month, day, hour, min, sec}; //	store in array
	return time[index];
}

int getTime()
{
	return (int)time(NULL);
}

void goto_xy(int x, int y)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x, y};
	SetConsoleCursorPosition(hOut, pos);
}

int main(void)
{
	char press;
	int timeNow = getTime();
	int timeInitial = timeNow - 1;
	double rate = 0;
	int correct = 0;
	int randomNum;
	int pressed = 1;
	system("COLOR F3"); 					//	set color: background-white text-blue

	while (press != 27)						//	quit when press is the ESC
	{			   
		press = 0; 							//	null
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF3);
		
		// update rate: correct times / game time
		rate = (double)correct / (double)(timeNow - timeInitial);
		
		if (pressed)						//	update key after pressed
		{
			srand((unsigned)time(NULL));	//	use time as the random seed
			//randomNum = rand() % 93 + 33; 	//	get a random number from 33~126 (! to ~)
			randomNum = rand() % 26 + 65;
			pressed = 0;
		}

		if (timeNow != getTime())			//	update board each second
		{
			timeNow = getTime();
			goto_xy(0, 0);
			printf("*******KEYBOARD ONLY********\n");
			printf("** Heal typing disability **\n");
			printf("****************************\n");
			printf("************** Author:LMC **\n");
			printf("******* Created:2021/10/10 *\n");
			printf("****************************\n\n");
			printf("----------------------------\n");
			printf("\tTime:%d\tRate:%.3f\t\n", timeNow - timeInitial, rate);
			printf("\tPlease press %c\n", randomNum);
			printf("----------------------------\n");
		}

		if (kbhit())						//	check press
		{
			goto_xy(0, 15);
			press = getch();
			if (press == randomNum)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3A);
				correct++;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3C);
				correct--;
			}
			printf("\t©³©¥©·\n");
			printf("\t©§%c©§\n", press);
			printf("\t©»©¥©¿\n");
			pressed = 1;
		}
	}

	system("COLOR F3");
	goto_xy(0, 20);
	printf("Your accuracy rate in %d seconds is %.2f%%!", timeNow - timeInitial, rate * 100.0);
	system("pause");
	return 0;
}
