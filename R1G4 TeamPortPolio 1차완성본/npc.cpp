#include "stdafx.h"
#include "npc.h"


npc::npc()
{
}


npc::~npc()
{
}

HRESULT npc::init(float x, float y, STATE state, DIRECTION direction)
{
	//��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	//���� �ʱ�ȭ
	_state = state;

	//�ִϸ��̼� ����
	switch (state)
	{
	case npc::IDLE:
		_img = _Idle;
		switch (direction)
		{
		case npc::LEFT:
			_npcMotion = _leftIdle;
			break;
		case npc::RIGHT:
			_npcMotion = _rightIdle;
			break;
		}
		break;
	case npc::REACT:
		_img = _React;
		switch (direction)
		{
		case npc::LEFT:
			_npcMotion = _leftReact;
			break;
		case npc::RIGHT:
			_npcMotion = _rightReact;
			break;
		}
		break;
	}
	_npcMotion->start();
	
	//�׸��� �̹��� �ʱ�ȭ
	_shadowImg = IMAGEMANAGER->findImage("Boy_Shadow");

	//��Ʈ ����
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_shadowRc = RectMakeCenter((_rc.left + _rc.right) / 2, _rc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
	
	return S_OK;
}

void npc::release()
{
}

void npc::update()
{
	_npcMotion->frameUpdate(TIMEMANAGER->getElapsedTime());
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_shadowRc = RectMakeCenter((_rc.left + _rc.right) / 2, _rc.bottom, _shadowImg->getWidth(), _shadowImg->getHeight());
}

void npc::render(POINT camera)
{
	//�̹��� ũ�Ⱑ ���ϴ� ����� �������� ���ϰų� ���־� �����Ѵ�.
	_shadowImg->alphaRender(getMemDC(), _shadowRc.left, _shadowRc.top,150, camera);

	_img->aniRender(getMemDC(), _rc.left, _rc.top, _npcMotion, camera);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _shadowRc, camera);
		Rectangle(getMemDC(), _rc, camera);
	}
}

void npc::setIdle(void * obj)
{
	npc* k = (npc*)obj;
	k->_img = k->_Idle;
	k->_state = IDLE;
	switch (k->_direction)
	{
	case LEFT:
		k->_npcMotion = k->_leftIdle;
		break;
	case RIGHT:
		k->_npcMotion = k->_rightIdle;
		break;
	}
	k->_npcMotion->start();
}

void npc::setReact(DIRECTION direction)
{
	_img = _React;
	_state = REACT;
	//_direction = direction;
	switch (direction)
	{
	case npc::LEFT:
		_npcMotion = _leftReact;
		break;
	case npc::RIGHT:
		_npcMotion = _rightReact;
		break;
	}
	_npcMotion->start();
}