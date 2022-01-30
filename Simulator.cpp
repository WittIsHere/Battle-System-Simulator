#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));
#include <time.h>		// Required for function(s): srand(time(NULL));


Simulator::Simulator()
{

}

Simulator::~Simulator()
{
}

// MAIN PHASES
void Simulator::Init()
{
}

void Simulator::PlayRound()
{
	entityManager->ResetEntitiesSpeed();
	entityManager->PlayTurns();
}

void Simulator::PlayRoundManual()
{
	if (noRepeat == 0)
	{
		entityManager->DrawAll();
		noRepeat++;
	}
	entityManager->ResetEntitiesSpeed();
	entityManager->PlayTurnsManual();
}

int Simulator::EndRoundCalculations()
{
	// Checking the entities to see if they are dead or alive
	if (entityManager->mainC->health <= 0)
	{
		//printf("\n _mainC is dead");
		entityManager->mainC->isAlive = false;
	}

	if (entityManager->keldari->health <= 0)
	{
		//printf("\n _keldari is dead");
		entityManager->keldari->isAlive = false;
	}

	if (entityManager->spiderA->health <= 0)
	{
		//printf("\n _spider A is dead");
		entityManager->spiderA->isAlive = false;
	}

	if (entityManager->spiderB->health <= 0)
	{
		//printf("\n _spider B is dead");
		entityManager->spiderB->isAlive = false;
	}

	if (entityManager->boss->health <= 0)
	{
		//printf("\n _boss is dead");
		entityManager->boss->isAlive = false;
	}

	// Win or Loss Conditions
	if (entityManager->spiderA->isAlive == false && entityManager->spiderB->isAlive == false)
	{
		if (entityManager->boss->isAlive == false)
		{
			//printf("\n ------------------------------------ YOU WON ----------");
			return 1;
		}
	}
	if (entityManager->mainC->isAlive == false && entityManager->keldari->isAlive == false)
	{
		//printf("\n ------------------------------- GAME OVER ----------");
		return 0;
	}

	// So entities don't have negative hp
	if (entityManager->keldari->health <= 0)
	{
		entityManager->keldari->health = 0;
	}
	if (entityManager->spiderA->health <= 0)
	{
		entityManager->spiderA->health = 0;
	}
	if (entityManager->spiderB->health <= 0)
	{
		entityManager->spiderB->health = 0;
	}
	if (entityManager->boss->health <= 0)
	{
		entityManager->boss->health = 0;
	}

	return -1;
}

// UI
void Simulator::DrawTitle()
{
	printf("\n");
	printf("  ________  __                                                                            \n");
	printf(" /        |/  |                                                                           \n");
	printf(" $$$$$$$$/ $$ |____    ______                                                             \n");
	printf("    $$ |   $$         /                                                                   \n");
	printf("    $$ |   $$$$$$$  |/$$$$$$  |                                                           \n");
	printf("    $$ |   $$ |  $$ |$$    $$ |                                                           \n");
	printf("    $$ |   $$ |  $$ |$$$$$$$$/                                                            \n");
	printf("    $$ |   $$ |  $$ |$$       |                                                           \n");
	printf("    $$/    $$/   $$/  $$$$$$$/                                                            \n");

	printf("  _______                        __                  __                                   \n");
	printf(" /                              /  |                /  |                                  \n");
	printf(" $$$$$$$  | ______    ______   _$$ |_     ______   _$$ |_    __    __   ______    ______  \n");
	printf(" $$ |__$$ |/         /        / $$   |   /        / $$   |  /  |  /  | /         /        \n");
	printf(" $$    $$//$$$$$$  |/$$$$$$  |$$$$$$/   /$$$$$$  |$$$$$$/   $$ |  $$ |/$$$$$$  |/$$$$$$  |\n");
	printf(" $$$$$$$/ $$ |  $$/ $$ |  $$ |  $$ | __ $$ |  $$ |  $$ | __ $$ |  $$ |$$ |  $$ |$$    $$ |\n");
	printf(" $$ |     $$ |      $$  __$$ |  $$ |/  |$$  __$$ |  $$ |/  |$$  __$$ |$$ |__$$ |$$$$$$$$/ \n");
	printf(" $$ |     $$ |      $$    $$/   $$  $$/ $$    $$/   $$  $$/ $$    $$ |$$    $$/ $$       |\n");
	printf(" $$/      $$/        $$$$$$/     $$$$/   $$$$$$/     $$$$/   $$$$$$$ |$$$$$$$/   $$$$$$$/ \n");
	printf("                                                            /   __$$ |$$ |                \n");
	printf("                                                            $$    $$/ $$ |                \n");
	printf("                                                             $$$$$$/  $$/                 \n");

	printf("\n");
}

