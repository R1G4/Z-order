#include "stdafx.h"
#include "kyoko.h"

HRESULT kyoko::init()
{
	addImage();
	addMotionAni();

	_image = IMAGEMANAGER->findImage("����_�Ϲ�");
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
	
	// �̵��� ������� �̵��� ���ΰ� - ���� �ȵɰŰ��� ���� ��ġ������ ����
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

	// �̹���ó���� ���� ��Ʈ
	_image_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	// �浹ó���� ���� ��Ʈ
	_rc = RectMakeCenter(_x, _y, 40, _image->getFrameHeight() - 30);
	// �ִϸ��̼� ���
	KEYANIMANAGER->update();

	// ��������
	_jump->update();
}

void kyoko::render()
{
	if (_image == IMAGEMANAGER->findImage("����_������"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top -50 , _kyokoMotion);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion);

	// �浹ó���� ���� ��Ʈ
	if(KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(), _rc);
}

// ������ �Ϲ� ������� �ݹ�
void kyoko::rightFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�Ϲ�");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightIdle"));
	k->getKyokoMotion()->start();
}

// ���� �Ϲ� ������� �ݹ�
void kyoko::leftFire(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�Ϲ�");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_IDLE);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftIdle"));
	k->getKyokoMotion()->start();
}

// ������ �ȱ� ������� �ݹ�
void kyoko::rightJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�ȱ�");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightWalk"));
	k->getKyokoMotion()->start();
}

// ���� �ȱ� ������� �ݹ�
void kyoko::leftJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�ȱ�");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_WALK);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftWalk"));
	k->getKyokoMotion()->start();
}

// ������ �ٱ� ������� �ݹ�
void kyoko::rightMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�޸���");
	k->setKyokoDirection(KYOKODIRECTION_RIGHT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoRightRun"));
	k->getKyokoMotion()->start();
}

// ���� �ٱ� ������� �ݹ�
void kyoko::leftMoveJump(void * obj)
{
	kyoko* k = (kyoko*)obj;

	k->_image = IMAGEMANAGER->findImage("����_�޸���");
	k->setKyokoDirection(KYOKODIRECTION_LEFT_RUN);
	k->setKyokoMotion(KEYANIMANAGER->findAnimation("kyokoLeftRun"));
	k->getKyokoMotion()->start();
}

