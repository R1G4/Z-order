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
	//이미지 및 애니메이션 추가
	addFrame();
	//그림자 초기화
	IMAGEMANAGER->addImage("Girl_Shadow", "SchoolGirl size200/SchoolGirl_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	_shadowImg = IMAGEMANAGER->findImage("Girl_Shadow");

	//이미지 초기화
	_schoolGirlImg = imgTaunt;

	//애니메이션 초기화
	_motion = aniLeftTaunt;
	_motion->start();

	//좌표 초기화
	_x = x;
	_y = y;

	_angle = 0;

	//에너미 렉트 초기화
	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(), _schoolGirlImg->getFrameHeight());
	//그림자 렉트 초기화
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right) / 2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
	
	_isAction = false;
	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	
	//추적 관련 초기회
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//에너미 상태 초기화
	_direction = LEFT;
	_state = TAUNT;

	//에너미 공격 생성 및 초기화
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

	//에너미 상태 설정
	state();

	//에너미 이동
	move();

	KEYANIMANAGER->update();

	//에너미 및 그림자 렉트 수정
	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(), _schoolGirlImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right) / 2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void schoolGirl::state()
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
			_schoolGirlImg = imgIdle;
			_motion = aniRightIdle;
			_motion->start();
			break;
		case LEFT:
			_motion->stop();
			_state = IDLE;
			_schoolGirlImg = imgIdle;
			_motion = aniLeftIdle;
			_motion->start();
			break;
		}
	}

	//특정 거리안에 플레이어가 존재 할 시
	float distance = getDistance(_x, _y, _kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y);
	if (distance < 500 && _isAction)
	{
		_isFollow = true;
		RECT temp;
		//플레이어와 에너미 충돌 시
		if (IntersectRect(&temp, &_kyoko->getRect(), &_schoolGirlRc))
		{
			switch (_state)
			{
				//IDLE 상태라면 공격, 방어 등등~
			case schoolGirl::IDLE:
				//공격 패턴 가져오기
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

				//이동 상태라면 애니메이션 중지(후에 IDLE상태로 설정 됨)
			case schoolGirl::WALK: case schoolGirl::RUN:
				_motion->stop();
				break;

				//기본공격
			case schoolGirl::ATTACK:
				if (_isAttack)
				{
					_isAttack = false;

					switch (_direction)
					{
					case schoolGirl::LEFT:
						_schoolGirlImg = imgAttack;
						_motion = aniLeftAttack;
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_schoolGirlImg = imgAttack;
						_motion = aniRightAttack;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 1
			case schoolGirl::COMBO_ATTACK_1:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = imgCombo_attack_1;
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = aniLeftCombo_attack_1;
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_motion = aniRightCombo_attack_1;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 2
			case schoolGirl::COMBO_ATTACK_2:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = imgCombo_attack_2;
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = aniLeftCombo_attack_2;
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_motion = aniRightCombo_attack_2;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 3
			case schoolGirl::COMBO_ATTACK_3:
				if (_isAttack)
				{
					_isAttack = false;
					_schoolGirlImg = imgCombo_attack_3;
					switch (_direction)
					{
					case schoolGirl::LEFT:
						_motion = aniLeftCombo_attack_3;
						_motion->start();
						break;
					case schoolGirl::RIGHT:
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
			if (((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_schoolGirlImg = imgRun;
				_motion = aniRightRun;
				_motion->start();
			}
			//두 거리가 가깝다면 걷는다
			else if (((_direction != RIGHT && _state != WALK) || (_direction == LEFT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 275)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = WALK;
				_schoolGirlImg = imgWalk;
				_motion = aniRightWalk;
				_motion->start();
			}
		}
		//플레이어의 위치가 에너미 보다 왼쪽에 있을 경우
		else if (_kyoko->getKyokoPoint().x <= _x)
		{
			//두 거리가 멀다면 달린다
			if (((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_schoolGirlImg = imgRun;
				_motion = aniLeftRun;
				_motion->start();
			}	
			//두 거리가 가깝다면 걷는다
			else if (((_direction != LEFT && _state != WALK) || (_direction == RIGHT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 275)
			{
				_motion->stop();
				_direction = LEFT;
				_state = WALK;
				_schoolGirlImg = imgWalk;
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
		case schoolGirl::IDLE:
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
				_schoolGirlImg = imgWalk;
				switch (_direction)
				{
				case schoolGirl::LEFT:
					_motion = aniLeftWalk;
					break;
				case schoolGirl::RIGHT:
					_motion = aniRightWalk;
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

void schoolGirl::move()
{
	//플레이어와 에너미의 각도 계산
	_angle = getAngle(_x, _y, _kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y);

	switch (_state)
	{
	case schoolGirl::WALK:
		if (_isFollow)
		{
			//에너미가 추적하고 있다면 해당 각도로 이동
			_x += cos(_angle) * ENEMYSPEED;
			_y += -sin(_angle) * ENEMYSPEED;
		}
		else
		{
			//탐색 중 이라면 X축으로만 이동
			float tempSpeed = ENEMYSPEED;
			switch (_direction)
			{
			case schoolGirl::LEFT:
				//벽에 닿을 경우 휴식상태로 전환
				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				//벽에 닿을 경우 휴식상태로 전환
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
			//에너미가 추적하고 있다면 해당 각도로 이동
			_x += cos(_angle) * 2 * ENEMYSPEED;
			_y += -sin(_angle) * 2 * ENEMYSPEED;
		}
		else
		{
			//탐색 중 이라면 X축으로만 이동
			float tempSpeed = ENEMYSPEED;
			switch (_direction)
			{
			case schoolGirl::LEFT:
				//벽에 닿을 경우 휴식상태로 전환
				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				//벽에 닿을 경우 휴식상태로 전환
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

void schoolGirl::render(POINT camera)
{
	//Rectangle(getMemDC(), _schoolGirlRc, camera);
	_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150, camera);

	switch (_state)
	{
	case schoolGirl::IDLE:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion, camera);
		break;
	case schoolGirl::ATTACK:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion, camera);
		break;
	case schoolGirl::COMBO_ATTACK_1:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 10, _motion, camera);
		break;
	case schoolGirl::COMBO_ATTACK_2:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top - 20, _motion, camera);
		break;
	default:
		_schoolGirlImg->aniRender(getMemDC(), _schoolGirlRc.left, _schoolGirlRc.top, _motion, camera);
		break;
	}
}

void schoolGirl::addFrame()
{
	imgIdle = IMAGEMANAGER->addFrameImage("Girl_Idle", "SchoolGirl size200/Girl_Idle.bmp", 0, 0, 1320, 400, 10, 2, true, RGB(255, 0, 255));;
	imgWalk = IMAGEMANAGER->addFrameImage("Girl_Walk", "SchoolGirl size200/Girl_Walk.bmp", 0, 0, 1394, 400, 12, 2, true, RGB(255, 0, 255));
	imgRun = IMAGEMANAGER->addFrameImage("Girl_Run", "SchoolGirl size200/Girl_Run.bmp", 0, 0, 1780, 400, 10, 2, true, RGB(255, 0, 255));
	imgBlock = IMAGEMANAGER->addFrameImage("Girl_Block", "SchoolGirl size200/Girl_Block.bmp", 0, 0, 460, 400, 3, 2, true, RGB(255, 0, 255));
	imgAttack = IMAGEMANAGER->addFrameImage("Girl_Attack", "SchoolGirl size200/Girl_Attack.bmp", 0, 0, 1934, 420, 8, 2, true, RGB(255, 0, 255));
	imgCombo_attack_1 = IMAGEMANAGER->addFrameImage("Girl_ComboAttack1", "SchoolGirl size200/Girl_ComboAttack1.bmp", 0, 0, 1505, 430, 7, 2, true, RGB(255, 0, 255));
	imgCombo_attack_2 = IMAGEMANAGER->addFrameImage("Girl_ComboAttack2", "SchoolGirl size200/Girl_ComboAttack2.bmp", 0, 0, 1470, 440, 7, 2, true, RGB(255, 0, 255));
	imgCombo_attack_3 = IMAGEMANAGER->addFrameImage("Girl_ComboAttack3", "SchoolGirl size200/Girl_ComboAttack3.bmp", 0, 0, 2700, 450, 12, 2, true, RGB(255, 0, 255));
	imgHit = IMAGEMANAGER->addFrameImage("Girl_Hit", "SchoolGirl size200/Girl_Hit.bmp", 0, 0, 1626, 400, 9, 2, true, RGB(255, 0, 255));
	imgDownup = IMAGEMANAGER->addFrameImage("Girl_Downup", "SchoolGirl size200/Girl_Downup.bmp", 0, 0, 7013, 380, 27, 2, true, RGB(255, 0, 255));
	imgKnockdown = IMAGEMANAGER->addFrameImage("Girl_Knockdown", "SchoolGirl size200/Girl_Knockdown.bmp", 0, 0, 4361, 380, 17, 2, true, RGB(255, 0, 255));
	imgDazed = IMAGEMANAGER->addFrameImage("Girl_Dazed", "SchoolGirl size200/Girl_Dazed.bmp", 0, 0, 656, 410, 4, 2, true, RGB(255, 0, 255));
	imgJump = IMAGEMANAGER->addFrameImage("Girl_Jump", "SchoolGirl size200/Girl_Jump.bmp", 0, 0, 432, 400, 3, 2, true, RGB(255, 0, 255));
	imgTaunt = IMAGEMANAGER->addFrameImage("Girl_Taunt", "SchoolGirl size200/Girl_Taunt.bmp", 0, 0, 4015, 420, 26, 2, true, RGB(255, 0, 255));

	aniRightIdle = new animation;
	aniRightIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniRightIdle->setPlayFrame(0, 9, false, true);
	aniRightIdle->setFPS(10);
	aniLeftIdle = new animation;
	aniLeftIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniLeftIdle->setPlayFrame(19, 10, false, true);
	aniLeftIdle->setFPS(10);

	aniRightWalk = new animation;
	aniRightWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniRightWalk->setPlayFrame(0, 11, false, true);
	aniRightWalk->setFPS(10);
	aniLeftWalk = new animation;
	aniLeftWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniLeftWalk->setPlayFrame(23, 12, false, true);
	aniLeftWalk->setFPS(10);

	aniRightRun = new animation;
	aniRightRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniRightRun->setPlayFrame(0, 9, false, true);
	aniRightRun->setFPS(10);
	aniLeftRun = new animation;
	aniLeftRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniLeftRun->setPlayFrame(19, 10, false, true);
	aniLeftRun->setFPS(10);

	aniRightBlock = new animation;
	aniRightBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniRightBlock->setPlayFrame(0, 2, false, false);
	aniRightBlock->setFPS(10);
	aniLeftBlock = new animation;
	aniLeftBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniLeftBlock->setPlayFrame(5, 3, false, false);
	aniLeftBlock->setFPS(10);

	aniRightAttack = new animation;
	aniRightAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniRightAttack->setPlayFrame(0, 7, false, false);
	aniRightAttack->setFPS(10);
	aniLeftAttack = new animation;
	aniLeftAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniLeftAttack->setPlayFrame(15, 8, false, false);
	aniLeftAttack->setFPS(10);

	aniRightCombo_attack_1 = new animation;
	aniRightCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniRightCombo_attack_1->setPlayFrame(0, 6, false, false);
	aniRightCombo_attack_1->setFPS(10);
	aniLeftCombo_attack_1 = new animation;
	aniLeftCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniLeftCombo_attack_1->setPlayFrame(13, 7, false, false);
	aniLeftCombo_attack_1->setFPS(10);

	aniRightCombo_attack_2 = new animation;
	aniRightCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniRightCombo_attack_2->setPlayFrame(0, 6, false, false);
	aniRightCombo_attack_2->setFPS(10);
	aniLeftCombo_attack_2 = new animation;
	aniLeftCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniLeftCombo_attack_2->setPlayFrame(13, 7, false, false);
	aniLeftCombo_attack_2->setFPS(10);

	aniRightCombo_attack_3 = new animation;
	aniRightCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniRightCombo_attack_3->setPlayFrame(0, 11, false, false);
	aniRightCombo_attack_3->setFPS(10);
	aniLeftCombo_attack_3 = new animation;
	aniLeftCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniLeftCombo_attack_3->setPlayFrame(23, 12, false, false);
	aniLeftCombo_attack_3->setFPS(10);

	aniRightHit = new animation;
	aniRightHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniRightHit->setPlayFrame(0, 8, false, false);
	aniRightHit->setFPS(10);
	aniLeftHit = new animation;
	aniLeftHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniLeftHit->setPlayFrame(17, 9, false, false);
	aniLeftHit->setFPS(10);

	aniRightDownup = new animation;
	aniRightDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniRightDownup->setPlayFrame(0, 26, false, false);
	aniRightDownup->setFPS(10);
	aniLeftDownup = new animation;
	aniLeftDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniLeftDownup->setPlayFrame(53, 27, false, false);
	aniLeftDownup->setFPS(10);

	aniRightKnockdown = new animation;
	aniRightKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniRightKnockdown->setPlayFrame(0, 16, false, false);
	aniRightKnockdown->setFPS(10);
	aniLeftKnockdown = new animation;
	aniLeftKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniLeftKnockdown->setPlayFrame(33, 17, false, false);
	aniLeftKnockdown->setFPS(10);

	aniRightDazed = new animation;
	aniRightDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniRightDazed->setPlayFrame(0, 3, false, false);
	aniRightDazed->setFPS(10);
	aniLeftDazed = new animation;
	aniLeftDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniLeftDazed->setPlayFrame(7, 4, false, false);
	aniLeftDazed->setFPS(10);

	aniRightJump = new animation;
	aniRightJump->init(imgJump->getWidth(), imgJump->getHeight(), imgJump->getFrameWidth(), imgJump->getFrameHeight());
	aniRightJump->setPlayFrame(0, 2, false, false);
	aniRightJump->setFPS(10);
	aniLeftJump = new animation;
	aniLeftJump->init(imgJump->getWidth(), imgJump->getHeight(), imgJump->getFrameWidth(), imgJump->getFrameHeight());
	aniLeftJump->setPlayFrame(5, 3, false, false);
	aniLeftJump->setFPS(10);

	aniRightTaunt = new animation;
	aniRightTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniRightTaunt->setPlayFrame(0, 25, false, false, ActionCheck, this);
	aniRightTaunt->setFPS(10);
	aniLeftTaunt = new animation;
	aniLeftTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniLeftTaunt->setPlayFrame(51, 26, false, false, ActionCheck, this);
	aniLeftTaunt->setFPS(10);
}

void schoolGirl::ActionCheck(void* obj)
{
	schoolGirl* k = (schoolGirl*)obj;
	k->_isAction = true;
}

void schoolGirl::RunningCheck(void* obj)
{
	schoolGirl* k = (schoolGirl*)obj;
}
