#include "stdafx.h"
#include "opTion.h"

opTion::opTion()
{
}

opTion::~opTion()
{
}

HRESULT opTion::init()
{
	IMAGEMANAGER->addImage("메뉴", "image/menu/phone.bmp", 287, 500, true, RGB(255, 0, 255));
	menu.img = IMAGEMANAGER->findImage("메뉴");
	menu.x = WINSIZEX / 5;
	menu.y = WINSIZEY + 100;
	movepower = 50;
	return S_OK;
}

void opTion::release()
{
}

void opTion::update()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (menu.y >= WINSIZEY)
		{
			up = true;
			down = false;
		}
		if (menu.y < WINSIZEY)
		{
			up = false;
			down = true;
		}
	}
	if (up) menu.y -= movepower;
	if (down) menu.y += movepower;
	if (menu.y <= WINSIZEY / 8)
	{
		menu.y = WINSIZEY / 8;
	}
	if (menu.y >= WINSIZEY + 100)
	{
		menu.y = WINSIZEY + 100;
	}
	menu.rc = RectMake(menu.x, menu.y, 100, 100);
	if (up && menu.y <= WINSIZEY / 8)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{

		}
	}
}

void opTion::render()
{
	menu.img->render(getMemDC(), menu.x, menu.y);
}