// ���� �̹��� ����
void kyoko::addImage()
{
	IMAGEMANAGER->addFrameImage("����_�Ϲ�", "kyoko/idle_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ȱ�", "kyoko/walk_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�޸���", "kyoko/run_1.bmp", 0, 0, 4800, 400, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "kyoko/jump_1.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����1", "kyoko/attack_1_1.bmp", 0, 0, 1800, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����2", "kyoko/attack_2_1.bmp", 0, 0, 2100, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����3", "kyoko/attack_3_3.bmp", 0, 0, 2700, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_������", "kyoko/attack_strong_2.bmp", 0, 0, 3000, 600, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����ű", "kyoko/mahaKick_2.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ǰ�1", "kyoko/attacked_1_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ǰ�2", "kyoko/attacked_2_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "kyoko/dead_1.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
}

// ���� �ൿ �ִϸ��̼�
void kyoko::addMotionAni()
{
	int rightIdle[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightIdle", "����_�Ϲ�", rightIdle, 12, 8, true, 1);

	int leftIdle[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftIdle", "����_�Ϲ�", leftIdle, 12, 8, true, 1);

	int rightWalk[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightWalk", "����_�ȱ�", rightWalk, 12, 5, true, 1);

	int leftWalk[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftWalk", "����_�ȱ�", leftWalk, 12, 5, true, 1);

	int rightRun[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightRun", "����_�޸���", rightRun, 16, 15, true, 1);

	int leftRun[] = { 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftRun", "����_�޸���", leftRun, 16, 15, true, 1);

	int arrRightAttack_1[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack1", "����_����1", arrRightAttack_1, 6, 10, false, rightFire, this, 1);

	int arrLeftAttack_1[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack1", "����_����1", arrLeftAttack_1, 6, 10, false, leftFire, this, 1);

	int arrRightAttack_2[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack2", "����_����2", arrRightAttack_2, 7, 10, false, rightFire, this, 1);

	int arrLeftAttack_2[] = { 13,12,11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack2", "����_����2", arrLeftAttack_2, 7, 10, false, leftFire, this, 1);

	int arrRightAttack_3[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack3", "����_����3", arrRightAttack_3, 9, 10, false, rightFire, this, 1);

	int arrLeftAttack_3[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack3", "����_����3", arrLeftAttack_3, 9, 10, false, leftFire, this, 1);

	int arrRightAttack_strong[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack_s", "����_������", arrRightAttack_strong, 10, 10, false, rightFire, this, 1);

	int arrLeftAttack_strong[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack_s", "����_������", arrLeftAttack_strong, 10, 10, false, leftFire, this, 1);

	int arrRightAttacked_1[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked1", "����_�ǰ�1", arrRightAttacked_1, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_1[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked1", "����_�ǰ�1", arrLeftAttacked_1, 4, 7, false, leftFire, this, 1);

	int arrRightAttacked_2[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttacked2", "����_�ǰ�2", arrRightAttacked_2, 4, 7, false, rightFire, this, 1);

	int arrLeftAttacked_2[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttacked2", "����_�ǰ�2", arrLeftAttacked_2, 4, 7, false, leftFire, this, 1);

	int arrRightJump[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJump", "����_����", arrRightJump, 1, 2, false, 1);

	int arrLeftJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJump", "����_����", arrLeftJump, 1, 2, false, 1);

	int arrRightJumpTop[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpTop", "����_����", arrRightJumpTop, 1, 2, false, 1);

	int arrLeftJumpTop[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpTop", "����_����", arrLeftJumpTop, 1, 2, false, 1);

	int arrRightJumpDown[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDown", "����_����", arrRightJumpDown, 1, 3, false, rightFire, this, 1);

	int arrLeftJumpDown[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDown", "����_����", arrLeftJumpDown, 1, 3, false, leftFire, this, 1);

	int arrRightJumpDownMove[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownMove", "����_����", arrRightJumpDownMove, 1, 3, false, rightJump, this, 1);

	int arrLeftJumpDownMove[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownMove", "����_����", arrLeftJumpDownMove, 1, 3, false, leftJump, this, 1);

	int RightMahaKick[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightMahaKick", "����_����ű", RightMahaKick, 22, 12, false, rightFire, this, 1);

	int LeftMahaKick[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftMahaKick", "����_����ű", LeftMahaKick, 22, 12, false, leftFire, this, 1);

	int RightDead[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightDead", "����_����", RightMahaKick, 22, 10, false, 1);

	int LeftDead[] = { 43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,22 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftDead", "����_����", LeftMahaKick, 22, 10, false, 1);

}

// �̵� ���
void kyoko::moveMotion()
{
	// ������ �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("����_�ȱ�");
		_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
		_kyokoMotion->start();
	}

	// ������ ���߱�
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_image = IMAGEMANAGER->findImage("����_�Ϲ�");
		_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
		_kyokoMotion->start();
	}

	
	// ���� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("����_�ȱ�");
		_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
		_kyokoMotion->start();
	}

	// ���� ���߱�
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_image = IMAGEMANAGER->findImage("����_�Ϲ�");
		_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
		_kyokoMotion->start();
	}

	// ��Ű�� �������
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_�ȱ�");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_�ȱ�");
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

	// �Ʒ�Ű�� �������
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_�ȱ�");
			_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_�ȱ�");
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

// ���� ���
void kyoko::attackMotion()
{
	// ��Ÿ
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_����1");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack1");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_����1");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_1;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack1");
			_kyokoMotion->start();
		}
	}

	// ������
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_������");
			_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack_s");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_������");
			_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_STRONG;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack_s");
			_kyokoMotion->start();
		}
	}

	// ����ű(�ʻ��)
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_����ű");
			_kyokoDirection = KYOKODIRECTION_RIGHT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightMahaKick");
			_kyokoMotion->start();
		}
		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
			_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_����ű");
			_kyokoDirection = KYOKODIRECTION_LEFT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftMahaKick");
			_kyokoMotion->start();
		}
	}
}

// ���� ���
void kyoko::jumpMotion()
{
	// ����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_jump->jumping(&_x, &_y, 8.0f, 0.4f);

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_����");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
		{
			_image = IMAGEMANAGER->findImage("����_����");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
		{
			_image = IMAGEMANAGER->findImage("����_����");
			_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
			_kyokoMotion->start();
		}

		if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
		{
			_image = IMAGEMANAGER->findImage("����_����");
			_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_MOVE;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
			_kyokoMotion->start();
		}
	}

	// �Ϲ������϶� ��� ����
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

	// �̵� �����϶� ��Ǻ���
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
