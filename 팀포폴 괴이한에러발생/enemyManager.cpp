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
	//에너미 생성 간격
	spawnInterval = 0;

	//해당 스테이지
	_nowStage = (STAGE_ENEMY)stageNum;

	//스테이지에 따른 에너미 생성
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

//해당 enemy 객체 제거
void enemyManager::removeEnemy(int i)
{
	SAFE_DELETE(_vEnemy[i]);
	_vEnemy.erase(_vEnemy.begin() + i);
}

//해당 Item 객체 제거
void enemyManager::removeItem(int i)
{
	SAFE_DELETE(_vItem[i]);
	_vItem.erase(_vItem.begin() + i);
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		//객체가 존재하지 않을 경우 예외
		if (!_vEnemy[i]) continue;

		//객체의 상태가 REMOVE라면 제거
		if (_vEnemy[i]->getState() == enemy::REMOVE)
		{
			//유닛 제거되기 직전에 좌표 얻어서 아이템 생성
			item* _item;
			_item = new item;
			_item->init(_vEnemy[i]->getEnemyPoint().x, (_vEnemy[i]->getShadowRc().top + _vEnemy[i]->getShadowRc().bottom) / 2);
			_vItem.push_back(_item);
			removeEnemy(i);
			break;
		}
		else
		{
			_vEnemy[i]->setKyokoAddressLink(_kyoko);
			_vEnemy[i]->update();
		}
	}
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getItemState() == item::REMOVE)
		{
			removeItem(i);
			break;
		}
		else
			_vItem[i]->update();
	}

	//에너미 생성 함수
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
			if (_vEnemy.size() < 6)
			{
				//스폰 간격을 체크해서 하기
				spawnInterval++;
				if (spawnInterval > 800)
				{
					//에너미 추가
					addEnemy();
					spawnInterval = 0;
				}
			}
			break;
		case enemyManager::STAGE_3:
			//현재 존재하는 에너미 갯수가 6개 미만 일경우
			if (_vEnemy.size() < 7)
			{
				//스폰 간격을 체크해서 하기
				spawnInterval++;
				if (spawnInterval > 650)
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
	cout << _nowStage;
	switch (_nowStage)
	{
		
		//(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));
		case enemyManager::STAGE_1:
			_vEnemy.push_back(setSchoolGirl(1700, 550, enemy::TAUNT, enemy::LEFT));
			_vEnemy.push_back(setSchoolGirl(1650, 525, enemy::IDLE));
			_vEnemy.push_back(setSchoolBoy(1600, 600, enemy::TAUNT, enemy::LEFT));
			_vEnemy.push_back(setSchoolBoy(1800, 600, enemy::IDLE));
			break;
		case enemyManager::STAGE_2:
			_vEnemy.push_back(setSchoolGirl(1700, 500, enemy::TAUNT, enemy::LEFT));
			_vEnemy.push_back(setSchoolBoy(1300, 500, enemy::TAUNT, enemy::LEFT));
			_vEnemy.push_back(setMT(370, 400, enemy::TAUNT, enemy::RIGHT));
			_vEnemy.push_back(setCheerLeader(2400, 500, enemy::IDLE));
			break;
		case enemyManager::STAGE_3:
			_vEnemy.push_back(setMT(400, 450, enemy::TAUNT, enemy::RIGHT));
			_vEnemy.push_back(setSchoolGirl(1000, 500, enemy::TAUNT, enemy::LEFT));
			_vEnemy.push_back(setCheerLeader(800, 550, enemy::IDLE));
			_vEnemy.push_back(setSchoolBoy(1300, 500, enemy::IDLE));
			_vEnemy.push_back(setCheerLeader(1700, 550, enemy::IDLE));
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
		case enemyManager::STAGE_2: case enemyManager::STAGE_3 :
			switch ((ENEMY_KINDS)RND->getFromIntTo(ENEMY_GIRL, ENEMY_CHEERLEADER + 1))
			{
				case enemyManager::ENEMY_GIRL:
					_vEnemy.push_back(setSchoolGirl(1080, 450, enemy::IDLE));
					break;
				case enemyManager::ENEMY_BOY:
					_vEnemy.push_back(setSchoolBoy(1080, 450, enemy::IDLE));
					break;
				case enemyManager::ENEMY_MT:
					_vEnemy.push_back(setMT(1080, 450, enemy::IDLE));
					break;
				case enemyManager::ENEMY_CHEERLEADER:
					_vEnemy.push_back(setCheerLeader(1080, 450, enemy::IDLE));
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
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render(camera);
	}
}