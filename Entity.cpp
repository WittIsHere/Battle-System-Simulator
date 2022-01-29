#include "Entity.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));
#include <time.h>		// Required for function(s): srand(time(NULL));

#define SOUL_CHAIN_MANA 30
#define INFLAME_MANA 80
#define INFLAME_DMG 20

#define DOUBLE_LUNGE_MANA 50
#define DOUBLE_LUNGE_DMG 40
#define STRONG_ATTACK_MOD 1.5
#define MATRIARCH_BREATH_MANA 30
#define MATRIARCH_BREATH_RECOVER 20

#define HP_POT_RECOVER 50
#define MP_POT_RECOVER 50
#define EXOTIC_PLANT_BUFF 2

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

// FUNCTIONS FOR SIMULATION MODE

void Entity::Update(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
{	
	if (this->myType == TYPE::MC)
	{
		//printf("\n - It is mainC Turn");
		MainCTurn(keldari, spiderA, spiderB, boss, inventory);
	}
	else if (this->myType == TYPE::KELDARI)
	{
		//printf("\n - It is Keldari Turn");
		KeldariTurn(mainC, spiderA, spiderB, boss, inventory);
	}
	else if (this->myType == TYPE::BOSS)
	{
		//printf("\n - It is BOSS Turn");
		BossTurn(mainC, keldari, spiderA, spiderB);
	}
	else if (this->myType == TYPE::SPIDER_A)
	{
		//printf("\n - It is SPIDER A Turn");
		SpiderATurn(mainC, keldari);
	}
	else if (this->myType == TYPE::SPIDER_B)
	{
		//printf("\n - It is SPIDER B Turn");
		SpiderBTurn(mainC, keldari);
	}

	this->EndTurn();
}

void Entity::MainCTurn(Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
{
	if (this->health <= 0)
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
	if (inventory->hasHpPotion == false && inventory->hasManaPotion == false)
	{
		if (inventory->hasPlant == false) hasItems = false;
	}
	if (inventory->hasPlant == false)
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
	if (inventory->testAttackOnly) action = 0;
	if (inventory->testExploit) action = 2;
	switch (action) // 0 - Attack, 1 - Special, 2 - Defend, 3 - Item
	{
	case 0:                                                                                       // --Attack--
		// We need to check which enemies are alive to determine the target
		//printf("\n MainC attacks ");
		if (spiderA->isAlive == true && spiderB->isAlive == true)
		{
			if (boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (boss->isAlive)
			{
				if (spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (spiderB->isAlive) // Boss and spiderB alive
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
				if (spiderA->isAlive == true && spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (spiderA->isAlive) // only spiderA alive
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
		if (this->empowered) finalDamage * EXOTIC_PLANT_BUFF;

		switch (target)
		{
		case 0:
			//printf("Boss");
			dmgMitigation = finalDamage * (boss->defense / 100);
			finalDamage -= dmgMitigation;
			boss->health -= finalDamage;
			break;
		case 1:
			//printf("spider A");
			dmgMitigation = finalDamage * (spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			spiderA->health -= finalDamage;
			break;
		case 2:
			//printf("spiderB");
			dmgMitigation = finalDamage * (spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			spiderB->health -= finalDamage;
			break;
		}
		break;
	case 1:                                                                         // -- Special --
		this->mana -= SOUL_CHAIN_MANA;
		//printf("\n MainC uses soul chain on ");
		if (spiderA->isAlive == true && spiderB->isAlive == true)
		{
			if (boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (boss->isAlive)
			{
				if (spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (spiderB->isAlive) // Boss and spiderB alive
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
				if (spiderA->isAlive == true && spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (spiderA->isAlive) // only spiderA alive
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
			boss->stuned = true;
			break;
		case 1:
			//printf("spiderA");
			spiderA->stuned = true;
			break;
		case 2:
			//printf("spiderB");
			spiderB->stuned = true;
			break;
		}
		break;
	case 2:                                                                          // --Defend--
		//printf("\n mainC blocks");
		this->defending = true;
		break;
	case 3:                                                                          // --Item--
		//printf("\n mainC uses item ");
		if (this->mana <= 30 && inventory->hasManaPotion == true)
		{
			//printf("MP POT");
			this->mana += MP_POT_RECOVER;
			inventory->hasManaPotion = false;
		}
		else if (this->health <= 40 && inventory->hasHpPotion == true)
		{
			//printf("HP POT");
			this->health += HP_POT_RECOVER;
			inventory->hasHpPotion = false;
		}
		else if (inventory->hasPlant == true)
		{
			//printf("Plant");
			this->empowered = true;
			inventory->hasPlant = false;
		}
		break;
	}
}

void Entity::KeldariTurn(Entity* mainc, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
{
	if (this->health <= 0)
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

	if (this->mana >= INFLAME_MANA)
	{
		hasMana = true;
	}
	if (inventory->hasHpPotion == false && inventory->hasManaPotion == false)
	{
		if (inventory->hasPlant == false) hasItems = false;
	}
	if (inventory->hasPlant == false)
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
	if (inventory->testAttackOnly) action = 0;
	if (inventory->testExploit)
	{
		if (inventory->exploitInt == 0)
		{
			action = 1;
			inventory->exploitInt++;
		}
		else
		{
			action = 2;
		}
	}

	switch (action) // 0 - Attack, 1 - Special, 2 - Defend, 3 - Item
	{
	case 0:                                                                                       // --Attack--
		// We need to check which enemies are alive to determine the target
		//printf("\n Keldari attacks ");
		if (spiderA->isAlive == true && spiderB->isAlive == true)
		{
			if (boss->isAlive) allAlive = true;
			else allAlive = false;
		}
		if (allAlive == true) // all alive
		{
			target = rand() % 3; // 0 - 2
		}
		else
		{
			if (boss->isAlive)
			{
				if (spiderA->isAlive) // Boss and spiderA alive
				{
					target = rand() % 2; // 0 - 1
				}
				else if (spiderB->isAlive) // Boss and spiderB alive
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
				if (spiderA->isAlive == true && spiderB->isAlive == true) // spiderA and spiderB alive
				{
					target = rand() % 1 + 1; // 1 - 2
				}
				else if (spiderA->isAlive) // only spiderA alive
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
			//printf("boss");
			dmgMitigation = finalDamage * (boss->defense / 100);
			finalDamage -= dmgMitigation;
			boss->health -= finalDamage;
			break;
		case 1:
			//printf("spider A");
			dmgMitigation = finalDamage * (spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			spiderA->health -= finalDamage;
			break;
		case 2:
			//printf("spider B");
			dmgMitigation = finalDamage * (spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			spiderB->health -= finalDamage;
			break;
		}
		break;
	case 1:                                                                         // -- Special --
		//printf("\n Keldari uses Inflame");
		this->mana -= INFLAME_MANA;
		boss->onFire = true;
		spiderA->onFire = true;
		spiderB->onFire = true;
		break;
	case 2:                                                                          // --Defend--
		//printf("\n Keldari blocks");
		this->defending = true;
		break;
	case 3:                                                                          // --Item--
		//printf("\n Keldari uses item ");
		if (this->mana <= 30 && inventory->hasManaPotion == true)
		{
			//printf("MP pot");
			this->mana += MP_POT_RECOVER;
			inventory->hasManaPotion = false;
		}
		else if (this->health <= 40 && inventory->hasHpPotion == true)
		{
			//printf("HP pot");
			this->health += HP_POT_RECOVER;
			inventory->hasHpPotion = false;
		}
		else if (inventory->hasPlant == true)
		{
			//printf("Plant");
			this->empowered = true;
			inventory->hasPlant = false;
		}
		break;
	}
}

void Entity::BossTurn(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB)
{
	if (this->health <= 0)
	{
		return;
	}
	if (this->onFire)
	{
		this->health -= INFLAME_DMG;
	}
	if (this->health <= 0)
	{
		return;
	}
	if (this->stuned)
	{
		this->stuned = false;
		return;
	}

	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	int target = -1; // 0 - mainC, 1 - Keldari
	float finalDamage = 0;
	float dmgMitigation = 0;

	bool forceHeal = false;
	float actualHP = spiderA->health + spiderB->health;
	float minHP = spiderA->baseHP + spiderB->baseHP;
	minHP = minHP * 0.5;

	if (actualHP < minHP)
	{
		forceHeal = true;
	}

	if ((forceHeal == true) && (this->mana >= MATRIARCH_BREATH_MANA))
	{
		//printf("\n BOSS heals");
		this->mana -= MATRIARCH_BREATH_MANA;
		spiderA->health += MATRIARCH_BREATH_RECOVER;
		spiderB->health += MATRIARCH_BREATH_RECOVER;
	}
	else
	{
		//printf("\n BOSS attacks ");
		if (mainC->isAlive && keldari->isAlive)
		{
			target = rand() % 2;
		}
		else if (mainC->isAlive)
		{
			target = 0;
		}
		else
		{
			target = 1;
		}

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= this->critChance) critSucces = true;
		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = this->attack + modifier;
		if (critSucces) finalDamage * 1.5;

		
		switch (target)
		{
		case 0:
			//printf("mainC");
			dmgMitigation = finalDamage * (mainC->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			mainC->health -= finalDamage;
			break;
		case 1:
			//printf("keldari");
			dmgMitigation = finalDamage * (keldari->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			keldari->health -= finalDamage;
			break;
		}
	}
}

void Entity::SpiderATurn(Entity* mainC, Entity* keldari)
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
	if (this->mana <= DOUBLE_LUNGE_MANA) attackChoosen = 1;
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
	float dmgMitigation = 0;

	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= this->critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (mainC->isAlive == false)
	{
		target = 2;
	}
	else if (keldari->isAlive == false)
	{
		target = 1;
	}

	switch (attackChoosen)
	{
	case 1:
		switch (target)
		{
		case 1:
			//printf("\n spider A attacks mainC");
			totalDmg = this->attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);

			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
			}

			mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider A attacks keldari");
			totalDmg = this->attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
			}
			keldari->health -= totalDmg;
			break;
		}
		break;
	case 2:
		//printf("\n spider A uses Double Lunge");
		this->mana -= DOUBLE_LUNGE_MANA;

		totalDmg = DOUBLE_LUNGE_DMG + modifier;
		dmgMitigation = (totalDmg * (mainC->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		mainC->health -= totalDmg;

		totalDmg = DOUBLE_LUNGE_DMG + modifier;
		dmgMitigation = (totalDmg * (keldari->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		keldari->health -= totalDmg;
		break;
	}
}

void Entity::SpiderBTurn(Entity* mainC, Entity* keldari)
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

	if (mainC->isAlive == false)
	{
		target = 2;
	}
	else if (keldari->isAlive == false)
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
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);

			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
			}

			mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B light attacks keldari");

			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * 0.9;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
			}
			keldari->health -= totalDmg;
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
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);
			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
			}
			mainC->health -= totalDmg;

			break;
		case 2:
			//printf("\n spider B heavy attacks keldari");
			totalDmg = this->attack + modifier;
			totalDmg = totalDmg * STRONG_ATTACK_MOD;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
			}
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
			}
			keldari->health -= totalDmg;
			break;
		}
		break;
	}
}

// FUNCTIONS FOR PLAY MODE

void Entity::UpdateM(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
{
	if (this->myType == TYPE::MC)
	{
		//printf("\n - It is mainC Turn");
		MainCTurnM(keldari, spiderA, spiderB, boss, inventory);
	}
	else if (this->myType == TYPE::KELDARI)
	{
		//printf("\n - It is Keldari Turn");
		KeldariTurnM(mainC, spiderA, spiderB, boss, inventory);
	}
	else if (this->myType == TYPE::BOSS)
	{
		//printf("\n - It is BOSS Turn");
		BossTurnM(mainC, keldari, spiderA, spiderB);
	}
	else if (this->myType == TYPE::SPIDER_A)
	{
		//printf("\n - It is SPIDER A Turn");
		SpiderATurnM(mainC, keldari);
	}
	else if (this->myType == TYPE::SPIDER_B)
	{
		//printf("\n - It is SPIDER B Turn");
		SpiderBTurnM(mainC, keldari);
	}

	this->EndTurn();
}

void Entity::MainCTurnM(Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
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
			dmgMitigation = finalDamage * (boss->defense / 100);
			finalDamage -= dmgMitigation;
			boss->health -= finalDamage;
			printf("\n Main Character dealt %f damage to boss!", finalDamage);
			break;
		case 2:
			//printf("spider A");
			dmgMitigation = finalDamage * (spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			spiderA->health -= finalDamage;
			printf("\n Main Character dealt %f damage to spider A!", finalDamage);
			break;
		case 3:
			//printf("spiderB");
			dmgMitigation = finalDamage * (spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			spiderB->health -= finalDamage;
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
			boss->stuned = true;
			printf("\n Boss is Stuned!");
			break;
		case 2:
			//printf("spiderA");
			spiderA->stuned = true;
			printf("\n Spider A is Stuned!");
			break;
		case 3:
			//printf("spiderB");
			spiderB->stuned = true;
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
				this->health += HP_POT_RECOVER;
				if (this->health >= 100)
				{
					this->health = 100;
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
				this->mana += MP_POT_RECOVER;
				if (this->mana >= 100)
				{
					this->mana = 100;
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
				this->empowered = true;
				inventory->hasPlant = false;
			}
			break;
		}
		break;
		}
	}
}

void Entity::KeldariTurnM(Entity* mainc, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory)
{
	if (this->health <= 0)
	{
		printf("\n Keldari is dead!");
		return;
	}

	printf("\n It's Keldari Turn");
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
			//printf("Boss");
			dmgMitigation = finalDamage * (boss->defense / 100);
			finalDamage -= dmgMitigation;
			boss->health -= finalDamage;
			printf("\n Keldari dealt %f damage to Boss!", finalDamage);
			break;
		case 2:
			//printf("spider A");
			dmgMitigation = finalDamage * (spiderA->defense / 100);
			finalDamage -= dmgMitigation;
			spiderA->health -= finalDamage;
			printf("\n Keldari dealt %f damage to spider A!", finalDamage);
			break;
		case 3:
			//printf("spiderB");
			dmgMitigation = finalDamage * (spiderB->defense / 100);
			finalDamage -= dmgMitigation;
			spiderB->health -= finalDamage;
			printf("\n Keldari dealt %f damage to spider B!", finalDamage);
			break;
		}
		break;
	case 2:                                                                         // -- Special --
		this->mana -= INFLAME_DMG;
		//printf("\n MainC uses soul chain on ");
		printf("\n You decide to use Inflame, all enemies are burning now!");
		boss->onFire = true;
		spiderA->onFire = true;
		spiderB->onFire = true;
		
		break;
	case 3:                                                                          // --Defend--
		printf("\n You decide to Block!");
		this->defending = true;
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
				printf("\n %d Keldari HP restored", HP_POT_RECOVER);
				this->health += HP_POT_RECOVER;
				if (this->health >= 100)
				{
					this->health = 100;
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
				printf("\n %d Keldari Mana restored", MP_POT_RECOVER);
				this->mana += MP_POT_RECOVER;
				if (this->mana >= 100)
				{
					this->mana = 100;
				}
				inventory->hasManaPotion = false;
			}
			break;
		}
		case 3:
		{
			if (inventory->hasPlant == true)
			{
				printf("\n Keldari ate the exotic plant");
				printf("\n Keldari feels stronger, attack 2x");
				this->empowered = true;
				inventory->hasPlant = false;
			}
			break;
		}
		break;
		}
	}
}

void Entity::BossTurnM(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB)
{
	if (this->health <= 0)
	{
		printf("\n Boss is dead!");
		this->onFire = false;
		return;
	}
	if (this->onFire)
	{
		printf("\n Boss is on fire, taking %d damage", INFLAME_DMG);
		this->health -= INFLAME_DMG;
	}
	if (this->health <= 0)
	{
		printf("\n Boss died to Inflame damage!");
		return;
	}
	if (this->stuned)
	{
		printf("\n Boss is stuned, skipping turn");
		this->stuned = false;
		return;
	}

	bool critSucces = false;
	int modifier = 0;
	int critGen = 0;
	int target = -1; // 0 - mainC, 1 - Keldari
	float finalDamage = 0;
	float dmgMitigation = 0;

	bool forceHeal = false;
	float actualHP = spiderA->health + spiderB->health;
	float minHP = spiderA->baseHP + spiderB->baseHP;
	minHP = minHP * 0.5;

	if (actualHP < minHP)
	{
		forceHeal = true;
	}

	if ((forceHeal == true) && (this->mana >= MATRIARCH_BREATH_MANA))
	{
		printf("\n BOSS heals %d to the minions...", MATRIARCH_BREATH_RECOVER);
		this->mana -= MATRIARCH_BREATH_MANA;
		spiderA->health += MATRIARCH_BREATH_RECOVER;
		spiderB->health += MATRIARCH_BREATH_RECOVER;
	}
	else
	{
		printf("\n BOSS attacks ");
		if (mainC->isAlive && keldari->isAlive)
		{
			target = rand() % 2;
		}
		else if (mainC->isAlive)
		{
			target = 0;
		}
		else
		{
			target = 1;
		}

		critGen = rand() % 100 + 1; // range of 1 - 100
		if (critGen <= this->critChance) critSucces = true;
		modifier = rand() % 10 + -5; // -5 - +5

		finalDamage = this->attack + modifier;
		if (critSucces) finalDamage * 1.5;


		switch (target)
		{
		case 0:
			printf("Main character");
			dmgMitigation = finalDamage * (mainC->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			mainC->health -= finalDamage;
			if (critSucces)printf("\n Critical Strike!!");
			printf("\n Dealing %f damage", finalDamage);
			break;
		case 1:
			printf("Keldari");
			dmgMitigation = finalDamage * (keldari->defense / 100);
			finalDamage = finalDamage -= dmgMitigation;
			keldari->health -= finalDamage;
			if (critSucces)printf("\n Critical Strike!!");
			printf("\n Dealing %f damage", finalDamage);
			break;
		}
	}
}

void Entity::SpiderATurnM(Entity* mainC, Entity* keldari)
{
	if (this->health <= 0)
	{
		printf("\n Spider A is dead!");
		this->onFire = false;
		return;
	}
	if (this->onFire)
	{
		printf("\n Spider A is on fire, taking %d damage", INFLAME_DMG);
		this->health -= INFLAME_DMG;
	}
	if (this->health <= 0)
	{
		printf("\n Spider A died to Inflame damage!");
		return;
	}
	if (this->stuned)
	{
		printf("\n Spider A is stuned, skipping turn");
		this->stuned = false;
		return;
	}

	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
	if (this->mana <= DOUBLE_LUNGE_MANA) attackChoosen = 1;
	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
	float dmgMitigation = 0;

	int totalDmg = 0;

	int critGen = rand() % 100 + 1; // range of 1 - 100
	bool critSuccess = false;

	if (critGen <= this->critChance)
	{
		critSuccess = true;
	}

	int modifier = rand() % 10 + -5; // -5 - +5

	if (mainC->isAlive == false)
	{
		target = 2;
	}
	else if (keldari->isAlive == false)
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
			totalDmg = this->attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);

			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
				printf("\n Main Character blocks the attack");
			}

			mainC->health -= totalDmg;
			printf("\n Dealing a total of %d damage",totalDmg);
			break;
		case 2:
			printf("\n Spider A attacks Keldari");
			totalDmg = this->attack + modifier;
			if (critSuccess == true)
			{
				totalDmg = totalDmg * 1.5;
				printf("\n Critical Strike!!");
			}
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			keldari->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		}
		break;
	case 2:
		printf("\n spider A uses Double Lunge");
		this->mana -= DOUBLE_LUNGE_MANA;

		totalDmg = DOUBLE_LUNGE_DMG + modifier;
		dmgMitigation = (totalDmg * (mainC->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		mainC->health -= totalDmg;
		printf("\n Deals %d to Main Character", totalDmg);
		totalDmg = DOUBLE_LUNGE_DMG + modifier;
		dmgMitigation = (totalDmg * (keldari->defense / 100));
		totalDmg = totalDmg - dmgMitigation;
		keldari->health -= totalDmg;
		printf(" and %d to Keldari", totalDmg);
		break;
	}
}

void Entity::SpiderBTurnM(Entity* mainC, Entity* keldari)
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

	if (mainC->isAlive == false)
	{
		target = 2;
	}
	else if (keldari->isAlive == false)
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
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);

			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
				printf("\n Main Character Blocks the attack");
			}

			mainC->health -= totalDmg;
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
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			keldari->health -= totalDmg;
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
			totalDmg = totalDmg - (totalDmg * (mainC->defense) / 100);
			if (mainC->defending == true)
			{
				mainC->defending = false;
				totalDmg = 0;
				printf("\n Main Character Blocks the attack");
			}
			mainC->health -= totalDmg;
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
			totalDmg = totalDmg - (totalDmg * (keldari->defense) / 100);
			if (keldari->defending == true)
			{
				keldari->defending = false;
				totalDmg = 0;
				printf("\n Keldari Blocks the attack");
			}
			keldari->health -= totalDmg;
			printf("\n Dealing a total of %d damage", totalDmg);
			break;
		}
		break;
	}
}


