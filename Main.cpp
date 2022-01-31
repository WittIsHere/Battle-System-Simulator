#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));
#include <time.h>		// Required for function(s): srand(time(NULL));


int main()
{
	srand(time(NULL)); // Seed Init

	// We create the simulator
	Simulator* simulator = new Simulator;

	simulator->entityManager->SetSimulator(simulator);

	simulator->entityManager->mainC->SetSimulator(simulator);
	simulator->entityManager->keldari->SetSimulator(simulator);
	simulator->entityManager->boss->SetSimulator(simulator);
	simulator->entityManager->spiderA->SetSimulator(simulator);
	simulator->entityManager->spiderB->SetSimulator(simulator);

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
		simulator->ConfigSimulation();
		simulator->TestConfiguration();
		simulator->entityManager->InitAll(simulator->simParameters->playerLevel);
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
		for (int i = 0; i < simulator->simParameters->nIterations; i++)
		{
			if (simulator->simParameters->showInfo) printf("\n __________");
			int onLoop = -1;
			while (onLoop == -1)
			{
				simulator->PlayRound();
				onLoop = simulator->EndRoundCalculations();

				if (onLoop == 1)
				{
					simulator->playerWins++;
					printf("\n Simulation [%d] WIN", i+1);
				}
				else if (onLoop == 0)
				{
					printf("\n Simulation [%d] LOSS", i+1);
				}
			}
			// We reset the entities for next loop
			simulator->entityManager->InitAll(simulator->simParameters->playerLevel);
			simulator->simParameters->ResetParameters();
			if(simulator->simParameters->useInventory) simulator->inventory->ResetInventory();
		}

		simulator->ResultsScreen();
	}
	system("cls");
	printf("\n Closing Program\n ");
	//delete simulator;
	system("pause");
	return 0;
}


