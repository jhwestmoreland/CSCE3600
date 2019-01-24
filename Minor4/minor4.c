/*
	Jared Westmoreland
	10/17/2017
	Shortest Remaining Time First

	--This helped me a lot
www.quora.com/How-do-I-write-a-C-program-to-implement-a-SRTF-Shortest-Remaining-Time-First-scheduling-algorithm-along-with-displaying-the-Gantt-chart

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//gets user input
	char here[800];
	printf("Enter name of process file: ");
        scanf("%s", &here[0]);

	//file
        FILE *fp;
        fp = fopen(here ,"r");

	//All the variables I needed
	char pd[800];	//PX
	int arrive[800];//arrival time
	int burst[800]; //burst time
	int num1[1];    //copy arrive
	int num2[1];    //copy burst
	int k=0;
	int i;
	int total=0;	 //helps find throughput
	float through=1; //throughput 
	int remain=0;    //counter to see the remaining
	int smallest;    //helps find the smallest burst
	int time;        //clock
	double end;         //subs the end
	double average=0;   //wait time
	double totaltime=0; //turnaround
	int rt[800];        //copy of burst
	int av[800];        //basically stores all values of wait
	int fin[800];       //basically stores all values of finish


        //if the file does not exit
	if (fp == NULL)
	{
		printf("error: unable open file %s. terminating...\n", here);
		exit(EXIT_FAILURE);
	}
	//if it does
	else
	{
		//part of the display
		printf("\nPID\tarrive\tburst\tremain\tfinish\twait\n");
		printf("--------------------------------------------\n");
		while(!feof(fp))
		{
			//grabs everything from the file
			fscanf(fp,"%s %d %d", pd, num2, num1);

			//puts the info into arrays that can properly store them
			arrive[k]=num2[0];
			burst[k]=num1[0];
			rt[k]=burst[k]; //copy burst
			//break if the previous value matches the new one
			if(burst[k-1] == burst[k] && arrive[k-1] == arrive[k])
			{
				break;
			}
			//counts how many lines there are in the file
			k++;
		}

		//sets the value so it has something to compare
		rt[7]=9999;

		//this for loop caculates the Shortest Remaining Time First
		for(time=0;remain!=k;time++)
		{
			//gives the predefined value to compare 
			smallest=7;
			for(i=0;i<k;i++)
			{
				//looks for the smallest values
				if(arrive[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
				{
					smallest=i;
				}
			}
			//goes to the next burst copied value 
			rt[smallest]--;

			//if it is 0
			if(rt[smallest]==0)
			{
				remain++;
				end=time+1; 						//basically end needs to be time but 1 more
				average+=end-burst[smallest]-arrive[smallest];          //gets the value of waiting
				av[smallest] =end-burst[smallest]-arrive[smallest];     //stores each value the equation gets
				totaltime+=end-arrive[smallest];                        //finds finish
				fin[smallest] = end-arrive[smallest];                   //stores finish put needs k
			}
		}
		//calcutes total
		for(i=0; i<k; i++)
		{
			total = total + burst[i];
		}
		//Displays the information gathered above
		for(i=0; i<k; i++)
		{
			//fin[i]+1 allows me to get the value of finish (the correct value)
			 printf("P%d\t%d\t%d\t0\t%d\t%d\n", i+1, arrive[i], burst[i],fin[i]+i, av[i]);
		}
		//calculates throughput
		through = (float)(k)/total;
		//Prints Throughput & Waiting time average, and turaround time average
		printf("average throughput\t=  %.4f processes/unit\n", through);
		printf("average waiting time\t=  %.4lf units\n", average/k);
		printf("average turnaround time\t=  %.4lf units\n", totaltime/k);
	}
	//closes the file
	fclose(fp);
}
