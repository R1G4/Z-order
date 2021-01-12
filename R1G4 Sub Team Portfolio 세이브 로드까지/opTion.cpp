#include "stdafx.h"
#include "opTion.h"
#include "tempStage.h"
opTion::opTion()
{
}

opTion::~opTion()
{
}

HRESULT opTion::init()
{
	IMAGEMANAGER->addImage("¸Þ´º", "image/menu/phone.bmp", 287, 500, true, RGB(255, 0, 255));
	menu.img = IMAGEMANAGER->findImage("¸Þ´º");


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
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			
			char temp[128];
			vector<string> vStr;
			switch (saveSlot)
			{
			case 1:
				//EFFECTMANAGER->release();
				//delete(em);
				//delete(_kyoko);
				vStr.push_back(itoa(STATUSMANAGER->getHp(), temp, 10));
				vStr.push_back(itoa(stageNum, temp, 10));
				TXTDATA->txtSave("A.txt", vStr);				
				SCENEMANAGER->changeScene("·Îµù¾À", 0,1);
				break;
			case 2:
				vStr.push_back(itoa(STATUSMANAGER->getHp(), temp, 10));
				vStr.push_back(itoa(stageNum, temp, 10));
				TXTDATA->txtSave("B.txt", vStr);
				SCENEMANAGER->changeScene("·Îµù¾À", 0, 2);
				break;
			case 3:
				vStr.push_back(itoa(STATUSMANAGER->getHp(), temp, 10));
				vStr.push_back(itoa(stageNum, temp, 10));
				TXTDATA->txtSave("C.txt", vStr);
				SCENEMANAGER->changeScene("·Îµù¾À", 0, 3);
				break;
			}
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
