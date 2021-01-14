#include "stdafx.h"
#include "boss.h"
#include "kyoko.h"


HRESULT boss::init()
{
	setImage();
	setKeyAnimation();

	_bossHPBar = new bossHPBar;
	_bossHPBar->init(WINSIZEX / 2, WINSIZEY / 2 + 100, 437, 35);
	_bossHPBar->setGauge(_bossHP, _maxHP);

	_bossDirection = BOSS_LEFT_IDLE;
	_pahse = PAHSE_1;
	_currentFrameX = _currentFrameY = 0;
	_bossHP = _maxHP = 100;
	_count = _index = _count2 = 0;
	_count3 = _attackCount = 0;
	_jumpPower = _gravity = 0;
	_rnd = 0;
	_randomAttack = 0;
	_isJump = false;
	_isJumping = false;
	_isAttack = false;
	_isTackle = false;
	_isAttacked = false;
	_isGetUp = false;
	_isDizzy = false;

	_leftAttackedCount = 0;
	_rightAttackedCount = 0;

	_speed = 1.5;
	_angle = PI / 2;
	_angle2 = PI / 2;
	_x = WINSIZEX / 2 + 380;
	_y = WINSIZEY / 2 + 100;
	_x2 = WINSIZEX / 2 + 400;
	_y2 = WINSIZEY / 2 + 70;


	_boss->setX(_x);
	_boss->setY(_y);
	_bossShadow->setX(_x2);
	_bossShadow->setY(_y2 + 175);

	_rcBoss = RectMakeCenter(_x, _y, _boss->getFrameWidth(), _boss->getFrameHeight() - 100);
	//_rcSkill = RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100);
	_rcBossShadow = RectMakeCenter(_x2, _y2 + 175, _bossShadow->getWidth(), _bossShadow->getHeight());
	_rcBossAttack = RectMake(0, 0, 0, 0);


	setAttackInfo();



	return S_OK;
}

void boss::release()
{

}

void boss::setAttackRect(BOSSDIRECTION direction)
{
	int index;
	attackInfo attackinfo;
	switch (direction)
	{
	case BOSS_RIGHT_ELBOW: case BOSS_RIGHT_SLAP:

		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.right - 50, _rcBoss.top + attackinfo.plusY, attackinfo.width, attackinfo.height);

		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;
	case BOSS_LEFT_ELBOW: case BOSS_LEFT_SLAP:
		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.left - 50, _rcBoss.top + 100, attackinfo.width, attackinfo.height);
		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;

	case BOSS_RIGHT_GETUP:
		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.right - 300, _rcBoss.bottom - 250, attackinfo.width, attackinfo.height);
		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;
	case BOSS_LEFT_GETUP:
		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.left - 100, _rcBoss.bottom - 250, attackinfo.width, attackinfo.height);
		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;
	case BOSS_RIGHT_ROAR:
		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.right - 300, _rcBoss.bottom - 250, attackinfo.width, attackinfo.height);
		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;
	case BOSS_LEFT_ROAR:
		attackinfo = _mAttackInfo.find(direction)->second;
		index = (int)_bossMotion->getIndex();
		if (attackinfo.index == index)
		{
			_rcBossAttack = RectMake(_rcBoss.left - 100, _rcBoss.bottom - 250, attackinfo.width, attackinfo.height);
		}
		else
			_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;

	default:
		_rcBossAttack = RectMake(_x, _y, 0, 0);
		break;
	}
}

void boss::setAttackInfo()
{
	attackInfo attackTemp;

	//프레임중 실제 공격하는 모션 인덱스만 렉트 적용
	attackTemp.index = 6;	//프레임의 몇번째 인덱스인지
	attackTemp.plusY = 150;
	attackTemp.width = 100;
	attackTemp.height = 100;
	_mAttackInfo.insert(make_pair(BOSS_RIGHT_ELBOW, attackTemp));
	_mAttackInfo.insert(make_pair(BOSS_LEFT_ELBOW, attackTemp));

	attackTemp.index = 8;
	attackTemp.plusY = 150;
	attackTemp.width = 150;
	attackTemp.height = 100;
	_mAttackInfo.insert(make_pair(BOSS_LEFT_SLAP, attackTemp));
	_mAttackInfo.insert(make_pair(BOSS_RIGHT_SLAP, attackTemp));

	attackTemp.index = 5;
	attackTemp.plusY = 200;
	attackTemp.width = 300;
	attackTemp.height = 300;
	_mAttackInfo.insert(make_pair(BOSS_LEFT_GETUP, attackTemp));
	_mAttackInfo.insert(make_pair(BOSS_RIGHT_GETUP, attackTemp));

	attackTemp.index = 5;
	attackTemp.plusY = 200;
	attackTemp.width = 300;
	attackTemp.height = 300;
	_mAttackInfo.insert(make_pair(BOSS_LEFT_ROAR, attackTemp));
	_mAttackInfo.insert(make_pair(BOSS_RIGHT_ROAR, attackTemp));
}


