#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
	printf("	  		               _____    _    _    __     ____          \n");
	printf("	  		              /  ___|  | |  | |  /  \\   |    |       \n");
	printf("	  		              | |      | |  | | |    |  | || |       \n");
	printf("	  		              | |___   | |__| | | || |  |  __|       \n");
	printf("			              \\___  \\  |  __  | | || |  | |         \n");
	printf("			                  | |  | |  | | | || |  | |         \n");
	printf("			               ___| |  | |  | | |    |  | |         \n");
	printf("			              |_____/  |_|  |_|  \\__/   |_|         \n");


	int izbor = 1;
	while (izbor != 999)
	{
		izbor = menu();
	}

	return 0;
}
