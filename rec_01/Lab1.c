#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int counter;
	int retcode;
	double *dbl_ptr;
	FILE *fp;
	srand(time(NULL));
	// Part 1
	dbl_ptr = malloc(10 * sizeof(double));
	if (!dbl_ptr)
	{
		printf("Memory allocation error!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Memory allocation successful.\n");
	}
	// Part 2
	for (counter = 0; counter < 10; counter++)
	{
		dbl_ptr[counter] = (double)(rand()%1000);
	}
	// Part 3
	fp = fopen("rec01.txt", "w");
	if (fp == NULL)
	{
		printf("Unable to open file!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Opened file successfully for writing.\n");
	}
	// Part 4
	fwrite(dbl_ptr, sizeof(double), 10, fp);
	if (retcode != 10)
	{
		printf("Write error!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Write was successful.\n");
	}
	fclose(fp);
	free(dbl_ptr);
	// Part 5
	dbl_ptr = malloc(10 * sizeof(double));
	if (!dbl_ptr)
	{
		printf("Memory allocation error!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Memory allocation successful.\n");
	}
	// Part 6
	fp = fopen("rec01.txt", "r");
	if (fp == NULL)
	{
		printf("Unable to open the file!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Opened file successfully for reading.\n");
	}
	// Part 7
	retcode= fread(dbl_ptr, *dbl_ptr, 10, fp);
	if (retcode != 10)
	{
		printf("Read error!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf( "Read was successful.\n" );
	}
	fclose(fp);
	// Part 8
	printf("The numbers read from file are:\n");
	for (counter = 0; counter < 10; counter++)
	{
		printf("%f\n", dbl_ptr[counter]);
	}
	free(dbl_ptr);
	return 0;
}