void boss::move()
{
	if (_bossDirection == BOSS_LEFT_WALK || _bossDirection == BOSS_RIGHT_WALK)
	{
		_angle = getAngle(_x, _y, (_player->getRect().left + _player->getRect().right) / 2, (_player->getRect().top + _player->getRect().bottom) / 2);
		_x += cosf(_angle) * BOSSSPEED;
		_y += -sinf(_angle) * BOSSSPEED;
		_x2 += cosf(_angle) * BOSSSPEED;
		_y2 += -sinf(_angle) * BOSSSPEED;
	}


	if (_bossDirection == BOSS_LEFT_JUMPUP || _bossDirection == BOSS_LEFT_JUMPDOWN
		|| _bossDirection == BOSS_RIGHT_JUMPUP || _bossDirection == BOSS_RIGHT_JUMPDOWN)
	{
		_angle = getAngle(_x2, _y2, (_player->getShadow().left + _player->getShadow().right) / 2, (_player->getShadow().top + _player->getShadow().bottom) / 2);
		_x += cosf(_angle) * BOSSSPEED;
		_y += -sinf(_angle) * BOSSSPEED;
		_x2 += cosf(_angle) * BOSSSPEED * 3;
		_y2 += -sinf(_angle) * BOSSSPEED * 3;
	}

	if (_bossDirection == BOSS_LEFT_TACKLE || _bossDirection == BOSS_RIGHT_TACKLE)
	{
		_angle = getAngle(_x2, _y2, (_player->getShadow().left + _player->getShadow().right) / 2, (_player->getShadow().top + _player->getShadow().bottom) / 2);
		_x += cosf(_angle) * BOSSSPEED * 3;
		_y += -sinf(_angle) * BOSSSPEED * 3;
		_x2 += cosf(_angle) * BOSSSPEED * 3;
		_y2 += -sinf(_angle) * BOSSSPEED * 3;
	}


	if (_bossDirection == BOSS_LEFT_IDLE || _bossDirection == BOSS_RIGHT_IDLE)
	{
		_isAttack = false;
	}
}



