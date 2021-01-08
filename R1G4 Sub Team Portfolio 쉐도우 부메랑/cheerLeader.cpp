#include "stdafx.h"
#include "cheerLeader.h"
#include "kyoko.h"

cheerLeader::cheerLeader()
{
}

cheerLeader::~cheerLeader()
{
}

HRESULT cheerLeader::init(float x, float y, bool isTaunt = false, int direction = RND->getFromIntTo(0, 2))
{
	//이미지 및 애니메이션 초기화
	addFrame();

	//이미지 초기화
	_enemyImg = imgTaunt;

	//에너미 상태 초기화
	_direction = (DIRECTION)direction;
	_state = isTaunt == true ? TAUNT : IDLE;

	//좌표 초기화
	_x = x;
	_y = y;
	_speed = 2.6f;
	_angle = 0;

	//애니메이션 적용
	switch (_state)
	{
	case cheerLeader::IDLE:
		switch (_direction)
		{
		case cheerLeader::LEFT:
			_isAction = true;
			_motion = aniLeftIdle;
			break;
		case cheerLeader::RIGHT:
			_isAction = true;
			_motion = aniRightIdle;
			break;
		}

		break;
	case cheerLeader::TAUNT:
		switch (_direction)
		{
		case cheerLeader::LEFT:
			_isAction = false;
			_motion = aniLeftTaunt;
			break;
		case cheerLeader::RIGHT:
			_isAction = false;
			_motion = aniRightTaunt;
			break;
		}
		break;
	}
	_motion->start();

	//에너미 렉트 초기화
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	//그림자 렉트 초기화
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());

	_isAttack = false;
	_isFollow = false;
	_isRunning = true;

	//추적 관련 초기회
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);


	//에너미 공격 생성 및 초기화
	_enemyAttack = new enemyAttack;
	_enemyAttack->init();
	return S_OK;
}

void cheerLeader::release()
{
}

