#include "stdafx.h"
#include "ghostScene.h"

HRESULT ghostScene::init()
{
	_background = IMAGEMANAGER->addImage("¹è°æ", "0.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_kyoko = new kyoko;
	_kyoko->init();

	return S_OK;
}

void ghostScene::release()
{

}

void ghostScene::update()
{
	_kyoko->update();

}

void ghostScene::render()
{
	_background->render(getMemDC());
	_kyoko->render();
}
