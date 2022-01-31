#pragma once
#include "Globals.h"
#include "Entity.h"
#include "E_Keldari.h"
#include "E_Boss.h"
#include "E_SpiderA.h"
#include "E_SpiderB.h"

class Entity;

class E_Player : public Entity
{
public:
	E_Player() {};
	E_Player(const char* n) : name(n) {}

	void Draw();

	void Turn();
	void TurnM();

	const char* name = nullptr;
};