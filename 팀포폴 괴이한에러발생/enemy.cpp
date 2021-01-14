#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
	: _angle(0),
	_alphaInterval(0),
	_alphaValue(0),
	_pushPower(5.7f),
	_pushDecrease(0.06f),
	_isAttack(false),
	_isFollow(false),
	_isRunning(false),
	_isCollision(false),
	_isBounce(false)
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

	//�и� ���¶��
	if (_isPush)
	{
		//�и� ���� 0 ���Ϸ� �������ٸ� �ʱ�ȭ
		if (_pushPower <= 0)
		{
			_pushPower = 5.7f;
			_pushDecrease = 0.05f;
			_isPush = false;
			return;
		}

		switch (_direction)
		{
		case enemy::LEFT:
			//���� ƨ�� �� �ݴ�� �̴����� �ۿ��Ѵ�.
			if (_isBounce)
				_x -= _pushPower;
			//�׷��� ���� ��� ���������� �̴����� �ۿ� �Ѵ�.
			else
				_x += _pushPower;
			_pushPower -= _pushDecrease;
			break;
		case enemy::RIGHT:
			//���� ƨ�� �� �ݴ�� �̴����� �ۿ��Ѵ�.
			if (_isBounce)
				_x += _pushPower;
			//�׷��� ���� ��� ���������� �̴����� �ۿ� �Ѵ�.
			else
				_x -= _pushPower;
			_pushPower -= _pushDecrease;
			break;
		}
	}
	//�и� ���°� �ƴ϶�� ƨ��� ���µ� �ƴϹǷ� �ʱ�ȭ�Ѵ�.
	else
		_isBounce = false;
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
	if (_state == DAZED || _state == DOWNUP || _state == KNOCKDOWN || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return false;

	//0���� 3������ ������ �޾Ƽ�(4���� ����� �� �� 1��) 0�� �ƴ� ��� ����
	if (RND->getFromIntTo(0, 4) != 0)
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
	if (_state == BLOCK || _state == DOWNUP || _state == KNOCKDOWN || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return;

	//ü�� ����
	_hp--;
	if (_hp <= 0)
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

	_isPush = true;
	if (_hp <= 0)
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

void enemy::actionCheck(void* obj)
{
	enemy* k = (enemy*)obj;
	k->_isAction = true;
}

void enemy::leftStun(void* obj)
{
	enemy* k = (enemy*)obj;
	if (RND->getFromIntTo(0, 2) >= 1)
	{
		k->getMotion()->stop();
		k->setDirection(LEFT);
		k->setState(DAZED);
		k->setImage(k->getImgDazed());
		k->setMotion(k->getAniLeftDazed());
		k->getMotion()->start();
		k->enemy::effectStun(LEFT);
	}
}

void enemy::rightStun(void* obj)
{
	enemy* k = (enemy*)obj;
	if (RND->getFromIntTo(0, 2) >= 1)
	{
		k->getMotion()->stop();
		k->setDirection(RIGHT);
		k->setState(DAZED);
		k->setImage(k->getImgDazed());
		k->setMotion(k->getAniRightDazed());
		k->getMotion()->start();
		k->enemy::effectStun(RIGHT);
	}
}

void enemy::setDead(void* obj)
{
	enemy* k = (enemy*)obj;
	k->setState(DEAD);
}

void enemy::setBounce()
{
	//ó�� ƨ�� ��� �̴� ���� ƨ��� ���� �����ش�.
	if (!_isBounce)
		_pushPower += 0.2f;

	//ƨ��� ���·� ��ȯ�Ѵ�.
	_isBounce = true;
}
