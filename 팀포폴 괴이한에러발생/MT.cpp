#include "stdafx.h"
#include "MT.h"
#include "kyoko.h"

MT::MT()
{
}

MT::~MT()
{
}

HRESULT MT::init(float x, float y, STATE state, DIRECTION direction)
{
	//이미지 및 애니메이션 초기화
	addFrame();

	//에너미 공용 초기화
	enemy::init(x, y, state, direction);

	//해당 에너미 스피드
	_speed = 2.3f;

	//해당 에너미 체력
	_hp = 9;

	setAttackInfo();

	return S_OK;
}

void MT::release()
{
}

void MT::setAttackInfo()
{
	attackInfo attackTemp;

	//프레임중 실제 공격하는 모션 인덱스만 렉트 적용

	//일반공격1
	attackTemp.index = 3;
	attackTemp.plusY = 30;
	attackTemp.width = 70;
	attackTemp.height = 40;
	_mAttackInfo.insert(make_pair(ATTACK, attackTemp));

	//콤보 1
	attackTemp.index = 3;
	attackTemp.plusY = 30;
	attackTemp.width = 70;
	attackTemp.height = 40;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_1, attackTemp));

	//콤보2
	attackTemp.index = 3;
	attackTemp.plusY = 80;
	attackTemp.width = 70;
	attackTemp.height = 50;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_2, attackTemp));

	//콤보3
	attackTemp.index = 3;
	attackTemp.plusY = 50;
	attackTemp.width = 70;
	attackTemp.height = 80;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_3, attackTemp));
}

