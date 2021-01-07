#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init()
{
	SOUNDMANAGER->addSound("감비노1", "08_Childish Gambino - Redbone.mp3", true, false);
	SOUNDMANAGER->addSound("감비노2", "08_Childish Gambino - Redbone.mp3", true, false);
	SOUNDMANAGER->addSound("감비노3", "08_Childish Gambino - Redbone.mp3", true, false);


	return S_OK;
}

void soundTestScene::release()
{

}

void soundTestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SOUNDMANAGER->play("감비노1", 1.0f);
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->play("감비노2", 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->play("감비노3", 0.3f);
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop("감비노1");
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->stop("감비노2");
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SOUNDMANAGER->stop("감비노3");
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SOUNDMANAGER->pause("감비노1");
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		SOUNDMANAGER->pause("감비노2");
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		SOUNDMANAGER->pause("감비노3");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SOUNDMANAGER->resume("감비노1");
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		SOUNDMANAGER->resume("감비노2");
	}
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		SOUNDMANAGER->resume("감비노3");
	}
}

void soundTestScene::render()
{
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 100, "사운드씬", strlen("사운드씬"));
}
