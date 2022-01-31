#pragma once
#include "Globals.h"
#include "Entity.h"

class Entity;

class E_Boss : public Entity
{
public:
	E_Boss() {};
	E_Boss(const char* n) : name(n) {}

	void Draw();

	void Turn();
	void TurnM();

	const char* name = nullptr;
};