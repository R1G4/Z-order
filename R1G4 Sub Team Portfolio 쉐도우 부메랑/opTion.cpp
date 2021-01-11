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


	volume = 0.5f;
	
	
	return S_OK;
}

void opTion::release()
{
}

void opTion::update()
{
	volumeCon();
	volumebar.x = WINSIZEX / 5 + 143.5f;
	volumebar.y = menu.y + 140;
	volumebar.rc = RectMakeCenter(volumebar.x, volumebar.y, 200, 10);

	conball.x = volumebar.rc.left + 200 * volume;
	conball.y = menu.y + 140;
	conball.rc = RectMakeCenter(conball.x, conball.y, 20, 20);


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
	Rectangle(getMemDC(), volumebar.rc);
	Ellipse(getMemDC(), conball.rc);
}

void opTion::volumeCon()
{
	RECT temp;


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&volumebar.rc, _ptMouse))
		{
			volume = ((float)_ptMouse.x - 299.5f) / 200.f;
			SOUNDMANAGER->setVolume(volume);
		}
	}
}
