#pragma once
#include "gameNode.h"

class enemyAttack : public gameNode
{
	//공격 상태
	enum ATTACK_STATE
	{
		NONE = 0,
		ATTACK = 4,
		COMBO_ATTACK_1 = 5,
		COMBO_ATTACK_2 = 6,
		COMBO_ATTACK_3 = 7
	};

	ATTACK_STATE _attackState;
	int _comboTimer;	//콤보공격 타이머(타이머 0이상 일 때만 콤보공격을 이어간다.)
	int _attackDelay;	//공격 딜레이(바로 공격하면 사실상 난이도 급상승)
public:
	enemyAttack();
	~enemyAttack();

	HRESULT init();
	void release();
	void update();
	void render();
	int selectedAttack(int attack);	//선택된 공격 체크
};

