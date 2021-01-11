#include "stdafx.h"
#include "schoolBoy.h"
#include "kyoko.h"

schoolBoy::schoolBoy()
{
}

schoolBoy::~schoolBoy()
{
}

HRESULT schoolBoy::init(float x, float y, STATE state, DIRECTION direction)
{
	//�̹��� �� �ִϸ��̼� �ʱ�ȭ
	addFrame();

	//���ʹ� ���� �ʱ�ȭ
	enemy::init(x, y, state, direction);

	//�ش� ���ʹ� ���ǵ�
	_speed = 1.8f;

	setAttackInfo();
	return S_OK;
}

void schoolBoy::release()
{
}

void schoolBoy::setAttackInfo()
{
	attackInfo attackTemp;
	attackTemp.damage = 1;
	attackTemp.isTouch = false;

	//�������� ���� �����ϴ� ��� �ε����� ��Ʈ ����

	//�Ϲݰ���1
	attackTemp.startIndex = 2;
	attackTemp.endIndex = 4;
	attackTemp.plusY = 15;
	attackTemp.width = 80;
	attackTemp.height = 40;
	_mAttackInfo.insert(make_pair(ATTACK, attackTemp));

	//�޺� 1
	attackTemp.startIndex = 3;
	attackTemp.endIndex = 4;
	attackTemp.plusY = 0;
	attackTemp.width = 90;
	attackTemp.height = 100;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_1, attackTemp));

	//�޺�2
	attackTemp.startIndex = 2;
	attackTemp.endIndex = 3;
	attackTemp.plusY = 10;
	attackTemp.width = 70;
	attackTemp.height = 70;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_2, attackTemp));

	//�޺�3
	attackTemp.startIndex = 2;
	attackTemp.endIndex = 5;
	attackTemp.plusY = 40;
	attackTemp.width = 80;
	attackTemp.height = 40;
	_mAttackInfo.insert(make_pair(COMBO_ATTACK_3, attackTemp));
}

