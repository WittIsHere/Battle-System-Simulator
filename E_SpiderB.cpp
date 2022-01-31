#include "E_SpiderB.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_SpiderB::Turn()
{
	if (this->health <= 0)
	{
		return;
	}
	if (this->onFire == true)
	{
		this->health -= INFLAME_DMG;
	}
	if (this->health <= 0)
	{
		return;
	}
	else if (this->stuned == true)
	{
		this->stuned = false;
		return;
	}


	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari


	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= this->critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (simulator->entityManager->mainC->isAlive == false)
	{
		target = 2;
	}
	else if (simulator->entityManager->keldari->isAlive == false)
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
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * 0.8;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);

			if (simulator->entityManager->mainC->defending == true)
			{
				simulator->entityManager->mainC->defending = false;
				totalDmg = 0;
			}

			simulator->entityManager->mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B light attacks keldari");

			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * 0.9;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
			if (simulator->entityManager->keldari->defending == true)
			{
				simulator->entityManager->keldari->defending = false;
				totalDmg = 0;
			}
			simulator->entityManager->keldari->health -= totalDmg;
			break;
		}
		break;
	case 2:
		switch (target)
		{
		case 1:
			//printf("\n spider B heavy attacks mainC");
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);
			if (simulator->entityManager->mainC->defending == true)
			{
				simulator->entityManager->mainC->defending = false;
				totalDmg = 0;
			}
			simulator->entityManager->mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B heavy attacks keldari");
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
			if (simulator->entityManager->keldari->defending == true)
			{
				simulator->entityManager->keldari->defending = false;
				totalDmg = 0;
			}
			simulator->entityManager->keldari->health -= totalDmg;
			break;
		}
		break;
	}
}

void E_SpiderB::TurnM()
{
	if (this->health <= 0)
	{
		printf("\n Spider B is dead!");
		this->onFire = false;
		return;
	}
	if (this->onFire)
	{
		printf("\n Spider B is on fire, taking %d damage", INFLAME_DMG);
		this->health -= INFLAME_DMG;
	}
	if (this->health <= 0)
	{
		printf("\n Spider B died to Inflame damage!");
		return;
	}
	if (this->stuned)
	{
		printf("\n Spider B is stuned, skipping turn");
		this->stuned = false;
		return;
	}

	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari


	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= this->critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (simulator->entityManager->mainC->isAlive == false)
	{
		target = 2;
	}
	else if (simulator->entityManager->keldari->isAlive == false)
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
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * 0.8;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);

			if (simulator->entityManager->mainC->defending == true)
			{
				simulator->entityManager->mainC->defending = false;
				simulator->entityManager->mainC->
				totalDmg = 0;
				printf("\n Main Character Blocks the attack");
			}

			simulator->entityManager->mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		case 2:
			printf("\n Spider B light attacks Keldari");

			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * 0.9;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
			if (simulator->entityManager->keldari->defending == true)
			{
				simulator->entityManager->keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			simulator->entityManager->keldari->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		}
		break;
	case 2:
		switch (target)
		{
		case 1:
			printf("\n Spider B heavy attacks Main Character");
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);
			if (simulator->entityManager->mainC->defending == true)
			{
				simulator->entityManager->mainC->defending = false;
			
				totalDmg = 0;
				printf("\n Main Character Blocks the attack");
			}
			simulator->entityManager->mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		case 2:
			printf("\n Spider B heavy attacks Keldari");
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
			if (simulator->entityManager->keldari->defending == true)
			{
				simulator->entityManager->keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			simulator->entityManager->keldari->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		}
		break;
	}
}
