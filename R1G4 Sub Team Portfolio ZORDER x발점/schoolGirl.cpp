#include "stdafx.h"
#include "schoolGirl.h"
#include "kyoko.h"

schoolGirl::schoolGirl()
{
}

schoolGirl::~schoolGirl()
{
}

HRESULT schoolGirl::init(float x, float y, STATE state, DIRECTION direction)
{
	//�̹��� �� �ִϸ��̼� �ʱ�ȭ
	addFrame();

	//���ʹ� ���� �ʱ�ȭ
	enemy::init(x, y, state, direction);

	//�ش� ���ʹ� ���ǵ�
	_speed = 1.8f;

	return S_OK;
}

void schoolGirl::release()
{
}

void schoolGirl::update()
{
	enemy::update();

	_enemyAttack->update();

	//���ʹ� ���� ����
	state();

	//���ʹ� �̵�
	move();

	//KEYANIMANAGER->update();

	//���ʹ� �� �׸��� ��Ʈ ����
	_rc = RectMakeCenter(_x, _y + 10, 40, 152);
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void schoolGirl::addFrame()
{
	imgIdle = IMAGEMANAGER->findImage("Girl_Idle");
	imgWalk = IMAGEMANAGER->findImage("Girl_Walk");
	imgRun = IMAGEMANAGER->findImage("Girl_Run");
	imgBlock = IMAGEMANAGER->findImage("Girl_Block");
	imgAttack = IMAGEMANAGER->findImage("Girl_Attack");
	imgCombo_attack_1 = IMAGEMANAGER->findImage("Girl_ComboAttack1");
	imgCombo_attack_2 = IMAGEMANAGER->findImage("Girl_ComboAttack2");
	imgCombo_attack_3 = IMAGEMANAGER->findImage("Girl_ComboAttack3");
	imgHit = IMAGEMANAGER->findImage("Girl_Hit");
	imgDownup = IMAGEMANAGER->findImage("Girl_Downup");
	imgKnockdown = IMAGEMANAGER->findImage("Girl_Knockdown");
	imgDazed = IMAGEMANAGER->findImage("Girl_Dazed");
	imgJump = IMAGEMANAGER->findImage("Girl_Jump");
	imgTaunt = IMAGEMANAGER->findImage("Girl_Taunt");
	_shadowImg = IMAGEMANAGER->findImage("Girl_Shadow");

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
	aniRightTaunt->setFPS(9);
	aniLeftTaunt = new animation;
	aniLeftTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniLeftTaunt->setPlayFrame(51, 26, false, false, ActionCheck, this);
	aniLeftTaunt->setFPS(9);
}

void schoolGirl::render(POINT camera)
{
	//Rectangle(getMemDC(), _enemyRc, camera);

	/*RECT temp = RectMakeCenter(_kyoko->getKyokoPoint().x, _kyoko->getKyokoPoint().y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2 - 40);
	Rectangle(getMemDC(), , camera);*/
	/*if (_kyoko)
	{
		RECT temp = RectMakeCenter((_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2, _kyoko->getRect().right - _kyoko->getRect().left, _kyoko->getRect().bottom - _kyoko->getRect().top - 100);
		 Rectangle(getMemDC(), temp, camera);
	}*/
	enemy::render(camera);

	switch (_state)
	{
	case schoolGirl::IDLE: case schoolGirl::ATTACK:  case schoolGirl::COMBO_ATTACK_1:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 10, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 10, _motion, camera);
		break;
	case schoolGirl::COMBO_ATTACK_2:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 20, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 20, _motion, camera);
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
		//Rectangle(getMemDC(), _enemyRc, camera);
	}
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

	//Ư�� �Ÿ��ȿ� �÷��̾ ���� �� ��
	float distance = getDistance(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);
	if (distance < 525 && _isAction)
	{
		//�Ÿ��ȿ� ���� �� �� ����ǥ�� �����ش�.
		if (!_isFollow)
		{
			//�����ϰ��� �ϴ� ���⿡ ����� ��ġ�� �Ķ��Ÿ�� ������.
			if (_kyoko->getKyokoPoint().x > _x)
				enemy::effectPoint(RIGHT);
			else
				enemy::effectPoint(LEFT);
		}

		//������ �����Ѵ�.
		_isFollow = true;

		RECT temp;
		//�÷��̾�� ���ʹ� �浹 ��
		if (IntersectRect(&temp, &RectMakeCenter((_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2, _kyoko->getRect().right - _kyoko->getRect().left, _kyoko->getRect().bottom - _kyoko->getRect().top - 100), &_enemyRc))
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
						_enemyImg = imgAttack;
						_motion = aniLeftAttack;
						_motion->start();
						break;
					case schoolGirl::RIGHT:
						_enemyImg = imgAttack;
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
					_enemyImg = imgCombo_attack_1;
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
					_enemyImg = imgCombo_attack_2;
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
					_enemyImg = imgCombo_attack_3;
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
			if (((_direction != RIGHT && _state != RUN) || (_direction == LEFT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = RIGHT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniRightRun;
				_motion->start();
			}
			//�� �Ÿ��� �����ٸ� �ȴ´�
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
		//�÷��̾��� ��ġ�� ���ʹ� ���� ���ʿ� ���� ���
		else if (_kyoko->getKyokoPoint().x <= _x)
		{
			//�� �Ÿ��� �ִٸ� �޸���
			if (((_direction != LEFT && _state != RUN) || (_direction == RIGHT && _state == RUN) || (_direction == LEFT && _state == WALK) || (_direction == RIGHT && _state == WALK) || _state == IDLE) && distance > 250)
			{
				_motion->stop();
				_direction = LEFT;
				_state = RUN;
				_enemyImg = imgRun;
				_motion = aniLeftRun;
				_motion->start();
			}
			//�� �Ÿ��� �����ٸ� �ȴ´�
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
				_enemyImg = imgWalk;
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
	//�浿�ߴٸ� �̵��� �����Ѵ�.
	if (_isCollision)
		return;

	//�÷��̾�� ���ʹ��� ���� ���
	_angle = getAngle(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);
	int temp;
	switch (_state)
	{
	case schoolGirl::WALK:
		if (_isFollow)
		{
			//���ʹ̰� �����ϰ� �ִٸ� �ش� ������ �̵�
			_x += cos(_angle) * _speed;
			_y += -sin(_angle) * _speed;
		}
		else
		{
			//Ž�� �� �̶�� X�����θ� �̵�
			switch (_direction)
			{
			case schoolGirl::LEFT:
				////���� ���� ���� ��� �޽Ļ��·� ��ȯ
				//if (_x - _speed < _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
				//	_motion->stop();
				//else
				_x -= _speed;
				break;
			case schoolGirl::RIGHT:
				////������ ���� ���� ��� �޽Ļ��·� ��ȯ
				//if (_x + _speed > WINSIZEX - _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
				//	_motion->stop();
				//else
				_x += _speed;

				break;
			}
		}
		break;
	case schoolGirl::RUN:
		if (_isFollow)
		{
			//���ʹ̰� �����ϰ� �ִٸ� �ش� ������ �̵�
			_x += cos(_angle) * 2 * _speed;
			_y += -sin(_angle) * 2 * _speed;
		}
		else
		{
			//Ž�� �� �̶�� X�����θ� �̵�
			switch (_direction)
			{
			case schoolGirl::LEFT:
				////���� ���� ���� ��� �޽Ļ��·� ��ȯ
				//if (_x - 2 * _speed < _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
				//	_motion->stop();
				//else
				_x -= 2 * _speed;
				break;
			case schoolGirl::RIGHT:
				//������ ���� ���� ��� �޽Ļ��·� ��ȯ
			/*	if (_x + 2 * _speed > WINSIZEX - _enemyImg->getWidth() / (_enemyImg->getMaxFrameX() + 1) / 2)
					_motion->stop();
				else*/
				_x += 2 * _speed;

				break;
			}
		}
		break;
	}
}

void schoolGirl::ActionCheck(void* obj)
{
	schoolGirl* k = (schoolGirl*)obj;
	k->_isAction = true;
}