void schoolBoy::update()
{
	setAttackRect(_state, _direction);

	_enemyAttack->update();

	//���ʹ� ���� ����
	state();

	//���ʹ� �̵�
	move();

	//���ʹ� �� �׸��� ��Ʈ ����
	_rc = RectMakeCenter(_x, _y + 10, 40, 152);
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void schoolBoy::addFrame()
{
	imgIdle = IMAGEMANAGER->findImage("Boy_Idle");
	imgWalk = IMAGEMANAGER->findImage("Boy_Walk");
	imgRun = IMAGEMANAGER->findImage("Boy_Run");
	imgBlock = IMAGEMANAGER->findImage("Boy_Block");
	imgAttack = IMAGEMANAGER->findImage("Boy_Attack");
	imgCombo_attack_1 = IMAGEMANAGER->findImage("Boy_ComboAttack1");
	imgCombo_attack_2 = IMAGEMANAGER->findImage("Boy_ComboAttack2");
	imgCombo_attack_3 = IMAGEMANAGER->findImage("Boy_ComboAttack3");
	imgHit = IMAGEMANAGER->findImage("Boy_Hit");
	imgDownup = IMAGEMANAGER->findImage("Boy_Downup");
	imgDazed = IMAGEMANAGER->findImage("Boy_Dazed");
	imgJump = IMAGEMANAGER->findImage("Boy_Jump");
	imgKnockdown = IMAGEMANAGER->findImage("Boy_Knockdown");
	imgTaunt = IMAGEMANAGER->findImage("Boy_Taunt");
	_shadowImg = IMAGEMANAGER->findImage("Boy_Shadow");

	aniRightIdle = new animation;
	aniRightIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniRightIdle->setPlayFrame(0, 7, false, true);
	aniRightIdle->setFPS(10);
	aniLeftIdle = new animation;
	aniLeftIdle->init(imgIdle->getWidth(), imgIdle->getHeight(), imgIdle->getFrameWidth(), imgIdle->getFrameHeight());
	aniLeftIdle->setPlayFrame(15, 8, false, true);
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
	aniRightAttack->setPlayFrame(0, 6, false, false);
	aniRightAttack->setFPS(10);
	aniLeftAttack = new animation;
	aniLeftAttack->init(imgAttack->getWidth(), imgAttack->getHeight(), imgAttack->getFrameWidth(), imgAttack->getFrameHeight());
	aniLeftAttack->setPlayFrame(13, 7, false, false);
	aniLeftAttack->setFPS(10);

	aniRightCombo_attack_1 = new animation;
	aniRightCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniRightCombo_attack_1->setPlayFrame(0, 8, false, false);
	aniRightCombo_attack_1->setFPS(10);
	aniLeftCombo_attack_1 = new animation;
	aniLeftCombo_attack_1->init(imgCombo_attack_1->getWidth(), imgCombo_attack_1->getHeight(), imgCombo_attack_1->getFrameWidth(), imgCombo_attack_1->getFrameHeight());
	aniLeftCombo_attack_1->setPlayFrame(17, 9, false, false);
	aniLeftCombo_attack_1->setFPS(10);

	aniRightCombo_attack_2 = new animation;
	aniRightCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniRightCombo_attack_2->setPlayFrame(0, 3, false, false);
	aniRightCombo_attack_2->setFPS(10);
	aniLeftCombo_attack_2 = new animation;
	aniLeftCombo_attack_2->init(imgCombo_attack_2->getWidth(), imgCombo_attack_2->getHeight(), imgCombo_attack_2->getFrameWidth(), imgCombo_attack_2->getFrameHeight());
	aniLeftCombo_attack_2->setPlayFrame(7, 4, false, false);
	aniLeftCombo_attack_2->setFPS(10);

	aniRightCombo_attack_3 = new animation;
	aniRightCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniRightCombo_attack_3->setPlayFrame(0, 6, false, false);
	aniRightCombo_attack_3->setFPS(10);
	aniLeftCombo_attack_3 = new animation;
	aniLeftCombo_attack_3->init(imgCombo_attack_3->getWidth(), imgCombo_attack_3->getHeight(), imgCombo_attack_3->getFrameWidth(), imgCombo_attack_3->getFrameHeight());
	aniLeftCombo_attack_3->setPlayFrame(13, 7, false, false);
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
	aniRightKnockdown->setPlayFrame(0, 18, false, false);
	aniRightKnockdown->setFPS(10);
	aniLeftKnockdown = new animation;
	aniLeftKnockdown->init(imgKnockdown->getWidth(), imgKnockdown->getHeight(), imgKnockdown->getFrameWidth(), imgKnockdown->getFrameHeight());
	aniLeftKnockdown->setPlayFrame(37, 19, false, false);
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
	aniRightTaunt->setPlayFrame(0, 10, false, false, ActionCheck, this);
	aniRightTaunt->setFPS(7);
	aniLeftTaunt = new animation;
	aniLeftTaunt->init(imgTaunt->getWidth(), imgTaunt->getHeight(), imgTaunt->getFrameWidth(), imgTaunt->getFrameHeight());
	aniLeftTaunt->setPlayFrame(21, 11, false, false, ActionCheck, this);
	aniLeftTaunt->setFPS(7);
}

void schoolBoy::render(POINT camera)
{
	enemy::render(camera);
	switch (_state)
	{
	case schoolBoy::COMBO_ATTACK_1:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 32, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 32, _motion, camera);
		break;
	case schoolBoy::COMBO_ATTACK_2:
		switch (_direction)
		{
		case schoolBoy::LEFT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left + 2, _shadowRc.top - 17, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left + 2, _enemyRc.top - 17, _motion, camera);
			break;
		case schoolBoy::RIGHT:
			_shadowImg->alphaRender(getMemDC(), _shadowRc.left - 2, _shadowRc.top - 17, 150, camera);
			_enemyImg->aniRender(getMemDC(), _enemyRc.left - 2, _enemyRc.top - 17, _motion, camera);
			break;
		}
		break;
	case schoolBoy::JUMP:
		_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top - 40, 150, camera);
		_enemyImg->aniRender(getMemDC(), _enemyRc.left, _enemyRc.top - 40, _motion, camera);
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
		Rectangle(getMemDC(), _enemyRc, camera);
	}
}

