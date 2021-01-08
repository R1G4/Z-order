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
	//�̹��� �� �ִϸ��̼� �߰�
	addFrame();
	//�׸��� �ʱ�ȭ
	IMAGEMANAGER->addImage("Girl_Shadow", "SchoolGirl size200/SchoolGirl_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	_shadowImg = IMAGEMANAGER->findImage("Girl_Shadow");

	//�̹��� �ʱ�ȭ
	_schoolGirlImg = imgTaunt;

	//�ִϸ��̼� �ʱ�ȭ
	_motion = aniLeftTaunt;
	_motion->start();

	//��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	_angle = 0;

	//���ʹ� ��Ʈ �ʱ�ȭ
	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(), _schoolGirlImg->getFrameHeight());
	//�׸��� ��Ʈ �ʱ�ȭ
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right) / 2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
	
	_isAction = false;
	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	
	//���� ���� �ʱ�ȸ
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//���ʹ� ���� �ʱ�ȭ
	_direction = LEFT;
	_state = TAUNT;

	//���ʹ� ���� ���� �� �ʱ�ȭ
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

	//���ʹ� ���� ����
	state();

	//���ʹ� �̵�
	move();

	KEYANIMANAGER->update();

	//���ʹ� �� �׸��� ��Ʈ ����
	_schoolGirlRc = RectMakeCenter(_x, _y, _schoolGirlImg->getFrameWidth(), _schoolGirlImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_schoolGirlRc.left + _schoolGirlRc.right) / 2, _schoolGirlRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void schoolGirl::state()
{
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime());

	//�ִϸ��̼��� ���� ��� IDLE�� ��ȯ
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

	//Ư�� �Ÿ��ȿ� �÷��̾ ���� �� ��
	float distance = getDistance(_x, _y, _kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y);
	if (distance < 500 && _isAction)
	{
		_isFollow = true;
		RECT temp;
		//�÷��̾�� ���ʹ� �浹 ��
		if (IntersectRect(&temp, &_kyoko->getRect(), &_schoolGirlRc))
		{
			switch (_state)
			{
				//IDLE ���¶�� ����, ��� ���~
			case schoolGirl::IDLE:
				//���� ���� ��������
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

				//�̵� ���¶�� �ִϸ��̼� ����(�Ŀ� IDLE���·� ���� ��)
			case schoolGirl::WALK: case schoolGirl::RUN:
				_motion->stop();
				break;

				//�⺻����
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
				//�޺����� 1
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
				//�޺����� 2
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
				//�޺����� 3
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
			//���ʹ̴� �̵� �� �ʿ� ������ �Ʒ� �ڵ�� ��ŵ
			return;
		}

		//�÷��̾��� ��ġ�� ���ʹ� ���� �����ʿ� ���� ���
		if (_kyoko->getKyokoPoint().x > _x)
		{
			//�� �Ÿ��� �ִٸ� �޸���
			if (((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_schoolGirlImg = imgRun;
				_motion = aniRightRun;
				_motion->start();
			}
			//�� �Ÿ��� �����ٸ� �ȴ´�
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
		//�÷��̾��� ��ġ�� ���ʹ� ���� ���ʿ� ���� ���
		else if (_kyoko->getKyokoPoint().x <= _x)
		{
			//�� �Ÿ��� �ִٸ� �޸���
			if (((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 275)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_schoolGirlImg = imgRun;
				_motion = aniLeftRun;
				_motion->start();
			}	
			//�� �Ÿ��� �����ٸ� �ȴ´�
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
	//���� �Ÿ��� ���� ���� ��� ���� ����
	else
	{
		switch (_state)
		{
		case schoolGirl::IDLE:
			//Ž�� Ÿ�̸Ӱ� �پ���.
			_questTimer--;
			//Ž�� Ÿ�̸Ӱ� �ּ� Ž�� �ð���ŭ ���� �� ���
			if (_questTimer < _questMin)
			{
				//�ּ� Ž�� �ð� ������ �ʱ�ȭ
				_questMin = RND->getFromIntTo(50, 140);
				
				//Ž�� ���� ��ȯ
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
				//Ž�� Ÿ�̸Ӱ� ���� �� ���
				if (_questTimer < 0)
				{
					//Ž�� Ÿ�̸� ������ �ʱ�ȭ
					_questTimer = RND->getFromIntTo(180, 220);
					//�޽����� ��ȯ
					_motion->stop();
				}
			}
			break;
		}
	}
}

void schoolGirl::move()
{
	//�÷��̾�� ���ʹ��� ���� ���
	_angle = getAngle(_x, _y, _kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y);

	switch (_state)
	{
	case schoolGirl::WALK:
		if (_isFollow)
		{
			//���ʹ̰� �����ϰ� �ִٸ� �ش� ������ �̵�
			_x += cos(_angle) * ENEMYSPEED;
			_y += -sin(_angle) * ENEMYSPEED;
		}
		else
		{
			//Ž�� �� �̶�� X�����θ� �̵�
			float tempSpeed = ENEMYSPEED;
			switch (_direction)
			{
			case schoolGirl::LEFT:
				//���� ���� ��� �޽Ļ��·� ��ȯ
				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				//���� ���� ��� �޽Ļ��·� ��ȯ
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
			//���ʹ̰� �����ϰ� �ִٸ� �ش� ������ �̵�
			_x += cos(_angle) * 2 * ENEMYSPEED;
			_y += -sin(_angle) * 2 * ENEMYSPEED;
		}
		else
		{
			//Ž�� �� �̶�� X�����θ� �̵�
			float tempSpeed = ENEMYSPEED;
			switch (_direction)
			{
			case schoolGirl::LEFT:
				//���� ���� ��� �޽Ļ��·� ��ȯ
				if (_x - tempSpeed < _schoolGirlImg->getWidth() / 2)
					_motion->stop();
				else
					_x -= ENEMYSPEED;
				break;
			case schoolGirl::RIGHT:
				//���� ���� ��� �޽Ļ��·� ��ȯ
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
