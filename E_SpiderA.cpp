#include "E_SpiderA.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_SpiderA::Turn()
{
	EntitiesManager* manager = mySim->entityManager;
	SimulationParameters* parameters = mySim->simParameters;
	AllModVars* myModVars = mySim->modVars;
	
	if (parameters->showInfo) printf("\n - Spider A Turn");

	if (health <= 0)
	{
		if (parameters->showInfo) printf("\n Spider A is Dead!");
		return;
	}
	if (onFire == true)
	{
		if (parameters->showInfo) printf("\n Spider A takes %d INFLAME DMG", myModVars->inflame_DMG);
		health -= myModVars->inflame_DMG;
	}
	if (health <= 0)
	{
		return;
	}
	else if (stuned == true)
	{
		if (parameters->showInfo) printf("\n Spider A is Stuned!");
		stuned = false;
		return;
	}


	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	if (mana <= myModVars->double_Lunge_MANA) attackChoosen = 1;
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
	float dmgMitigation = 0;

	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (manager->mainC->isAlive == false)
	{
		target = 2;
	}
	else if (manager->keldari->isAlive == false)
	{
		target = 1;
	}

	switch (attackChoosen)
	{
	case 1:
		switch (target)
		{
		case 1:
			if (parameters->showInfo) printf("\n Spider B attacks main character");
			totalDmg = attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (manager->mainC->defense) / 100);

			if (manager->mainC->defending == true)
			{
				manager->mainC->defending = false;
				totalDmg = 0;
			}
			if (parameters->showInfo) printf("\n Dealing %d damage", totalDmg);
			manager->mainC->health -= totalDmg;

			break;
		case 2:
			if (parameters->showInfo) printf("\n Spder A attacks Keldari");
			totalDmg = attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (manager->keldari->defense) / 100);
			if (manager->keldari->defending == true)
			{
				manager->keldari->defending = false;
				totalDmg = 0;
			}
			if (parameters->showInfo) printf("\n Dealing %d damage", totalDmg);
			manager->keldari->health -= totalDmg;
			break;
		}
		break;
	case 2:
		if (parameters->showInfo) printf("\n Spider A uses DOUBLE LUNGE");
		mana -= myModVars->double_Lunge_MANA;

		totalDmg = myModVars->double_Lunge_DMG + modifier;
		dmgMitigation = (totalDmg * (manager->mainC->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		if (parameters->showInfo) printf("\n Dealing %d damage to main character", totalDmg);
		manager->mainC->health -= totalDmg;

		totalDmg = myModVars->double_Lunge_DMG + modifier;
		dmgMitigation = (totalDmg * (manager->keldari->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		if (parameters->showInfo) printf("\n Dealing %d damage to Keldari", totalDmg);
		manager->keldari->health -= totalDmg;
		break;
	}
}

void E_SpiderA::TurnM()
{
	EntitiesManager* manager = mySim->entityManager;
	AllModVars* myModVars = mySim->modVars;

	if (health <= 0)
	{
		printf("\n Spider A is dead!");
		onFire = false;
		return;
	}
	if (onFire)
	{
		printf("\n Spider A is on fire, taking %d damage", myModVars->inflame_DMG);
		health -= myModVars->inflame_DMG;
	}
	if (health <= 0)
	{
		printf("\n Spider A died to Inflame damage!");
		return;
	}
	if (stuned)
	{
		printf("\n Spider A is stuned, skipping turn");
		stuned = false;
		return;
	}

	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	if (mana <= myModVars->double_Lunge_MANA) attackChoosen = 1;
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
	float dmgMitigation = 0;

	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (manager->mainC->isAlive == false)
	{
		target = 2;
	}
	else if (manager->keldari->isAlive == false)
	{
		target = 1;
	}

	switch (attackChoosen)
	{
	case 1:
		switch (target)
		{
		case 1:
			printf("\n Spider A attacks main character");
			totalDmg = attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (manager->mainC->defense) / 100);

			if (manager->mainC->defending == true)
			{
				manager->mainC->defending = false;
				totalDmg = 0;
				printf("\n Main Character blocks the attack");
			}

			manager->mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		case 2:
			printf("\n Spider A attacks Keldari");
			totalDmg = attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (manager->keldari->defense) / 100);
			if (manager->keldari->defending == true)
			{
				manager->keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			manager->keldari->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		}
		break;
	case 2:
		printf("\n spider A uses Double Lunge");
		mana -= myModVars->double_Lunge_MANA;

		totalDmg = myModVars->double_Lunge_DMG + modifier;
		dmgMitigation = (totalDmg * (manager->mainC->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		manager->mainC->health -= totalDmg;
		printf("\n Deals %d to Main Character", totalDmg);
		totalDmg = myModVars->double_Lunge_DMG + modifier;
		dmgMitigation = (totalDmg * (manager->keldari->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		manager->keldari->health -= totalDmg;
		printf(" and %d to Keldari", totalDmg);
		break;
	}
}
