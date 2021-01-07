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

	_door_rc = RectMake(1380, 400, 300, 130);

	return S_OK;
}

void tempStage::release()
{
}

void tempStage::update()
{
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	_em->update();

	changeMap();
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);
	


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
	}
	_player->render(camera);
	_em->render(camera);


}

void tempStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow()) && KEYMANAGER->isStayKeyDown('Z'))
	{
		delete(_player);
		SCENEMANAGER->changeScene("보스스테이지");
		SOUNDMANAGER->stop("MainStage");
	}
}
