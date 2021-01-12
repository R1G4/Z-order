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

//�ش� enemy ��ü ����
void enemyManager::removeEnemy(int i)
{
	SAFE_DELETE(_vEnemy[i]);
	_vEnemy.erase(_vEnemy.begin() + i);
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		//��ü�� �������� ���� ��� ����
		if (!_vEnemy[i]) continue;

		//��ü�� ���°� REMOVE��� ����
		if(_vEnemy[i]->getState() == enemy::REMOVE)
			removeEnemy(i);

		_vEnemy[i]->setKyokoAddressLink(_kyoko);
		_vEnemy[i]->update();
	}

	//for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	//{
	//	(*_viEnemy)->setKyokoAddressLink(_kyoko);
	//	(*_viEnemy)->update();
	//}

	spawn();
}

void enemyManager::spawn()
{
	//���ʹ� ����
	switch (_nowStage)
	{
	case enemyManager::STAGE_1:
		//���� �����ϴ� ���ʹ� ������ 6�� �̸� �ϰ��
		if (_vEnemy.size() < 6)
		{
			//���� ������ üũ�ؼ� �ϱ�
			spawnInterval++;
			if (spawnInterval > 750)
			{
				//���ʹ� �߰�
				addEnemy();
				spawnInterval = 0;
			}
		}
		break;
	case enemyManager::STAGE_2:
		//���� �����ϴ� ���ʹ� ������ 6�� �̸� �ϰ��
		if (_vEnemy.size() < 7)
		{
			//���� ������ üũ�ؼ� �ϱ�
			spawnInterval++;
			if (spawnInterval > 750)
			{
				//���ʹ� �߰�
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
		_vEnemy.push_back(setSchoolGirl(1650, 525, enemy::IDLE));
		_vEnemy.push_back(setSchoolBoy(1600, 600, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setSchoolBoy(1800, 600, enemy::IDLE));
		break;
	case enemyManager::STAGE_2:
		_vEnemy.push_back(setSchoolGirl(1700, 500, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setSchoolBoy(1300, 500, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setMT(370, 400, enemy::TAUNT, enemy::RIGHT));
		_vEnemy.push_back(setCheerLeader(2400, 500, enemy::IDLE));
		_vEnemy.push_back(setCheerLeader(2800, 500, enemy::IDLE));
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
}