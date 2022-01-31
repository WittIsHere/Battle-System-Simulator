#include "E_Boss.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_Boss::Turn()
{
	EntitiesManager* manager = mySim->entityManager;
	SimulationParameters* parameters = mySim->simParameters;

	if (parameters->showInfo) printf("\n - Boss Turn");

	if (health <= 0)
	{
		if (parameters->showInfo) printf("\n Boss is Dead!");
		return;
	}
	if (onFire)
	{
		if (parameters->showInfo) printf("\n Boss takes %d INFLAME DAMAGE", INFLAME_DMG);
		health -= INFLAME_DMG;
	}
	if (health <= 0)
	{
		return;
	}
	if (stuned)
	{
		if (parameters->showInfo) printf("\n Boss is stuned!");
		stuned = false;
		return;
	}

	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	int target = -1; // 0 - mainC, 1 - Keldari
	float finalDamage = 0;
	float dmgMitigation = 0;

	bool forceHeal = false;
	float actualHP = manager->spiderA->health + manager->spiderB->health;
	float minHP = manager->spiderA->baseHP + manager->spiderB->baseHP;
	minHP = minHP * 0.5;

	if (actualHP < minHP)
	{
		forceHeal = true;
	}

	if ((forceHeal == true) && (mana >= MATRIARCH_BREATH_MANA))
	{
		if (parameters->showInfo) printf("\n Boss heals %d to its allies", MATRIARCH_BREATH_RECOVER);
		mana -= MATRIARCH_BREATH_MANA;
		manager->spiderA->health += MATRIARCH_BREATH_RECOVER;
		manager->spiderB->health += MATRIARCH_BREATH_RECOVER;
	}
	else
	{
		if (parameters->showInfo) printf("\n Boss attacks ");
		if (manager->mainC->isAlive && manager->keldari->isAlive)
		{
			target = rand() % 2;
		}
		else if (manager->mainC->isAlive)
		{
			target = 0;
		}
		else
		{
			target = 1;
		}

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= critChance) critSucces = true;
		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = attack + modifier;
		if (critSucces) finalDamage * 1.5;


		switch (target)
		{
		case 0:
			if (parameters->showInfo) printf("main character");
			dmgMitigation = finalDamage * (manager->mainC->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			if (parameters->showInfo) printf("\n Dealing a total of %f damage", finalDamage);
			manager->mainC->health -= finalDamage;
			break;
		case 1:
			if (parameters->showInfo) printf("Keldari");
			dmgMitigation = finalDamage * (manager->keldari->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			if (parameters->showInfo) printf("\n Dealing a total of %f damage", finalDamage);
			manager->keldari->health -= finalDamage;
			break;
		}
	}
}

void E_Boss::TurnM()
{
	EntitiesManager* manager = mySim->entityManager;

	if (health <= 0)
	{
		printf("\n Boss is dead!");
		onFire = false;
		return;
	}
	if (onFire)
	{
		printf("\n Boss is on fire, taking %d damage", INFLAME_DMG);
		health -= INFLAME_DMG;
	}
	if (health <= 0)
	{
		printf("\n Boss died to Inflame damage!");
		return;
	}
	if (stuned)
	{
		printf("\n Boss is stuned, skipping turn");
		stuned = false;
		return;
	}

	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	int target = -1; // 0 - mainC, 1 - Keldari
	float finalDamage = 0;
	float dmgMitigation = 0;

	bool forceHeal = false;
	float actualHP = manager->spiderA->health + manager->spiderB->health;
	float minHP = manager->spiderA->baseHP + manager->spiderB->baseHP;
	minHP = minHP * 0.5;

	if (actualHP < minHP)
	{
		forceHeal = true;
	}

	if ((forceHeal == true) && (mana >= MATRIARCH_BREATH_MANA))
	{
		printf("\n BOSS heals %d to the minions...", MATRIARCH_BREATH_RECOVER);
		mana -= MATRIARCH_BREATH_MANA;
		manager->spiderA->health += MATRIARCH_BREATH_RECOVER;
		manager->spiderB->health += MATRIARCH_BREATH_RECOVER;
	}
	else
	{
		printf("\n BOSS attacks ");
		if (manager->mainC->isAlive && manager->keldari->isAlive)
		{
			target = rand() % 2;
		}
		else if (manager->mainC->isAlive)
		{
			target = 0;
		}
		else
		{
			target = 1;
		}

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= critChance) critSucces = true;
		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = attack + modifier;
		if (critSucces) finalDamage * 1.5;


		switch (target)
		{
		case 0:
			printf("Main character");
			dmgMitigation = finalDamage * (manager->mainC->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			manager->mainC->health -= finalDamage;
			if (critSucces)printf("\n Critical Strike!!");
			printf("\n Dealing %f damage", finalDamage);
			break;
		case 1:
			printf("Keldari");
			dmgMitigation = finalDamage * (manager->keldari->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			manager->keldari->health -= finalDamage;
			if (critSucces)printf("\n Critical Strike!!");
			printf("\n Dealing %f damage", finalDamage);
			break;
		}
	}
}
