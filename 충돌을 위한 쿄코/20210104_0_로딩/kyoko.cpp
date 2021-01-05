#include "stdafx.h"
#include "kyoko.h"

HRESULT kyoko::init()
{
	addImage();
	addMotionAni();

	_image = IMAGEMANAGER->findImage("ÄìÄÚ_ÀÏ¹Ý");
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
	
	// ÀÌµ¿½Ã ¾î´ÀÁ¤µµ ÀÌµ¿ÇÒ °ÍÀÎ°¡ - ¾²¸é ¾ÈµÉ°Å°°Àº ´À³¦ À§Ä¡‹š¹®¿¡ ²¿ÀÓ
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

	// ÀÌ¹ÌÁöÃ³¸®¸¦ À§ÇÑ ·ºÆ®
	_image_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	// Ãæµ¹Ã³¸®¸¦ À§ÇÑ ·ºÆ®
	_rc = RectMakeCenter(_x, _y, 40, _image->getFrameHeight() - 30);
	// ¾Ö´Ï¸ÞÀÌ¼Ç Àç»ý
	KEYANIMANAGER->update();

	// Á¡ÇÁ¾÷µ«
	_jump->update();
}

void kyoko::render()
{
	if (_image == IMAGEMANAGER->findImage("ÄìÄÚ_°­°ø°Ý"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top -50 , _kyokoMotion);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion);

	// Ãæµ¹Ã³¸®¸¦ À§ÇÑ ·ºÆ®
	if(KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(), _rc);
}

// ¿À¸¥ÂÊ ÀÏ¹Ý ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::rightFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_ÀÏ¹Ý");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightIdle"));
	k->getKyokoMotion()->start();
}

// ¿ÞÂÊ ÀÏ¹Ý ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::leftFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_ÀÏ¹Ý");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftIdle"));
	k->getKyokoMotion()->start();
}

// ¿À¸¥ÂÊ °È±â ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::rightJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightWalk"));
	k->getKyokoMotion()->start();
}

// ¿ÞÂÊ °È±â ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::leftJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftWalk"));
	k->getKyokoMotion()->start();
}

// ¿À¸¥ÂÊ ¶Ù±â ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::rightMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_´Þ¸®±â");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightRun"));
	k->getKyokoMotion()->start();
}

// ¿ÞÂÊ ¶Ù±â ¸ð¼ÇÀ¸·Î ÄÝ¹é
void kyoko::leftMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("ÄìÄÚ_´Þ¸®±â");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftRun"));
	k->getKyokoMotion()->start();
}

// ÄìÄÚ ÀÌ¹ÌÁö »ðÀÔ
void kyoko::addImage()
{
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_ÀÏ¹Ý", "kyoko/idle_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_°È±â", "kyoko/walk_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_´Þ¸®±â", "kyoko/run_1.bmp", 0, 0, 4800, 400, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_Á¡ÇÁ", "kyoko/jump_1.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_°ø°Ý1", "kyoko/attack_1_1.bmp", 0, 0, 1800, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_°ø°Ý2", "kyoko/attack_2_1.bmp", 0, 0, 2100, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_°ø°Ý3", "kyoko/attack_3_3.bmp", 0, 0, 2700, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_°­°ø°Ý", "kyoko/attack_strong_2.bmp", 0, 0, 3000, 600, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_¸¶ÇÏÅ±", "kyoko/mahaKick_2.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_ÇÇ°Ý1", "kyoko/attacked_1_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_ÇÇ°Ý2", "kyoko/attacked_2_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄìÄÚ_Á×À½", "kyoko/dead_1.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
}

