#include "stdafx.h"
#include "tempStage.h"

HRESULT tempStage::init()
{
	SOUNDMANAGER->play("MainStage",0.8);
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->init();
	_em->setKyokoMemory(_player);
	return S_OK;
}

void tempStage::release()
{

}

void tempStage::update()
{
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH,stage1);
	_em->update();
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);
	


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
	}
	_player->render(camera);
	_em->render(camera);
}
