#include "E.Player.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));

void E_Player::Turn()
{
	EntitiesManager* manager = mySim->entityManager;
	PlayerInventory* inventory = mySim->inventory;
	SimulationParameters* parameters = mySim->simParameters;

	if (parameters->showInfo) printf("\n - Main Character Turn");

	if (health <= 0)
	{
		if (parameters->showInfo) printf("\n Main character is Dead!");
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

	if (mana >= SOUL_CHAIN_MANA)
	{
		hasMana = true;
	}
	if (inventory->hasHpPotion == false && inventory->hasManaPotion == false)
	{
		if (inventory->hasPlant == false) hasItems = false;
	}
	if (inventory->hasPlant == false)
	{
		if (mana <= 30 && health <= 40) hasItems = false;
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
	if (parameters->testExploit) action = 2;
	if (parameters->testAttackOnly) action = 0;
	switch (action) // 0 - Attack, 1 - Special, 2 - Defend, 3 - Item
	{
	case 0:                                                                                       // --Attack--
		// We need to check which enemies are alive to determine the target
		if (parameters->showInfo) printf("\n Main character attacks ");
		if (manager->spiderA->isAlive == true && manager->spiderB->isAlive == true)
		{
			if (manager->boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (manager->boss->isAlive)
			{
				if (manager->spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (manager->spiderB->isAlive) // Boss and spiderB alive
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
				if (manager->spiderA->isAlive == true && manager->spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (manager->spiderA->isAlive) // only spiderA alive
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
		if (critGen <= critChance) critSucces = true;

		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = attack + modifier;
		if (critSucces) finalDamage * 1.5;
		if (empowered) finalDamage* EXOTIC_PLANT_BUFF;

		switch (target)
		{
		case 0:
			if (parameters->showInfo) printf("Boss");
			dmgMitigation = finalDamage * (manager->boss->defense / 100);
			finalDamage -= dmgMitigation;
			if (parameters->showInfo) printf("\n Dealing a total of %f damage", finalDamage);
			manager->boss->health -= finalDamage;
			break;
		case 1:
			if (parameters->showInfo) printf("Spider A");
			dmgMitigation = finalDamage * (manager->spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			if (parameters->showInfo) printf("\n Dealing a total of %f damage", finalDamage);
			manager->spiderA->health -= finalDamage;
			break;
		case 2:
			if (parameters->showInfo) printf("Spider B");
			dmgMitigation = finalDamage * (manager->spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			if (parameters->showInfo) printf("\n Dealing a total of %f damage", finalDamage);
			manager->spiderB->health -= finalDamage;
			break;
		}
		break;
	case 1:                                                                         // -- Special --
		mana -= SOUL_CHAIN_MANA;
		if (parameters->showInfo) printf("\n Main character uses SOUL CHAIN on ");
		if (manager->spiderA->isAlive == true && manager->spiderB->isAlive == true)
		{
			if (manager->boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (manager->boss->isAlive)
			{
				if (manager->spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (manager->spiderB->isAlive) // Boss and spiderB alive
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
				if (manager->spiderA->isAlive == true && manager->spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (manager->spiderA->isAlive) // only spiderA alive
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
			if (parameters->showInfo) printf("Boss");
			manager->boss->stuned = true;
			break;
		case 1:
			if (parameters->showInfo) printf("Spider A");
			manager->spiderA->stuned = true;
			break;
		case 2:
			if (parameters->showInfo) printf("Spider B");
			manager->spiderB->stuned = true;
			break;
		}
		break;
	case 2:                                                                          // --Defend--
		if (parameters->showInfo) printf("\n Main character defends");
		defending = true;
		break;
	case 3:                                                                          // --Item--
		if (parameters->showInfo) printf("\n Main character uses ");
		if (mana <= 30 && inventory->hasManaPotion == true)
		{
			if (parameters->showInfo) printf("MP potion");
			mana += MP_POT_RECOVER;
			inventory->hasManaPotion = false;
		}
		else if (health <= 40 && inventory->hasHpPotion == true)
		{
			if (parameters->showInfo) printf("HP potion");
			health += HP_POT_RECOVER;
			inventory->hasHpPotion = false;
		}
		else if (inventory->hasPlant == true)
		{
			if (parameters->showInfo) printf("Exotic Plant");
			empowered = true;
			inventory->hasPlant = false;
		}
		break;
	}
}

void E_Player::TurnM()
{
	EntitiesManager* manager = mySim->entityManager;
	PlayerInventory* inventory = mySim->inventory;

	if (health <= 0)
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
		if (critGen <= critChance) critSucces = true;

		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = this->attack + modifier;
		if (critSucces) finalDamage * 1.5;
		if (empowered) finalDamage* EXOTIC_PLANT_BUFF;

		switch (target)
		{
		case 1:
			dmgMitigation = finalDamage * (manager->boss->defense / 100);
			finalDamage -= dmgMitigation;
			manager->boss->health -= finalDamage;
			printf("\n Main Character dealt %f damage to boss!", finalDamage);
			break;
		case 2:
			//printf("spider A");
			dmgMitigation = finalDamage * (manager->spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			manager->spiderA->health -= finalDamage;
			printf("\n Main Character dealt %f damage to spider A!", finalDamage);
			break;
		case 3:
			//printf("spiderB");
			dmgMitigation = finalDamage * (manager->spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			manager->spiderB->health -= finalDamage;
			printf("\n Main Character dealt %f damage to spider B!", finalDamage);
			break;
		}
		break;
	case 2:                                                                         // -- Special --
		mana -= SOUL_CHAIN_MANA;
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
			manager->boss->stuned = true;
			printf("\n Boss is Stuned!");
			break;
		case 2:
			//printf("spiderA");
			manager->spiderA->stuned = true;
			printf("\n Spider A is Stuned!");
			break;
		case 3:
			//printf("spiderB");
			manager->spiderB->stuned = true;
			printf("\n Spider B is Stuned!");
			break;
		}
		break;
	case 3:                                                                          // --Defend--
		printf("\n You decide to Block!");
		defending = true;
		break;
	case 4:                                                                          // --Item--
		printf("\n Inventory");

		if (inventory->hasHpPotion == true)
		{
			printf("\n 1 - Health potion");
		}
		else
		{
			printf("\n 1 - You used your health potion");
		}
		if (inventory->hasManaPotion == true)
		{
			printf("\n 2 - Mana potion");
		}
		else
		{
			printf("\n 2 - You used your mana potion");
		}
		if (inventory->hasPlant == true)
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
			if (inventory->hasHpPotion == true)
			{

				printf("\n Using Health Potion on self");
				printf("\n %d Main Character HP restored", HP_POT_RECOVER);
				health += HP_POT_RECOVER;
				if (health >= 100)
				{
					health = 100;
				}
				inventory->hasHpPotion = false;
			}
			break;
		}
		case 2:
		{
			if (inventory->hasManaPotion == true)
			{
				printf("\n Using Mana Potion on self");
				printf("\n %d Main Character Mana restored", MP_POT_RECOVER);
				mana += MP_POT_RECOVER;
				if (mana >= 100)
				{
					mana = 100;
				}
				inventory->hasManaPotion = false;
			}
			break;
		}
		case 3:
		{
			if (inventory->hasPlant == true)
			{
				printf("\n Main Character ate the exotic plant");
				printf("\n You feel stronger, attack 2x");
				empowered = true;
				inventory->hasPlant = false;
			}
			break;
		}
		break;
		}
	}
}