void schoolBoy::setAttackRect(STATE state, DIRECTION direction)
{
	int index;
	switch (state)
	{
	case enemy::ATTACK:
	case enemy::COMBO_ATTACK_1:
	case enemy::COMBO_ATTACK_2:
	case enemy::COMBO_ATTACK_3:
		attackInfo attackinfo = _mAttackInfo.find(state)->second;
		index = (int)_motion->getIndex();
		if (attackinfo.startIndex <= index && attackinfo.endIndex >= index)
		{
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
		break;
	default:
		_attackRc = RectMake(_x, _y, 0, 0);
		break;
	}
}

void schoolBoy::state()
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
		if (IntersectRect(&temp, &RectMakeCenter((_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2, _kyoko->getRect().right - _kyoko->getRect().left, _kyoko->getRect().bottom - _kyoko->getRect().top - 40), &_enemyRc))
		{
			switch (_state)
			{
				//IDLE ���¶�� ����, ��� ���~
			case schoolBoy::IDLE:
				//���� ���� ��������
				_state = (STATE)_enemyAttack->selectedAttack(_state);
				if (_state != IDLE)
					_isAttack = true;
				break;

				//�̵� ���¶�� �ִϸ��̼� ����(�Ŀ� IDLE���·� ���� ��)
			case schoolBoy::WALK: case schoolBoy::RUN:
				_motion->stop();
				break;

				//�⺻����
			case schoolBoy::ATTACK:
				if (_isAttack)
				{
					_isAttack = false;

					switch (_direction)
					{
					case schoolBoy::LEFT:
						_enemyImg = imgAttack;
						_motion = aniLeftAttack;
						_motion->start();
						break;
					case schoolBoy::RIGHT:
						_enemyImg = imgAttack;
						_motion = aniRightAttack;
						_motion->start();
						break;
					}
				}
				break;
				//�޺����� 1
			case schoolBoy::COMBO_ATTACK_1:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_1;
					switch (_direction)
					{
					case schoolBoy::LEFT:
						_motion = aniLeftCombo_attack_1;
						_motion->start();
						break;
					case schoolBoy::RIGHT:
						_motion = aniRightCombo_attack_1;
						_motion->start();
						break;
					}
				}
				break;
				//�޺����� 2
			case schoolBoy::COMBO_ATTACK_2:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_2;
					switch (_direction)
					{
					case schoolBoy::LEFT:
						_motion = aniLeftCombo_attack_2;
						_motion->start();
						break;
					case schoolBoy::RIGHT:
						_motion = aniRightCombo_attack_2;
						_motion->start();
						break;
					}
				}
				break;
				//�޺����� 3
			case schoolBoy::COMBO_ATTACK_3:
				if (_isAttack)
				{
					_isAttack = false;
					_enemyImg = imgCombo_attack_3;
					switch (_direction)
					{
					case schoolBoy::LEFT:
						_motion = aniLeftCombo_attack_3;
						_motion->start();
						break;
					case schoolBoy::RIGHT:
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
		case schoolBoy::IDLE:
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
				case schoolBoy::LEFT:
					_motion = aniLeftWalk;
					break;
				case schoolBoy::RIGHT:
					_motion = aniRightWalk;
					break;
				}
				_motion->start();
			}
			break;
		case schoolBoy::WALK: case schoolBoy::RUN:
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

void schoolBoy::move()
{
	//�浿�ߴٸ� �̵��� �����Ѵ�.
	if (_isCollision)
		return;
	//�÷��̾�� ���ʹ��� ���� ���
	_angle = getAngle(_x, _y, (_kyoko->getRect().left + _kyoko->getRect().right) / 2, (_kyoko->getRect().top + _kyoko->getRect().bottom) / 2);

	switch (_state)
	{
	case schoolBoy::WALK:
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
			case schoolBoy::LEFT:
				_x -= _speed;
				break;
			case schoolBoy::RIGHT:
				_x += _speed;

				break;
			}

		}
		break;
	case schoolBoy::RUN:
		if (_isFollow)
		{
			//���ʹ̰� �����ϰ� �ִٸ� �ش� ������ �̵�
			_x += cos(_angle) * 2.2 * _speed;
			_y += -sin(_angle) * 2.2 * _speed;
		}
		else
		{
			//Ž�� �� �̶�� X�����θ� �̵�
			switch (_direction)
			{
			case schoolBoy::LEFT:
				_x -= 2.2 * _speed;
				break;
			case schoolBoy::RIGHT:
				_x += 2.2 * _speed;

				break;
			}
		}
		break;
	}
}

void schoolBoy::ActionCheck(void* obj)
{
	schoolBoy* k = (schoolBoy*)obj;
	k->_isAction = true;
}
