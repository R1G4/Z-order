#include "stdafx.h"
#include "enemyManager.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	setEnemy();
	return S_OK;
}

void enemyManager::release()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();
	}
}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->setKyokoAddressLink(_kyoko);
		(*_viEnemy)->update();
	}
}

void enemyManager::setEnemy()
{
	//테스트, x,y지정하여 막 뿌려도 됨

	/*for (int i = 1; i < 3; i++)
	{
		enemy* _en;
		_en = new schoolGirl;
		_en->init(i * 200, i * 200);
		_vEnemy.push_back(_en);
	}
	for (int i = 1; i < 3; i++)
	{
		enemy* _en;
		_en = new schoolBoy;
		_en->init(i * 300, 500);
		_vEnemy.push_back(_en);
	}*/

	//임시로 생성중
	enemy* _en1;
	_en1 = new schoolGirl;
	//좌표x, 좌표y, 초기 상태 (Idle or Taunt), 방향( 0 == Left, 1= Right)
	//init(float x, float y, bool isTaunt = false, int direction = RND->getFromIntTo(0, 2));
	_en1->init(1000, 200, true, 0);
	_vEnemy.push_back(_en1);

	enemy* _en2;
	_en2 = new schoolBoy;
	_en2->init(200, 500, true, 1);
	_vEnemy.push_back(_en2);

	enemy* _en3;
	_en3 = new schoolBoy;
	_en3->init(1000, 600, true, 1);
	_vEnemy.push_back(_en3);

	enemy* _en4;
	_en4 = new MT;
	_en4->init(400, 400, true, 1);
	_vEnemy.push_back(_en4);

	enemy* _en5;
	_en5 = new cheerLeader;
	_en5->init(1000, 400, true, 0);
	_vEnemy.push_back(_en5);
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

void enemyManager::render(POINT camera)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render(camera);
	}
}
