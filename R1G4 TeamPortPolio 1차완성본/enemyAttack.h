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

	ATTACK_STATE _attackState;	//에너미의 공격상태를 저장한다.(에너미가 공격 할 경우 전에 공격상태에 따라 콤보공격인지 일반공격인지 나누어 지기에)
	int _comboTimer;			//콤보공격 가능 타이머(ex:콤보공격1이 끝나고 2로 콤보공격이 가능한 시간)
	int _attackDelay;			//공격 딜레이(이게 없으면 계속 공격하므로 난이도 급상승을 위해 딜레이를 넣음)
public:
	enemyAttack();
	~enemyAttack();

	HRESULT init();
	void release();
	void update();
	void render();
	int selectedAttack(int attack);	//에너미가 공격 할 경우 그 전에 공격과 위의 변수에 따라 공격상태 선택하여 반환한다.
};

