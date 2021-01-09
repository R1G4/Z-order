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
	//이미지 초기화
	_enemyImg = imgTaunt;

	//에너미 상태 초기화
	_direction = direction;
	_state = state;

	//좌표 초기화
	_x = x;
	_y = y;
	_angle = 0;

	_rc = RectMakeCenter(_x, _y, 40, 200);
	//에너미 렉트 초기화
	_enemyRc = RectMakeCenter(_x, _y, _enemyImg->getFrameWidth(), _enemyImg->getFrameHeight());
	//그림자 렉트 초기화
	_shadowRc = RectMakeCenter((_enemyRc.left + _enemyRc.right) / 2, _enemyRc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());

	_isAttack = false;
	_isFollow = false;
	_isRunning = true;
	_isCollision = false;

	//추적 관련 초기화
	_questTimer = RND->getFromIntTo(170, 230);
	_questMin = RND->getFromIntTo(50, 150);

	//에너미 공격 생성 및 초기화
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
	//느낌표 추가
}

void enemy::sternAction()
{
	//스턴효과 추가
}

void enemy::render(POINT camera)
{
}
