#include "E.Player.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_Player::Turn()
{
	if (health <= 0)
	{
		return;
	}

	// Initializing needed bools:

	bool allAlive = false;
	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	int target = -1; // 0 - Boss, 1 - SpiderA, 2 - SpiderB
	float finalDamage = 0;
	float dmgMitigation = 0;

	int action = -1;
	bool hasItems = true;
	bool hasMana = false;

	int safeAction = -1;

	if (this->mana >= SOUL_CHAIN_MANA)
	{
		hasMana = true;
	}
	if (simulator->inventory->hasHpPotion == false && simulator->inventory->hasManaPotion == false)
	{
		if (simulator->inventory->hasPlant == false) hasItems = false;
	}
	if (simulator->inventory->hasPlant == false)
	{
		if (this->mana <= 30 && this->health <= 40) hasItems = false;
	}

	// all of this so IA does not make dumb decisions.
	if (hasItems == true)
	{
		if (hasMana)
		{
			action = rand() % 4;
		}
		else
		{
			action = rand() % 4;
			if (action == 1)
			{
				safeAction = rand() % 3;
				switch (safeAction)
				{
				case 0:
					action = 0;
					break;
				case 1:
					action = 2;
					break;
				case 2:
					action = 3;
					break;
				}
			}
		}
	}
	else
	{
		if (hasMana)
		{
			action = rand() % 3;
		}
		else
		{
			action = rand() % 2;
			action = action * 2;
		}
	}
	if (simulator->inventory->testAttackOnly) action = 0;
	if (simulator->inventory->testExploit) action = 2;
	switch (action) // 0 - Attack, 1 - Special, 2 - Defend, 3 - Item
	{
	case 0:                                                                                       // --Attack--
		// We need to check which enemies are alive to determine the target
		//printf("\n MainC attacks ");
		if (simulator->entityManager->spiderA->isAlive == true && simulator->entityManager->spiderB->isAlive == true)
		{
			if (simulator->entityManager->boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (simulator->entityManager->boss->isAlive)
			{
				if (simulator->entityManager->spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (simulator->entityManager->spiderB->isAlive) // Boss and spiderB alive
				{
					target = rand() % 2; // 0 - 1
					if (target == 1) target = 2;
				}
				else // Only Boss alive
				{
					target = 0;
				}
			}
			else
			{
				if (simulator->entityManager->spiderA->isAlive == true && simulator->entityManager->spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (simulator->entityManager->spiderA->isAlive) // only spiderA alive
				{
					target = 1;
				}
				else // only spiderB alive
				{
					target = 2;
				}
			}
		}
		// Known the target now we need to determine the final damage

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= this->critChance) critSucces = true;

		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = this->attack + modifier;
		if (critSucces) finalDamage * 1.5;
		if (this->empowered) finalDamage* EXOTIC_PLANT_BUFF;

		switch (target)
		{
		case 0:
			//printf("Boss");
			dmgMitigation = finalDamage * (simulator->entityManager->boss->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->boss->health -= finalDamage;
			break;
		case 1:
			//printf("spider A");
			dmgMitigation = finalDamage * (simulator->entityManager->spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->spiderA->health -= finalDamage;
			break;
		case 2:
			//printf("spiderB");
			dmgMitigation = finalDamage * (simulator->entityManager->spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->spiderB->health -= finalDamage;
			break;
		}
		break;
	case 1:                                                                         // -- Special --
		this->mana -= SOUL_CHAIN_MANA;
		//printf("\n MainC uses soul chain on ");
		if (simulator->entityManager->spiderA->isAlive == true && simulator->entityManager->spiderB->isAlive == true)
		{
			if (simulator->entityManager->boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (simulator->entityManager->boss->isAlive)
			{
				if (simulator->entityManager->spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (simulator->entityManager->spiderB->isAlive) // Boss and spiderB alive
				{
					target = rand() % 2; // 0 - 1
					if (target == 1) target = 2;
				}
				else // Only Boss alive
				{
					target = 0;
				}
			}
			else
			{
				if (simulator->entityManager->spiderA->isAlive == true && simulator->entityManager->spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (simulator->entityManager->spiderA->isAlive) // only spiderA alive
				{
					target = 1;
				}
				else // only spiderB alive
				{
					target = 2;
				}
			}
		}
		switch (target)
		{
		case 0:
			//printf("Boss");
			simulator->entityManager->boss->stuned = true;
			break;
		case 1:
			//printf("spiderA");
			simulator->entityManager->spiderA->stuned = true;
			break;
		case 2:
			//printf("spiderB");
			simulator->entityManager->spiderB->stuned = true;
			break;
		}
		break;
	case 2:                                                                          // --Defend--
		//printf("\n mainC blocks");
		this->defending = true;
		break;
	case 3:                                                                          // --Item--
		//printf("\n mainC uses item ");
		if (this->mana <= 30 && simulator->inventory->hasManaPotion == true)
		{
			//printf("MP POT");
			this->mana += MP_POT_RECOVER;
			simulator->inventory->hasManaPotion = false;
		}
		else if (this->health <= 40 && simulator->inventory->hasHpPotion == true)
		{
			//printf("HP POT");
			this->health += HP_POT_RECOVER;
			simulator->inventory->hasHpPotion = false;
		}
		else if (simulator->inventory->hasPlant == true)
		{
			//printf("Plant");
			this->empowered = true;
			simulator->inventory->hasPlant = false;
		}
		break;
	}
}

void E_Player::TurnM()
{
	if (this->health <= 0)
	{
		printf("\n Main Character is dead!");
		return;
	}

	printf("\n It's Main Character Turn");
	printf("\n 1 - Attack");
	printf("\n 2 - Special");
	printf("\n 3 - Block");
	printf("\n 4 - Item");
	// Initializing needed bools:

	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	float finalDamage = 0;
	float dmgMitigation = 0;
	int target = 0;
	int itemAction = 0;

	int playerAction = 0;
	printf("\n\n Choose your action: ");
	scanf_s("%d", &playerAction);

	switch (playerAction) // 0 - Attack, 1 - Special, 2 - Defend, 3 - Item
	{
	case 1:                                                                                       // --Attack--
		// We need to check which enemies are alive to determine the target

		printf("\n You decide to attack!");
		printf("\n 1 - Attack Matriarch");
		printf("\n 2 - Attack Spider A");
		printf("\n 3 - Attack Spider B");
		printf("\n\n Choose your action: ");

		scanf_s("%d", &target);

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= this->critChance) critSucces = true;

		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = this->attack + modifier;
		if (critSucces) finalDamage * 1.5;
		if (this->empowered) finalDamage* EXOTIC_PLANT_BUFF;

		switch (target)
		{
		case 1:
			dmgMitigation = finalDamage * (simulator->entityManager->boss->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->boss->health -= finalDamage;
			printf("\n Main Character dealt %f damage to boss!", finalDamage);
			break;
		case 2:
			//printf("spider A");
			dmgMitigation = finalDamage * (simulator->entityManager->spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->spiderA->health -= finalDamage;
			printf("\n Main Character dealt %f damage to spider A!", finalDamage);
			break;
		case 3:
			//printf("spiderB");
			dmgMitigation = finalDamage * (simulator->entityManager->spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			simulator->entityManager->spiderB->health -= finalDamage;
			printf("\n Main Character dealt %f damage to spider B!", finalDamage);
			break;
		}
		break;
	case 2:                                                                         // -- Special --
		this->mana -= SOUL_CHAIN_MANA;
		//printf("\n MainC uses soul chain on ");
		printf("\n You decide to use Soul Chain!");
		printf("\n 1 - Target Matriarch");
		printf("\n 2 - Target Spider A");
		printf("\n 3 - Target Spider B");
		printf("\n\n Choose your action: ");

		scanf_s("%d", &target);

		switch (target)
		{
		case 1:
			//printf("Boss");
			simulator->entityManager->boss->stuned = true;
			printf("\n Boss is Stuned!");
			break;
		case 2:
			//printf("spiderA");
			simulator->entityManager->spiderA->stuned = true;
			printf("\n Spider A is Stuned!");
			break;
		case 3:
			//printf("spiderB");
			simulator->entityManager->spiderB->stuned = true;
			printf("\n Spider B is Stuned!");
			break;
		}
		break;
	case 3:                                                                          // --Defend--
		printf("\n You decide to Block!");
		this->defending = true;
		break;
	case 4:                                                                          // --Item--
		printf("\n Inventory");

		if (simulator->inventory->hasHpPotion == true)
		{
			printf("\n 1 - Health potion");
		}
		else
		{
			printf("\n 1 - You used your health potion");
		}
		if (simulator->inventory->hasManaPotion == true)
		{
			printf("\n 2 - Mana potion");
		}
		else
		{
			printf("\n 2 - You used your mana potion");
		}
		if (simulator->inventory->hasPlant == true)
		{
			printf("\n 3 - Exotic Plant");
		}
		else
		{
			printf("\n 3 - You used your exotic plant");
		}

		printf("\n\n Choose your action: ");
		scanf_s("%d", &itemAction);
		switch (itemAction)
		{
		case 1:
		{
			if (simulator->inventory->hasHpPotion == true)
			{

				printf("\n Using Health Potion on self");
				printf("\n %d Main Character HP restored", HP_POT_RECOVER);
				this->health += HP_POT_RECOVER;
				if (this->health >= 100)
				{
					this->health = 100;
				}
				simulator->inventory->hasHpPotion = false;
			}
			break;
		}
		case 2:
		{
			if (simulator->inventory->hasManaPotion == true)
			{
				printf("\n Using Mana Potion on self");
				printf("\n %d Main Character Mana restored", MP_POT_RECOVER);
				this->mana += MP_POT_RECOVER;
				if (this->mana >= 100)
				{
					this->mana = 100;
				}
				simulator->inventory->hasManaPotion = false;
			}
			break;
		}
		case 3:
		{
			if (simulator->inventory->hasPlant == true)
			{
				printf("\n Main Character ate the exotic plant");
				printf("\n You feel stronger, attack 2x");
				this->empowered = true;
				simulator->inventory->hasPlant = false;
			}
			break;
		}
		break;
		}
	}
}

