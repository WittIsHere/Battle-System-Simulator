//#include "E_Boss.h"
//
//void E_Boss::Turn()
//{
//	if (this->health <= 0)
//	{
//		return;
//	}
//	if (this->onFire)
//	{
//		this->health -= INFLAME_DMG;
//	}
//	if (this->health <= 0)
//	{
//		return;
//	}
//	if (this->stuned)
//	{
//		this->stuned = false;
//		return;
//	}
//
//	bool critSucces = false;
//	int modifier = 0;
//	int critGen = 0;
//	int target = -1; // 0 - mainC, 1 - Keldari
//	float finalDamage = 0;
//	float dmgMitigation = 0;
//
//	bool forceHeal = false;
//	float actualHP = simulator->entityManager->spiderA->health + simulator->entityManager->spiderB->health;
//	float minHP = simulator->entityManager->spiderA->baseHP + simulator->entityManager->spiderB->baseHP;
//	minHP = minHP * 0.5;
//
//	if (actualHP < minHP)
//	{
//		forceHeal = true;
//	}
//
//	if ((forceHeal == true) && (this->mana >= MATRIARCH_BREATH_MANA))
//	{
//		//printf("\n BOSS heals");
//		this->mana -= MATRIARCH_BREATH_MANA;
//		simulator->entityManager->spiderA->health += MATRIARCH_BREATH_RECOVER;
//		simulator->entityManager->spiderB->health += MATRIARCH_BREATH_RECOVER;
//	}
//	else
//	{
//		//printf("\n BOSS attacks ");
//		if (simulator->entityManager->mainC->isAlive && simulator->entityManager->keldari->isAlive)
//		{
//			target = rand() % 2;
//		}
//		else if (simulator->entityManager->mainC->isAlive)
//		{
//			target = 0;
//		}
//		else
//		{
//			target = 1;
//		}
//
//		critGen = rand() % 100 + 1; // range of 1 - 100
//		if (critGen <= this->critChance) critSucces = true;
//		modifier = rand() % 10 + -5; // -5 - +5
//
//		finalDamage = this->attack + modifier;
//		if (critSucces) finalDamage * 1.5;
//
//
//		switch (target)
//		{
//		case 0:
//			//printf("mainC");
//			dmgMitigation = finalDamage * (simulator->entityManager->mainC->defense / 100);
//			finalDamage = finalDamage -= dmgMitigation;
//			simulator->entityManager->mainC->health -= finalDamage;
//			break;
//		case 1:
//			//printf("keldari");
//			dmgMitigation = finalDamage * (simulator->entityManager->keldari->defense / 100);
//			finalDamage = finalDamage -= dmgMitigation;
//			simulator->entityManager->keldari->health -= finalDamage;
//			break;
//		}
//	}
//}
//
//void E_Boss::TurnM()
//{
//	if (this->health <= 0)
//	{
//		printf("\n Boss is dead!");
//		this->onFire = false;
//		return;
//	}
//	if (this->onFire)
//	{
//		printf("\n Boss is on fire, taking %d damage", INFLAME_DMG);
//		this->health -= INFLAME_DMG;
//	}
//	if (this->health <= 0)
//	{
//		printf("\n Boss died to Inflame damage!");
//		return;
//	}
//	if (this->stuned)
//	{
//		printf("\n Boss is stuned, skipping turn");
//		this->stuned = false;
//		return;
//	}
//
//	bool critSucces = false;
//	int modifier = 0;
//	int critGen = 0;
//	int target = -1; // 0 - mainC, 1 - Keldari
//	float finalDamage = 0;
//	float dmgMitigation = 0;
//
//	bool forceHeal = false;
//	float actualHP = simulator->entityManager->spiderA->health + simulator->entityManager->spiderB->health;
//	float minHP = simulator->entityManager->spiderA->baseHP + simulator->entityManager->spiderB->baseHP;
//	minHP = minHP * 0.5;
//
//	if (actualHP < minHP)
//	{
//		forceHeal = true;
//	}
//
//	if ((forceHeal == true) && (this->mana >= MATRIARCH_BREATH_MANA))
//	{
//		printf("\n BOSS heals %d to the minions...", MATRIARCH_BREATH_RECOVER);
//		this->mana -= MATRIARCH_BREATH_MANA;
//		simulator->entityManager->spiderA->health += MATRIARCH_BREATH_RECOVER;
//		simulator->entityManager->spiderB->health += MATRIARCH_BREATH_RECOVER;
//	}
//	else
//	{
//		printf("\n BOSS attacks ");
//		if (simulator->entityManager->mainC->isAlive && simulator->entityManager->keldari->isAlive)
//		{
//			target = rand() % 2;
//		}
//		else if (simulator->entityManager->mainC->isAlive)
//		{
//			target = 0;
//		}
//		else
//		{
//			target = 1;
//		}
//
//		critGen = rand() % 100 + 1; // range of 1 - 100
//		if (critGen <= this->critChance) critSucces = true;
//		modifier = rand() % 10 + -5; // -5 - +5
//
//		finalDamage = this->attack + modifier;
//		if (critSucces) finalDamage * 1.5;
//
//
//		switch (target)
//		{
//		case 0:
//			printf("Main character");
//			dmgMitigation = finalDamage * (simulator->entityManager->mainC->defense / 100);
//			finalDamage = finalDamage -= dmgMitigation;
//			simulator->entityManager->mainC->health -= finalDamage;
//			if (critSucces)printf("\n Critical Strike!!");
//			printf("\n Dealing %f damage", finalDamage);
//			break;
//		case 1:
//			printf("Keldari");
//			dmgMitigation = finalDamage * (simulator->entityManager->keldari->defense / 100);
//			finalDamage = finalDamage -= dmgMitigation;
//			simulator->entityManager->keldari->health -= finalDamage;
//			if (critSucces)printf("\n Critical Strike!!");
//			printf("\n Dealing %f damage", finalDamage);
//			break;
//		}
//	}
//}
