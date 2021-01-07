#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init()
{
	SOUNDMANAGER->play("BossSound", 0.8);
	stage1 = IMAGEMANAGER->findImage("StageBoss");
	stage1Pic = IMAGEMANAGER->findImage("StageBossPic");
	_player = new kyoko;
	_player->init();


	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
}

void BossStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
	}
	_player->render(camera);
}
