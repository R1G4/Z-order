#pragma once
#include "gameNode.h"

class enemyAttack : public gameNode
{
	enum ATTACK_STATE
	{
		NONE = 0,
		ATTACK = 4,
		COMBO_ATTACK_1 = 5,
		COMBO_ATTACK_2 = 6,
		COMBO_ATTACK_3 = 7
	};

	ATTACK_STATE _attackState;
	int _comboTimer;
	int _attackDelay;
public:
	enemyAttack();
	~enemyAttack();

	HRESULT init();
	void release();
	void update();
	void render();
	int selectedAttack(int attack);
	//int setAttack();
};

