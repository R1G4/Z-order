#include "stdafx.h"
#include "schoolGirl.h"
#include "kyoko.h"

schoolGirl::schoolGirl()
{
}


schoolGirl::~schoolGirl()
{
}

HRESULT schoolGirl::init(float x, float y)
{
	//enemy::init();
	addFrame();
	_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Taunt");
	_shadowImg = IMAGEMANAGER->findImage("Girl_Shadow");
	_motion = KEYANIMANAGER->findAnimation("Girl_LeftTaunt");
	_motion->start();
	_x = x;
	_y = y;
	_angle = 0;
	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(),_schoolGirlImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right)/2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
	_isAction = false;
	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	_questInterval = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);
	_direction = LEFT;
	_state = TAUNT;
	_enemyAttack = new enemyAttack;
	_enemyAttack->init();
	return S_OK;
}

void schoolGirl::release()
{
}

void schoolGirl::update()
{
	_enemyAttack->update();

	state();

	move();

	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(),_schoolGirlImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right) / 2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void schoolGirl::state()
{
	//애니메이션이 멈춘 경우 IDLE로 전환
	if (!_motion->isPlay())
	{
		switch (_direction)
		{
		case RIGHT:
			_motion->stop();
			_state = IDLE;
			_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Idle");
			_motion = KEYANIMANAGER->findAnimation("Girl_RightIdle");
			_motion->start();
			break;
		case LEFT:
			_motion->stop();
			_state = IDLE;
			_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Idle");
			_motion = KEYANIMANAGER->findAnimation("Girl_LeftIdle");
			_motion->start();
			break;
		}
	}

	//거리안에 
	float distance = getDistance(_x, _y, _kyoko->getRect().left, _kyoko->getRect().top);
	//cout << _kyoko->getShadow().left<<endl;
	if (distance < 500 && _isAction)
	{
		_isFollow = true;
		RECT temp;
		if (IntersectRect(&temp, &_kyoko->getRect(), &_schoolGirlRc))
		{
			switch (_state)
			{
			case schoolGirl::IDLE:
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

			case schoolGirl::WALK: case schoolGirl::RUN:
				_motion->stop();
				break;
			case schoolGirl::ATTACK:
				if (_isAttack)
				{
					_isAttack = false;

					switch (_direction)
					{
					case schoolGirl::LEFT:
						_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Attack");
						_motion = KEYANIMANAGER->findAnimation("Girl_LeftAttack");
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Attack");
						_motion = KEYANIMANAGER->findAnimation("Girl_RightAttack");
						_motion->start();
						break;
					}
				}
				break;
			case schoolGirl::COMBO_ATTACK_1:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = IMAGEMANAGER->findImage("Girl_ComboAttack1");
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = KEYANIMANAGER->findAnimation("Girl_LeftComboAttack1");
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_motion = KEYANIMANAGER->findAnimation("Girl_RightComboAttack1");
						_motion->start();
						break;
					}
				}
				break;
			case schoolGirl::COMBO_ATTACK_2:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = IMAGEMANAGER->findImage("Girl_ComboAttack2");
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = KEYANIMANAGER->findAnimation("Girl_LeftComboAttack2");
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_motion = KEYANIMANAGER->findAnimation("Girl_RightComboAttack2");
						_motion->start();
						break;
					}
				}
				break;
			case schoolGirl::COMBO_ATTACK_3:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = IMAGEMANAGER->findImage("Girl_ComboAttack3");
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = KEYANIMANAGER->findAnimation("Girl_LeftComboAttack3");
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_motion = KEYANIMANAGER->findAnimation("Girl_RightComboAttack3");
						_motion->start();
						break;
					}
				}
				break;
			}
			return;
		}

		if (_kyoko->getKyokoPoint().x > _x)
		{
			if (((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Run");
				_motion = KEYANIMANAGER->findAnimation("Girl_RightRun");
				_motion->start();
			}
			else if (((_direction != RIGHT && _state != WALK) || (_direction == LEFT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 275)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = WALK;
				_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Walk");
				_motion = KEYANIMANAGER->findAnimation("Girl_RightWalk");
				_motion->start();
			}
		}
		else if (_kyoko->getKyokoPoint().x <= _x)
		{
			if (((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Run");
				_motion = KEYANIMANAGER->findAnimation("Girl_LeftRun");
				_motion->start();
			}
			else if (((_direction != LEFT && _state != WALK) || (_direction == RIGHT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 275)
			{
				_motion->stop();
				_direction = LEFT;
				_state = WALK;
				_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Walk");
				_motion = KEYANIMANAGER->findAnimation("Girl_LeftWalk");
				_motion->start();
			}
		}
	}
	else
	{
		switch (_state)
		{
			case schoolGirl::IDLE:
				_questInterval--;
				if (_questInterval < _questMin)
				{
					_questMin = RND->getFromIntTo(50, 140);
					_state = WALK;
					_direction = (DIRECTION)RND->getFromIntTo(LEFT, RIGHT + 1);
					_schoolGirlImg = IMAGEMANAGER->findImage("Girl_Walk");
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = KEYANIMANAGER->findAnimation("Girl_LeftWalk");
						break;
					case schoolGirl::RIGHT:
						_motion = KEYANIMANAGER->findAnimation("Girl_RightWalk");
						break;

					}
					_motion->start();
				}
			break;
			case schoolGirl::WALK: case schoolGirl::RUN:
				if (_isFollow)
				{
					_motion->stop();
					_isFollow = false;
				}
				else
				{
					_questInterval--;
					if (_questInterval < 0)
					{
						_questInterval = RND->getFromIntTo(180, 220);
						_motion->stop();
					}
				}
				break;
		}
	}
}

void schoolGirl::move()
{
	_angle = getAngle(_x, _y, _kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y);

	switch (_state)
	{
	case schoolGirl::WALK:
		if (_isFollow)
		{
			_x += cos(_angle) * ENEMYSPEED;
			_y += -sin(_angle) * ENEMYSPEED;
		}
		else
		{
			float tempSpeed = ENEMYSPEED;
			switch (_direction)
			{
			case schoolGirl::LEFT:

				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				if (_x + tempSpeed > WINSIZEX - _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x += ENEMYSPEED;

				break;
			}

		}
		break;
	case schoolGirl::RUN:
		if (_isFollow)
		{
			_x += cos(_angle) * 2 * ENEMYSPEED;
			_y += -sin(_angle) * 2 * ENEMYSPEED;
		}
		else
		{
			float tempSpeed = ENEMYSPEED;

			switch (_direction)
			{
			case schoolGirl::LEFT:
				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				if (_x + tempSpeed > WINSIZEX - _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x += ENEMYSPEED;

				break;
			}
		}
		break;
	}
}

void schoolGirl::render()
{
	Rectangle(getMemDC(), _schoolGirlRc);
	_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150);
	switch (_state)
	{
		case ATTACK:
			_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion);
			break;
		case COMBO_ATTACK_1:
			_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion);
			break;
		case COMBO_ATTACK_2:
			_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 20, _motion);
			break;
		default:
			_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top, _motion);
			break;
	}
}

void schoolGirl::render(POINT camera)
{
	Rectangle(getMemDC(), _schoolGirlRc,camera);
	_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150,camera);
	switch (_state)
	{
	case ATTACK:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion,camera);
		break;
	case COMBO_ATTACK_1:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion,camera);
		break;
	case COMBO_ATTACK_2:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 20, _motion,camera);
		break;
	default:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top, _motion,camera);
		break;
	}

}