void boss::update()
{

	RECT _temp;

	_distance = getDistance(_x, _y, (_player->getRect().left + _player->getRect().right) / 2, (_player->getRect().top + _player->getRect().bottom) / 2);
	//평상시 걷거나 할때 상태
	if (!_isJump)
	{
		_rcBoss = RectMakeCenter(_x, _y, _boss->getFrameWidth(), _boss->getFrameHeight());		//보스렉트
		//_rcSkill = RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100);	//보스 스킬 렉트
		_rcBossShadow = RectMakeCenter(_x, _rcBoss.bottom, _bossShadow->getWidth(), _bossShadow->getHeight());	//보스 그림자 렉트
	}
	//점프뛰었을때
	else
	{
		_rcBoss = RectMakeCenter(_x2, _y, _boss->getFrameWidth(), _boss->getFrameHeight());
		//_rcSkill = RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100);
		_rcBossShadow = RectMakeCenter(_x2, _y2, _bossShadow->getWidth(), _bossShadow->getHeight());
	}

	if (_bossDirection == BOSS_LEFT_DIE_END || _bossDirection == BOSS_RIGHT_DIE_END)
	{
		return;
	}


	if (!_isAttacked)	//맞은상태가 아닐때 공격모션 실행
	{



		//근거리
		if (_distance < 500 && !_isAttack && _bossHP > 0)
		{
			//플레이어가 우측에 있을때
			if (_player->getKyokoPoint().x > _x && !_isJump)
			{
				RECT _temp;
				if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
				{
					int rnd = RND->getFromIntTo(0, 2);
					BOSSDIRECTION tempDirection = rnd == 0 ? BOSS_RIGHT_ELBOW : BOSS_RIGHT_SLAP;

					if (!_isAttack && _bossDirection != BOSS_RIGHT_ELBOW && tempDirection == BOSS_RIGHT_ELBOW)
					{
						_bossMotion->stop();
						_bossDirection = BOSS_RIGHT_ELBOW;
						_boss = IMAGEMANAGER->findImage("boss_elbow");
						_bossMotion = KEYANIMANAGER->findAnimation("boss_rightElbow");
						_bossMotion->start();
						SOUNDMANAGER->play("slap", 0.5f);
						_isAttack = true;
					}
					if (!_isAttack && _bossDirection != BOSS_RIGHT_SLAP && tempDirection == BOSS_RIGHT_SLAP)
					{
						_bossMotion->stop();
						_bossDirection = BOSS_RIGHT_SLAP;
						_boss = IMAGEMANAGER->findImage("boss_slap");
						_bossMotion = KEYANIMANAGER->findAnimation("boss_rightSlap");
						_bossMotion->start();
						SOUNDMANAGER->play("slap", 0.5f);
						_isAttack = true;
					}
				}
				else if (_bossDirection == BOSS_LEFT_WALK || _bossDirection == BOSS_LEFT_IDLE || _bossDirection == BOSS_RIGHT_IDLE)
				{
					_bossMotion->stop();
					_isAttack = false;
					_bossDirection = BOSS_RIGHT_WALK;
					_boss = IMAGEMANAGER->findImage("boss_walk");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_rightWalk");
					_bossMotion->start();
				}
			}
			else
			{
				RECT _temp;
				if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
				{
					int rnd = RND->getFromIntTo(0, 2);
					BOSSDIRECTION tempDirection = rnd == 0 ? BOSS_LEFT_ELBOW : BOSS_LEFT_SLAP;

					if (!_isAttack && _bossDirection != BOSS_LEFT_ELBOW && tempDirection == BOSS_LEFT_ELBOW)
					{
						_bossMotion->stop();
						_bossDirection = BOSS_LEFT_ELBOW;
						_boss = IMAGEMANAGER->findImage("boss_elbow");
						_bossMotion = KEYANIMANAGER->findAnimation("boss_leftElbow");
						_bossMotion->start();
						SOUNDMANAGER->play("slap", 0.5f);
						_isAttack = true;
					}
					if (!_isAttack&&_bossDirection != BOSS_LEFT_SLAP && tempDirection == BOSS_LEFT_SLAP)
					{
						_bossMotion->stop();
						_bossDirection = BOSS_LEFT_SLAP;
						_boss = IMAGEMANAGER->findImage("boss_slap");
						_bossMotion = KEYANIMANAGER->findAnimation("boss_leftSlap");
						_bossMotion->start();
						SOUNDMANAGER->play("slap", 0.5f);
						_isAttack = true;
					}
				}
				else if (_bossDirection == BOSS_RIGHT_WALK || _bossDirection == BOSS_LEFT_IDLE || _bossDirection == BOSS_RIGHT_IDLE)
				{
					_bossMotion->stop();
					_bossDirection = BOSS_LEFT_WALK;
					_boss = IMAGEMANAGER->findImage("boss_walk");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_leftWalk");
					_bossMotion->start();
				}
			}
		}

		//원거리
		if (_distance > 500 && !_isAttack && _pahse != PAHSE_1 && _bossHP > 0)	// _isAttack 한번만 돌게
		{
			int rnd = RND->getInt(2);

			switch (rnd)
			{
			case 0:
				_y2 = _rcBoss.bottom;	//점프 한번만 뛰었을때 그림자y축이랑 보스 바텀 체인지
				SOUNDMANAGER->play("jump_up", 0.5f);
				if (_player->getKyokoPoint().x > _x)
				{
					_bossMotion->stop();
					_bossDirection = BOSS_RIGHT_JUMPUP;
					_boss = IMAGEMANAGER->findImage("boss_jumpUp");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_rightJumpUp");
					_bossMotion->start();
					_isAttack = true;
					_isJump = true;
				}
				else
				{
					_bossMotion->stop();
					_bossDirection = BOSS_LEFT_JUMPUP;
					_boss = IMAGEMANAGER->findImage("boss_jumpUp");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_leftJumpUp");
					_bossMotion->start();
					_isAttack = true;
					_isJump = true;
				}
				break;
			case 1:
				SOUNDMANAGER->play("tackle", 0.5f);
				if (_player->getKyokoPoint().x > _x && !_isTackle)
				{
					RECT _temp;
					_bossMotion->stop();
					_x2 += BOSSSPEED * 2;
					_bossDirection = BOSS_RIGHT_TACKLE;
					_boss = IMAGEMANAGER->findImage("boss_tackle");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_rightTackle");
					_bossMotion->start();
					_isAttack = true;
					_isTackle = true;
				}
				if (_player->getKyokoPoint().x < _x && !_isTackle)
				{
					_bossMotion->stop();
					_x2 -= BOSSSPEED * 2;
					_bossDirection = BOSS_LEFT_TACKLE;
					_boss = IMAGEMANAGER->findImage("boss_tackle");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_leftTackle");
					_bossMotion->start();
					_isAttack = true;
					_isTackle = true;
				}
				break;
			default:
				break;
			}

		}


		move();
		jumpUp();
		tackle();

	}//isAttacked 끝


	if (_bossDirection == BOSS_LEFT_IDLE || _bossDirection == BOSS_RIGHT_IDLE)
	{
		_isAttacked = false;
	}
	cout << _isAttacked << endl;

	leftDizzy();
	rightDizzy();
	pahse();
	setAttackRect(_bossDirection);
	effect(_bossDirection);
	_bossHPBar->setX(WINSIZEX / 2 - 250);
	_bossHPBar->setY(WINSIZEY / 2 + 245);
	_bossHPBar->setGauge(_bossHP, _maxHP);
	_bossHPBar->update();

}

