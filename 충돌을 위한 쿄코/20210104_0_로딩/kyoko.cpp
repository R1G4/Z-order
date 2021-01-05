#include "stdafx.h"
#include "kyoko.h"

HRESULT kyoko::init()
{
	addImage();
	addMotionAni();

	_image = IMAGEMANAGER->findImage("쿄코_일반");
	_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
	_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_image_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());


	_jump = new jump;
	_jump->init();
	_kyokoMotion->start();

	return S_OK;
}

void kyoko::release()
{
}

void kyoko::update()
{
	moveMotion();
	attackMotion();
	jumpMotion();
	
	// 이동시 어느정도 이동할 것인가 - 쓰면 안될거같은 느낌 위치떄문에 꼬임
	switch (_kyokoDirection)
	{
	case KYOKODIRECTION_RIGHT_WALK: case KYOKODIRECTION_RIGHT_JUMP_MOVE: 
	case KYOKODIRECTION_RIGHT_JUMP_TOP_MOVE: case KYOKODIRECTION_RIGHT_JUMP_DOWN_MOVE:
		_x += KYOKOSPEED;
		break;
	case KYOKODIRECTION_RIGHT_RUN:
		_x += KYOKOSPEED * 2;
		break;

	case KYOKODIRECTION_LEFT_WALK: case KYOKODIRECTION_LEFT_JUMP_MOVE:
	case KYOKODIRECTION_LEFT_JUMP_TOP_MOVE: case KYOKODIRECTION_LEFT_JUMP_DOWN_MOVE:
		_x -= KYOKOSPEED;
		break;
	case KYOKODIRECTION_LEFT_RUN:
		_x -= KYOKOSPEED * 2;
		break;
	}

	// 이미지처리를 위한 렉트
	_image_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	// 충돌처리를 위한 렉트
	_rc = RectMakeCenter(_x, _y, 40, _image->getFrameHeight() - 30);
	// 애니메이션 재생
	KEYANIMANAGER->update();

	// 점프업뎃
	_jump->update();
}

void kyoko::render()
{
	if (_image == IMAGEMANAGER->findImage("쿄코_강공격"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top -50 , _kyokoMotion);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion);

	// 충돌처리를 위한 렉트
	if(KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(), _rc);
}

// 오른쪽 일반 모션으로 콜백
void kyoko::rightFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_일반");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightIdle"));
	k->getKyokoMotion()->start();
}

// 왼쪽 일반 모션으로 콜백
void kyoko::leftFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_일반");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftIdle"));
	k->getKyokoMotion()->start();
}

// 오른쪽 걷기 모션으로 콜백
void kyoko::rightJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_걷기");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightWalk"));
	k->getKyokoMotion()->start();
}

// 왼쪽 걷기 모션으로 콜백
void kyoko::leftJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_걷기");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftWalk"));
	k->getKyokoMotion()->start();
}

// 오른쪽 뛰기 모션으로 콜백
void kyoko::rightMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_달리기");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightRun"));
	k->getKyokoMotion()->start();
}

// 왼쪽 뛰기 모션으로 콜백
void kyoko::leftMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("쿄코_달리기");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftRun"));
	k->getKyokoMotion()->start();
}