// ÄìÄÚ Çàµ¿ ¾Ö´Ï¸ÅÀÌ¼Ç
void kyoko::addMotionAni()
{
	int rightIdle[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightIdle", "ÄìÄÚ_ÀÏ¹Ý", rightIdle, 12, 8, true, 1);

	int leftIdle[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftIdle", "ÄìÄÚ_ÀÏ¹Ý", leftIdle, 12, 8, true, 1);

	int rightWalk[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightWalk", "ÄìÄÚ_°È±â", rightWalk, 12, 5, true, 1);

	int leftWalk[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftWalk", "ÄìÄÚ_°È±â", leftWalk, 12, 5, true, 1);

	int rightRun[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightRun", "ÄìÄÚ_´Þ¸®±â", rightRun, 16, 15, true, 1);

	int leftRun[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftRun", "ÄìÄÚ_´Þ¸®±â", leftRun, 16, 15, true, 1);

	int arrRightAttack_1[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack1", "ÄìÄÚ_°ø°Ý1", arrRightAttack_1, 6, 10, false, rightFire, this, 1);

	int arrLeftAttack_1[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack1", "ÄìÄÚ_°ø°Ý1", arrLeftAttack_1, 6, 10, false, leftFire, this, 1);

	int arrRightAttack_2[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack2", "ÄìÄÚ_°ø°Ý2", arrRightAttack_2, 7, 10, false, rightFire, this, 1);

	int arrLeftAttack_2[] = { 13,12,11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack2", "ÄìÄÚ_°ø°Ý2", arrLeftAttack_2, 7, 10, false, leftFire, this, 1);

	int arrRightAttack_3[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack3", "ÄìÄÚ_°ø°Ý3", arrRightAttack_3, 9, 10, false, rightFire, this, 1);

	int arrLeftAttack_3[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack3", "ÄìÄÚ_°ø°Ý3", arrLeftAttack_3, 9, 10, false, leftFire, this, 1);

	int arrRightAttack_strong[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack_s", "ÄìÄÚ_°­°ø°Ý", arrRightAttack_strong, 10, 10, false, rightFire, this, 1);

	int arrLeftAttack_strong[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack_s", "ÄìÄÚ_°­°ø°Ý", arrLeftAttack_strong, 10, 10, false, leftFire, this, 1);

	int arrRightAttacked_1[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked1", "ÄìÄÚ_ÇÇ°Ý1", arrRightAttacked_1, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_1[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked1", "ÄìÄÚ_ÇÇ°Ý1", arrLeftAttacked_1, 4, 7, false, leftFire, this, 1);

	int arrRightAttacked_2[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked2", "ÄìÄÚ_ÇÇ°Ý2", arrRightAttacked_2, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_2[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked2", "ÄìÄÚ_ÇÇ°Ý2", arrLeftAttacked_2, 4, 7, false, leftFire, this, 1);

	int arrRightJump[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJump", "ÄìÄÚ_Á¡ÇÁ", arrRightJump, 1, 2, false, 1);

	int arrLeftJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJump", "ÄìÄÚ_Á¡ÇÁ", arrLeftJump, 1, 2, false, 1);

	int arrRightJumpTop[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpTop", "ÄìÄÚ_Á¡ÇÁ", arrRightJumpTop, 1, 2, false, 1);

	int arrLeftJumpTop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpTop", "ÄìÄÚ_Á¡ÇÁ", arrLeftJumpTop, 1, 2, false, 1);

	int arrRightJumpDown[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDown", "ÄìÄÚ_Á¡ÇÁ", arrRightJumpDown, 1, 3, false, rightFire, this, 1);

	int arrLeftJumpDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDown", "ÄìÄÚ_Á¡ÇÁ", arrLeftJumpDown, 1, 3, false, leftFire, this, 1);

	int arrRightJumpDownMove[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownMove", "ÄìÄÚ_Á¡ÇÁ", arrRightJumpDownMove, 1, 3, false, rightJump, this, 1);

	int arrLeftJumpDownMove[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownMove", "ÄìÄÚ_Á¡ÇÁ", arrLeftJumpDownMove, 1, 3, false, leftJump, this, 1);

	int RightMahaKick[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightMahaKick", "ÄìÄÚ_¸¶ÇÏÅ±", RightMahaKick, 22, 12, false, rightFire, this, 1);

	int LeftMahaKick[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftMahaKick", "ÄìÄÚ_¸¶ÇÏÅ±", LeftMahaKick, 22, 12, false, leftFire, this, 1);

	int RightDead[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightDead", "ÄìÄÚ_Á×À½", RightMahaKick, 22, 10, false, 1);

	int LeftDead[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftDead", "ÄìÄÚ_Á×À½", LeftMahaKick, 22, 10, false, 1);

}

// ÀÌµ¿ ¸ð¼Ç
void kyoko::moveMotion()
{
	// ¿À¸¥ÂÊ ÀÌµ¿
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
		_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
		_kyokoMotion->start();
	}

	// ¿À¸¥ÂÊ ¸ØÃß±â
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("ÄìÄÚ_ÀÏ¹Ý");
		_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
		_kyokoMotion->start();
	}

	
	// ¿ÞÂÊ ÀÌµ¿
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
		_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
		_kyokoMotion->start();
	}

	// ¿ÞÂÊ ¸ØÃß±â
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("ÄìÄÚ_ÀÏ¹Ý");
		_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
		_kyokoMotion->start();
	}

	// À§Å°¸¦ ´©¸¦°æ¿ì
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
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

	// ¾Æ·¡Å°¸¦ ´©¸¦°æ¿ì
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°È±â");
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

// °ø°Ý ¸ð¼Ç
void kyoko::attackMotion()
{
	// ÆòÅ¸
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°ø°Ý1");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack1");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°ø°Ý1");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack1");
			_kyokoMotion->start();
		}
	}

	// °­°ø°Ý
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°­°ø°Ý");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack_s");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_°­°ø°Ý");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack_s");
			_kyokoMotion->start();
		}
	}

	// ¸¶ÇÏÅ±(ÇÊ»ì±â)
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_¸¶ÇÏÅ±");
			_kyokoDirection = KYOKODIRECTION_RIGHT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightMahaKick");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_¸¶ÇÏÅ±");
			_kyokoDirection = KYOKODIRECTION_LEFT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftMahaKick");
			_kyokoMotion->start();
		}
	}
}

// Á¡ÇÁ ¸ð¼Ç
void kyoko::jumpMotion()
{
	// Á¡ÇÁ
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_jump->jumping(&_x, &_y, 8.0f, 0.4f);

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_Á¡ÇÁ");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_Á¡ÇÁ");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_Á¡ÇÁ");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
		{
			_image = IMAGEMANAGER->findImage("ÄìÄÚ_Á¡ÇÁ");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}
	}

	// ÀÏ¹ÝÁ¡ÇÁÀÏ¶§ ¸ð¼Ç º¯°æ
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

	// ÀÌµ¿ Á¡ÇÁÀÏ¶§ ¸ð¼Çº¯°æ
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
