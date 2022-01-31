#include "Entity.h"
#include "Simulator.h"
#include "Globals.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));
#include <time.h>		// Required for function(s): srand(time(NULL));



void Entity::Draw(bool first)
{
	if (first == true)
	{
		printf("\n -> %s <- \n", name);

		printf("    Health: %d \n", health);


		if (magicType != 0)
		{
			printf("    Mana: %d \n", mana);
		}
		if (health > 0)
		{
			if (empowered == true)
			{
				printf("    Empowered\n");
			}
			if (onFire == true)
			{
				printf("    On fire\n");
			}
			if (stuned == true)
			{
				printf("    Stuned\n");
			}
			if (defending == true)
			{
				printf("    Defending\n");
			}
		}
		else
		{
			printf("    Dead\n");
		}
	}
	else
	{
		printf("\n %s \n", name);

		printf(" Health: %d \n", health);

		if (magicType != 0)
		{
			printf(" Mana: %d \n", mana);
		}

		if (health > 0)
		{
			if (empowered == true)
			{
				printf(" Empowered\n");
			}
			if (onFire == true)
			{
				printf(" On fire\n");
			}
			if (stuned == true)
			{
				printf(" Stuned\n");
			}
			if (defending == true)
			{
				printf(" Defending\n");
			}
		}
		else
		{
			printf(" Dead\n");
		}
	}

}

void Entity::Turn()
{
}

void Entity::TurnM()
{
}

void Entity::operator=(const Entity& a)
{
	name = a.name;
	health = a.health;
	baseHP = a.baseHP;
	baseSpeed = a.baseSpeed;
	isAlive = a.isAlive;
	mana = a.mana;
	speed = a.speed;
	onFire = a.onFire;
	stuned = a.stuned;
	empowered = a.empowered;
	magicType = a.magicType;
	defending = a.defending;
}

void Entity::SetSimulator(Simulator* sim)
{
	mySim = sim;
}


