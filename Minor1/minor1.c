/*
	Name:		Jared Westmoreland
	Major: 		Computer Engineering
	Student ID: 	11022685
	Class: 		CSCE 3600.01 Systems Programming
	Date:		September 16,2017
	Due date: 	Monday, September 18,2017
	Description:	Opens a file and compare each word with the user input. If a word
			is similar I counts it as 1 to X
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char *argv[])
{
	printf("\n");
/*
*****************************************************************************************************************
	These if statements basically are here to indicate if the user
	actually put a file and a word to search for. If the user did
	not put anything it will return Error									*/

	if(argv[1] == NULL)
	{
		printf("Error: Unable to find user input File Name and input to search\n\n");
		exit(EXIT_FAILURE);
	}
	else if(argv[2] == NULL)
	{
		printf("Error: Unable to find the user input to search for word patterns\n\n");
                exit(EXIT_FAILURE);
	}
/*
*****************************************************************************************************************
	These are my many variable within the program								*/

	int number=0;
	FILE *fp;		//which includes a file
	char file_name[800];
	char input[800];
	char file[800][800];
	char buff[800];
	int i=0;
	int j;
	int k;
	int largest[800];
	int large=0;
	char yup[800];
	int line[800];

/*
*****************************************************************************************************************
	This basically makes it easier for me to understand and implement					*/

	strcpy(file_name, argv[1]);
	strcpy(input, argv[2]);

/*
*****************************************************************************************************************
	Opens the file and checks if it actually exist or if it does not. If it is unable
	to locate it, the program returns Unable to open file							*/

	fp = fopen(file_name, "r");
        if (fp == NULL)
        {
                printf("Unable to open file!\n");
                exit(EXIT_FAILURE);
        }
/*
*****************************************************************************************************************
	This while loop read and puts every line in to buff as a string						*/

	while(fgets(buff, sizeof(buff), fp))
       	{
		/*This for loop determines the longest line and then stores the longest line into
		  large (largest line)*/
		for(j=0; j<strnlen(buff, 800); j++)
                {
			/*Just in case if the first line is the longest.
			  Intially store it into large*/
			if(j > large)
               	        {
				//If another line is longer update it
               	                large = strnlen(buff, 800);
               	        	strcpy(yup, buff); //This is the sentence
			}
		}
		/*_________________________Important Note to Grader________________________________
			This is to find the amound of user's inputs there are with in the text file.
		  I sadly was unable to figure out how to each sentence independently to count
		  the total amount. Rather it counts only once if it ever found one or more of
		  the user's input.
		*/
		if(strstr(buff, input))
		{
			strcpy(file[number],buff);
			line[number]=i+1;
			number++;
		}
		i++; //counts how many lines there are total
	}
/*
*****************************************************************************************************************
	This is the Display to show the results of the program							*/

	printf("Total number Occurrences of \"%s\" in File: %d\n",input,number);
	printf("------------------------------------------------------\n");
	for(k=0; k<=i; k++)
	{
		if(line[k]!= 0)
		{
			printf("Line %d: ", line[k]);
		}
		printf("%s", file[k]);
	}
	printf("------------------------------------------------------\n");
	printf("Total Lines in File\t= %d\n", i);
	printf("Characters Longest Line\t= %d\n", large);
	printf("Longest line\t\t= %s\n",yup);
	fclose(fp);
}
