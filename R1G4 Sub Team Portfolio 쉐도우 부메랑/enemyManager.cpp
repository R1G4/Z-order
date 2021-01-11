#include "stdafx.h"
#include "enemyManager.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init(int stageNum)
{
	spawnInterval = 0;
	_nowStage = (STAGE_ENEMY)stageNum;
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

	spawn();
}

void enemyManager::spawn()
{
	//에너미 스폰
	switch (_nowStage)
	{
	case enemyManager::STAGE_1:
		//현재 존재하는 에너미 갯수가 6개 미만 일경우
		if (_vEnemy.size() < 6)
		{
			//스폰 간격을 체크해서 하기
			spawnInterval++;
			if (spawnInterval > 750)
			{
				//에너미 추가
				addEnemy();
				spawnInterval = 0;
			}
		}
		break;
	case enemyManager::STAGE_2:
		//현재 존재하는 에너미 갯수가 6개 미만 일경우
		if (_vEnemy.size() < 7)
		{
			//스폰 간격을 체크해서 하기
			spawnInterval++;
			if (spawnInterval > 750)
			{
				//에너미 추가
				addEnemy();
				spawnInterval = 0;
			}
		}
		break;
	}
}

void enemyManager::setEnemy()
{
	switch (_nowStage)
	{
		//(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));
	case enemyManager::STAGE_1:
		_vEnemy.push_back(setSchoolGirl(1700, 550, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setSchoolGirl(1700, 700, enemy::IDLE));
		_vEnemy.push_back(setSchoolBoy(1600, 600, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setSchoolBoy(1750, 750, enemy::IDLE));
		break;
	case enemyManager::STAGE_2:
		_vEnemy.push_back(setSchoolGirl(1200, 800, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setSchoolBoy(1300, 500, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setMT(340, 400, enemy::TAUNT, enemy::RIGHT));
		_vEnemy.push_back(setCheerLeader(2200, 600, enemy::IDLE));
		_vEnemy.push_back(setCheerLeader(2500, 800, enemy::IDLE));
		break;
	}
}

void enemyManager::addEnemy()
{
	switch (_nowStage)
	{
	case enemyManager::STAGE_1:
		switch ((ENEMY_KINDS)RND->getFromIntTo(ENEMY_GIRL, ENEMY_BOY + 1))
		{
		case enemyManager::ENEMY_GIRL:
			_vEnemy.push_back(setSchoolGirl(1550, 450, enemy::IDLE));
			break;
		case enemyManager::ENEMY_BOY:
			_vEnemy.push_back(setSchoolBoy(1550, 450, enemy::IDLE));
			break;
		}
		break;
	case enemyManager::STAGE_2:
		switch ((ENEMY_KINDS)RND->getFromIntTo(ENEMY_GIRL, ENEMY_CHEERLEADER + 1))
		{
		case enemyManager::ENEMY_GIRL:
			_vEnemy.push_back(setSchoolGirl(1080, 390, enemy::IDLE));
			break;
		case enemyManager::ENEMY_BOY:
			_vEnemy.push_back(setSchoolBoy(1080, 390, enemy::IDLE));
			break;
		case enemyManager::ENEMY_MT:
			_vEnemy.push_back(setMT(1080, 390, enemy::IDLE));
			break;
		case enemyManager::ENEMY_CHEERLEADER:
			_vEnemy.push_back(setCheerLeader(1080, 390, enemy::IDLE));
			break;
		}
		break;
	}
}

enemy* enemyManager::setSchoolGirl(float x, float y, enemy::STATE state, enemy::DIRECTION direction)
{
	enemy* _en;
	_en = new schoolGirl;
	_en->init(x, y, state, direction);
	return _en;
}

enemy* enemyManager::setSchoolBoy(float x, float y, enemy::STATE state, enemy::DIRECTION direction)
{
	enemy* _en;
	_en = new schoolBoy;
	_en->init(x, y, state, direction);
	return _en;
}

enemy* enemyManager::setMT(float x, float y, enemy::STATE state, enemy::DIRECTION direction)
{
	enemy* _en;
	_en = new MT;
	_en->init(x, y, state, direction);
	return _en;
}

enemy* enemyManager::setCheerLeader(float x, float y, enemy::STATE state, enemy::DIRECTION direction)
{
	enemy* _en;
	_en = new cheerLeader;
	_en->init(x, y, state, direction);
	return _en;
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