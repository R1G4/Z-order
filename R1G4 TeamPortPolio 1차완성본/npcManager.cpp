#include "stdafx.h"
#include "npcManager.h"


npcManager::npcManager()
{
}

npcManager::~npcManager()
{
}

HRESULT npcManager::init()
{
	return S_OK;
}

void npcManager::setNpc(int stageNum)
{
	//�ش� ��������
	_nowStage = (STAGE_NPC)stageNum;

	//���������� ����Ǹ� ������ NPC�� �����Ѵ�.
	_vNpc.clear();

	//�� ���������� ���� NPC ����
	switch (_nowStage)
	{
	case npcManager::STAGE_1:
		_vNpc.push_back(setNpcBoy(1360, 392, npc::IDLE, npc::LEFT));
		_vNpc.push_back(setNpcTeacher(1800, 500, npc::IDLE, npc::LEFT));
		break;
	case npcManager::STAGE_2:
		_vNpc.push_back(setNpcGirl(600, 400, npc::IDLE, npc::LEFT));
		_vNpc.push_back(setNpcGirl(3120, 400, npc::IDLE, npc::LEFT));
		_vNpc.push_back(setNpcBoy(2500, 380, npc::IDLE, npc::LEFT));
		_vNpc.push_back(setNpcBoy(3000, 380, npc::IDLE, npc::RIGHT));
		break;
	case npcManager::STAGE_3:
		_vNpc.push_back(setNpcGirl(600, 400, npc::IDLE, npc::RIGHT));
		break;
	}
}

//�ش� NPC ��ü ����
void npcManager::removeNpc(int i)
{
	SAFE_RELEASE(_vNpc[i]);
	SAFE_DELETE(_vNpc[i]);
	_vNpc.erase(_vNpc.begin() + i);
}

npc* npcManager::setNpcBoy(float x, float y, npc::STATE state, npc::DIRECTION direction)
{
	npc* _npc;
	_npc = new npcBoy;
	_npc->init(x, y, state, direction);
	return _npc;
}

npc* npcManager::setNpcGirl(float x, float y, npc::STATE state, npc::DIRECTION direction)
{
	npc* _npc;
	_npc = new npcGirl;
	_npc->init(x, y, state, direction);
	return _npc;
}

npc* npcManager::setNpcTeacher(float x, float y, npc::STATE state, npc::DIRECTION direction)
{
	npc* _npc;
	_npc = new npcTeacher;
	_npc->init(x, y, state, direction);
	return _npc;
}

void npcManager::release()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->release();
	}
}

void npcManager::update()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->update();
	}
}

void npcManager::render(POINT camera)
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->render(camera);
	}
}
