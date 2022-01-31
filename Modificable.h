#pragma once

class AllModVars
{
public:
	// Level Related
	float level_1_Progression = 1.0f;
	float level_2_Progression = 1.2f;
	float level_3_Progression = 1.7f;
	float level_4_Progression = 2.15f;
	float level_5_Progression = 2.6f;

	// Player
	int mC_Attack = 20;
	int mC_Defense = 20;

	// Keldari
	int keld_Attack = 30;
	int keld_Defense = 10;

	// Boss
	int boss_Attack = 0;
	int boss_Defense = 0;

	// Spider A
	int sA_Attack = 20;
	int sA_Defense = 20;

	// Spider B
	int sB_Attack = 20;
	int sB_Defense = 20;

	// Spells

	int matriarch_Breath_HP = 20;
	int matriarch_Breath_MANA = 30;
	int double_Lunge_DMG = 40;
	int double_Lunge_MANA = 50;
	float heavy_Att_MOD = 1.5f;

	int soul_Chain_MANA = 30;
	int inflame_MANA = 80;
	int inflame_DMG = 20;

	// Items
	float exotic_Plant_Buff = 2.0f;
	int hP_potion = 50;
	int mP_potion = 50;

};