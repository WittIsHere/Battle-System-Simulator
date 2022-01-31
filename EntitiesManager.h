#pragma once
#include "Entity.h"
#include "E.Player.h"
#include "E_Keldari.h"
#include "E_Boss.h"
#include "E_SpiderA.h"
#include "E_SpiderB.h"

#include <vector>


class EntitiesManager
{
public:
	EntitiesManager();
	~EntitiesManager() { delete this; };

	void InitAll(int level);
	void PlayTurns();
	void PlayTurnsManual();
	void IncreaseSpeedAll();

	Entity* ReturnHighest();
	void DrawAll();

	void ResetEntitiesSpeed();

	void SetSimulator(Simulator* sim);

public:

	Simulator* mySim = nullptr;

	// All characters for the battle
	E_Player* mainC = new E_Player();
	E_Keldari* keldari = new E_Keldari();
	E_Boss* boss = new E_Boss();
	E_SpiderA* spiderA = new E_SpiderA();
	E_SpiderB* spiderB = new E_SpiderB();

	int playerLevel = 0;
};