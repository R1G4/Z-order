#include "stdafx.h"
#include "kyoko.h"

HRESULT kyoko::init()
{
	addMotionAni();

	_image = IMAGEMANAGER->findImage("����_�Ϲ�");
	_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
	_shadow = IMAGEMANAGER->findImage("�׸���");
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

	// ���ݸ���� �������� ����?
	_attack_rc = RectMake(_rc.left, _rc.top, 0, 0);
	attackMotion();
	jumpMotion();

	// �̹���ó���� ���� ��Ʈ

	if (!_isJump)
	{
		_i_x = (_shadow_rc.left + _shadow_rc.right) / 2;
		_i_y = _shadow_rc.top - 80;
		_image_rc = RectMakeCenter(_i_x, _i_y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	else
		_image_rc = RectMakeCenter(_i_x, _i_y, _image->getFrameWidth(), _image->getFrameHeight());
	// �浹ó���� ���� ��Ʈ
	if (!_isJump)
	{
		_i_x = (_shadow_rc.left + _shadow_rc.right) / 2;
		_i_y = _shadow_rc.top - 80;
		_rc = RectMakeCenter(_i_x, _i_y, 40, _image->getFrameHeight() - 40);
	}
	else
		_rc = RectMakeCenter(_i_x, _i_y, 40, _image->getFrameHeight() - 40);

	// �׸���ó���� ���� ��Ʈ (z-order)
	_shadow_rc = RectMakeCenter(_x, _y, _shadow->getWidth(), _shadow->getHeight());
	// �ִϸ��̼� ���
	//KEYANIMANAGER->update();

	// ��������
	_jump->update();
	_shadow_jump->update();
}

void kyoko::render()
{
	_shadow->render(getMemDC(), _shadow_rc.left, _shadow_rc.top);

	if (_image == IMAGEMANAGER->findImage("����_������"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top - 50, _kyokoMotion);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion);
	// �浹ó���� ���� ��Ʈ(�����)
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

	if (_image == IMAGEMANAGER->findImage("����_������"))
	{
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top - 50, _kyokoMotion, camera);
	}
	else
		_image->aniRender(getMemDC(), _image_rc.left, _image_rc.top, _kyokoMotion, camera);

	// �浹ó���� ���� ��Ʈ
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc, camera);
		Rectangle(getMemDC(), _shadow_rc, camera);
		Rectangle(getMemDC(), _attack_rc, camera);
	}
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
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack1", "����_����1", arrRightAttack_1, 6, 15, false, rightFire, this, 1);

	int arrLeftAttack_1[] = { 11,10,9,8,7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack1", "����_����1", arrLeftAttack_1, 6, 15, false, leftFire, this, 1);

	int arrRightAttack_2[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack2", "����_����2", arrRightAttack_2, 7, 15, false, rightFire, this, 1);

	int arrLeftAttack_2[] = { 13,12,11,10,9,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack2", "����_����2", arrLeftAttack_2, 7, 15, false, leftFire, this, 1);

	int arrRightAttack_3[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttack3", "����_����3", arrRightAttack_3, 9, 15, false, rightFire, this, 1);

	int arrLeftAttack_3[] = { 17,16,15,14,13,12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttack3", "����_����3", arrLeftAttack_3, 9, 15, false, leftFire, this, 1);

	int arrRightAttack_dash[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttackDash", "����_�뽬����", arrRightAttack_dash, 8, 15, false, rightFire, this, 1);

	int arrLeftAttack_dash[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttackDash", "����_�뽬����", arrLeftAttack_dash, 8, 15, false, leftFire, this, 1);

	int arrRightAttack_jump[] = { 1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightAttackJump", "����_��������", arrRightAttack_jump, 2, 10, false, 1);

	int arrLeftAttack_jump[] = { 4,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftAttackJump", "����_��������", arrLeftAttack_jump, 2, 10, false, 1);

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

	int arrRightJumpDownWalk[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownWalk", "����_����", arrRightJumpDownWalk, 1, 3, false, rightJump, this, 1);

	int arrLeftJumpDownRun[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownRun", "����_����", arrLeftJumpDownRun, 1, 3, false, leftMoveJump, this, 1);

	int arrRightJumpDownRun[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoRightJumpDownRun", "����_����", arrRightJumpDownRun, 1, 3, false, rightMoveJump, this, 1);

	int arrLeftJumpDownWalk[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("kyokoLeftJumpDownWalk", "����_����", arrLeftJumpDownWalk, 1, 3, false, leftJump, this, 1);

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
	// ���� ���Ҷ�
	if (!_isAttack)
	{
		// ������ �̵�
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			// �ι� ���� ��� �޸����
			if (_isRunning)
			{
				_image = IMAGEMANAGER->findImage("����_�޸���");
				_kyokoDirection = KYOKODIRECTION_RIGHT_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightRun");
				_kyokoMotion->start();
			}

			// �ѹ� ���� ��� �ȱ��
			if (!_isRunning && !_isJump)
			{
				_image = IMAGEMANAGER->findImage("����_�ȱ�");
				_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
				_kyokoMotion->start();
				_isRunning = true;
			}
		}
		// ������ Ű ������ ������ �̵�
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
		// ������ ���߱�
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_�Ϲ�");
				_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
				_kyokoMotion->start();
				_r_count = 1;
			}
			_isMoving = false;
			_isCollision = false;
		}

		// ���� �̵�
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			// �ι� ���� ��� �޸����
			if (_isRunning)
			{
				_image = IMAGEMANAGER->findImage("����_�޸���");
				_kyokoDirection = KYOKODIRECTION_LEFT_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftRun");
				_kyokoMotion->start();
			}

			// �ѹ� ���� ��� �ȱ��
			if (!_isRunning && !_isJump)
			{
				_image = IMAGEMANAGER->findImage("����_�ȱ�");
				_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
				_kyokoMotion->start();
				_isRunning = true;
			}
		}
		// ���� Ű ������ ������ �̵�
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
		// ���� ���߱�
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_�Ϲ�");
				_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
				_kyokoMotion->start();
			}
			_isMoving = false;
			_isCollision = false;
		}

		// ��Ű�� ���� ���
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
		// ���� Ű ������ ������ �̵�
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
		// ���� Ű ���� ����
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
				{
					_image = IMAGEMANAGER->findImage("����_�Ϲ�");
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
					_image = IMAGEMANAGER->findImage("����_�Ϲ�");
					_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}
		}

		// �Ʒ�Ű�� ���� ���
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
		// �Ʒ��� Ű ������ ������ �̵�
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
		// �Ʒ��� Ű ���� ����
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
				{
					_image = IMAGEMANAGER->findImage("����_�Ϲ�");
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
					_image = IMAGEMANAGER->findImage("����_�Ϲ�");
					_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
					_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
					_kyokoMotion->start();
				}
				_isMoving = false;
				_isCollision = false;
			}
		}

		// �����ð��ȿ� �ѹ� �� ����Ű�� ������ �޸�����
		if (_isRunning) _r_count++;
		if (_r_count >= 20) { _isRunning = false; _r_count = 0; }
	}

	// �������ݽ�
	else
	{
		// ������ Ű �������
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �Ϲ�/�ȱ� ���� ���ݽ�
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// �̵������� ���� ����
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
			// �޸��� ���� ���ݽ�
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

		// ���� Ű �������
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// �Ϲ�/�ȱ� ���� ���ݽ�
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// �̵������� ���� ����
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
			// �޸��� ���� ���ݽ�
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

		// �� Ű ���� ���
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			// �Ϲ�/�ȱ� ���� ���ݽ�
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// �̵������� ���� ����
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
			// �޸��� ���� ���ݽ�
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

		// �Ʒ� Ű ���� ���
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			// �Ϲ�/�ȱ� ���� ���ݽ�
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP &&
				_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK)
			{
				// �̵������� ���� ����
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
			// �޸��� ���� ���ݽ�
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

		// Ű�� �����
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

// ���� ���
void kyoko::attackMotion()
{
	// ��Ÿ
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_isAttack = true;
		if (_z_count == 0)
		{
			// �Ϲ��̳� �ȱ� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
			{
				_image = IMAGEMANAGER->findImage("����_����1");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_1;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack1");
				_kyokoMotion->start();

				_z_count = 1;
			}
			if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
				_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
			{
				_image = IMAGEMANAGER->findImage("����_����1");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_1;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack1");
				_kyokoMotion->start();

				_z_count = 1;
			}

			// �޸��� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_�뽬����");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_DASH;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackDash");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}
			if (_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_�뽬����");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_DASH;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackDash");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �Ϲ� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �ȱ� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �޸��� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.right = _rc.right + 100;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �Ϲ� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �ȱ� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_WALK ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_WALK)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}

			// �޸��� ���� �����϶� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_TOP_RUN ||
				_kyokoDirection == KYOKODIRECTION_LEFT_JUMP_DOWN_RUN)
			{
				_image = IMAGEMANAGER->findImage("����_��������");
				_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttackJump");
				_kyokoMotion->start();

				// Ÿ�� ����
				_attack_rc.left = _rc.left - 100;
				_attack_rc.right = _rc.right;
				_attack_rc.bottom = _rc.bottom;

				_z_count = 0;
			}
		}
		else if (_z_count == 1)
		{
			_frame_count = 0;
			// �Ϲ� ���ݿ��� ���Ӱ���
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1)
				_isNextAttack = true;
			if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_1)
				_isNextAttack = true;
		}
		else if (_z_count == 2)
		{
			_frame_count = 0;
			// �Ϲ� ���ݿ��� ���Ӱ���
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2)
				_isNextAttack = true;
			if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_2)
				_isNextAttack = true;
		}
	}

	// ������
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_isAttack = true;
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

	// ����ű(�ʻ��) - _maha_count�� ������ �̻� ������ ���Ұ�
	if (KEYMANAGER->isOnceKeyDown('A') && _maha_count > 120)
	{
		_isAttack = true;
		if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_WALK ||
			_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
		{
			_image = IMAGEMANAGER->findImage("����_����ű");
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
			_image = IMAGEMANAGER->findImage("����_����ű");
			_kyokoDirection = KYOKODIRECTION_LEFT_MAHAKICK;
			_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftMahaKick");
			_kyokoMotion->start();
			_maha_count = _maha_count - 150;
			_isMahaKick = true;
		}
	}

	// �Ϲݰ���1 ��Ʈ ����
	if (_kyokoMotion->getNowPlayIndex() == 2 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;
			cout << "�Ϲݰ���1" << endl;

			// Ÿ�� ����
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
			cout << "�Ϲݰ���1" << endl;

			// Ÿ�� ����
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// �Ϲݰ���2 ��Ʈ ����
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;
			cout << "�Ϲݰ���2" << endl;

			// Ÿ�� ����
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
			cout << "�Ϲݰ���2" << endl;

			// Ÿ�� ����
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// �Ϲݰ���3 ��Ʈ ����
	if (_kyokoMotion->getNowPlayIndex() == 3 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_3)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;
			cout << "�Ϲݰ���3" << endl;

			// Ÿ�� ����
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
			cout << "�Ϲݰ���3" << endl;

			// Ÿ�� ����
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// ������ ��Ʈ ����
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_STRONG)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;
			cout << "������" << endl;

			// Ÿ�� ����
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
			cout << "������" << endl;

			// Ÿ�� ����
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// ����ű ��Ʈ ����
	if ((_kyokoMotion->getNowPlayIndex() == 4 || _kyokoMotion->getNowPlayIndex() == 9 || _kyokoMotion->getNowPlayIndex() == 15) && 
		_kyokoDirection == KYOKODIRECTION_RIGHT_MAHAKICK)
	{
		_frame_count++;
		if (_frame_count >= 3)
		{
			_frame_count = 0;
			cout << "������" << endl;

			// Ÿ�� ����
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
			cout << "������" << endl;

			// Ÿ�� ����
			_attack_rc.left = _rc.left - 100;
			_attack_rc.right = _rc.right;
			_attack_rc.bottom = _rc.bottom;
		}
	}

	// �ڿ������� ���Ӱ����� ���� ����
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_1 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("����_����2");
		_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_2;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack2");
		_kyokoMotion->start();
		_z_count = 2;
		_isNextAttack = false;
	}
	if (_kyokoMotion->getNowPlayIndex() == 5 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_1 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("����_����2");
		_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_2;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack2");
		_kyokoMotion->start();
		_z_count = 2;
		_isNextAttack = false;
	}

	if (_kyokoMotion->getNowPlayIndex() == 6 && _kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_2 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("����_����3");
		_kyokoDirection = KYOKODIRECTION_RIGHT_ATTACK_3;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightAttack3");
		_kyokoMotion->start();
		_z_count = 3;
		_isNextAttack = false;
	}
	if (_kyokoMotion->getNowPlayIndex() == 6 && _kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_2 && _isNextAttack)
	{
		_kyokoMotion->stop();
		_image = IMAGEMANAGER->findImage("����_����3");
		_kyokoDirection = KYOKODIRECTION_LEFT_ATTACK_3;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftAttack3");
		_kyokoMotion->start();
		_z_count = 3;
		_isNextAttack = false;
	}
	
	// ������ idle���·� ���� ���Ӱ��� ī��Ʈ�� 0����
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE || _kyokoDirection == KYOKODIRECTION_LEFT_IDLE ||
		_kyokoDirection == KYOKODIRECTION_RIGHT_WALK || _kyokoDirection == KYOKODIRECTION_LEFT_WALK ||
		_kyokoDirection == KYOKODIRECTION_RIGHT_RUN || _kyokoDirection == KYOKODIRECTION_LEFT_RUN)
	{
		_isAttack = false;
		_isMahaKick = false;
		_z_count = 0;
		_frame_count = 0;
	}

	// �ʻ�� ������ ä��� (+����ó��)
	if (_maha_count <= 0)
		_maha_count = 0;
	if (!_isMahaKick && _maha_count <= 361)
		_maha_count++;
}

