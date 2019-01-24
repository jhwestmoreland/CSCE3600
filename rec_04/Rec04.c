#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i=0;
	int j=0;
	int n;
	int *burst=0;
	int *wait=0;
	int *turn=0;
	int count;
	int waits=0;
	int turns=0;
	float avgwaits;
	float avgturns;
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	burst = malloc(n*sizeof(int));
	turn = malloc(n*sizeof(int));
	wait = malloc(n*sizeof(int));

	for(count =0; count< n; count++)
	{
		printf("Enter the burst time of process #%d: ", count);
		scanf("%d", &burst[count]);
	}

	wait[0] = 0;
	turn[0] = burst[0];

	for(count =0; count< n; count++)
	{
		waits = waits + wait[count];
                turns = turns + turn[count];

		if(count == n-1)break;
		wait[count+1] = burst[count] + wait[count];
		turn[count+1] = turn[count] + burst[count+1];
	}
	avgwaits= (waits/n);
	avgturns= ((turns)/n);

	printf("process burst   wait    turn\n");
	for(count =0; count< n; count++)
        {
		printf("P%d\t", count);
		printf("%d\t", burst[count]);
		printf("%d\t", wait[count]);
		printf("%d\n", turn[count]);
        }

	printf("avg waiting time\t=%.4f\n", avgwaits);
        printf("avg turnaround time\t=%.4f\n", avgturns);
	free(burst);
	free(turn);
	free(wait);
}
