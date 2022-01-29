#pragma once
#include "Entity.h"
#include <vector>

class Entity;
class PlayerInventory;

class EntitiesManager
{
public:
	EntitiesManager();
	~EntitiesManager() {};

	void InitAll(int level);
	void PlayTurns(PlayerInventory* inventory);
	void PlayTurnsManual(PlayerInventory* inventory);
	void IncreaseSpeedAll();

	Entity* ReturnHighest(Entity* a, Entity* b, Entity* c, Entity* d, Entity* e);
	void DrawAll(Entity* a, Entity* b, Entity* c, Entity* d, Entity* e);

	void ResetEntitiesSpeed();

public:

	// All characters for the battle
	Entity* mainC = new Entity("Player");
	Entity* keldari = new Entity("Keldari");
	Entity* spiderA = new Entity("Spider A");
	Entity* spiderB = new Entity("Spider B");
	Entity* boss = new Entity("Boss");

	int playerLevel = 0;
};