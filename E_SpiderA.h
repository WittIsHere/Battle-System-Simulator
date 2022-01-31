#pragma once
#include "Globals.h"
#include "Entity.h"


class E_SpiderA : public Entity
{
public:
	E_SpiderA() {};

	void Draw();

	void Turn();
	void TurnM();

};