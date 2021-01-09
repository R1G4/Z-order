#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y, STATE state, DIRECTION direction)
{
	//�̹��� �ʱ�ȭ
	_enemyImg = imgTaunt;

	//���ʹ� ���� �ʱ�ȭ
	_direction = direction;
	_state = state;

	//��ǥ �ʱ�ȭ
	_x = x;
	_y = y;
	_angle = 0;

	_rc = RectMakeCenter(_x, _y, 40, 200);
	//���ʹ� ��Ʈ �ʱ�ȭ
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	//�׸��� ��Ʈ �ʱ�ȭ
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());

	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	_isCollision = false;

	//���� ���� �ʱ�ȭ
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//���ʹ� ���� ���� �� �ʱ�ȭ
	_enemyAttack = new enemyAttack;
	_enemyAttack->init();
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::pointAction()
{
	//����ǥ �߰�
}

void enemy::sternAction()
{
	//����ȿ�� �߰�
}

void enemy::render(POINT camera)
{
}
