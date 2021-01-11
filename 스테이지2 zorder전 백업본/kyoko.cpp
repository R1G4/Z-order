#include "stdafx.h"
#include "kyoko.h"

HRESULT kyoko::init()
{
	addMotionAni();

	_image = IMAGEMANAGER->findImage("쿄코_일반");
	_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
	_shadow = IMAGEMANAGER->findImage("그림자");
	_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;

	_r_count = 0;
	_z_count = 0;
	_maha_count = 362;


	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 + 200;

	_shadow_rc = RectMakeCenter(_x, _y, _shadow->getWidth(), _shadow->getHeight());
	_image_rc = RectMakeCenter((_shadow_rc.left + _shadow_rc.right) / 2, _shadow_rc.top - 100,
		_image->getFrameWidth(), _image->getFrameHeight());
	_attack_rc = _image_rc;

	_i_x = (_shadow_rc.left + _shadow_rc.right) / 2;
	_i_y = _shadow_rc.top - 80;

	_jump = new jump;
	_jump->init();
	_shadow_jump = new jump;
	_shadow_jump->init();

	_kyokoMotion->start();

	_isMoving = false;
	_isAttack = false;
	_isJump = false;
	_isCollision = false;

	return S_OK;
}

void kyoko::release()
{
}

void kyoko::update()
{
	moveMotion();

	// 공격모션이 들어가기전에 리셋?
	_attack_rc = RectMake(_rc.left, _rc.top, 0, 0);
	attackMotion();
	jumpMotion();

	// 이미지처리를 위한 렉트

	if (!_isJump)
	{
		_i_x = (_shadow_rc.left + _shadow_rc.right) / 2;
		_i_y = _shadow_rc.top - 80;
		_image_rc = RectMakeCenter(_i_x, _i_y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	else
		_image_rc = RectMakeCenter(_i_x, _i_y, _image->getFrameWidth(), _image->getFrameHeight());
	// 충돌처리를 위한 렉트
	if (!_isJump)
	{
		_i_x = (_shadow_rc.left + _shadow_rc.right) / 2;
		_i_y = _shadow_rc.top - 80;
		_rc = RectMakeCenter(_i_x, _i_y, 40, _image->getFrameHeight() - 40);
	}
	else
		_rc = RectMakeCenter(_i_x, _i_y, 40, _image->getFrameHeight() - 40);

	// 그림자처리를 위한 렉트 (z-order)
	_shadow_rc = RectMakeCenter(_x, _y, _shadow->getWidth(), _shadow->getHeight());
	// 애니메이션 재생
	//KEYANIMANAGER->update();

	// 점프업뎃
	_jump->update();
	_shadow_jump->update();
}

void kyoko::render()
{
	_shadow->render(getMemDC(), _shadow_rc.left, _shadow_rc.top);

	if (_image == IMAGEMANAGER->findImage("쿄코_강공격"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top - 50, _kyokoMotion);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion);
	// 충돌처리를 위한 렉트(디버깅)
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), _shadow_rc);
		Rectangle(getMemDC(), _attack_rc);
	}
}

