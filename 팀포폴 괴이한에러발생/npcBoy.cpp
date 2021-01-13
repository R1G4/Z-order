#include "stdafx.h"
#include "npcBoy.h"


npcBoy::npcBoy()
{
}


npcBoy::~npcBoy()
{
}

HRESULT npcBoy::init(float x, float y, STATE state, DIRECTION direction)
{
	//이미지 및 애니메이션 담기
	_Idle = IMAGEMANAGER->findImage("NpcBoyIdle");
	_React = IMAGEMANAGER->findImage("NpcBoyReact");

	_leftIdle = new animation;
	_leftIdle->init(_Idle->getWidth(), _Idle->getHeight()
		, _Idle->getFrameWidth(), _Idle->getFrameHeight());
	_leftIdle->setPlayFrame(0, _Idle->getMaxFrameX(), false, true);
	_leftIdle->setFPS(8);

	_rightIdle = new animation;
	_rightIdle->init(_Idle->getWidth(), _Idle->getHeight()
		, _Idle->getFrameWidth(), _Idle->getFrameHeight());
	_rightIdle->setPlayFrame(_Idle->getMaxFrameX() * 2 + 1, _Idle->getMaxFrameX() + 1, false, true);
	_rightIdle->setFPS(8);

	_leftReact = new animation;
	_leftReact->init(_React->getWidth(), _React->getHeight()
		, _React->getFrameWidth(), _React->getFrameHeight());
	_leftReact->setPlayFrame(0, _React->getMaxFrameX(), false, false, setIdle, this);
	_leftReact->setFPS(8);

	_rightReact = new animation;
	_rightReact->init(_React->getWidth(), _React->getHeight()
		, _React->getFrameWidth(), _React ->getFrameHeight());
	_rightReact->setPlayFrame(_React->getMaxFrameX() * 2 + 1, _React->getMaxFrameX() + 1, false, false, setIdle, this);
	_rightReact->setFPS(8);

	npc::init(x, y, state, direction);

	return S_OK;
}

void npcBoy::release()
{
	npc::release();
}

void npcBoy::update()
{
	npc::update();
}

void npcBoy::render()
{
}

void npcBoy::render(POINT camera)
{
	npc::render(camera);
}
