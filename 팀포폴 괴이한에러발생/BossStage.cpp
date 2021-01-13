#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init()
{

	SOUNDMANAGER->play("BossSound", 0.1f);
	stage1 = IMAGEMANAGER->findImage("StageBoss");
	stage1Pic = IMAGEMANAGER->findImage("StageBossPic");
	_player = new kyoko;
	_player->init();

	_door_rc = RectMake(100, 450, 180, 200);
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	UI->update();

	changeMap();
}

void BossStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
	}
	_player->render(camera);
	UI->render();

}

void BossStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow()) && KEYMANAGER->isStayKeyDown('Z'))
	{
		delete(_player);
		SCENEMANAGER->changeScene("스테이지1");
		SOUNDMANAGER->stop("BossSound");
	}
}
