#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));
#include <time.h>		// Required for function(s): srand(time(NULL));

Simulator* simulator = new Simulator;

int main()
{
	srand(time(NULL)); // Seed Init


	// We create the simulator
	

	simulator->playerWins = 0;

	// We start the program
	simulator->TitleScreen();
	simulator->SecondScreen();
	if (simulator->playing == true)
	{
		int a = 0;
		a = simulator->BattlePresentation();
		simulator->entityManager->InitAll(a);
		system("cls");
	}
	else
	{
		simulator->simParameters = simulator->ConfigSimulation();
		simulator->TestConfiguration();
		simulator->entityManager->InitAll(simulator->simParameters.playerLevel);
	}

	// testing puroposes
	//simulator->simParameters.nIterations = 10000; // :D
	//simulator->simParameters.playerLevel = 1;
	//simulator->entityManager->InitAll(4);
	//simulator->playing = true;

	if (simulator->playing)
	{
		int onLoop = -1;
		while (onLoop == -1)
		{
			simulator->PlayRoundManual();
			onLoop = simulator->EndRoundCalculations();
			if (onLoop == 1)
			{
				simulator->VictoryScreen();
			}
			else if (onLoop == 0)
			{
				simulator->LostScreen();
			}
		}
	}
	else
	{
		for (int i = 0; i < simulator->simParameters.nIterations; i++)
		{
			int onLoop = -1;
			while (onLoop == -1)
			{
				simulator->PlayRound();
				onLoop = simulator->EndRoundCalculations();

				if (onLoop == 1)
				{
					simulator->playerWins++;
					printf("\n Simulation [%d] WIN", i);
				}
				else if (onLoop == 0)
				{
					printf("\n Simulation [%d] LOSS", i);
				}
			}
			// We reset the entities for next loop
			simulator->entityManager->InitAll(simulator->simParameters.playerLevel);
			//simulator->inventory->ResetInventory();
		}

		simulator->ResultsScreen();
	}
	system("cls");
	printf("\n Closing Program\n ");
	//delete simulator;
	system("pause");
	return 0;
}