void MT::update()
{
	enemy::update();

	//에너미 렉트 초기화
	setAttackRect(_state, _direction);

	//에너미 패턴 관련 객체
	_enemyAttack->update();

	//에너미 상태 설정
	state();

	//에너미 이동
	move();

	//에너미 및 그림자 렉트 수정
	_rc = RectMakeCenter(_x, _y + 10, 40, 152);
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void MT::addFrame()
{
	imgIdle = IMAGEMANAGER->findImage("MT_Idle");
	imgWalk = IMAGEMANAGER->findImage("MT_Walk");
	imgRun = IMAGEMANAGER->findImage("MT_Run");
	imgBlock = IMAGEMANAGER->findImage("MT_Block");
	imgAttack = IMAGEMANAGER->findImage("MT_Attack");
	imgCombo_attack_1 = IMAGEMANAGER->findImage("MT_ComboAttack1");
	imgCombo_attack_2 = IMAGEMANAGER->findImage("MT_ComboAttack2");
	imgCombo_attack_3 = IMAGEMANAGER->findImage("MT_ComboAttack3");
	imgHit = IMAGEMANAGER->findImage("MT_Hit");
	imgDownup = IMAGEMANAGER->findImage("MT_Downup");
	imgDazed = IMAGEMANAGER->findImage("MT_Dazed");
	imgKnockdown = IMAGEMANAGER->findImage("MT_Knockdown");
	imgTaunt = IMAGEMANAGER->findImage("MT_Taunt");
	_shadowImg = IMAGEMANAGER->findImage("MT_Shadow");

	//Idle 상태
	aniRightIdle = new animation;
	aniRightIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniRightIdle->setPlayFrame(0, imgIdle->getMaxFrameX(), false, true);
	aniRightIdle->setFPS(10);
	aniLeftIdle = new animation;
	aniLeftIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniLeftIdle->setPlayFrame(imgIdle->getMaxFrameX() * 2 + 1, imgIdle->getMaxFrameX() + 1, false, true);
	aniLeftIdle->setFPS(10);

	//Walk 상태
	aniRightWalk = new animation;
	aniRightWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniRightWalk->setPlayFrame(0, imgWalk->getMaxFrameX(), false, true);
	aniRightWalk->setFPS(10);
	aniLeftWalk = new animation;
	aniLeftWalk->init(imgWalk->getWidth(), imgWalk->getHeight(), imgWalk->getFrameWidth(), imgWalk->getFrameHeight());
	aniLeftWalk->setPlayFrame(imgWalk->getMaxFrameX() * 2 + 1, imgWalk->getMaxFrameX() + 1, false, true);
	aniLeftWalk->setFPS(10);

	//Run 상태
	aniRightRun = new animation;
	aniRightRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniRightRun->setPlayFrame(0, imgRun->getMaxFrameX(), false, true);
	aniRightRun->setFPS(10);
	aniLeftRun = new animation;
	aniLeftRun->init(imgRun->getWidth(), imgRun->getHeight(), imgRun->getFrameWidth(), imgRun->getFrameHeight());
	aniLeftRun->setPlayFrame(imgRun->getMaxFrameX() * 2 + 1, imgRun->getMaxFrameX() + 1, false, true);
	aniLeftRun->setFPS(10);

	//Block 상태
	aniRightBlock = new animation;
	aniRightBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniRightBlock->setPlayFrame(0, imgBlock->getMaxFrameX(), false, false);
	aniRightBlock->setFPS(10);
	aniLeftBlock = new animation;
	aniLeftBlock->init(imgBlock->getWidth(), imgBlock->getHeight(), imgBlock->getFrameWidth(), imgBlock->getFrameHeight());
	aniLeftBlock->setPlayFrame(imgBlock->getMaxFrameX() * 2 + 1, imgBlock->getMaxFrameX() + 1, false, false);
	aniLeftBlock->setFPS(10);

	//Attack 상태
	aniRightAttack = new animation;
	aniRightAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniRightAttack->setPlayFrame(0, imgAttack->getMaxFrameX(), false, false);
	aniRightAttack->setFPS(10);
	aniLeftAttack = new animation;
	aniLeftAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniLeftAttack->setPlayFrame(imgAttack->getMaxFrameX() * 2 + 1, imgAttack->getMaxFrameX() + 1, false, false);
	aniLeftAttack->setFPS(10);

	//ComboAttack 1 상태
	aniRightCombo_attack_1 = new animation;
	aniRightCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniRightCombo_attack_1->setPlayFrame(0, imgCombo_attack_1->getMaxFrameX(), false, false);
	aniRightCombo_attack_1->setFPS(10);
	aniLeftCombo_attack_1 = new animation;
	aniLeftCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniLeftCombo_attack_1->setPlayFrame(imgCombo_attack_1->getMaxFrameX() * 2 + 1, imgCombo_attack_1->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_1->setFPS(10);

	//ComboAttack 2 상태
	aniRightCombo_attack_2 = new animation;
	aniRightCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniRightCombo_attack_2->setPlayFrame(0, imgCombo_attack_2->getMaxFrameX(), false, false);
	aniRightCombo_attack_2->setFPS(10);
	aniLeftCombo_attack_2 = new animation;
	aniLeftCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniLeftCombo_attack_2->setPlayFrame(imgCombo_attack_2->getMaxFrameX() * 2 + 1, imgCombo_attack_2->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_2->setFPS(10);

	//ComboAttack 3 상태
	aniRightCombo_attack_3 = new animation;
	aniRightCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniRightCombo_attack_3->setPlayFrame(0, imgCombo_attack_3->getMaxFrameX(), false, false);
	aniRightCombo_attack_3->setFPS(10);
	aniLeftCombo_attack_3 = new animation;
	aniLeftCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniLeftCombo_attack_3->setPlayFrame(imgCombo_attack_3->getMaxFrameX() * 2 + 1, imgCombo_attack_3->getMaxFrameX() + 1, false, false);
	aniLeftCombo_attack_3->setFPS(10);

	//Hit 상태
	aniRightHit = new animation;
	aniRightHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniRightHit->setPlayFrame(0, imgHit->getMaxFrameX(), false, false);
	aniRightHit->setFPS(10);
	aniLeftHit = new animation;
	aniLeftHit->init(imgHit->getWidth(), imgHit->getHeight(), imgHit->getFrameWidth(), imgHit->getFrameHeight());
	aniLeftHit->setPlayFrame(imgHit->getMaxFrameX() * 2 + 1, imgHit->getMaxFrameX() + 1, false, false);
	aniLeftHit->setFPS(10);

	//Downup 상태
	aniRightDownup = new animation;
	aniRightDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniRightDownup->setPlayFrame(0, imgDownup->getMaxFrameX(), false, false, rightStun, this);
	aniRightDownup->setFPS(6);
	aniLeftDownup = new animation;
	aniLeftDownup->init(imgDownup->getWidth(), imgDownup->getHeight(), imgDownup->getFrameWidth(), imgDownup->getFrameHeight());
	aniLeftDownup->setPlayFrame(imgDownup->getMaxFrameX() * 2 + 1, imgDownup->getMaxFrameX() + 1, false, false, leftStun, this);
	aniLeftDownup->setFPS(6);

	//Knockdown 상태
	aniRightKnockdown = new animation;
	aniRightKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniRightKnockdown->setPlayFrame(0, imgKnockdown->getMaxFrameX(), false, false, setDead, this);
	aniRightKnockdown->setFPS(6);
	aniLeftKnockdown = new animation;
	aniLeftKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniLeftKnockdown->setPlayFrame(imgKnockdown->getMaxFrameX() * 2 + 1, imgKnockdown->getMaxFrameX() + 1, false, false, setDead, this);
	aniLeftKnockdown->setFPS(6);

	//Dazed 상태
	aniRightDazed = new animation;
	aniRightDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniRightDazed->setPlayFrame(0, imgDazed->getMaxFrameX(), false, false);
	aniRightDazed->setFPS(5);
	aniLeftDazed = new animation;
	aniLeftDazed->init(imgDazed->getWidth(), imgDazed->getHeight(), imgDazed->getFrameWidth(), imgDazed->getFrameHeight());
	aniLeftDazed->setPlayFrame(imgDazed->getMaxFrameX() * 2 + 1, imgDazed->getMaxFrameX() + 1, false, false);
	aniLeftDazed->setFPS(5);

	//Taunt 상태
	aniRightTaunt = new animation;
	aniRightTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniRightTaunt->setPlayFrame(0, imgTaunt->getMaxFrameX(), false, false, actionCheck, this);
	aniRightTaunt->setFPS(4);
	aniLeftTaunt = new animation;
	aniLeftTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniLeftTaunt->setPlayFrame(imgTaunt->getMaxFrameX() * 2 + 1, imgTaunt->getMaxFrameX() + 1, false, false, actionCheck, this);
	aniLeftTaunt->setFPS(4);
}

void MT::render(POINT camera)
{
	//이펙트 랜더
	enemy::render(camera);

	//이미지 크기가 변하는 모션은 보정값을 더하거나 빼주어 랜더한다.
	switch (_state)
	{
	case MT::DEAD:
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 20, _motion, camera);
		break;
	case MT::DOWNUP: case MT::KNOCKDOWN:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 20, _motion, camera);
		break;
	case MT::COMBO_ATTACK_2:
		switch (_direction)
		{
		case MT::LEFT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left - 3, _shadowRc.top, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left - 3, _enemyRc.top - 10, _motion, camera);
			break;
		case MT::RIGHT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left + 3, _shadowRc.top - 10, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left + 3, _enemyRc.top - 10, _motion, camera);
			break;
		}
		break;
	case MT::COMBO_ATTACK_3:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 25, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 25, _motion, camera);
		break;
	default:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top, _motion, camera);
		break;
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _shadowRc, camera);
		Rectangle(getMemDC(), _rc, camera);

		HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _attackRc, camera);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
	}
}