void schoolGirl::addFrame()
{
	
	//IMAGEMANAGER->addImage("Girl_Shadow", "SchoolGirl size200/SchoolGirl_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	//_schoolGirlImg = IMAGEMANAGER->addFrameImage("Girl_Idle", "SchoolGirl size200/Girl_Idle.bmp", 0, 0, 1320, 400, 10, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Walk", "SchoolGirl size200/Girl_Walk.bmp", 0, 0, 1394, 400, 12, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Run", "SchoolGirl size200/Girl_Run.bmp", 0, 0, 1780, 400, 10, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Block", "SchoolGirl size200/Girl_Block.bmp", 0, 0, 460, 400, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Attack", "SchoolGirl size200/Girl_Attack.bmp", 0, 0, 1934, 420, 8, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_ComboAttack1", "SchoolGirl size200/Girl_ComboAttack1.bmp", 0, 0, 1505, 430, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_ComboAttack2", "SchoolGirl size200/Girl_ComboAttack2.bmp", 0, 0, 1470, 440, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_ComboAttack3", "SchoolGirl size200/Girl_ComboAttack3.bmp", 0, 0, 2700, 450, 12, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Hit", "SchoolGirl size200/Girl_Hit.bmp", 0, 0, 1626, 400, 9, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Downup", "SchoolGirl size200/Girl_Downup.bmp", 0, 0, 7013, 380, 27, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Dazed", "SchoolGirl size200/Girl_Dazed.bmp", 0, 0, 656, 410, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Jump", "SchoolGirl size200/Girl_Jump.bmp", 0, 0, 432, 400, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Knockdown", "SchoolGirl size200/Girl_Knockdown.bmp", 0, 0, 4361, 380, 17, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Girl_Taunt", "SchoolGirl size200/Girl_Taunt.bmp", 0, 0, 4015, 420, 26, 2, true, RGB(255, 0, 255));

	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightIdle", "Girl_Idle", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftIdle", "Girl_Idle", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightWalk", "Girl_Walk", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftWalk", "Girl_Walk", 24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightRun", "Girl_Run", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftRun", "Girl_Run", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightBlock", "Girl_Block", 0, 3, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftBlock", "Girl_Block", 6, 3, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightAttack", "Girl_Attack", 0, 8, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftAttack", "Girl_Attack", 16, 8, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack1", "Girl_ComboAttack1", 0, 7, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack1", "Girl_ComboAttack1", 14, 7, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack2", "Girl_ComboAttack2", 0, 7, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack2", "Girl_ComboAttack2", 14, 7, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack3", "Girl_ComboAttack3", 0, 12, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack3", "Girl_ComboAttack3", 24, 12, 10, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightHit", "Girl_Hit", 0, 9, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftHit", "Girl_Hit", 18, 9, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightDownup", "Girl_Downup", 0, 27, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftDownup", "Girl_Downup", 54, 27, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightDazed", "Girl_Dazed", 0, 4, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftDazed", "Girl_Dazed", 8, 4, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightJump", "Girl_Jump", 0, 3, 4, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftJump", "Girl_Jump", 6, 3, 4, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightKnockdown", "Girl_Knockdown", 0, 17, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftKnockdown", "Girl_Knockdown", 34, 17, 8, false,  10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightTaunt", "Girl_Taunt", 0, 26, 8, false, ActionCheck, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftTaunt", "Girl_Taunt", 52, 26, 8, false, ActionCheck, this, 10);
}

void schoolGirl::ActionCheck(void* obj)
{
	schoolGirl* k = (schoolGirl*)obj;
	k->_isAction = true;
}

void schoolGirl::RunningCheck(void* obj)
{
	schoolGirl* k = (schoolGirl*)obj;
	//k->_isRunning = false;
}
//void schoolGirl::setRightIdle(void* obj)
//{
//	schoolGirl* k = (schoolGirl*)obj;
//	k->getMotion()->pause();
//	k->getMotion()->stop();
//	k->setImage(IMAGEMANAGER->findImage(+ "Girl_Idle"));
//	k->setState(IDLE);
//	k->setMotion(KEYANIMANAGER->findAnimation("Girl_RightIdle"));
//	k->getMotion()->start();
//}
//
//void schoolGirl::setLeftIdle(void* obj)
//{
//	schoolGirl* k = (schoolGirl*)obj;
//	k->getMotion()->pause();
//	k->getMotion()->stop();
//	k->setImage(IMAGEMANAGER->findImage(k->getKinds() + "_Idle"));
//	k->setState(IDLE);
//	k->setMotion(KEYANIMANAGER->findAnimation(k->getKinds() + "_LeftIdle"));
//	k->getMotion()->start();
//}