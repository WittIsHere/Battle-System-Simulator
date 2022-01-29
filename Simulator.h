#pragma once
#include "EntitiesManager.h"

struct SimulationParameters
{
	int playerLevel;
	int nIterations;
};

class PlayerInventory
{
public:
	PlayerInventory() { hasManaPotion = true; hasHpPotion = true; hasPlant = true; }

	void ResetInventory() { hasManaPotion = true; hasHpPotion = true; hasPlant = true; exploitInt = 0; }

	bool hasManaPotion = true;
	bool hasHpPotion = true;
	bool hasPlant = true;

	bool testAttackOnly = false;
	bool testExploit = false;
	int exploitInt = 0;
};

class EntitiesManager;

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
	SimulationParameters ConfigSimulation();
	void TestConfiguration();
	int BattlePresentation();
	void VictoryScreen();
	void LostScreen();
	void ResultsScreen();

public:
	EntitiesManager* entityManager = new EntitiesManager;
	SimulationParameters simParameters = {};
	PlayerInventory* inventory = new PlayerInventory;

	bool playing = 0;


	// global vars
	int totalGold = 0;
	int totalExp = 0;
	
	int playerWins = 0;

	int noRepeat = 0;
};