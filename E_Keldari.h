#pragma once
#include "Globals.h"
#include "Entity.h"
class Entity;
class E_Keldari : public Entity
{
public:
	E_Keldari() {};
	E_Keldari(const char* n) : name(n) {}

	void Draw();

	void Turn();
	void TurnM();

	const char* name = nullptr;
};