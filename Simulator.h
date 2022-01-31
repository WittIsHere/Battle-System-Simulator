#pragma once
#include "EntitiesManager.h"
#include "Modificable.h"

class SimulationParameters
{
public:
	void ResetParameters() { exploitInt = 0; }

	int playerLevel = 0;
	int nIterations = 0;


	bool testAttackOnly = false;
	bool testExploit = false;
	int exploitInt = 0;

	bool useInventory = false;
	bool showInfo = false;
};

class PlayerInventory
{
public:
	PlayerInventory() { hasManaPotion = true; hasHpPotion = true; hasPlant = true; }

	void ResetInventory() { hasManaPotion = true; hasHpPotion = true; hasPlant = true; }

	bool hasManaPotion = true;
	bool hasHpPotion = true;
	bool hasPlant = true;

};

class EntitiesManager;
class AllModVars;

class Simulator
{
public:
	Simulator();
	~Simulator();

	void Init();
	void PlayRound();
	void PlayRoundManual();

	int EndRoundCalculations();

	// UI
	void DrawTitle();

	// Screens
	void TitleScreen();
	void SecondScreen();
	void ConfigSimulation();
	void TestConfiguration();
	int BattlePresentation();
	void VictoryScreen();
	void LostScreen();
	void ResultsScreen();

public:
	EntitiesManager* entityManager = new EntitiesManager;
	SimulationParameters* simParameters = new SimulationParameters;
	PlayerInventory* inventory = new PlayerInventory;
	AllModVars* modVars = new AllModVars;

	bool playing = 0;


	// global vars
	int totalGold = 0;
	int totalExp = 0;
	
	int playerWins = 0;

	int noRepeat = 0;
};