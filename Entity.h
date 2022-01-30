#pragma once
#include "Main.cpp"

enum class TYPE
{
	NONE,
	MC,
	KELDARI,
	BOSS,
	SPIDER_A,
	SPIDER_B
};

class PlayerInventory;
class Simulator;

class Entity
{
public:
	Entity() {};
	Entity(const char* n) : name(n) {}
	~Entity() { delete this; } // ??

	void Draw(bool first);
	void Update();

	void UpdateM();

	void EndTurn() { speed = 0; }
	void ResetSpeed() { speed = baseSpeed; }

	void operator=(const Entity& a);

	public:

	const char* name = nullptr;
	int level = 1;

	int baseHP = 0;
	int health = 0;
	int mana = 0;
	int magicType = 0; // Change this
	int attack = 0;
	int defense = 0;
	int critChance = 0;
	int baseSpeed = 0;
	int speed = 0;

	TYPE myType = TYPE::NONE;

	bool isAlive = true;

	bool onFire = false;
	bool stuned = false;
	bool empowered = false;
	bool defending = false;

};