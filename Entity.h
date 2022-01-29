#pragma once

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

class Entity
{
public:
	Entity() {};
	Entity(const char* n) : name(n) {}
	~Entity() {}

	void Draw(bool first);
	void Update(Entity* mainC, Entity* keldari, Entity* banditA, Entity* banditB, Entity* boss, PlayerInventory* inventory);

	void MainCTurn(Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory);
	void KeldariTurn(Entity* mainC, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory);
	void BossTurn(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB);
	void SpiderATurn(Entity* mainC, Entity* keldari);
	void SpiderBTurn(Entity* mainC, Entity* keldari);

	void UpdateM(Entity* mainC, Entity* keldari, Entity* banditA, Entity* banditB, Entity* boss, PlayerInventory* inventory);

	void MainCTurnM(Entity* keldari, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory);
	void KeldariTurnM(Entity* mainC, Entity* spiderA, Entity* spiderB, Entity* boss, PlayerInventory* inventory);
	void BossTurnM(Entity* mainC, Entity* keldari, Entity* spiderA, Entity* spiderB);
	void SpiderATurnM(Entity* mainC, Entity* keldari);
	void SpiderBTurnM(Entity* mainC, Entity* keldari);

	void EndTurn() { speed = 0; }
	void ResetSpeed() { speed = baseSpeed; }

	void operator=(const Entity& a)
	{
		name = a.name;
		health = a.health;
		baseHP = a.baseHP;
		baseSpeed = a.baseSpeed;
		isAlive = a.isAlive;
		mana = a.mana;
		speed = a.speed;
		onFire = a.onFire;
		stuned = a.stuned;
		empowered = a.empowered;
		magicType = a.magicType;
		defending = a.defending;
	}

public:
	const char* name = nullptr;

	bool isAlive = true;

	bool onFire = false;
	bool stuned = false;
	bool empowered = false;
	bool defending = false;

	TYPE myType = TYPE::NONE;

	int level = 1;

	int baseHP = 0;
	int health = 0;
	int mana = 0;
	int magicType = 0;
	int defense = 0;
	int attack = 0;
	int critChance = 0;
	int baseSpeed = 0;
	int speed = 0;
};