void MT::setAttackRect(STATE state, DIRECTION direction)
{
	int index;
	switch (state)
	{
	case enemy::ATTACK:
	case enemy::COMBO_ATTACK_1:
	case enemy::COMBO_ATTACK_2:
	case enemy::COMBO_ATTACK_3:
		//미리 생성해둔 공격용 렉트관련 맵에서 조회를 한다.
		attackInfo attackinfo = _mAttackInfo.find(state)->second;
		index = (int)_motion->getIndex();
		//애니메이션에서 해당 인덱스를 받아온 후 공격 인덱스랑 일치 할 경우
		if (attackinfo.index == index)
		{
			//방향에 따른 공격용 렉트를 생성한다.
			switch (direction)
			{
			case LEFT:
				_attackRc = RectMake(_rc.left - attackinfo.width, _rc.top + attackinfo.plusY, attackinfo.width, attackinfo.height);
				break;
			case RIGHT:
				_attackRc = RectMake(_rc.right, _rc.top + attackinfo.plusY, attackinfo.width, attackinfo.height);
				break;
			}
		}
		else	//공격용 렉트를 숨긴다.
			_attackRc = RectMake(_x, _y, 0, 0);
		break;
	default:	//공격용 렉트를 숨긴다.
		_attackRc = RectMake(_x, _y, 0, 0);
		break;
	}
}

