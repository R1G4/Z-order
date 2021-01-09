#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{
	/*if (enemyNum == 0)
	{
		_schoolGirl = new schoolGirl;
		_schoolGirl->init(x, y);
	}*/
	return S_OK;
}

void enemy::release()
{
	/*if(_schoolGirl)
		_schoolGirl->release();*/
}

void enemy::update()
{
	/*if(_schoolGirl)
		_schoolGirl->update();*/
}

void enemy::render()
{
	/*if(_schoolGirl)
		_schoolGirl->render();*/
}

void enemy::render(POINT camera)
{
}
