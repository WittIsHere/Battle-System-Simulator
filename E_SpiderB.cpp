#include "E_SpiderB.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_SpiderB::Turn()
{
	EntitiesManager* manager = mySim->entityManager;

	if (health <= 0)
	{
		return;
	}
	if (onFire == true)
	{
		health -= INFLAME_DMG;
	}
	if (health <= 0)
	{
		return;
	}
	else if (stuned == true)
	{
		stuned = false;
		return;
	}


	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari


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
			//printf("\n spider B light attacks mainC");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * 0.8;
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

			manager->mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B light attacks keldari");

			totalDmg = attack + modifier;
			totalDmg = totalDmg * 0.9;
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
			manager->keldari->health -= totalDmg;
			break;
		}
		break;
	case 2:
		switch (target)
		{
		case 1:
			//printf("\n spider B heavy attacks mainC");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
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
			manager->mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B heavy attacks keldari");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
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
			manager->keldari->health -= totalDmg;
			break;
		}
		break;
	}
}

void E_SpiderB::TurnM()
{
	EntitiesManager* manager = mySim->entityManager;

	if (health <= 0)
	{
		printf("\n Spider B is dead!");
		onFire = false;
		return;
	}
	if (onFire)
	{
		printf("\n Spider B is on fire, taking %d damage", INFLAME_DMG);
		health -= INFLAME_DMG;
	}
	if (health <= 0)
	{
		printf("\n Spider B died to Inflame damage!");
		return;
	}
	if (stuned)
	{
		printf("\n Spider B is stuned, skipping turn");
		stuned = false;
		return;
	}

	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari


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
			printf("\n Spider B light attacks Main Character");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * 0.8;
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
				printf("\n Main Character Blocks the attack");
			}

			manager->mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		case 2:
			printf("\n Spider B light attacks Keldari");

			totalDmg = attack + modifier;
			totalDmg = totalDmg * 0.9;
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
		switch (target)
		{
		case 1:
			printf("\n Spider B heavy attacks Main Character");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
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
				printf("\n Main Character Blocks the attack");
			}
			manager->mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		case 2:
			printf("\n Spider B heavy attacks Keldari");
			totalDmg = attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
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
	}
}
