#pragma once
#include "gameNode.h"
#include "npcBoy.h"
#include "npcGirl.h"
#include "npcTeacher.h"

class npcManager : public gameNode
{
	//�ش� ��������
	enum STAGE_NPC
	{
		STAGE_1 = 1,
		STAGE_2 = 2,
		STAGE_3
	};

	//NPC ����
	enum NPC_KINDS
	{
		NPC_GIRL = 0,
		NPC_BOY
	};

	//NPC�� ��Ƶδ� ����
	typedef vector<npc*> vNpc;
	typedef vector<npc*>::iterator viNpc;

	vNpc _vNpc;
	viNpc _viNpc;
	STAGE_NPC _nowStage;
public:
	npcManager();
	~npcManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);

	void setNpc(int stageNum);	//Npc �߰�
	void removeNpc(int i);		//Npc ����

	npc * setNpcBoy(float x, float y, npc::STATE state = npc::IDLE, npc::DIRECTION direction = (npc::DIRECTION)RND->getFromIntTo(0, 2)); //Npc Boy �߰�
	npc * setNpcGirl(float x, float y, npc::STATE state, npc::DIRECTION direction); //Npc Girl �߰�
	npc * setNpcTeacher(float x, float y, npc::STATE state, npc::DIRECTION direction); //Npc Teacher �߰�

	//����
	vector<npc*> getVNpc() { return _vNpc; }
};