// SCREENS
void Simulator::TitleScreen()
{
	DrawTitle();

	printf(" This simulation system has been created for GAME DESIGN II delivery 2");
	printf("\n Done by: Arnau Lucena, Abraham Diaz and Aram Galarza \n\n ");

	system("pause");
	system("cls");
}

void Simulator::SecondScreen()
{
	printf("\n Welcome to the simulator");

	printf("\n\n Press 1 to start simulating");
	printf("\n\n Press 2 to play the battle");
	printf("\n\n Your choice: ");

	int startKey = ' ';
	scanf_s(" %d", &startKey);
	if (startKey == 1) playing = false;
	else if (startKey == 2) playing = true;
	else
	{
		system("cls");
		printf("\n Non valid option registred");
		SecondScreen();
	}
}

SimulationParameters Simulator::ConfigSimulation()
{
	SimulationParameters customP;

	printf("\n Choose the parameters:");

	printf(" Introduce the level of the party members (1 - 5): ");
	int startKey = ' ';
	scanf_s(" %d", &startKey);
	customP.playerLevel = startKey;

	printf("\n Introduce the number of iterations you want: ");
	int startKey2 = ' ';
	scanf_s(" %d", &startKey2);
	customP.nIterations = startKey2;

	return customP;
}

void Simulator::TestConfiguration()
{
	printf("\n Detect dominant strategy options:");
	printf("\n 1 - None");
	printf("\n 2 - Attack only");
	printf("\n 3 - Exploit (Inflame + perma block)");
	printf("\n Enter your choice: ");

	int startKey = ' ';
	scanf_s(" %d", &startKey);
	if (startKey == 2) inventory->testAttackOnly = true;
	else if (startKey == 3) inventory->testExploit = true;

}

int Simulator::BattlePresentation()
{
	printf("\n -- Welcome to the Matriarch BOSS figth --");
	printf("\n\n Adjusting the console window is adviced");
	printf("\n Please enter the level of your party: ");
	int startKey = ' ';
	scanf_s(" %d", &startKey);
	return startKey;
}

void Simulator::VictoryScreen()
{
	system("cls");
	//DrawAll(entityManager->mainC, entityManager->keldari, entityManager->banditA, entityManager->banditB);

	totalGold += rand() % 11 + 10;
	totalExp += rand() % 31 + 0;

	printf("\n\n You won the battle!");

	printf("\n\n Gold earned: %d", totalGold);
	printf("\n Experience granted: %d", totalExp);

	printf("\n ");

	system("pause");
}

void Simulator::LostScreen()
{
//	entityManager->mainC->health = 0;

	system("cls");
//	DrawAll(entityManager->mainC, entityManager->keldari, entityManager->banditA, entityManager->banditB);

	printf("You lost the battle!");

	printf("\n\n Gold earned: 0");
	printf("\n Experience granted: 0");

	printf("\n\n GAME OVER");

	printf("\n ");
	system("pause");
}

void Simulator::ResultsScreen()
{
	system("cls");
	printf("\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	printf("\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	printf("\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	printf("\n\n Results of the simulation:");

	printf("\n\n Number of iterations: %d", simParameters.nIterations);
	printf("\n Player wins: %d", playerWins);

	float percentWins = playerWins*100;
	percentWins = percentWins / simParameters.nIterations;
	printf("\n Player wins: %f", percentWins);
	
	printf("\n ");
	system("pause");
}
