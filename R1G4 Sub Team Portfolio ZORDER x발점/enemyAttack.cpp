#include "stdafx.h"
#include "enemyAttack.h"


enemyAttack::enemyAttack()
{
}


enemyAttack::~enemyAttack()
{
}

HRESULT enemyAttack::init()
{
	//공격 딜레이 초기화
	_attackDelay = RND->getFromIntTo(80, 120);
	//콤보공격 가능 타이머 초기화
	_comboTimer = 200;
	//공격상태 저장
	_attackState = ATTACK;
	return S_OK;
}

void enemyAttack::release()
{
}

void enemyAttack::update()
{
	_attackDelay--;
	_comboTimer--;

	//콤보공격 가능 타이머가 0이하로 떨어지면 저장해준 공격 상태 변경
	if (_comboTimer <= 0)
		_attackState = NONE;
}

void enemyAttack::render()
{
}

int enemyAttack::selectedAttack(int attack)
{
	if ((ATTACK_STATE)attack == NONE && _attackDelay <= 0)
	{
		if (_attackState == ATTACK || _attackState == NONE || _attackState == COMBO_ATTACK_3)
		{
			//0에서 부터 3 미만의 난수를 생성
			int random = RND->getFromIntTo(0, 3);
			//0에서 부터 1까지는 ATTACK 3은 콤보공격
			_attackState = random <= 1 ? ATTACK : COMBO_ATTACK_1;
			if (_attackState == ATTACK)
				_attackDelay = RND->getFromIntTo(100, 140);
			else
				_attackDelay = RND->getFromIntTo(70, 100);
		}
		else if (_attackState == COMBO_ATTACK_1 && _comboTimer > 0)
		{
			_attackState = COMBO_ATTACK_2;
			_attackDelay = RND->getFromIntTo(70, 100);
		}
		else if (_attackState == COMBO_ATTACK_2 && _comboTimer > 0)
		{
			_attackState = COMBO_ATTACK_3;
			_attackDelay = RND->getFromIntTo(70, 100);
		}
		else return NONE;

		_comboTimer = 200;
	}
	else return NONE;

	return _attackState;
}