void kyoko::render(POINT camera)
{
	_shadow->render(getMemDC(), _shadow_rc.left, _shadow_rc.top, camera);

	if (_image == IMAGEMANAGER->findImage("쿄코_강공격"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top - 50, _kyokoMotion, camera);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion, camera);

	// 충돌처리를 위한 렉트
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc, camera);
		Rectangle(getMemDC(), _shadow_rc, camera);
		Rectangle(getMemDC(), _attack_rc, camera);
	}
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
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack1", "쿄코_공격1", arrRightAttack_1, 6, 15, false, rightFire, this, 1);

	int arrLeftAttack_1[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack1", "쿄코_공격1", arrLeftAttack_1, 6, 15, false, leftFire, this, 1);

	int arrRightAttack_2[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack2", "쿄코_공격2", arrRightAttack_2, 7, 15, false, rightFire, this, 1);

	int arrLeftAttack_2[] = { 13,12,11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack2", "쿄코_공격2", arrLeftAttack_2, 7, 15, false, leftFire, this, 1);

	int arrRightAttack_3[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack3", "쿄코_공격3", arrRightAttack_3, 9, 15, false, rightFire, this, 1);

	int arrLeftAttack_3[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack3", "쿄코_공격3", arrLeftAttack_3, 9, 15, false, leftFire, this, 1);

	int arrRightAttack_dash[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttackDash", "쿄코_대쉬공격", arrRightAttack_dash, 8, 15, false, rightFire, this, 1);

	int arrLeftAttack_dash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttackDash", "쿄코_대쉬공격", arrLeftAttack_dash, 8, 15, false, leftFire, this, 1);

	int arrRightAttack_jump[] = { 1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttackJump", "쿄코_점프공격", arrRightAttack_jump, 2, 10, false, 1);

	int arrLeftAttack_jump[] = { 4,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttackJump", "쿄코_점프공격", arrLeftAttack_jump, 2, 10, false, 1);

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

	int arrRightJumpDownWalk[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownWalk", "쿄코_점프", arrRightJumpDownWalk, 1, 3, false, rightJump, this, 1);

	int arrLeftJumpDownRun[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownRun", "쿄코_점프", arrLeftJumpDownRun, 1, 3, false, leftMoveJump, this, 1);

	int arrRightJumpDownRun[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownRun", "쿄코_점프", arrRightJumpDownRun, 1, 3, false, rightMoveJump, this, 1);

	int arrLeftJumpDownWalk[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownWalk", "쿄코_점프", arrLeftJumpDownWalk, 1, 3, false, leftJump, this, 1);

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
	// 공격 안할때
	if (!_isAttack)
	{
		// 오른쪽 이동
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			// 두번 누를 경우 달리기로
			if (_isRunning)
			{
				_image = IMAGEMANAGER->findImage("쿄코_달리기");
				_kyokoDirection = KYOKODIRECTION_RIGHT_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightRun");
				_kyokoMotion->start();
			}

			// 한번 누를 경우 걷기로
			if (!_isRunning && !_isJump)
			{
				_image = IMAGEMANAGER->findImage("쿄코_걷기");
				_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
				_kyokoMotion->start();
				_isRunning = true;
			}
		}
		// 오른쪽 키 누르고 있을때 이동
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_isMoving = true;
					_x += KYOKOSPEED;
					_i_x += KYOKOSPEED;
				}
			}
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_isMoving = true;
					_x += KYOKOSPEED * 2;
					_i_x += KYOKOSPEED * 2;
				}
			}
		}
		// 오른쪽 멈추기
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_일반");
				_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
				_kyokoMotion->start();
				_r_count = 1;
			}
			_isMoving = false;
			_isCollision = false;
		}

		// 왼쪽 이동
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			// 두번 누를 경우 달리기로
			if (_isRunning)
			{
				_image = IMAGEMANAGER->findImage("쿄코_달리기");
				_kyokoDirection = KYOKODIRECTION_LEFT_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftRun");
				_kyokoMotion->start();
			}

			// 한번 누를 경우 걷기로
			if (!_isRunning && !_isJump)
			{
				_image = IMAGEMANAGER->findImage("쿄코_걷기");
				_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
				_kyokoMotion->start();
				_isRunning = true;
			}
		}
		// 왼쪽 키 누르고 있을때 이동
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_x -= KYOKOSPEED;
					_i_x -= KYOKOSPEED;
					_isMoving = true;
				}
			}
			if (_kyokoDirection == KYOKODIRECTION_LEFT_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN || _kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_x -= KYOKOSPEED * 2;
					_i_x -= KYOKOSPEED * 2;
					_isMoving = true;
				}
			}
		}
		// 왼쪽 멈추기
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_일반");
				_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
				_kyokoMotion->start();
			}
			_isMoving = false;
			_isCollision = false;
		}

		// 위키를 누를 경우
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
		// 위쪽 키 누르고 있을때 이동
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_isMoving = true;
					_y -= KYOKOSPEED / 2;
					_i_y -= KYOKOSPEED / 2;
				}
			}
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_isMoving = true;
					_y -= KYOKOSPEED;
					_i_y -= KYOKOSPEED;
				}
			}
		}
		// 위쪽 키 뗄때 멈춤
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
				{
					_image = IMAGEMANAGER->findImage("쿄코_일반");
					_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}
			if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
				{
					_image = IMAGEMANAGER->findImage("쿄코_일반");
					_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}
		}

		// 아래키를 누를 경우
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
		// 아래쪽 키 누르고 있을때 이동
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_y += KYOKOSPEED / 2;
					_i_y += KYOKOSPEED / 2;
					_isMoving = true;
				}
			}
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_y += KYOKOSPEED;
					_i_y += KYOKOSPEED;
					_isMoving = true;
				}
			}
		}
		// 아래쪽 키 뗄때 멈춤
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
				{
					_image = IMAGEMANAGER->findImage("쿄코_일반");
					_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}

			if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
				{
					_image = IMAGEMANAGER->findImage("쿄코_일반");
					_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}
		}

		// 일정시간안에 한번 더 방향키를 누르면 달리기모션
		if (_isRunning) _r_count++;
		if (_r_count >= 20) { _isRunning = false; _r_count = 0; }
	}

	// 점프공격시
	else
	{
		// 오른쪽 키 누를경우
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// 일반/걷기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// 이동점프로 상태 변경
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				}
				if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				}

				if (_isCollision)
					_isMoving = true;
				else
				{
					_x += KYOKOSPEED;
					_i_x += KYOKOSPEED;
					_isMoving = true;
				}
			}
			// 달리기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_x += KYOKOSPEED * 2;
					_i_x += KYOKOSPEED * 2;
					_isMoving = true;
				}
			}
		}

		// 왼쪽 키 누를경우
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// 일반/걷기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// 이동점프로 상태 변경
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				}
				if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				}

				if (_isCollision)
					_isMoving = true;
				else
				{
					_x -= KYOKOSPEED;
					_i_x -= KYOKOSPEED;
					_isMoving = true;
				}
			}
			// 달리기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_x -= KYOKOSPEED * 2;
					_i_x -= KYOKOSPEED * 2;
					_isMoving = true;
				}
			}
		}

		// 위 키 누를 경우
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			// 일반/걷기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// 이동점프로 상태 변경
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				}
				if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				}

				if (_isCollision)
					_isMoving = true;
				else
				{
					_y -= KYOKOSPEED / 2;
					_i_y -= KYOKOSPEED / 2;
					_isMoving = true;
				}
			}
			// 달리기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_y -= KYOKOSPEED;
					_i_y -= KYOKOSPEED;
					_isMoving = true;
				}
			}
		}

		// 아래 키 누를 경우
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			// 일반/걷기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// 이동점프로 상태 변경
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				}
				if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP)
				{
					_speed = 2.5f;
					_jump->setJumpSpeed(_speed);
					_shadow_jump->setJumpSpeed(_speed);
					_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				}

				if (_isCollision)
					_isMoving = true;
				else
				{
					_y += KYOKOSPEED / 2;
					_i_y += KYOKOSPEED / 2;
					_isMoving = true;
				}
			}
			// 달리기 점프 공격시
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN)
			{
				if (_isCollision)
					_isMoving = true;
				else
				{
					_y += KYOKOSPEED;
					_i_y += KYOKOSPEED;
					_isMoving = true;
				}
			}
		}

		// 키를 뗄경우
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_speed = 0;
			_jump->setJumpSpeed(_speed);
			_shadow_jump->setJumpSpeed(_speed);
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP;
			_isMoving = false;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_speed = 0;
			_jump->setJumpSpeed(_speed);
			_shadow_jump->setJumpSpeed(_speed);
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP;
			_isMoving = false;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_speed = 0;
			_jump->setJumpSpeed(_speed);
			_shadow_jump->setJumpSpeed(_speed);
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP;
			_isMoving = false;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_speed = 0;
			_jump->setJumpSpeed(_speed);
			_shadow_jump->setJumpSpeed(_speed);
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP;
			_isMoving = false;
		}
	}
}

