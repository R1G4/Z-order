#include "stdafx.h"
#include "tempStage.h"

HRESULT tempStage::init()
{
	SOUNDMANAGER->play("MainStage",0.8);
	stage1 = IMAGEMANAGER->findImage("stage1");
	stage1Pic = IMAGEMANAGER->findImage("stage1Pic");
	_player = new kyoko;
	_player->init();
	return S_OK;
}

void tempStage::release()
{
	_player->release();
}

void tempStage::update()
{
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH,stage1);
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);
	stage1Pic->render(getMemDC(), 0, 0, camera);
	_player->render(camera);
}
