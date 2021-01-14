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
	_attackDelay = RND->getFromIntTo(70, 100);
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
	//타이머와 딜레이는 상시적으로 줄어든다.
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
	//공격 패턴
	if ((ATTACK_STATE)attack == NONE && _attackDelay <= 0)
	{
		if (_attackState == ATTACK || _attackState == NONE || _attackState == COMBO_ATTACK_3)
		{
			//0에서 부터 3 미만의 난수를 생성
			int random = RND->getFromIntTo(0,3);
			//0에서 부터 1까지는 ATTACK 3은 콤보공격
			_attackState = random <= 1 ? ATTACK : COMBO_ATTACK_1;
			
			//공격 종류에 따른 공격 딜레이를 난수로 획득
			if(_attackState == ATTACK)
				_attackDelay = RND->getFromIntTo(70, 100);
			else 
				_attackDelay = RND->getFromIntTo(40, 90);
		}
		else if (_attackState == COMBO_ATTACK_1 && _comboTimer > 0)
		{
			_attackState = COMBO_ATTACK_2;
			_attackDelay = RND->getFromIntTo(40, 90);
		}
		else if (_attackState == COMBO_ATTACK_2 && _comboTimer > 0)
		{
			_attackState = COMBO_ATTACK_3;
			_attackDelay = RND->getFromIntTo(40, 90);
		}
		else return NONE;

		_comboTimer = 200;
	}
	//공격이 해당되지 않으므로 NONE으로 반환(enemy에서는 Idle상태다)
	else return NONE;

	//선택된 공격을 반환한다.
	return _attackState;
}
