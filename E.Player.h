#pragma once
#include "Globals.h"
#include "Entity.h"


class E_Player : public Entity
{
public:
	E_Player() {};

	void Draw();

	void Turn();
	void TurnM();
};