void cheerLeader::update()
{
	_enemyAttack->update();

	//에너미 상태 설정
	state();

	//에너미 이동
	move();

	KEYANIMANAGER->update();

	//에너미 및 그림자 렉트 수정
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void cheerLeader::addFrame()
{
	imgIdle = IMAGEMANAGER->findImage("CheerLeader_Idle");
	imgWalk = IMAGEMANAGER->findImage("CheerLeader_Walk");
	imgRun = IMAGEMANAGER->findImage("CheerLeader_Run");
	imgBlock = IMAGEMANAGER->findImage("CheerLeader_Block");
	imgAttack = IMAGEMANAGER->findImage("CheerLeader_Attack");
	imgCombo_attack_1 = IMAGEMANAGER->findImage("CheerLeader_ComboAttack1");
	imgCombo_attack_2 = IMAGEMANAGER->findImage("CheerLeader_ComboAttack2");
	imgCombo_attack_3 = IMAGEMANAGER->findImage("CheerLeader_ComboAttack3");
	imgHit = IMAGEMANAGER->findImage("CheerLeader_Hit");
	imgDownup = IMAGEMANAGER->findImage("CheerLeader_Downup");
	imgDazed = IMAGEMANAGER->findImage("CheerLeader_Dazed");
	imgJump = IMAGEMANAGER->findImage("CheerLeader_Jump");
	imgKnockdown = IMAGEMANAGER->findImage("CheerLeader_Knockdown");
	imgTaunt = IMAGEMANAGER->findImage("CheerLeader_Idle");
	_shadowImg = IMAGEMANAGER->findImage("CheerLeader_Shadow");

	aniRightIdle = new animation;
	aniRightIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniRightIdle->setPlayFrame(0, imgIdle->getMaxFrameX(), false, true);
	aniRightIdle->setFPS(10);
	aniLeftIdle = new animation;
	aniLeftIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniLeftIdle->setPlayFrame(imgIdle->getMaxFrameX() * 2 + 1, imgIdle->getMaxFrameX() + 1, false, true);
	aniLeftIdle->setFPS(10);

	aniRightWalk = new animation;
	aniRightWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniRightWalk->setPlayFrame(0, imgWalk->getMaxFrameX(), false, true);
	aniRightWalk->setFPS(10);
	aniLeftWalk = new animation;
	aniLeftWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniLeftWalk->setPlayFrame(imgWalk->getMaxFrameX() * 2 + 1, imgWalk->getMaxFrameX() + 1, false, true);
	aniLeftWalk->setFPS(10);

	aniRightRun = new animation;
	aniRightRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniRightRun->setPlayFrame(0, imgRun->getMaxFrameX(), false, true);
	aniRightRun->setFPS(10);
	aniLeftRun = new animation;
	aniLeftRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniLeftRun->setPlayFrame(imgRun->getMaxFrameX() * 2 + 1, imgRun->getMaxFrameX() + 1, false, true);
	aniLeftRun->setFPS(10);

	aniRightBlock = new animation;
	aniRightBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniRightBlock->setPlayFrame(0, imgBlock->getMaxFrameX(), false, false);
	aniRightBlock->setFPS(10);
	aniLeftBlock = new animation;
	aniLeftBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniLeftBlock->setPlayFrame(imgBlock->getMaxFrameX() * 2 + 1, imgBlock->getMaxFrameX() + 1, false, false);
	aniLeftBlock->setFPS(10);

	aniRightAttack = new animation;
	aniRightAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniRightAttack->setPlayFrame(0, imgAttack->getMaxFrameX(), false, false);
	aniRightAttack->setFPS(10);
	aniLeftAttack = new animation;
	aniLeftAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniLeftAttack->setPlayFrame(imgAttack->getMaxFrameX() * 2 + 1, imgAttack->getMaxFrameX() + 1, false, false);
	aniLeftAttack->setFPS(10);

	aniRightCombo_attack_1 = new animation;
	aniRightCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniRightCombo_attack_1->setPlayFrame(0, imgCombo_attack_1->getMaxFrameX(), false, false);
	aniRightCombo_attack_1->setFPS(10);
	aniLeftCombo_attack_1 = new animation;
	aniLeftCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniLeftCombo_attack_1->setPlayFrame(imgCombo_attack_1->getMaxFrameX() * 2 + 1, imgCombo_attack_1->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_1->setFPS(10);

	aniRightCombo_attack_2 = new animation;
	aniRightCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniRightCombo_attack_2->setPlayFrame(0, imgCombo_attack_2->getMaxFrameX(), false, false);
	aniRightCombo_attack_2->setFPS(10);
	aniLeftCombo_attack_2 = new animation;
	aniLeftCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniLeftCombo_attack_2->setPlayFrame(imgCombo_attack_2->getMaxFrameX() * 2 + 1, imgCombo_attack_2->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_2->setFPS(10);

	aniRightCombo_attack_3 = new animation;
	aniRightCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniRightCombo_attack_3->setPlayFrame(0, imgCombo_attack_3->getMaxFrameX(), false, false);
	aniRightCombo_attack_3->setFPS(10);
	aniLeftCombo_attack_3 = new animation;
	aniLeftCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniLeftCombo_attack_3->setPlayFrame(imgCombo_attack_3->getMaxFrameX() * 2 + 1, imgCombo_attack_3->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_3->setFPS(10);

	aniRightHit = new animation;
	aniRightHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniRightHit->setPlayFrame(0, imgHit->getMaxFrameX(), false, false);
	aniRightHit->setFPS(10);
	aniLeftHit = new animation;
	aniLeftHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniLeftHit->setPlayFrame(imgHit->getMaxFrameX() * 2 + 1, imgHit->getMaxFrameX() + 1, false, false);
	aniLeftHit->setFPS(10);

	aniRightDownup = new animation;
	aniRightDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniRightDownup->setPlayFrame(0, imgDownup->getMaxFrameX(), false, false);
	aniRightDownup->setFPS(10);
	aniLeftDownup = new animation;
	aniLeftDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniLeftDownup->setPlayFrame(imgDownup->getMaxFrameX() * 2 + 1, imgDownup->getMaxFrameX() + 1, false, false);
	aniLeftDownup->setFPS(10);

	aniRightKnockdown = new animation;
	aniRightKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniRightKnockdown->setPlayFrame(0, imgKnockdown->getMaxFrameX(), false, false);
	aniRightKnockdown->setFPS(10);
	aniLeftKnockdown = new animation;
	aniLeftKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniLeftKnockdown->setPlayFrame(imgKnockdown->getMaxFrameX() * 2 + 1, imgKnockdown->getMaxFrameX() + 1, false, false);
	aniLeftKnockdown->setFPS(10);

	aniRightDazed = new animation;
	aniRightDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniRightDazed->setPlayFrame(0, imgDazed->getMaxFrameX(), false, false);
	aniRightDazed->setFPS(10);
	aniLeftDazed = new animation;
	aniLeftDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniLeftDazed->setPlayFrame(imgDazed->getMaxFrameX() * 2 + 1, imgDazed->getMaxFrameX() + 1, false, false);
	aniLeftDazed->setFPS(10);

	aniRightJump = new animation;
	aniRightJump->init(imgJump->getWidth(), imgJump->getHeight(), imgJump->getFrameWidth(), imgJump->getFrameHeight());
	aniRightJump->setPlayFrame(0, imgJump->getMaxFrameX(), false, false);
	aniRightJump->setFPS(10);
	aniLeftJump = new animation;
	aniLeftJump->init(imgJump->getWidth(), imgJump->getHeight(), imgJump->getFrameWidth(), imgJump->getFrameHeight());
	aniLeftJump->setPlayFrame(imgJump->getMaxFrameX() * 2 + 1, imgJump->getMaxFrameX() + 1, false, false);
	aniLeftJump->setFPS(10);

	aniRightTaunt = new animation;
	aniRightTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniRightTaunt->setPlayFrame(0, imgTaunt->getMaxFrameX(), false, false, ActionCheck, this);
	aniRightTaunt->setFPS(4);
	aniLeftTaunt = new animation;
	aniLeftTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniLeftTaunt->setPlayFrame(imgTaunt->getMaxFrameX() * 2 + 1, imgTaunt->getMaxFrameX() + 1, false, false, ActionCheck, this);
	aniLeftTaunt->setFPS(4);
}

void cheerLeader::render(POINT camera)
{
	switch (_state)
	{
	case cheerLeader::DOWNUP: case cheerLeader::KNOCKDOWN:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 20, _motion, camera);
		break;
	case cheerLeader::COMBO_ATTACK_2:
		switch (_direction)
		{
		case cheerLeader::LEFT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left - 3, _shadowRc.top, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left - 3, _enemyRc.top - 10, _motion, camera);
			break;
		case cheerLeader::RIGHT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left + 3, _shadowRc.top - 10, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left + 3, _enemyRc.top - 10, _motion, camera);
			break;
		}
		break;
	case cheerLeader::COMBO_ATTACK_3:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 25, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 25, _motion, camera);
		break;
	default:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top, _motion, camera);
		break;
	}
}

