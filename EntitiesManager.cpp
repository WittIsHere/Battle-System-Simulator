#include "EntitiesManager.h"
#include "Simulator.h"

#include <stdio.h>		// Required for function(s): printf(); scanf(); scanf_s(); 
#include <stdlib.h>		// Required for function(s): rand(); system(); srand(); srand(time(NULL));



EntitiesManager::EntitiesManager()
{}

void EntitiesManager::InitAll(int level)
{
	AllModVars* myModVars = mySim->modVars;

	mainC->name = "Player";
	mainC->baseHP = 100;
	mainC->health = mainC->baseHP;
	mainC->mana = 100;
	mainC->magicType = 1;
	mainC->critChance = 10;
	mainC->baseSpeed = 50;
	mainC->speed = mainC->baseSpeed;;
	mainC->myType = TYPE::MC;
	mainC->defending = false;
	mainC->empowered = false;
	mainC->onFire = false;
	mainC->stuned = false;
	mainC->isAlive = true;

	keldari->name = "Keldari";
	keldari->baseHP = 100;
	keldari->health = keldari->baseHP;
	keldari->mana = 100;
	keldari->magicType = 1;
	keldari->critChance = 10;
	keldari->baseSpeed = 70;
	keldari->speed = keldari->baseSpeed;
	keldari->myType = TYPE::KELDARI;
	keldari->empowered = false;
	keldari->defending = false;
	keldari->onFire = false;
	keldari->stuned = false;
	keldari->isAlive = true;

	switch (level)
	{
		case 1:
			mainC->defense = myModVars->mC_Defense * myModVars->level_1_Progression;
			mainC->attack = myModVars->mC_Attack * myModVars->level_1_Progression;

			keldari->defense = myModVars->keld_Defense * myModVars->level_1_Progression;
			keldari->attack = myModVars->keld_Attack * myModVars->level_1_Progression;

			break;

		case 2:
			mainC->defense = myModVars->mC_Defense * myModVars->level_2_Progression;
			mainC->attack = myModVars->mC_Attack * myModVars->level_2_Progression;

			keldari->defense = myModVars->keld_Defense * myModVars->level_2_Progression;
			keldari->attack = myModVars->keld_Attack * myModVars->level_2_Progression;

			break;
		
		case 3:
			mainC->defense = myModVars->mC_Defense * myModVars->level_3_Progression;
			mainC->attack = myModVars->mC_Attack * myModVars->level_3_Progression;

			keldari->defense = myModVars->keld_Defense * myModVars->level_3_Progression;
			keldari->attack = myModVars->keld_Attack * myModVars->level_3_Progression;

			break;
		
		case 4:
			mainC->defense = myModVars->mC_Defense * myModVars->level_4_Progression;
			mainC->attack = myModVars->mC_Attack * myModVars->level_4_Progression;

			keldari->defense = myModVars->keld_Defense * myModVars->level_4_Progression;
			keldari->attack = myModVars->keld_Attack * myModVars->level_4_Progression;

			break;

		case 5:
			mainC->defense = myModVars->mC_Defense * myModVars->level_5_Progression;
			mainC->attack = myModVars->mC_Attack * myModVars->level_5_Progression;

			keldari->defense = myModVars->keld_Defense * myModVars->level_5_Progression;
			keldari->attack = myModVars->keld_Attack * myModVars->level_5_Progression;

			break;	
	}

	boss->name = "Boss";
	boss->baseHP = 100;
	boss->health = boss->baseHP;
	boss->mana = 100;
	boss->magicType = 1;
	boss->defense = 20;
	boss->attack = 20;
	boss->critChance = 5;
	boss->baseSpeed = 20;
	boss->speed = boss->baseSpeed;
	boss->myType = TYPE::BOSS;
	boss->empowered = false;
	boss->defending = false;
	boss->onFire = false;
	boss->stuned = false;
	boss->isAlive = true;

	spiderA->name = "Spider A";
	spiderA->baseHP = 100;
	spiderA->health = spiderA->baseHP;
	spiderA->mana = 100;
	spiderA->magicType = 1;
	spiderA->defense = myModVars->sA_Defense;
	spiderA->attack = myModVars->sA_Attack;
	spiderA->critChance = 10;
	spiderA->baseSpeed = 30;
	spiderA->speed = spiderA->baseSpeed;
	spiderA->myType = TYPE::SPIDER_A;
	spiderA->empowered = false;
	spiderA->defending = false;
	spiderA->onFire = false;
	spiderA->stuned = false;
	spiderA->isAlive = true;

	spiderB->name = "Spider B";
	spiderB->baseHP = 100;
	spiderB->health = spiderB->baseHP;
	spiderB->mana = 100;
	spiderB->magicType = 1;
	spiderB->defense = myModVars->sB_Defense;
	spiderB->attack = myModVars->sB_Attack;
	spiderB->critChance = 20;
	spiderB->baseSpeed = 90;
	spiderB->speed = spiderB->baseSpeed;
	spiderB->myType = TYPE::SPIDER_B;
	spiderB->empowered = false;
	spiderB->defending = false;
	spiderB->onFire = false;
	spiderB->stuned = false;
	spiderB->isAlive = true;
}