void boss::jumpUp()
{
	RECT _temp;
	_jumpPower -= _gravity;
	_y -= _jumpPower;

	if (_rcBoss.top <= -1000 && _bossDirection == BOSS_RIGHT_JUMPUP)
	{
		_isJumping = true;
		_gravity = 1.4f;
		_bossMotion->stop();
		_bossDirection = BOSS_RIGHT_JUMPDOWN;
		_boss = IMAGEMANAGER->findImage("boss_jumpDown");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightJumpDown");

		_bossMotion->start();
	}

	if (_rcBoss.top <= -1000 && _bossDirection == BOSS_LEFT_JUMPUP)
	{
		_isJumping = true;
		_gravity = 1.4f;
		_bossMotion->stop();
		_bossDirection = BOSS_LEFT_JUMPDOWN;
		_boss = IMAGEMANAGER->findImage("boss_jumpDown");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftJumpDown");
		_bossMotion->start();
	}


	if (_bossMotion->getBossIndex() >= 6 && _isJump && !_isJumping)
	{
		_jumpPower = 45;
		_gravity = 0.6f;
	}
	if (_rcBoss.bottom >= _rcBossShadow.top && _isJumping && _bossDirection == BOSS_RIGHT_JUMPDOWN)
	{
		_y = _y - 50;
		_jumpPower = 0;
		_gravity = 0;
		_isJumping = false;
		_isJump = false;
		_bossMotion->stop();
		_bossDirection = BOSS_RIGHT_JUMPDOWN_END;
		_boss = IMAGEMANAGER->findImage("boss_jumpDownEnd");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightJumpDownEnd");
		_x = _x2;
		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			_player->setHit(true);
		}
		_bossMotion->start();
		SOUNDMANAGER->play("jump_down", 0.5f);
	}
	if (_rcBoss.bottom >= _rcBossShadow.top && _isJumping && _bossDirection == BOSS_LEFT_JUMPDOWN)
	{
		_y = _y - 50;
		_jumpPower = 0;
		_gravity = 0;
		_isJumping = false;
		_isJump = false;
		_bossMotion->stop();
		_bossDirection = BOSS_LEFT_JUMPDOWN_END;
		_boss = IMAGEMANAGER->findImage("boss_jumpDownEnd");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftJumpDownEnd");
		_x = _x2;
		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			_player->setHit(true);
		}
		_bossMotion->start();
	}

}

void boss::tackle()
{
	RECT _temp;

	if (_isTackle && (_bossMotion->getBossIndex() >= 3) && _player->getKyokoPoint().x > _x)
	{
		RECT _temp;
		_bossMotion->stop();
		_x2 -= BOSSSPEED * 2;
		_bossDirection = BOSS_RIGHT_TACKLE;
		_boss = IMAGEMANAGER->findImage("boss_tackle");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightTackleLoop");
		_bossMotion->start();
		_isAttack = true;
		_isTackle = true;
		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			_bossMotion->stop();
			_bossDirection = BOSS_RIGHT_TAUNT;
			_boss = IMAGEMANAGER->findImage("boss_taunt");
			_bossMotion = KEYANIMANAGER->findAnimation("boss_rightTaunt");
			_player->setHit(true);
			_bossMotion->start();
			SOUNDMANAGER->play("taunt", 0.5f);
			_isTackle = false;
		}
	}
	if (_isTackle && (_bossMotion->getBossIndex() >= 3) && _player->getKyokoPoint().x < _x)
	{
		_bossMotion->stop();
		_x2 -= BOSSSPEED * 2;
		_bossDirection = BOSS_LEFT_TACKLE;
		_boss = IMAGEMANAGER->findImage("boss_tackle");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftTackleLoop");
		_bossMotion->start();
		_isAttack = true;
		_isTackle = true;
		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			_bossMotion->stop();
			_bossDirection = BOSS_LEFT_TAUNT;
			_boss = IMAGEMANAGER->findImage("boss_taunt");
			_bossMotion = KEYANIMANAGER->findAnimation("boss_leftTaunt");
			_player->setHit(true);
			_bossMotion->start();
			SOUNDMANAGER->play("taunt", 0.5f);
			_isTackle = false;
		}
	}
}


//플레이어 한테 맞았을때
void boss::leftAttackedMotion()
{
	if (_bossHP <= 0)
	{
		return;
	}

	if (!_isJump && !_isAttacked && _leftAttackedCount == 0)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		_bossDirection = BOSS_LEFT_GETHIT_1;
		_boss = IMAGEMANAGER->findImage("boss_getHit_1");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_1");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit1", 0.5f);
		_leftAttackedCount++;
	}
	if (!_isJump && !_isAttacked && _leftAttackedCount == 1)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		_bossDirection = BOSS_LEFT_GETHIT_2;
		_boss = IMAGEMANAGER->findImage("boss_getHit_2");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_2");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit2", 0.5f);
		_leftAttackedCount++;
	}
	if (!_isJump && !_isAttacked && _leftAttackedCount == 2)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		_bossDirection = BOSS_LEFT_GETHIT_3;
		_boss = IMAGEMANAGER->findImage("boss_getHit_3");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_3");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit3", 0.5f);
		_leftAttackedCount++;
	}

	if (_leftAttackedCount >= 3)
	{
		_leftAttackedCount = 0;
	}
}