void cheerLeader::state()
{
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime());

	//애니메이션이 멈춘 경우 IDLE로 전환
	if (!_motion->isPlay())
	{
		switch (_direction)
		{
		case RIGHT:
			_motion->stop();
			_state = IDLE;
			_enemyImg = imgIdle;
			_motion = aniRightIdle;
			_motion->start();
			break;
		case LEFT:
			_motion->stop();
			_state = IDLE;
			_enemyImg = imgIdle;
			_motion = aniLeftIdle;
			_motion->start();
			break;
		}
	}

	//특정 거리안에 플레이어가 존재 할 시
	float distance = getDistance(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);
	if (distance < 525 && _isAction)
	{
		_isFollow = true;
		RECT temp;
		//플레이어와 에너미 충돌 시
		if (IntersectRect(&temp, &RectMakeCenter((_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2, _kyoko->getRect().right - _kyoko->getRect().left, _kyoko->getRect().bottom - _kyoko->getRect().top - 40), &_enemyRc))
		{
			switch (_state)
			{
				//IDLE 상태라면 공격, 방어 등등~
			case cheerLeader::IDLE:
				//공격 패턴 가져오기
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

				//이동 상태라면 애니메이션 중지(후에 IDLE상태로 설정 됨)
			case cheerLeader::WALK: case cheerLeader::RUN:
				_motion->stop();
				break;

				//기본공격
			case cheerLeader::ATTACK:
				if (_isAttack)
				{
					_isAttack = false;

					switch (_direction)
					{
					case cheerLeader::LEFT:
						_enemyImg = imgAttack;
						_motion = aniLeftAttack;
						_motion->start();
						break;
					case cheerLeader::RIGHT:
						_enemyImg = imgAttack;
						_motion = aniRightAttack;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 1
			case cheerLeader::COMBO_ATTACK_1:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_1;
					switch (_direction)
					{
					case cheerLeader::LEFT:
						_motion = aniLeftCombo_attack_1;
						_motion->start();
						break;
					case cheerLeader::RIGHT:
						_motion = aniRightCombo_attack_1;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 2
			case cheerLeader::COMBO_ATTACK_2:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_2;
					switch (_direction)
					{
					case cheerLeader::LEFT:
						_motion = aniLeftCombo_attack_2;
						_motion->start();
						break;
					case cheerLeader::RIGHT:
						_motion = aniRightCombo_attack_2;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 3
			case cheerLeader::COMBO_ATTACK_3:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_3;
					switch (_direction)
					{
					case cheerLeader::LEFT:
						_motion = aniLeftCombo_attack_3;
						_motion->start();
						break;
					case cheerLeader::RIGHT:
						_motion = aniRightCombo_attack_3;
						_motion->start();
						break;
					}
				}
				break;
			}
			//에너미는 이동 할 필요 없으니 아래 코드는 스킵
			return;
		}

		//플레이어의 위치가 에너미 보다 오른쪽에 있을 경우
		if (_kyoko->getKyokoPoint().x > _x)
		{
			//두 거리가 멀다면 달린다
			if (((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniRightRun;
				_motion->start();
			}
			//두 거리가 가깝다면 걷는다
			else if (((_direction != RIGHT && _state != WALK) || (_direction == LEFT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 250)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = WALK;
				_enemyImg = imgWalk;
				_motion = aniRightWalk;
				_motion->start();
			}
		}
		//플레이어의 위치가 에너미 보다 왼쪽에 있을 경우
		else if (_kyoko->getKyokoPoint().x <= _x)
		{
			//두 거리가 멀다면 달린다
			if (((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniLeftRun;
				_motion->start();
			}
			//두 거리가 가깝다면 걷는다
			else if (((_direction != LEFT && _state != WALK) || (_direction == RIGHT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 250)
			{
				_motion->stop();
				_direction = LEFT;
				_state = WALK;
				_enemyImg = imgWalk;
				_motion = aniLeftWalk;
				_motion->start();
			}
		}
	}
	//추적 거리가 닿지 않을 경우 패턴 구현
	else
	{
		switch (_state)
		{
		case cheerLeader::IDLE:
			//탐색 타이머가 줄어든다.
			_questTimer--;
			//탐색 타이머가 최소 탐색 시간만큼 도달 할 경우
			if (_questTimer < _questMin)
			{
				//최소 탐색 시간 난수로 초기화
				_questMin = RND->getFromIntTo(50, 140);

				//탐색 으로 전환
				_state = WALK;
				_direction = (DIRECTION)RND->getFromIntTo(LEFT, RIGHT + 1);
				_enemyImg = imgWalk;
				switch (_direction)
				{
				case cheerLeader::LEFT:
					_motion = aniLeftWalk;
					break;
				case cheerLeader::RIGHT:
					_motion = aniRightWalk;
					break;
				}
				_motion->start();
			}
			break;
		case cheerLeader::WALK: case cheerLeader::RUN:
			if (_isFollow)
			{
				_motion->stop();
				_isFollow = false;
			}
			else
			{
				_questTimer--;
				//탐색 타이머가 종료 될 경우
				if (_questTimer < 0)
				{
					//탐색 타이머 난수로 초기화
					_questTimer = RND->getFromIntTo(180, 220);
					//휴식으로 전환
					_motion->stop();
				}
			}
			break;
		}
	}
}

void cheerLeader::move()
{
	//플레이어와 에너미의 각도 계산
	_angle = getAngle(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);

	switch (_state)
	{
	case cheerLeader::WALK:
		if (_isFollow)
		{
			//에너미가 추적하고 있다면 해당 각도로 이동
			_x += cos(_angle) * _speed;
			_y += -sin(_angle) * _speed;
		}
		else
		{
			//탐색 중 이라면 X축으로만 이동
			switch (_direction)
			{
			case cheerLeader::LEFT:
				//왼쪽 벽에 닿을 경우 휴식상태로 전환
				if (_x - _speed < _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
					_motion->stop();
				else
					_x -= _speed;
				break;
			case cheerLeader::RIGHT:
				//오른쪽 벽에 닿을 경우 휴식상태로 전환
				if (_x + _speed > WINSIZEX - _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
					_motion->stop();
				else
					_x += _speed;

				break;
			}

		}
		break;
	case cheerLeader::RUN:
		if (_isFollow)
		{
			//에너미가 추적하고 있다면 해당 각도로 이동
			_x += cos(_angle) * 2.1 * _speed;
			_y += -sin(_angle) * 2.1 * _speed;
		}
		else
		{
			//탐색 중 이라면 X축으로만 이동
			switch (_direction)
			{
			case cheerLeader::LEFT:
				//왼쪽 벽에 닿을 경우 휴식상태로 전환
				if (_x - 2.1 * _speed < _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
					_motion->stop();
				else
					_x -= 2.1 * _speed;
				break;
			case cheerLeader::RIGHT:
				//오른쪽 벽에 닿을 경우 휴식상태로 전환
				if (_x + 2.1 * _speed > WINSIZEX - _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
					_motion->stop();
				else
					_x += 2.1 * _speed;

				break;
			}
		}
		break;
	}
}

void cheerLeader::ActionCheck(void* obj)
{
	cheerLeader* k = (cheerLeader*)obj;
	k->_isAction = true;
}

void cheerLeader::RunningCheck(void* obj)
{
	cheerLeader* k = (cheerLeader*)obj;
}