#include "stdafx.h"
#include "ghostScene.h"

HRESULT ghostScene::init()
{
	_background = IMAGEMANAGER->addImage("¹è°æ", "0.bmp", 2991, 1000, true, RGB(255, 0, 255));

	_kyoko = new kyoko;
	_kyoko->init();

	return S_OK;
}

void ghostScene::release()
{

}

void ghostScene::update()
{
	_camera = CAMERAMANAGER->CameraMake(_kyoko->getRect().left, _kyoko->getRect().top, BOTH, _background);
	_kyoko->update();

}

void ghostScene::render()
{
	_background->render(getMemDC(), 0, 0, _camera);
	_kyoko->render(_camera);
}
