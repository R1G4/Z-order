#pragma once
#include "gameNode.h"

class npc :public gameNode
{	
public:
	//NPC 상태
	enum STATE
	{
		IDLE,
		REACT
	};

	//NPC 바라보는 방향
	enum DIRECTION
	{
		LEFT,
		RIGHT
	};

protected:
	image* _img;			//Npc 이미지
	image* _shadowImg;		//그림자 이미지
	animation* _npcMotion;	//Npc 애니메이션
	
	//상태 이미지
	image* _Idle;		
	image* _React;

	//상태 애니메이션
	animation* _leftIdle;
	animation* _rightIdle;
	animation* _leftReact;
	animation* _rightReact;

	STATE _state;				//상태
	DIRECTION _direction;		//방향

	float _x, _y;				// 좌표

	RECT _rc;					// 이미지 렉트
	RECT _shadowRc;				// 그림자용 렉트
public:
	npc();
	~npc();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);


	//Idle 상태로
	static void setIdle(void* obj);
	//React 상태로
	void setReact(DIRECTION direction);

	//겟터 셋터
	RECT getNpcRc() { return _rc; }

	//디버그용 렉트
	RECT& getDebugRect() { return _rc; }
	RECT& getDebugShadowRc() { return _shadowRc; }
};