void boss::rightAttackedMotion()
{
	if (_bossHP <= 0)
	{
		return;
	}
	if (!_isJump && !_isAttacked && _rightAttackedCount == 0)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		_bossDirection = BOSS_RIGHT_GETHIT_1;
		_boss = IMAGEMANAGER->findImage("boss_getHit_1");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_1");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit1", 0.5f);
		_rightAttackedCount++;
	}
	if (!_isJump && !_isAttacked && _rightAttackedCount == 1)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		_bossDirection = BOSS_RIGHT_GETHIT_2;
		_boss = IMAGEMANAGER->findImage("boss_getHit_2");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_2");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit2", 0.5f);
		_rightAttackedCount++;
	}

	if (!_isJump && !_isAttacked && _rightAttackedCount == 2)
	{
		_bossMotion->stop();
		_isAttack = false;
		_isAttacked = true;
		//_isDizzy = true;
		_bossDirection = BOSS_RIGHT_GETHIT_3;
		_boss = IMAGEMANAGER->findImage("boss_getHit_3");
		_bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_3");
		_bossMotion->start();
		SOUNDMANAGER->play("gethit3", 0.5f);
		_rightAttackedCount++;
	}

	if (_rightAttackedCount >= 3)
	{
		_rightAttackedCount = 0;
	}
}

