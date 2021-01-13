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
	return S_OK;
}

void enemyManager::setEnemy(int stageNum)
{
	//���ʹ� ���� ����
	spawnInterval = 0;

	//�ش� ��������
	_nowStage = (STAGE_ENEMY)stageNum;

	//���������� ����Ǹ� ������ ���ʹ� �������� �����Ѵ�.
	_vEnemy.clear();
	_vItem.clear();

	//�� ���������� ���� ���ʹ� ����
	switch (_nowStage)
	{
		//�Լ� ����
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
		_vEnemy.push_back(setMT(400, 480, enemy::TAUNT, enemy::RIGHT));
		_vEnemy.push_back(setSchoolGirl(1000, 525, enemy::TAUNT, enemy::LEFT));
		_vEnemy.push_back(setCheerLeader(800, 550, enemy::IDLE));
		_vEnemy.push_back(setSchoolBoy(800, 525, enemy::IDLE));
		_vEnemy.push_back(setCheerLeader(1100, 480, enemy::IDLE));
		break;
	}
}

void enemyManager::release()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();
	}
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->release();
	}
}

//�ش� enemy ��ü ����
void enemyManager::removeEnemy(int i)
{
	SAFE_RELEASE(_vEnemy[i]);
	SAFE_DELETE(_vEnemy[i]);
	_vEnemy.erase(_vEnemy.begin() + i);
}

//�ش� Item ��ü ����
void enemyManager::removeItem(int i)
{
	SAFE_RELEASE(_vItem[i]);
	SAFE_DELETE(_vItem[i]);
	_vItem.erase(_vItem.begin() + i);
}

void enemyManager::update()
{
	//���ʹ�
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		//��ü�� �������� ���� ��� ����
		if (!_vEnemy[i]) continue;

		//��ü�� ���°� REMOVE��� ����
		if (_vEnemy[i]->getState() == enemy::REMOVE)
		{
			//���� ���ŵǱ� ������ ��ǥ �� ������ ����
			item* _item;
			_item = new item;
			_item->init(_vEnemy[i]->getEnemyPoint().x, (_vEnemy[i]->getShadowRc().top + _vEnemy[i]->getShadowRc().bottom) / 2);
			_vItem.push_back(_item);
			removeEnemy(i);
			break;
		}
		else
		{
			//���� �ּ� �޾ƿ���
			_vEnemy[i]->setKyokoAddressLink(_kyoko);
			_vEnemy[i]->update();
		}
	}

	//������
	for (int i = 0; i < _vItem.size(); ++i)
	{
		//��ü�� ���°� REMOVE��������
		if (_vItem[i]->getItemState() == item::REMOVE)
		{
			removeItem(i);
			break;
		}
		else
			_vItem[i]->update();
	}

	//���ʹ� ����
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
		if (_vEnemy.size() < 6)
		{
			//���� ������ üũ�ؼ� �ϱ�
			spawnInterval++;
			if (spawnInterval > 800)
			{
				//���ʹ� �߰�
				addEnemy();
				spawnInterval = 0;
			}
		}
		break;
	case enemyManager::STAGE_3:
		//���� �����ϴ� ���ʹ� ������ 6�� �̸� �ϰ��
		if (_vEnemy.size() < 7&&!CAMERAMANAGER->getIsChainLock())
		{
			//���� ������ üũ�ؼ� �ϱ�
			spawnInterval++;
			if (spawnInterval > 650)
			{
				//���ʹ� �߰�
				addEnemy();
				spawnInterval = 0;
			}
		}
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
	case enemyManager::STAGE_3:
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