// 공격 모션
void kyoko::attackMotion()
{
	// 평타
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_isAttack = true;
		if (_z_count == 0)
		{
			// 일반이나 걷기 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
			{
				_image = IMAGEMANAGER->findImage("쿄코_공격1");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_1;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack1");
				_kyokoMotion->start();

				_z_count = 1;
			}
			if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
				_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
			{
				_image = IMAGEMANAGER->findImage("쿄코_공격1");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_1;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack1");
				_kyokoMotion->start();

				_z_count = 1;
			}

			// 달리기 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_대쉬공격");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_DASH;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackDash");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}
			if (_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_대쉬공격");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_DASH;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackDash");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 일반 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 걷기 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 달리기 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 일반 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 걷기 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// 달리기 점프 상태일때 공격
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN)
			{
				_image = IMAGEMANAGER->findImage("쿄코_점프공격");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// 타격 범위
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}
		}
		else if (_z_count == 1)
		{
			_frame_count = 0;
			// 일반 공격에서 연속공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1)
				_isNextAttack = true;
			if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_1)
				_isNextAttack = true;
		}
		else if (_z_count == 2)
		{
			_frame_count = 0;
			// 일반 공격에서 연속공격
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2)
				_isNextAttack = true;
			if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_2)
				_isNextAttack = true;
		}
	}

	// 강공격
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_isAttack = true;
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

	// 마하킥(필살기) - _maha_count가 일정량 이상 없으면 사용불가
	if (KEYMANAGER->isOnceKeyDown('A') && _maha_count > 120)
	{
		_isAttack = true;
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_마하킥");
			_kyokoDirection = KYOKODIRECTION_RIGHT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightMahaKick");
			_kyokoMotion->start();
			_maha_count = _maha_count - 150;
			_isMahaKick = true;
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("쿄코_마하킥");
			_kyokoDirection = KYOKODIRECTION_LEFT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftMahaKick");
			_kyokoMotion->start();
			_maha_count = _maha_count - 150;
			_isMahaKick = true;
		}
	}

	// 일반공격1 렉트 조정
	if (_kyokoMotion->getNowPlayIndex() == 2 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.right = _rc.right + 100;
			_attack_rc.bottom = _rc.bottom;
		}
	}
	if (_kyokoMotion->getNowPlayIndex() == 2 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_1)
	{	
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// 일반공격2 렉트 조정
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.right = _rc.right + 100;
			_attack_rc.bottom = _rc.bottom;
		}
	}
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_2)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// 일반공격3 렉트 조정
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_3)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.right = _rc.right + 100;
			_attack_rc.bottom = _rc.bottom;
		}
	}
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_3)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// 강공격 렉트 조정
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_STRONG)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.right = _rc.right + 100;
			_attack_rc.bottom = _rc.bottom;
		}
	}
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_STRONG)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// 마하킥 렉트 조정
	if ((_kyokoMotion->getNowPlayIndex() == 4 || _kyokoMotion->getNowPlayIndex() == 9 || _kyokoMotion->getNowPlayIndex() == 15) && 
		_kyokoDirection == KYOKODIRECTION_RIGHT_MAHAKICK)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.right = _rc.right + 100;
			_attack_rc.bottom = _rc.bottom;
		}
	}
	if ((_kyokoMotion->getNowPlayIndex() == 4 || _kyokoMotion->getNowPlayIndex() == 9 || _kyokoMotion->getNowPlayIndex() == 15) &&
		_kyokoDirection == KYOKODIRECTION_LEFT_MAHAKICK)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;

			// 타격 범위
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// 자연스러운 연속공격을 위한 조건
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("쿄코_공격2");
		_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_2;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack2");
		_kyokoMotion->start();
		_z_count = 2;
		_isNextAttack = false;
	}
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_1 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("쿄코_공격2");
		_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_2;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack2");
		_kyokoMotion->start();
		_z_count = 2;
		_isNextAttack = false;
	}

	if (_kyokoMotion->getNowPlayIndex() == 6 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("쿄코_공격3");
		_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_3;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack3");
		_kyokoMotion->start();
		_z_count = 3;
		_isNextAttack = false;
	}
	if (_kyokoMotion->getNowPlayIndex() == 6 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_2 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("쿄코_공격3");
		_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_3;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack3");
		_kyokoMotion->start();
		_z_count = 3;
		_isNextAttack = false;
	}
	
	// 공격후 idle상태로 갈때 연속공격 카운트를 0으로
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE || _kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
		_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
		_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
	{
		_isAttack = false;
		_isMahaKick = false;
		_z_count = 0;
		_frame_count = 0;
	}

	// 필살기 게이지 채우기 (+예외처리)
	if (_maha_count <= 0)
		_maha_count = 0;
	if (!_isMahaKick && _maha_count <= 361)
		_maha_count++;
}