void EntitiesManager::PlayTurns()
{
	for (int i = 0; i < 5; i++)
	{
		Entity* currentTurn = ReturnHighest();
		currentTurn->Turn();
		currentTurn->EndTurn();
	}
	if (mySim->simParameters->showInfo) printf("\n ___");
}

void EntitiesManager::PlayTurnsManual()
{
	for (int i = 0; i < 5; i++)
	{
		Entity* currentTurn = ReturnHighest();
		currentTurn->TurnM();
		currentTurn->EndTurn();
		printf("\n ");
		system("pause");
		system("cls");
		IncreaseSpeedAll();
		DrawAll();
	}
}

void EntitiesManager::IncreaseSpeedAll()
{
	mainC->speed++;
	keldari->speed++;
	boss->speed++;
	spiderA->speed++;
	spiderB->speed++;
}

void EntitiesManager::ResetEntitiesSpeed()
{
	mainC->ResetSpeed();
	keldari->ResetSpeed();
	spiderA->ResetSpeed();
	spiderB->ResetSpeed();
	boss->ResetSpeed();
}

void EntitiesManager::SetSimulator(Simulator* sim)
{
	mySim = sim;
}

Entity* EntitiesManager::ReturnHighest()
{
	int as = mainC->speed;
	int bs = keldari->speed;
	int cs = spiderA->speed;
	int ds = spiderB->speed;
	int es = boss->speed;

	int low1 = 0;
	int low2 = 0;
	int high1 = 0;
	int high2 = 0;
	int lowest = 0;
	int highest = 0;
	int middle1 = 0;
	int middle2 = 0;

	if (mainC->speed < keldari->speed)
	{
		low1 = as;
		high1 = bs;
	}
	else
	{
		low1 = bs;
		high1 = as;
	}

	if (spiderA->speed < spiderB->speed)
	{
		low2 = cs;
		high2 = ds;
	}
	else
	{
		low2 = ds;
		high2 = cs;
	}

	if (low1 < low2)
	{
		lowest = low1;
		middle1 = low2;
	}
	else
	{
		lowest = low2;
		middle1 = low1;
	}

	if (high1 < high2)
	{
		highest = high2;
		middle2 = high1;
	}
	else
	{
		highest = high1;
		middle2 = high2;
	}
	if (highest < es)
	{
		highest = es;
	}

	if (highest == as)
	{
		return mainC;
	}
	else if (highest == bs)
	{
		return keldari;
	}
	else if (highest == cs)
	{
		return spiderA;
	}
	else if (highest == ds)
	{
		return spiderB;
	}
	else
	{
		return boss;
	}
}

void EntitiesManager::DrawAll()
{
	Entity as = *mainC;
	Entity bs = *keldari;
	Entity cs = *spiderA;
	Entity ds = *spiderB;
	Entity es = *boss;

	Entity high2 = 0;
	Entity high1 = 0;
	Entity low2 = 0;
	Entity low1 = 0;

	Entity ultra = 0;
	Entity highest = 0;
	Entity middle2 = 0;
	Entity middle1 = 0;
	Entity lowest = 0;


	if (as.speed < bs.speed)
	{
		low1 = as;
		high1 = bs;
	}
	else
	{
		low1 = bs;
		high1 = as;
	}

	if (cs.speed < ds.speed)
	{
		low2 = cs;
		high2 = ds;
	}
	else
	{
		low2 = ds;
		high2 = cs;
	}

	if (low1.speed < low2.speed)
	{
		lowest = low1;
		middle1 = low2;
	}
	else
	{
		lowest = low2;
		middle1 = low1;
	}

	if (high1.speed < high2.speed)
	{
		highest = high2;
		middle2 = high1;
	}
	else
	{
		highest = high1;
		middle2 = high2;
	}
	if (es.speed > highest.speed)
	{
		ultra = es;
	}
	else if (es.speed < highest.speed && es.speed > middle2.speed)
	{
		ultra = highest;
		highest = es;
	}
	else if (es.speed < middle2.speed && es.speed > middle1.speed)
	{
		ultra = highest;
		highest = middle2;
		middle2 = es;
	}
	else if (es.speed < middle1.speed && es.speed > lowest.speed)
	{
		ultra = highest;
		highest = middle2;
		middle2 = middle1;
		middle1 = es;
	}
	else
	{
		ultra = highest;
		highest = middle2;
		middle2 = middle1;
		middle1 = lowest;
		lowest = es;
	}

	printf("______________________________________________\n");
	ultra.Draw(true);
	highest.Draw(false);
	middle2.Draw(false);
	middle1.Draw(false);
	lowest.Draw(false);
	printf("______________________________________________\n");
}


