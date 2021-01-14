#include "stdafx.h"
#include "EndScene.h"

HRESULT EndScene::init()
{
	TheEnd = "video/ending_scene.wmv";
	VIDEOMANAGER->startVideo(TheEnd);
	return S_OK;
}

void EndScene::release()
{
}

void EndScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		VIDEOMANAGER->endVideo(true);
		SOUNDMANAGER->stop("introToStart");
		SCENEMANAGER->changeScene("시작화면");
	}
}

void EndScene::render()
{
}
