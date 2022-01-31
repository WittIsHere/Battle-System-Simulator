#pragma once
#include "Globals.h"
#include "Entity.h"


class E_Keldari : public Entity
{
public:
	E_Keldari() {};

	void Draw();

	void Turn();
	void TurnM();

};