void boss::leftDizzy()
{
	RECT _temp;
	if (_bossHP <= 0)
	{
		return;
	}


	if (_player->getKyokoPoint().x < _x && _bossDirection != BOSS_LEFT_ROAR && _bossDirection != BOSS_RIGHT_ROAR)
	{
		if (_bossDirection == BOSS_LEFT_GETHIT_3 && !_isDizzy)
		{

			if (_bossMotion->getBossIndex() >= 8)///////////////////////////////////////
			{
				cout << "getdizz" << endl;
				_bossMotion->stop();
				_isDizzy = true;
				_bossDirection = BOSS_LEFT_DIZZY;
				_boss = IMAGEMANAGER->findImage("boss_dizzy");
				_bossMotion = KEYANIMANAGER->findAnimation("boss_leftDizzy");
				_bossMotion->start();
			}
		}

		if (_isDizzy)
		{
			_count++;
			if (_count < 200)
			{
				if (IntersectRect(&_temp, &_player->getAttackRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
				{
					_bossMotion->stop();
					_bossDirection = BOSS_LEFT_GROUNDHIT;
					_boss = IMAGEMANAGER->findImage("boss_groundHit");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_leftGroundHit");
					_bossMotion->start();
					SOUNDMANAGER->play("groundhit", 0.5f);
				}
			}
			if ((_count > 200 && _count < 400) && (_bossDirection != BOSS_LEFT_IDLE && _bossDirection != BOSS_RIGHT_IDLE))
			{
				_bossMotion->stop();
				_isDizzy = false;
				_bossDirection = BOSS_LEFT_GETUP;
				_boss = IMAGEMANAGER->findImage("boss_getUp");
				_bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetUp");
				_bossMotion->start();
			}
		}
		else
		{
			_count = 0;
		}
	}
}
void boss::rightDizzy()
{
	RECT _temp;
	if (_bossHP <= 0)
	{
		return;
	}


	if (_player->getKyokoPoint().x > _x && _bossDirection != BOSS_LEFT_ROAR && _bossDirection != BOSS_RIGHT_ROAR)
	{
		if (_bossDirection == BOSS_RIGHT_GETHIT_3 && !_isDizzy)
		{
			if (_bossMotion->getBossIndex() >= 8)
			{
				cout << "bbbbb" << endl;
				_bossMotion->stop();
				_isDizzy = true;
				_bossDirection = BOSS_RIGHT_DIZZY;
				_boss = IMAGEMANAGER->findImage("boss_dizzy");
				_bossMotion = KEYANIMANAGER->findAnimation("boss_rightDizzy");
				_bossMotion->start();

			}
		}

		if (_isDizzy)
		{
			_count++;
			if (_count < 200)
			{
				if (IntersectRect(&_temp, &_player->getAttackRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
				{
					_bossMotion->stop();
					_bossDirection = BOSS_RIGHT_GROUNDHIT;
					_boss = IMAGEMANAGER->findImage("boss_groundHit");
					_bossMotion = KEYANIMANAGER->findAnimation("boss_rightGroundHit");
					_bossMotion->start();
					SOUNDMANAGER->play("groundhit", 0.5f);
				}
			}
			if (_count > 200 && _count < 400 && (_bossDirection != BOSS_LEFT_IDLE && _bossDirection != BOSS_RIGHT_IDLE))
			{
				_bossMotion->stop();
				_isDizzy = false;
				_bossDirection = BOSS_RIGHT_GETUP;
				_boss = IMAGEMANAGER->findImage("boss_getUp");
				_bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetUp");
				_bossMotion->start();
			}
		}
		else
		{
			_count = 0;
		}
	}
}

void boss::pahse()
{
	if (_bossHP < 100 && _bossHP > 70)
	{
		_pahse = PAHSE_1;
	}
	if (_bossHP < 70 && _bossHP > 30)
	{
		_pahse = PAHSE_2;
	}
	if (_bossHP > 0 && _bossHP < 30)
	{
		_pahse = PAHSE_3;
	}
	if (_bossHP <= 0)
	{
		_pahse = PAHSE_DEFEAT;
		_isAlive = false;
	}
}


void boss::rightAttackted(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();
	switch (k->_bossDirection)
	{
	case BOSS_LEFT_ELBOW: case BOSS_RIGHT_ELBOW: case BOSS_LEFT_SLAP: 	case BOSS_RIGHT_SLAP:
	case BOSS_LEFT_ROAR: 	case BOSS_RIGHT_ROAR:
		k->_isAttack = false;
		break;
	}

	if (k->_bossHP <= 0)
	{
		k->_bossDirection = BOSS_RIGHT_DIE;
		k->_boss = IMAGEMANAGER->findImage("boss_die");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightDie");
		k->_bossMotion->start();
	}
	else if (k->_bossHP == 70 || k->_bossHP == 30)
	{
		SOUNDMANAGER->play("roar", 0.5f);
		k->_bossDirection = BOSS_RIGHT_ROAR;
		k->_boss = IMAGEMANAGER->findImage("boss_roar");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightRoar");
		k->_bossMotion->start();

	}
	else
	{
		k->_bossDirection = BOSS_RIGHT_IDLE;
		k->_boss = IMAGEMANAGER->findImage("boss_idle");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightIdle");
		k->_bossMotion->start();
	}

}
void boss::leftAttackted(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();
	switch (k->_bossDirection)
	{
	case BOSS_LEFT_ELBOW: case BOSS_RIGHT_ELBOW: case BOSS_LEFT_SLAP: 	case BOSS_RIGHT_SLAP:
		k->_isAttack = false;
		break;
	}

	if (k->_bossHP <= 0)
	{
		k->_bossDirection = BOSS_LEFT_DIE;
		k->_boss = IMAGEMANAGER->findImage("boss_die");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftDie");
		k->_bossMotion->start();
	}
	else if (k->_bossHP == 70 || k->_bossHP == 30)
	{
		SOUNDMANAGER->play("roar", 0.5f);
		k->_bossDirection = BOSS_LEFT_ROAR;
		k->_boss = IMAGEMANAGER->findImage("boss_roar");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftRoar");
		k->_bossMotion->start();

	}
	else
	{
		k->_bossDirection = BOSS_LEFT_IDLE;
		k->_boss = IMAGEMANAGER->findImage("boss_idle");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftIdle");
		k->_bossMotion->start();
	}


}

void boss::setLeftIdle(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();
	switch (k->_bossDirection)
	{
	case BOSS_LEFT_ELBOW: case BOSS_RIGHT_ELBOW: case BOSS_LEFT_SLAP: 	case BOSS_RIGHT_SLAP:
		k->_isAttack = false;
		break;
	}

	k->_bossDirection = BOSS_LEFT_IDLE;
	k->_boss = IMAGEMANAGER->findImage("boss_idle");
	k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftIdle");
	k->_bossMotion->start();
}

void boss::setRightIdle(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();
	switch (k->_bossDirection)
	{
	case BOSS_LEFT_ELBOW: case BOSS_RIGHT_ELBOW: case BOSS_LEFT_SLAP: 	case BOSS_RIGHT_SLAP:
		k->_isAttack = false;
		break;
	}

	k->_bossDirection = BOSS_RIGHT_IDLE;
	k->_boss = IMAGEMANAGER->findImage("boss_idle");
	k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightIdle");
	k->_bossMotion->start();
}




void boss::setLeftDizzy(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();

	if (k->_bossHP <= 0)
	{
		k->_bossDirection = BOSS_LEFT_DIE;
		k->_boss = IMAGEMANAGER->findImage("boss_die");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftDie");
		k->_bossMotion->start();
	}
	else if (k->_bossHP == 70 || k->_bossHP == 30)
	{
		k->_bossDirection = BOSS_LEFT_ROAR;
		k->_boss = IMAGEMANAGER->findImage("boss_roar");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftRoar");
		k->_bossMotion->start();
	}
	else
	{
		k->_bossDirection = BOSS_LEFT_DIZZY;
		k->_boss = IMAGEMANAGER->findImage("boss_dizzy");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftDizzy");
		k->_bossMotion->start();
	}



}


void boss::setRightDizzy(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();

	if (k->_bossHP <= 0)
	{
		k->_bossDirection = BOSS_RIGHT_DIE;
		k->_boss = IMAGEMANAGER->findImage("boss_die");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightDie");
		k->_bossMotion->start();
	}
	else if (k->_bossHP == 70 || k->_bossHP == 30)
	{
		k->_bossDirection = BOSS_RIGHT_ROAR;
		k->_boss = IMAGEMANAGER->findImage("boss_roar");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightRoar");
		k->_bossMotion->start();
	}
	else
	{
		k->_bossDirection = BOSS_RIGHT_DIZZY;
		k->_boss = IMAGEMANAGER->findImage("boss_dizzy");
		k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightDizzy");
		k->_bossMotion->start();
	}
}

void boss::setLeftDieEnd(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();

	k->_bossDirection = BOSS_LEFT_DIE_END;
	k->_boss = IMAGEMANAGER->findImage("boss_die");
	k->_bossMotion = KEYANIMANAGER->findAnimation("boss_leftDieEND");
	k->_bossMotion->start();
	SOUNDMANAGER->play("die", 0.5f);
}

void boss::setRightDieEnd(void * obj)
{
	boss* k = (boss*)obj;
	k->_bossMotion->stop();

	k->_bossDirection = BOSS_RIGHT_DIE_END;
	k->_boss = IMAGEMANAGER->findImage("boss_die");
	k->_bossMotion = KEYANIMANAGER->findAnimation("boss_rightDieEND");
	k->_bossMotion->start();
	SOUNDMANAGER->play("die", 0.5f);
}

void boss::effect(BOSSDIRECTION direction)
{
	RECT _temp;
	switch (direction)
	{
	case BOSS_LEFT_JUMPDOWN_END: case BOSS_RIGHT_JUMPDOWN_END:

		if (_bossMotion->getBossIndex() == 0)
		{
			CAMERAMANAGER->setTime(1);
			EFFECTMANAGER->play("crack", _x, _rcBoss.bottom - 30);
		}
		break;
	case BOSS_LEFT_SLAP: case BOSS_LEFT_ELBOW: case BOSS_LEFT_GETUP: case BOSS_LEFT_ROAR:
		if (IntersectRect(&_temp, &_player->getRect(), &_rcBossAttack))
		{
			EFFECTMANAGER->play("hit", _x - 150, _y);
		}
		break;
	case BOSS_RIGHT_SLAP: case BOSS_RIGHT_ELBOW: case BOSS_RIGHT_GETUP: case BOSS_RIGHT_ROAR:
		if (IntersectRect(&_temp, &_player->getRect(), &_rcBossAttack))
		{
			EFFECTMANAGER->play("hit", _x + 150, _y);
		}
		break;
	case BOSS_LEFT_TACKLE:
		if (_bossMotion->getBossIndex() == 0)
		{
			EFFECTMANAGER->play("dash", _rcBoss.right + 10, _y + 50);
			CAMERAMANAGER->setTime(2);
		}

		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			EFFECTMANAGER->play("hit", _rcBoss.left - 10, _y);
		}
		break;
	case BOSS_RIGHT_TACKLE:
		if (_bossMotion->getBossIndex() == 0)
		{
			EFFECTMANAGER->play("dash", _rcBoss.left - 10, _y + 50);
			CAMERAMANAGER->setTime(2);

		}
		if (IntersectRect(&_temp, &_player->getRect(), &RectMakeCenter(_x, _y, 300, _boss->getFrameHeight() - 100)))
		{
			EFFECTMANAGER->play("hit", _rcBoss.right + 10, _y);
		}
		break;

	}
}

void boss::render()
{
	//_bossHPImage->render(getMemDC(), WINSIZEX / 2 - 265, WINSIZEY / 2 + 285);
	//Rectangle(getMemDC(), _rcBoss);
	//Rectangle(getMemDC(), _rcBossAttack);

	_boss->aniRender(getMemDC(), _rcBoss.left, _rcBoss.top, _bossMotion);
	_bossShadow->render(getMemDC(), _rcBossShadow.left, _rcBossShadow.top);

	//_bossHPBar->render();

}

void boss::render(POINT camera)
{
	//_bossHPImage->render(getMemDC(), WINSIZEX / 2 - 265, WINSIZEY / 2 + 285);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rcBoss, camera);
		Rectangle(getMemDC(), _rcBossAttack, camera);


	}
	EFFECTMANAGER->render(camera);
	_bossShadow->render(getMemDC(), _rcBossShadow.left, _rcBossShadow.top, camera);
	_boss->aniRender(getMemDC(), _rcBoss.left, _rcBoss.top, _bossMotion, camera);

	//_bossHPBar->render();

}

void boss::hpRender()
{
	_bossHPImage->render(getMemDC(), WINSIZEX / 2 - 265, WINSIZEY / 2 + 230);
	_bossHPBar->render();
}

void boss::hitDamage(float damage)
{
	_bossHP -= damage;
}

void boss::setImage()
{
	_boss = IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 0, 0, 3180, 634, 12, 2, true, RGB(255, 0, 255));
	_bossShadow = IMAGEMANAGER->addImage("boss_shadow", "image/boss/boss_shadow3.bmp", 250, 70, true, RGB(255, 0, 255));
	_bossMap = IMAGEMANAGER->addImage("boss_map", "image/boss/boss_map.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_bossHPImage = IMAGEMANAGER->addImage("boss_HP", "image/boss/boss_HP.bmp", 560, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_tackle", "image/boss/boss_tackle.bmp", 0, 0, 2882, 576, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_die", "image/boss/boss_die.bmp", 0, 0, 4576, 576, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_taunt", "image/boss/boss_taunt.bmp", 0, 0, 6900, 600, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_slap", "image/boss/boss_slap.bmp", 0, 0, 5278, 582, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_elbow", "image/boss/boss_elbow.bmp", 0, 0, 2915, 652, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_punch", "image/boss/boss_punch.bmp", 0, 0, 8100, 600, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_wupunch", "image/boss/boss_wupunch.bmp", 0, 0, 11880, 594, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_roar", "image/boss/boss_roar.bmp", 0, 0, 2916, 576, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 0, 0, 2110, 588, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_down", "image/boss/boss_down.bmp", 0, 0, 6600, 450, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jumpUp", "image/boss/boss_jumpUp.bmp", 0, 0, 1888, 672, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jumpDown", "image/boss/boss_jumpDown.bmp", 0, 0, 480, 460, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jumpDownEnd", "image/boss/boss_jumpDownEnd.bmp", 0, 0, 1224, 422, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getUp", "image/boss/boss_getUp.bmp", 0, 0, 3735, 580, 15, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss_getHit", "image/boss/boss_getHit.bmp", 0, 0, 2700, 600, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_1", "image/boss/boss_getHit_1.bmp", 0, 0, 540, 540, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_2", "image/boss/boss_getHit_2.bmp", 0, 0, 560, 560, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_3", "image/boss/boss_getHit_3.bmp", 0, 0, 2700, 540, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_dizzy", "image/boss/boss_dizzy96.bmp", 0, 0, 1024, 634, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_groundHit", "image/boss/boss_groundHit99.bmp", 0, 0, 1036, 660, 4, 2, true, RGB(255, 0, 255));
}

void boss::setKeyAnimation()
{
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftIdle", "boss_idle", 22, 12, 10, true, 10);	//11프레임부터 21까지. fps 10 < 프레임 읽는 속도 
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightIdle", "boss_idle", 0, 11, 10, true, 10);	//0프레임부터 10까지. 프레임 루프 true or false, 버퍼 10은 뭔지모름
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftWalk", "boss_walk", 19, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightWalk", "boss_walk", 0, 9, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftSlap", "boss_slap", 27, 14, 10, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightSlap", "boss_slap", 0, 13, 10, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftElbow", "boss_elbow", 21, 11, 10, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightElbow", "boss_elbow", 0, 10, 10, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDie", "boss_die", 25, 13, 8, false, setLeftDieEnd, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDieEND", "boss_die", 13, 17, 10, true, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDie", "boss_die", 0, 12, 8, false, setRightDieEnd, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDieEND", "boss_die", 8, 12, 10, true, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftPunch", "boss_punch", 53, 27, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightPunch", "boss_punch", 0, 26, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftTackle", "boss_tackle", 21, 11, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightTackle", "boss_tackle", 0, 10, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftTackleLoop", "boss_tackle", 18, 11, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightTackleLoop", "boss_tackle", 0, 7, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDown", "boss_down", 43, 22, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDown", "boss_down", 0, 21, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftJumpUp", "boss_jumpUp", 15, 8, 10, false, 10);				// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightJumpUp", "boss_jumpUp", 0, 7, 10, false, 10);				// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftJumpDown", "boss_jumpDown", 3, 2, 8, false, 10);			// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightJumpDown", "boss_jumpDown", 0, 1, 8, false, 10);			// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftJumpDownEnd", "boss_jumpDownEnd", 11, 6, 4, false, setLeftIdle, this, 10);		// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightJumpDownEnd", "boss_jumpDownEnd", 0, 5, 6, false, setRightIdle, this, 10);		// 루프 삭제
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftRoar", "boss_roar", 23, 12, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightRoar", "boss_roar", 0, 11, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftTaunt", "boss_taunt", 45, 23, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightTaunt", "boss_taunt", 0, 22, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetUp", "boss_getUp", 29, 15, 8, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetUp", "boss_getUp", 0, 14, 8, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_1", "boss_getHit_1", 3, 2, 4, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_1", "boss_getHit_1", 0, 1, 4, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_2", "boss_getHit_2", 3, 2, 4, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_2", "boss_getHit_2", 0, 1, 4, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_3", "boss_getHit_3", 19, 10, 10, false, leftAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_3", "boss_getHit_3", 0, 9, 10, false, rightAttackted, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDizzy", "boss_dizzy", 7, 4, 8, true, setLeftIdle, this, 10);	//일단 루프 true로
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDizzy", "boss_dizzy", 0, 3, 8, true, setRightIdle, this, 10);	//일단 루프 true로
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGroundHit", "boss_groundHit", 7, 4, 8, false, setLeftDizzy, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGroundHit", "boss_groundHit", 0, 3, 8, false, setRightDizzy, this, 10);

	//KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit", "boss_getHit", 17, 9, 10, true);		//맞는모션 전체. 일단 1,2,3,타 맞는 모션 따로 해놔서 주석
	//KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit", "boss_getHit", 0, 8, 10, true);

	_bossMotion = KEYANIMANAGER->findAnimation("boss_leftIdle");
}






