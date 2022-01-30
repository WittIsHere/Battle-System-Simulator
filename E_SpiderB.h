#pragma once
#include "Globals.h"
#include "Entity.h"
class Entity;
class E_SpiderB : public Entity
{
public:
	E_SpiderB() {};
	E_SpiderB(const char* n) : name(n) {}

	void Draw();
	
	void Turn();
	void TurnM();

	const char* name = nullptr;
};