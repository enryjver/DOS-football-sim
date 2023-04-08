#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Team1PlayersGLOB[11], Team2PlayersGLOB[11];

//commentary
char shotMiss[5][50]={"\nThe shot flies high over the crossbar.", "\nVery poor shot, completely off target.", "\nAnd he misses!", "\nWavyard shot, missed the target completely.", "\nShot's out."};
char goalFromPost[5][70]={"\nAnd it's in from the post!","\nLucky striker, the ball goes in after hitting the goal frame.","\nIt's in from the crossbar!", "\nThe post comes to the striker's aid, it's a goal!", "\nThe goalkeeper's save wasn't enough, it goes in from the post."};
char shotMissFromPost[5][50]={"\nIt goes out after hitting the post.","\nIt hits the post!","\nOut after hitting the frame of the goal.","\nIt hits the crossbar!","\nOut after hitting the crossbar."};

void PenShootout()
{
	int side=0,sideGK=0, pot_pre=0, coinFlip=0, turnNo=10, commLine=0, luckyPost=0, aiScore=0, playerScore=0,gkError=0,gkErrorChance=0;
	printf("A coin is thrown into the air to decide wich side starts first.\n");
	coinFlip=rand() % 2+1;
	switch (coinFlip)
		{
			case 1:
				printf("The player starts first.");
				goto aiTurn;  //playerTurn
				break;
			case 2:
				printf("The AI starts first.");
				goto aiTurn;
				break;
			default:
				printf("\nError #02\nSimulation stopped.");
				exit(0);
		}
	aiTurn:
	commLine=rand()%4+0;
	side=rand()%3+1;
	pot_pre=rand()%5+1;
	printf("DEBUG: commLine=%d		side=%d		pot_pre=%d", commLine, side, pot_pre);
	printf("\n\n[AI.SCORE=%d]\nWich side is the goalkeeper going to dive?\n1. Left		2. Center		3. Right\nUser> ",aiScore);
	scanf("%d",&sideGK);
	printf("The AI approaches the penalty spot...");
	if (Team2PlayersGLOB[turnNo]-pot_pre<0)
	{
		luckyPost=rand()%10+0;
		switch(luckyPost)
			{
			case 8:
				printf("%s",goalFromPost[commLine]);
				printf("debug GOAL:POST");
				aiScore++;
				break;
			case 9:
			case 10:
				printf("%s",shotMissFromPost[commLine]);
				printf("debug MISS:POST");
				break;
			default:
				printf("%s", shotMiss[commLine]);
				printf("debug MISS");
			}
		
		/*luckyPost=rand()%10+0;
		if (luckyPost==8)
		{
			printf("%s",goalFromPost[commLine]);
			aiScore++;
		}
		else if (luckyPost>=9)
		{
			printf("%s",shotMissFromPost[commLine]);
		}
		else
		{
			printf("%s", shotMiss[commLine]);
		}*/
	}
	else
	{
		if (side==sideGK)
		{
			gkError=pot_pre*2;
			gkErrorChance=rand()%10+0;
			if (gkError>gkErrorChance)
			{
				printf("\ngoal");
				aiScore++;
			}
			else
			{
				printf("\nsave");
			}
		}
		else
		{
			printf("\ngoal");
			aiScore++;
		}
	}
	goto aiTurn;

	/*playerTurn:
	commLine=rand()%4+0;
	side=rand()%3+1;
	pot_pre=rand()%5+1;
	printf("\nWich side is the goalkeeper going to dive?\n1. Left		2. Center		3. Right\nUser> ");
	scanf("%d",&sideGK);
	printf("\nThe AI approaches the penalty spot...");
	if (Team2PlayersGLOB[turnNo]-pot_pre<0)
	{
		luckyPost=8;
		//luckyPost=rand()%10+0;
		if (luckyPost==8)
		{
			printf("%s",goalFromPost[commLine]);
			aiScore++;
		}
		else if (luckyPost>=9)
		{
			printf("%s",shotMissFromPost[commLine]);
		}
		else
		{
			printf("%s", shotMiss[commLine]);
		}
	}
	else
	{
		if (side==sideGK)
		{
			gkError=pot_pre*2;
			gkErrorChance=rand()%10+0;
			if (gkError>gkErrorChance)
			{
				printf("goal");
				aiScore++;
			}
			else
			{
				printf("save");
			}
		}
	}
	goto aiTurn;*/

	exit(0);
}

void MatchSimulator()
{
	int codeChrono, addedTime=99, matchTime=0, addedTimeCheck=0, halfNo=1, halfLenght=45;
	int simSpeed=0; //simspeed
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
				PenShootout();
				break;
			default:
				printf("\nError #01\nSimulation stopped.");
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
	for (loop=0;loop<11;loop++)
		{
			Team1PlayersGLOB[loop]=Team1Players[loop];
			Team2PlayersGLOB[loop]=Team2Players[loop];
		}
	MatchSimulator();
}

int main()
{
	int MMchoice;
	
	printf("DOS Football Simulator\n\nMain menu\n1. Sim match\n2. Quit\nUser> ");
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