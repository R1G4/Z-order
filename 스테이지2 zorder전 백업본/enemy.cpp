#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y, STATE state, DIRECTION direction)
{
	//���ʹ� ���� �ʱ�ȭ
	_direction = direction;
	_state = state;
	//��ǥ �ʱ�ȭ
	_x = x;
	_y = y;
	_angle = 0;
	_alphaInterval = 0;
	_alphaValue = 0;
	_hp = 8;
	//�̹��� �� �ִϸ��̼� ����
	switch (_state)
	{
	case enemy::IDLE:

		_enemyImg = imgIdle;
		switch (_direction)
		{
		case enemy::LEFT:
			_isAction = true;
			_motion = aniLeftIdle;
			break;
		case enemy::RIGHT:
			_isAction = true;
			_motion = aniRightIdle;
			break;
		}

		break;
	case enemy::TAUNT:
		_enemyImg = imgTaunt;
		switch (_direction)
		{
		case enemy::LEFT:
			_isAction = false;
			_motion = aniLeftTaunt;
			break;
		case enemy::RIGHT:
			_isAction = false;
			_motion = aniRightTaunt;
			break;
		}
		break;
	}

	//�ִϸ��̼� ����
	_motion->start();

	//�浹�� ��Ʈ �ʱ�ȭ
	_rc = RectMakeCenter(_x, _y, 40, 200);
	//���ʹ� ��Ʈ �ʱ�ȭ
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	//�׸��� ��Ʈ �ʱ�ȭ
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());

	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	_isCollision = false;

	//���� ���� �ʱ�ȭ
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//���ʹ� ���� ���� �� �ʱ�ȭ
	_enemyAttack = new enemyAttack;
	_enemyAttack->init();
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	if (_state == DEAD)
		setAlpha();
}

void enemy::render()
{
}

void enemy::effectPoint(DIRECTION direction)
{
	switch (direction)
	{
	case enemy::LEFT:
		EFFECTMANAGER->play("Enemy_Point", _x - 55, _enemyRc.top - 55);
		break;
	case enemy::RIGHT:
		EFFECTMANAGER->play("Enemy_Point", _x + 55, _enemyRc.top - 55);
		break;
	}
}

void enemy::effectStun(DIRECTION direction)
{
	switch (direction)
	{
	case enemy::LEFT:
		EFFECTMANAGER->play("Enemy_Stun", _x, _enemyRc.top - 10);
		break;
	case enemy::RIGHT:
		EFFECTMANAGER->play("Enemy_Stun", _x, _enemyRc.top - 10);
		break;
	}
}

void enemy::render(POINT camera)
{
	EFFECTMANAGER->render(camera);
}

bool enemy::block(DIRECTION _direction)
{
	//�ش� ������ �� ����
	if (_state == DAZED  || _state == DOWNUP || _state == KNOCKDOWN || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return false;

	//0���� 3������ ������ �޾Ƽ�(4���� ����� �� �� 1��) 0�� �ƴ� ��� ����
	if(RND->getFromIntTo(0, 4) != 0)
		return false;

	_motion->stop();
	_state = BLOCK;
	_enemyImg = imgBlock;
	switch (_direction)
	{
	case enemy::LEFT:
		_motion = aniLeftBlock;
		break;
	case enemy::RIGHT:
		_motion = aniRightBlock;
		break;
	}
	_motion->start();

	return true;
}

void enemy::hit(DIRECTION direction)
{
	//�ش� ������ �� ����
	if (_state == BLOCK || _state == DOWNUP || _state == KNOCKDOWN  || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return;

	//ü�� ����
	_hp--;
	if (_hp < 0)
	{
		//ü���� 0 ���϶�� knockdown ���� ����
		knockdown(direction);
		return;
	}

	_motion->stop();
	_state = HIT;
	_enemyImg = imgHit;
	switch (direction)
	{
	case enemy::LEFT:
		_motion = aniLeftHit;
		break;
	case enemy::RIGHT:
		_motion = aniRightHit;
		break;
	}
	_motion->start();
}

void enemy::downup(DIRECTION direction)
{
	//�ش� ������ �� ����
	if (_state == BLOCK || _state == DOWNUP || _state == KNOCKDOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return;

	//ü�� ����
	_hp -= 2;
	if (_hp < 0)
	{
		//ü���� 0 ���϶�� knockdown ���� ����
		knockdown(direction);
		return;
	}

	_motion->stop();
	_state = DOWNUP;
	_enemyImg = imgDownup;
	switch (direction)
	{
	case enemy::LEFT:
		_motion = aniLeftDownup;
		break;
	case enemy::RIGHT:
		_motion = aniRightDownup;
		break;
	}
	_motion->start();
}

void enemy::knockdown(DIRECTION direction)
{
	_motion->stop();
	_state = KNOCKDOWN;
	_enemyImg = imgKnockdown;
	switch (direction)
	{
	case enemy::LEFT:
		_motion = aniLeftKnockdown;
		break;
	case enemy::RIGHT:
		_motion = aniRightKnockdown;
		break;
	}
	_motion->start();
}

void enemy::setAlpha()
{
	//���� ���� ����
	_alphaInterval++;

	//���ݿ� ���� ���� ����
	_alphaValue = 140;
	if (_alphaInterval / 13 == 1)
		_alphaValue = 55;
	if (_alphaInterval / 18 == 2)
		_alphaValue = 200;
	if (_alphaInterval / 13 == 3)
		_alphaValue = 140;
	if (_alphaInterval / 13 == 4)
		_alphaValue = 55;
	if (_alphaInterval / 18 == 5)
		_state = REMOVE;
}