void MT::state()
{
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime());

	//애니메이션이 멈춘 경우 IDLE로 전환
	if (!_motion->isPlay() && _state != KNOCKDOWN && _state != DEAD && _state != REMOVE)
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
	if (distance < 600 && _isAction && _state != KNOCKDOWN && _state != DEAD && _state != REMOVE)
	{
		//거리안에 존재 할 시 느낌표를 보여준다.
		if (!_isFollow)
		{
			//접근하고자 하는 방향에 가까운 위치를 파라메타로 보낸다.
			if (_kyoko->getKyokoPoint().x > _x)
				enemy::effectPoint(RIGHT);
			else
				enemy::effectPoint(LEFT);
		}

		//추적을 시작한다.
		_isFollow = true;

		RECT temp;
		//플레이어와 에너미 충돌 시
		if (IntersectRect(&temp,
			&RectMakeCenter((_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2, _kyoko->getRect().right - _kyoko->getRect().left, _kyoko->getRect().bottom - _kyoko->getRect().top - 100),
			&RectMakeCenter(_x, _y, 500, _enemyImg->getFrameHeight())))	//에너미 넓이 고정으로 생성
		{
			switch (_state)
			{
				//IDLE 상태라면 공격, 방어 등등~
			case MT::IDLE:
				//공격 패턴 가져오기
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

				//이동 상태라면 애니메이션 중지(후에 IDLE상태로 설정 됨)
			case MT::WALK: case MT::RUN:
				_motion->stop();
				break;

				//기본공격
			case MT::ATTACK:
				if (_isAttack)
				{
					_isAttack = false;

					switch (_direction)
					{
					case MT::LEFT:
						_enemyImg = imgAttack;
						_motion = aniLeftAttack;
						_motion->start();
						break;
					case MT::RIGHT:
						_enemyImg = imgAttack;
						_motion = aniRightAttack;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 1
			case MT::COMBO_ATTACK_1:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_1;
					switch (_direction)
					{
					case MT::LEFT:
						_motion = aniLeftCombo_attack_1;
						_motion->start();
						break;
					case MT::RIGHT:
						_motion = aniRightCombo_attack_1;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 2
			case MT::COMBO_ATTACK_2:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_2;
					switch (_direction)
					{
					case MT::LEFT:
						_motion = aniLeftCombo_attack_2;
						_motion->start();
						break;
					case MT::RIGHT:
						_motion = aniRightCombo_attack_2;
						_motion->start();
						break;
					}
				}
				break;
				//콤보공격 3
			case MT::COMBO_ATTACK_3:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_3;
					switch (_direction)
					{
					case MT::LEFT:
						_motion = aniLeftCombo_attack_3;
						_motion->start();
						break;
					case MT::RIGHT:
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
			if (_state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_2 || _state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_3 ||
				((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniRightRun;
				_motion->start();
			}
			//두 거리가 가깝다면 걷는다
			else if (_state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_2 || _state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_3 ||
				((_direction != RIGHT && _state != WALK) || (_direction == LEFT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 250)
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
			if (_state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_2 || _state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_3 ||
				((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniLeftRun;
				_motion->start();
			}
			//두 거리가 가깝다면 걷는다
			else if (_state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_2 || _state == ATTACK || _state == COMBO_ATTACK_1 || _state == COMBO_ATTACK_3 ||
				((_direction != LEFT && _state != WALK) || (_direction == RIGHT && _state == WALK) || (_direction == LEFT && _state == RUN) || (_direction == RIGHT && _state == RUN) || _state == IDLE) && distance <= 250)
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
	else if (_state != DOWNUP && _state != KNOCKDOWN && _state != DEAD && _state != REMOVE)
	{
		switch (_state)
		{
		case MT::IDLE:
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
				case MT::LEFT:
					_motion = aniLeftWalk;
					break;
				case MT::RIGHT:
					_motion = aniRightWalk;
					break;
				}
				_motion->start();
			}
			break;
		case MT::WALK: case MT::RUN:
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

void MT::move()
{
	//충동했다면 이동을 제한한다.
	if (_isCollision)
		return;
	//플레이어와 에너미의 각도 계산
	_angle = getAngle(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);

	switch (_state)
	{
	case MT::WALK:
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
			case MT::LEFT:
				_x -= _speed;
				break;
			case MT::RIGHT:
				_x += _speed;

				break;
			}

		}
		break;
	case MT::RUN:
		if (_isFollow)
		{
			//에너미가 추적하고 있다면 해당 각도로 이동
			_x += cos(_angle) * 2.5 * _speed;
			_y += -sin(_angle) * 2.5 * _speed;
		}
		else
		{
			//탐색 중 이라면 X축으로만 이동
			switch (_direction)
			{
			case MT::LEFT:
				_x -= 2 * _speed;
				break;
			case MT::RIGHT:
				_x += 2 * _speed;

				break;
			}
		}
		break;
	}
}