// 쿄코 이미지 삽입
void kyoko::addImage()
{
	IMAGEMANAGER->addFrameImage("쿄코_일반", "kyoko/idle_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_걷기", "kyoko/walk_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_달리기", "kyoko/run_1.bmp", 0, 0, 4800, 400, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_점프", "kyoko/jump_1.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격1", "kyoko/attack_1_1.bmp", 0, 0, 1800, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격2", "kyoko/attack_2_1.bmp", 0, 0, 2100, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격3", "kyoko/attack_3_3.bmp", 0, 0, 2700, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_강공격", "kyoko/attack_strong_2.bmp", 0, 0, 3000, 600, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_마하킥", "kyoko/mahaKick_2.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_피격1", "kyoko/attacked_1_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_피격2", "kyoko/attacked_2_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_죽음", "kyoko/dead_1.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
}

// 쿄코 행동 애니매이션
void kyoko::addMotionAni()
{
	int rightIdle[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightIdle", "쿄코_일반", rightIdle, 12, 8, true, 1);

	int leftIdle[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftIdle", "쿄코_일반", leftIdle, 12, 8, true, 1);

	int rightWalk[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightWalk", "쿄코_걷기", rightWalk, 12, 5, true, 1);

	int leftWalk[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftWalk", "쿄코_걷기", leftWalk, 12, 5, true, 1);

	int rightRun[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightRun", "쿄코_달리기", rightRun, 16, 15, true, 1);

	int leftRun[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftRun", "쿄코_달리기", leftRun, 16, 15, true, 1);

	int arrRightAttack_1[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack1", "쿄코_공격1", arrRightAttack_1, 6, 10, false, rightFire, this, 1);

	int arrLeftAttack_1[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack1", "쿄코_공격1", arrLeftAttack_1, 6, 10, false, leftFire, this, 1);

	int arrRightAttack_2[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack2", "쿄코_공격2", arrRightAttack_2, 7, 10, false, rightFire, this, 1);

	int arrLeftAttack_2[] = { 13,12,11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack2", "쿄코_공격2", arrLeftAttack_2, 7, 10, false, leftFire, this, 1);

	int arrRightAttack_3[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack3", "쿄코_공격3", arrRightAttack_3, 9, 10, false, rightFire, this, 1);

	int arrLeftAttack_3[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack3", "쿄코_공격3", arrLeftAttack_3, 9, 10, false, leftFire, this, 1);

	int arrRightAttack_strong[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack_s", "쿄코_강공격", arrRightAttack_strong, 10, 10, false, rightFire, this, 1);

	int arrLeftAttack_strong[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack_s", "쿄코_강공격", arrLeftAttack_strong, 10, 10, false, leftFire, this, 1);

	int arrRightAttacked_1[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked1", "쿄코_피격1", arrRightAttacked_1, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_1[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked1", "쿄코_피격1", arrLeftAttacked_1, 4, 7, false, leftFire, this, 1);

	int arrRightAttacked_2[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked2", "쿄코_피격2", arrRightAttacked_2, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_2[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked2", "쿄코_피격2", arrLeftAttacked_2, 4, 7, false, leftFire, this, 1);

	int arrRightJump[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJump", "쿄코_점프", arrRightJump, 1, 2, false, 1);

	int arrLeftJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJump", "쿄코_점프", arrLeftJump, 1, 2, false, 1);

	int arrRightJumpTop[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpTop", "쿄코_점프", arrRightJumpTop, 1, 2, false, 1);

	int arrLeftJumpTop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpTop", "쿄코_점프", arrLeftJumpTop, 1, 2, false, 1);

	int arrRightJumpDown[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDown", "쿄코_점프", arrRightJumpDown, 1, 3, false, rightFire, this, 1);

	int arrLeftJumpDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDown", "쿄코_점프", arrLeftJumpDown, 1, 3, false, leftFire, this, 1);

	int arrRightJumpDownMove[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownMove", "쿄코_점프", arrRightJumpDownMove, 1, 3, false, rightJump, this, 1);

	int arrLeftJumpDownMove[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownMove", "쿄코_점프", arrLeftJumpDownMove, 1, 3, false, leftJump, this, 1);

	int RightMahaKick[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightMahaKick", "쿄코_마하킥", RightMahaKick, 22, 12, false, rightFire, this, 1);

	int LeftMahaKick[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftMahaKick", "쿄코_마하킥", LeftMahaKick, 22, 12, false, leftFire, this, 1);

	int RightDead[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightDead", "쿄코_죽음", RightMahaKick, 22, 10, false, 1);

	int LeftDead[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftDead", "쿄코_죽음", LeftMahaKick, 22, 10, false, 1);

}

// 이동 모션
void kyoko::moveMotion()
{
	// 오른쪽 이동
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("쿄코_걷기");
		_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
		_kyokoMotion->start();
	}

	// 오른쪽 멈추기
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("쿄코_일반");
		_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
		_kyokoMotion->start();
	}

	
	// 왼쪽 이동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("쿄코_걷기");
		_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
		_kyokoMotion->start();
	}

	// 왼쪽 멈추기
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("쿄코_일반");
		_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
		_kyokoMotion->start();
	}

	// 위키를 누를경우
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_걷기");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_걷기");
			_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
			_kyokoMotion->start();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK)
		{
			_y -= KYOKOSPEED;
		}
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_y -= KYOKOSPEED * 2;
		}
	}

	// 아래키를 누를경우
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_걷기");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_걷기");
			_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
			_kyokoMotion->start();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK)
		{
			_y += KYOKOSPEED;
		}
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_y += KYOKOSPEED * 2;
		}
	}
}

// 공격 모션
void kyoko::attackMotion()
{
	// 평타
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_공격1");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack1");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_공격1");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack1");
			_kyokoMotion->start();
		}
	}

	// 강공격
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_강공격");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack_s");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_강공격");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack_s");
			_kyokoMotion->start();
		}
	}

	// 마하킥(필살기)
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_마하킥");
			_kyokoDirection = KYOKODIRECTION_RIGHT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightMahaKick");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_마하킥");
			_kyokoDirection = KYOKODIRECTION_LEFT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftMahaKick");
			_kyokoMotion->start();
		}
	}
}

// 점프 모션
void kyoko::jumpMotion()
{
	// 점프
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_jump->jumping(&_x, &_y, 8.0f, 0.4f);

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_점프");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("쿄코_점프");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
		{
			_image = IMAGEMANAGER->findImage("쿄코_점프");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
		{
			_image = IMAGEMANAGER->findImage("쿄코_점프");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}
	}

	// 일반점프일때 모션 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDown");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDown");
		_kyokoMotion->start();
	}

	// 이동 점프일때 모션변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_MOVE && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP_MOVE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_MOVE && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN_MOVE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDownMove");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_MOVE && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP_MOVE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_MOVE && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN_MOVE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDownMove");
		_kyokoMotion->start();
	}
}
