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
	_kyoko = new kyoko;
	_kyoko->init();
	setEnemy();
	return S_OK;
}

void enemyManager::release()
{
	_kyoko->release();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();
	}
}

void enemyManager::update()
{
	_kyoko->update();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->setKyokoAddressLink(_kyoko);
		(*_viEnemy)->update();
	}
}

void enemyManager::setEnemy()
{
	enemy* _en;
	_en = new schoolGirl;
	_en->init(1200, 600);
	_vEnemy.push_back(_en);
	/*for (int i = 1; i < 2; i++)
	{
		enemy* _en;
		_en = new schoolGirl;
		_en->init(i * 600, i * 600);
		_vEnemy.push_back(_en);
	}*/
}

void enemyManager::render()
{
	_kyoko->render();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}
