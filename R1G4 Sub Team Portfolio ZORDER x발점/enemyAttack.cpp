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
	//���� ������ �ʱ�ȭ
	_attackDelay = RND->getFromIntTo(80, 120);
	//�޺����� ���� Ÿ�̸� �ʱ�ȭ
	_comboTimer = 200;
	//���ݻ��� ����
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

	//�޺����� ���� Ÿ�̸Ӱ� 0���Ϸ� �������� �������� ���� ���� ����
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
			//0���� ���� 3 �̸��� ������ ����
			int random = RND->getFromIntTo(0, 3);
			//0���� ���� 1������ ATTACK 3�� �޺�����
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
