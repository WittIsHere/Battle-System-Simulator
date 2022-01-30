#pragma once
#include "Globals.h"
#include "Entity.h"

class Entity;
class E_SpiderA : public Entity
{
public:
	E_SpiderA() {};
	E_SpiderA(const char* n) : name(n) {}

	void Draw();

	void Turn();
	void TurnM();

	const char* name = nullptr;
};