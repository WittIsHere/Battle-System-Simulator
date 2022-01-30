//#include "E_SpiderA.h"
//
//void E_SpiderA::Turn()
//{
//	if (this->health <= 0)
//	{
//		return;
//	}
//	if (this->onFire == true)
//	{
//		this->health -= INFLAME_DMG;
//	}
//	if (this->health <= 0)
//	{
//		return;
//	}
//	else if (this->stuned == true)
//	{
//		this->stuned = false;
//		return;
//	}
//
//
//	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
//	if (this->mana <= DOUBLE_LUNGE_MANA) attackChoosen = 1;
//	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
//	float dmgMitigation = 0;
//
//	int totalDmg = 0;
//
//	int critGen = rand() % 100 + 1; // range of 1 - 100
//	bool critSuccess = false;
//
//	if (critGen <= this->critChance)
//	{
//		critSuccess = true;
//	}
//
//	int modifier = rand() % 10 + -5; // -5 - +5
//
//	if (simulator->entityManager->mainC->isAlive == false)
//	{
//		target = 2;
//	}
//	else if (simulator->entityManager->keldari->isAlive == false)
//	{
//		target = 1;
//	}
//
//	switch (attackChoosen)
//	{
//	case 1:
//		switch (target)
//		{
//		case 1:
//			//printf("\n spider A attacks mainC");
//			totalDmg = this->attack + modifier;
//			if (critSuccess == true)
//			{
//				totalDmg = totalDmg * 1.5;
//			}
//			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);
//
//			if (simulator->entityManager->mainC->defending == true)
//			{
//				simulator->entityManager->mainC->defending = false;
//				totalDmg = 0;
//			}
//
//			simulator->entityManager->mainC->health -= totalDmg;
//
//			break;
//		case 2:
//			//printf("\n spider A attacks keldari");
//			totalDmg = this->attack + modifier;
//			if (critSuccess == true)
//			{
//				totalDmg = totalDmg * 1.5;
//			}
//			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
//			if (simulator->entityManager->keldari->defending == true)
//			{
//				simulator->entityManager->keldari->defending = false;
//				totalDmg = 0;
//			}
//			simulator->entityManager->keldari->health -= totalDmg;
//			break;
//		}
//		break;
//	case 2:
//		//printf("\n spider A uses Double Lunge");
//		this->mana -= DOUBLE_LUNGE_MANA;
//
//		totalDmg = DOUBLE_LUNGE_DMG + modifier;
//		dmgMitigation = (totalDmg * (simulator->entityManager->mainC->defense / 100));
//		totalDmg = totalDmg - dmgMitigation;
//		simulator->entityManager->mainC->health -= totalDmg;
//
//		totalDmg = DOUBLE_LUNGE_DMG + modifier;
//		dmgMitigation = (totalDmg * (simulator->entityManager->keldari->defense / 100));
//		totalDmg = totalDmg - dmgMitigation;
//		simulator->entityManager->keldari->health -= totalDmg;
//		break;
//	}
//}
//
//void E_SpiderA::TurnM()
//{
//	if (this->health <= 0)
//	{
//		printf("\n Spider A is dead!");
//		this->onFire = false;
//		return;
//	}
//	if (this->onFire)
//	{
//		printf("\n Spider A is on fire, taking %d damage", INFLAME_DMG);
//		this->health -= INFLAME_DMG;
//	}
//	if (this->health <= 0)
//	{
//		printf("\n Spider A died to Inflame damage!");
//		return;
//	}
//	if (this->stuned)
//	{
//		printf("\n Spider A is stuned, skipping turn");
//		this->stuned = false;
//		return;
//	}
//
//	int attackChoosen = rand() % 2 + 1; // range of 1 - 2
//	if (this->mana <= DOUBLE_LUNGE_MANA) attackChoosen = 1;
//	int target = rand() % 2 + 1; // range of 1 - 2 /// 0 - mainC 1 - KEldari
//	float dmgMitigation = 0;
//
//	int totalDmg = 0;
//
//	int critGen = rand() % 100 + 1; // range of 1 - 100
//	bool critSuccess = false;
//
//	if (critGen <= this->critChance)
//	{
//		critSuccess = true;
//	}
//
//	int modifier = rand() % 10 + -5; // -5 - +5
//
//	if (simulator->entityManager->mainC->isAlive == false)
//	{
//		target = 2;
//	}
//	else if (simulator->entityManager->keldari->isAlive == false)
//	{
//		target = 1;
//	}
//
//	switch (attackChoosen)
//	{
//	case 1:
//		switch (target)
//		{
//		case 1:
//			printf("\n Spider A attacks main character");
//			totalDmg = this->attack + modifier;
//			if (critSuccess == true)
//			{
//				totalDmg = totalDmg * 1.5;
//				printf("\n Critical Strike!!");
//			}
//			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->mainC->defense) / 100);
//
//			if (simulator->entityManager->mainC->defending == true)
//			{
//				simulator->entityManager->mainC->defending = false;
//				totalDmg = 0;
//				printf("\n Main Character blocks the attack");
//			}
//
//			simulator->entityManager->mainC->health -= totalDmg;
//			printf("\n Dealing a total of %d damage", totalDmg);
//			break;
//		case 2:
//			printf("\n Spider A attacks Keldari");
//			totalDmg = this->attack + modifier;
//			if (critSuccess == true)
//			{
//				totalDmg = totalDmg * 1.5;
//				printf("\n Critical Strike!!");
//			}
//			totalDmg = totalDmg - (totalDmg * (simulator->entityManager->keldari->defense) / 100);
//			if (simulator->entityManager->keldari->defending == true)
//			{
//				simulator->entityManager->keldari->defending = false;
//				totalDmg = 0;
//				printf("\n Keldari Blocks the attack");
//			}
//			simulator->entityManager->keldari->health -= totalDmg;
//			printf("\n Dealing a total of %d damage", totalDmg);
//			break;
//		}
//		break;
//	case 2:
//		printf("\n spider A uses Double Lunge");
//		this->mana -= DOUBLE_LUNGE_MANA;
//
//		totalDmg = DOUBLE_LUNGE_DMG + modifier;
//		dmgMitigation = (totalDmg * (simulator->entityManager->mainC->defense / 100));
//		totalDmg = totalDmg - dmgMitigation;
//		simulator->entityManager->mainC->health -= totalDmg;
//		printf("\n Deals %d to Main Character", totalDmg);
//		totalDmg = DOUBLE_LUNGE_DMG + modifier;
//		dmgMitigation = (totalDmg * (simulator->entityManager->keldari->defense / 100));
//		totalDmg = totalDmg - dmgMitigation;
//		simulator->entityManager->keldari->health -= totalDmg;
//		printf(" and %d to Keldari", totalDmg);
//		break;
//	}
//}