// 점프 모션
void kyoko::jumpMotion()
{
	// 점프
	if (!_isAttack)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_isJump = true;

			// 일반상태 오른쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
			{
				_speed = 0;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// 일반상태 왼쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
			{
				_speed = 0;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			// 걷기상태 오른쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 2.5f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// 걷기상태 왼쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 2.5f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			// 달리기상태 오른쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 5.0f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// 달리기상태 왼쪽 점프
			if (_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 5.0f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("쿄코_점프");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			_jump->jumping(&_i_x, &_i_y, 20.0f, 1.0f);
			_shadow_jump->jumping(&_x, &_y, 0.0f, 0.0f);
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

	// 걷기 점프일때 모션변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDownWalk");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDownWalk");
		_kyokoMotion->start();
	}

	// 달리기 점프일때 모션변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDownRun");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN && _jump->getJumpPower() <= 1 && _jump->getJumpPower() >= -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpTop");
		_kyokoMotion->start();
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN && _jump->getJumpPower() < -1)
	{
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDownRun");
		_kyokoMotion->start();
	}

	// 점프에서 움직이면 무브 상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_WALK;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP_WALK;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDownWalk");
		_kyokoMotion->start();
	}

	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_WALK;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP_WALK;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN && _isMoving)
	{
		if (_isCollision)
			_speed = 0;
		else
			_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDownWalk");
		_kyokoMotion->start();
	}

	// 걷기 점프에서 멈추면 그냥 점프 상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDown");
		_kyokoMotion->start();
	}

	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDown");
		_kyokoMotion->start();
	}

	// 달리기 점프에서 멈추면 그냥 점프 상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_TOP;
	}
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJumpDown");
		_kyokoMotion->start();
	}

	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_TOP;
	}
	if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN && !_isMoving)
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_DOWN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJumpDown");
		_kyokoMotion->start();
	}

	// 점프 공격시 땅에 닿으면 기본상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_일반");
		_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
		_kyokoMotion->start();
		_isMoving = false;
		_isCollision = false;
		_isJump = false;
	}

	// 점프 공격시 땅에 닿으면 기본상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_일반");
		_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
		_kyokoMotion->start();
		_isMoving = false;
		_isCollision = false;
		_isJump = false;
	}

	// 걷기 점프 공격시 땅에 닿으면 달리기상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_걷기");
		_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
		_kyokoMotion->start();
		_isJump = false;
	}

	// 걷기 점프 공격시 땅에 닿으면 달리기상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_걷기");
		_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
		_kyokoMotion->start();
		_isJump = false;
	}

	// 달리기 점프 공격시 땅에 닿으면 달리기상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 5;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_달리기");
		_kyokoDirection = KYOKODIRECTION_RIGHT_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightRun");
		_kyokoMotion->start();
		_isJump = false;
	}

	// 달리기 점프 공격시 땅에 닿으면 달리기상태로 변경
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 5;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("쿄코_달리기");
		_kyokoDirection = KYOKODIRECTION_LEFT_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftRun");
		_kyokoMotion->start();
		_isJump = false;
	}

	// 점프가 아닐때 bool 값 리셋
	if (_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_TOP && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_TOP &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_DOWN && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_DOWN &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_WALK && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_WALK &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_TOP_WALK && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_TOP_WALK &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_DOWN_WALK &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_RUN && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_RUN &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_TOP_RUN && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_TOP_RUN &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN && _kyokoDirection != KYOKODIRECTION_LEFT_JUMP_DOWN_RUN &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_ATTACK_JUMP && _kyokoDirection != KYOKODIRECTION_LEFT_ATTACK_JUMP &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK && _kyokoDirection != KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK &&
		_kyokoDirection != KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN && _kyokoDirection != KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN)
	{
		_isJump = false;
	}
}
