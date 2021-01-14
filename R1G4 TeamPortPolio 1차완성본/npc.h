#pragma once
#include "gameNode.h"

class npc :public gameNode
{	
public:
	//NPC ����
	enum STATE
	{
		IDLE,
		REACT
	};

	//NPC �ٶ󺸴� ����
	enum DIRECTION
	{
		LEFT,
		RIGHT
	};

protected:
	image* _img;			//Npc �̹���
	image* _shadowImg;		//�׸��� �̹���
	animation* _npcMotion;	//Npc �ִϸ��̼�
	
	//���� �̹���
	image* _Idle;		
	image* _React;

	//���� �ִϸ��̼�
	animation* _leftIdle;
	animation* _rightIdle;
	animation* _leftReact;
	animation* _rightReact;

	STATE _state;				//����
	DIRECTION _direction;		//����

	float _x, _y;				// ��ǥ

	RECT _rc;					// �̹��� ��Ʈ
	RECT _shadowRc;				// �׸��ڿ� ��Ʈ
public:
	npc();
	~npc();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);


	//Idle ���·�
	static void setIdle(void* obj);
	//React ���·�
	void setReact(DIRECTION direction);

	//���� ����
	RECT getNpcRc() { return _rc; }

	//����׿� ��Ʈ
	RECT& getDebugRect() { return _rc; }
	RECT& getDebugShadowRc() { return _shadowRc; }
};

