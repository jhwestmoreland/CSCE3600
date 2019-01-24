/*
	Jared Westmoreland
	System Programming 3600.001
	October 6, 2017
	If the user puts 5 inputs find the maximum number
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int total=0;
	int i;
	if (argc == 5 || argc == 6)
	{
		int *count;
		count = ((int*)malloc(argc));
		for(i=1; i<argc; i++)
		{
			count[i-2] = atoi(argv[i]);
			if(i == 1)
			{
				total = count[i-2];
			}
			else if(total < count[i-2] && i >= 2)
			{
				total  = count[i-2];
			}
		}
		printf("The maxium of %d integers is %d\n", i-1, total);
		free(count);
	}
	else
        {
                printf("usage: ./a.out int1 int2 int3 int4 [int5]\n");
        }
}