// ���� ���
void kyoko::jumpMotion()
{
	// ����
	if (!_isAttack)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_isJump = true;

			// �Ϲݻ��� ������ ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_IDLE)
			{
				_speed = 0;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// �Ϲݻ��� ���� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_IDLE)
			{
				_speed = 0;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			// �ȱ���� ������ ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_WALK)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 2.5f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// �ȱ���� ���� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_WALK)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 2.5f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_WALK;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			// �޸������ ������ ����
			if (_kyokoDirection == KYOKODIRECTION_RIGHT_RUN)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 5.0f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_RIGHT_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightJump");
				_kyokoMotion->start();
			}

			// �޸������ ���� ����
			if (_kyokoDirection == KYOKODIRECTION_LEFT_RUN)
			{
				if (_isCollision)
					_speed = 0;
				else
					_speed = 5.0f;
				_jump->setJumpSpeed(_speed);
				_shadow_jump->setJumpSpeed(_speed);
				_image = IMAGEMANAGER->findImage("����_����");
				_kyokoDirection = KYOKODIRECTION_LEFT_JUMP_RUN;
				_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftJump");
				_kyokoMotion->start();
			}

			_jump->jumping(&_i_x, &_i_y, 20.0f, 1.0f);
			_shadow_jump->jumping(&_x, &_y, 0.0f, 0.0f);
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

	// �ȱ� �����϶� ��Ǻ���
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

	// �޸��� �����϶� ��Ǻ���
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

	// �������� �����̸� ���� ���·� ����
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

	// �ȱ� �������� ���߸� �׳� ���� ���·� ����
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

	// �޸��� �������� ���߸� �׳� ���� ���·� ����
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

	//cout << "���� �ӵ� : " << _speed << endl;
	//cout << "������?" << _isMoving << endl;
	//cout << "���� ����?" << _kyokoDirection << endl;

	// ���� ���ݽ� ���� ������ �⺻���·� ����
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�Ϲ�");
		_kyokoDirection = KYOKODIRECTION_RIGHT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightIdle");
		_kyokoMotion->start();
		_isMoving = false;
		_isCollision = false;
		_isJump = false;
	}

	// ���� ���ݽ� ���� ������ �⺻���·� ����
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 0;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�Ϲ�");
		_kyokoDirection = KYOKODIRECTION_LEFT_IDLE;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftIdle");
		_kyokoMotion->start();
		_isMoving = false;
		_isCollision = false;
		_isJump = false;
	}

	// �ȱ� ���� ���ݽ� ���� ������ �޸�����·� ����
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�ȱ�");
		_kyokoDirection = KYOKODIRECTION_RIGHT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightWalk");
		_kyokoMotion->start();
		_isJump = false;
	}

	// �ȱ� ���� ���ݽ� ���� ������ �޸�����·� ����
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 2.5f;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�ȱ�");
		_kyokoDirection = KYOKODIRECTION_LEFT_WALK;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftWalk");
		_kyokoMotion->start();
		_isJump = false;
	}

	// �޸��� ���� ���ݽ� ���� ������ �޸�����·� ����
	if (_kyokoDirection == KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 5;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�޸���");
		_kyokoDirection = KYOKODIRECTION_RIGHT_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoRightRun");
		_kyokoMotion->start();
		_isJump = false;
	}

	// �޸��� ���� ���ݽ� ���� ������ �޸�����·� ����
	if (_kyokoDirection == KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN && (_shadow_rc.top <= _image_rc.bottom))
	{
		_speed = 5;
		_jump->setJumpSpeed(_speed);
		_shadow_jump->setJumpSpeed(_speed);
		_image = IMAGEMANAGER->findImage("����_�޸���");
		_kyokoDirection = KYOKODIRECTION_LEFT_RUN;
		_kyokoMotion = KEYANIMANAGER->findAnimation("kyokoLeftRun");
		_kyokoMotion->start();
		_isJump = false;
	}

	// ������ �ƴҶ� bool �� ����
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
