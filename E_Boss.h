#pragma once
#include "Entity.h"


class E_Boss : public Entity
{
public:
	E_Boss() {};

	void Draw();

	void Turn();
	void TurnM();

};