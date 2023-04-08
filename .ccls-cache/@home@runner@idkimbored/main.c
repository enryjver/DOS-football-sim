#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MatchSimulator()
{
	int codeChrono, addedTime=99, matchTime=0, addedTimeCheck=0, halfNo=1, halfLenght=45;
	int simSpeed=.5; //simspeed
	char startHalfPrompt;

	halfSim:
	switch (halfNo)
		{
			case 1:
				printf("\nStart of the 1st half.\n");
				break;
			case 2:
				printf("\nStart of the 2nd half.\n");
				break;
			case 3:
				printf("\nStart of the 1st half of extra time.\n");
				halfLenght=15;
				break;
			case 4:
				printf("\nStart of the 2nd half of extra time.\n");
				break;
			case 5:
				printf("\nPenalty shootout.\n");
				goto penShootout;
				break;
			default:
				printf("\nError MS#01\nSimulation stopped.");
				exit(0);
		}
	for (codeChrono=0;codeChrono<=halfLenght;codeChrono++)
		{
			switch (addedTime)
			{
				case 99:
					printf("%d'\n", matchTime);
					break;
				default:
					printf("%d' [+%d']\n",matchTime, addedTime);
			}

			if (codeChrono==halfLenght-1&& addedTimeCheck==0)
			{
				addedTime=rand() % 5+0;
				codeChrono=codeChrono-addedTime;
				addedTimeCheck++;
			}
			matchTime++;
			sleep(simSpeed);
		}
	printf("Start the next half? [y/n]\nUser> ");
	getchar();
	scanf("%c",&startHalfPrompt);
	switch (startHalfPrompt)
		{
			case 'y':
				matchTime=matchTime-addedTime-1;
				addedTime=99;
				addedTimeCheck=0;
				halfNo++;
				goto halfSim;
				break;
			default:
				NULL;
		}
	penShootout:
	
	exit(0);
}

void TeamsGenerator()
{
	int Team1Players[11], Team2Players[11], loop;

	srand(time(NULL));
	printf("\n     TEAM 1    TEAM 2\n");
	for (loop=0;loop<11;loop++)
		{
			Team1Players[loop]=rand() % 10+1;
			Team2Players[loop]=rand() % 10+1;
			printf("%d.		%d	|  %d\n",loop+1, Team1Players[loop], Team2Players[loop]);
		}
	MatchSimulator();
}

int main()
{
	int MMchoice;
	
	printf("FIFA DOS Football Simulator\n\nMain menu\n1. Sim match\n2. Quit\nUser> ");
	scanf("%d", &MMchoice);
	do
	{
		switch (MMchoice)
		{
			case 1:
				TeamsGenerator();
				break;
			case 2:
				break;
			default:
				printf("\nInvalid choice");
		}
	}while(MMchoice!=1 || MMchoice!=2);
}