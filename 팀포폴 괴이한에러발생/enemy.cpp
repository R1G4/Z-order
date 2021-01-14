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
	//에너미 상태 초기화
	_direction = direction;
	_state = state;
	//좌표 초기화
	_x = x;
	_y = y;
	//이미지 및 애니메이션 적용
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

	//애니메이션 실행
	_motion->start();

	//충돌용 렉트 초기화
	_rc = RectMakeCenter(_x, _y, 40, 200);
	//에너미 렉트 초기화
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	//그림자 렉트 초기화
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());

	//추적 관련 초기화
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//에너미 공격 생성 및 초기화
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

	//밀린 상태라면
	if (_isPush)
	{
		//밀린 힘이 0 이하로 떨어진다면 초기화
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
			//벽에 튕길 시 반대로 미는힘이 작용한다.
			if (_isBounce)
				_x -= _pushPower;
			//그렇지 않을 경우 정상적으로 미는힘이 작용 한다.
			else
				_x += _pushPower;
			_pushPower -= _pushDecrease;
			break;
		case enemy::RIGHT:
			//벽에 튕길 시 반대로 미는힘이 작용한다.
			if (_isBounce)
				_x += _pushPower;
			//그렇지 않을 경우 정상적으로 미는힘이 작용 한다.
			else
				_x -= _pushPower;
			_pushPower -= _pushDecrease;
			break;
		}
	}
	//밀린 상태가 아니라면 튕기는 상태도 아니므로 초기화한다.
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
	//해당 상태일 시 제외
	if (_state == DAZED || _state == DOWNUP || _state == KNOCKDOWN || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return false;

	//0부터 3까지의 난수를 받아서(4가지 경우의 수 중 1개) 0이 아닐 경우 제외
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
	//해당 상태일 시 제외
	if (_state == BLOCK || _state == DOWNUP || _state == KNOCKDOWN || _state == DOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return;

	//체력 설정
	_hp--;
	if (_hp <= 0)
	{
		//체력이 0 이하라면 knockdown 상태 설정
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
	//해당 상태일 시 제외
	if (_state == BLOCK || _state == DOWNUP || _state == KNOCKDOWN || _state == BLOCK || _state == DEAD || _state == REMOVE)
		return;

	//체력 설정
	_hp -= 2;

	_isPush = true;
	if (_hp <= 0)
	{
		//체력이 0 이하라면 knockdown 상태 설정
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
	//투명도 설정 간격
	_alphaInterval++;

	//간격에 따른 투명도 조절
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
	//처음 튕길 경우 미는 힘에 튕기는 힘을 더해준다.
	if (!_isBounce)
		_pushPower += 0.2f;

	//튕기는 상태로 전환한다.
	_isBounce = true;
}
