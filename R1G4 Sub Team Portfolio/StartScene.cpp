#include "stdafx.h"
#include "StartScene.h"
StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	openingVideo = "video/intro wmv.wmv";
	startVideo = "video/start wmv.wmv";
	VIDEOMANAGER->startVideo(openingVideo);
	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (VIDEOMANAGER->getCurrenVideo() != startVideo)
	{
		VIDEOMANAGER->endVideo(startVideo);
	}
	else
	{
			VIDEOMANAGER->endVideo(true);
		if(!VIDEOMANAGER->checkPlay())SCENEMANAGER->changeScene("세이브로드");
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			PostQuitMessage(0);
		}
	}
}

void StartScene::render()
{

}
