#pragma once
#include "Globals.h"
#include "Entity.h"


class E_SpiderB : public Entity
{
public:
	E_SpiderB() {};

	void Draw();
	
	void Turn();
	void TurnM();

};