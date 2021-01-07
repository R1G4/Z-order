#include "stdafx.h"
#include "selectScene.h"

HRESULT selectScene::init()
{

	IMAGEMANAGER->addImage("快林", "快林.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("快林")->render(getMemDC());

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	char str[128];
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "咯变促弗纠", strlen("咯变促弗纠"));
}
