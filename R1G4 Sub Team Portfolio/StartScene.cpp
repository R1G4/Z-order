#include "stdafx.h"
#include "StartScene.h"
/////////////////////////////�׽�Ʈ
#include<iostream>
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
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
	if(VIDEOMANAGER->getCurrenVideo()!=startVideo)VIDEOMANAGER->endVideo(startVideo);
	else
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			VIDEOMANAGER->endVideo(true);
			SCENEMANAGER->changeScene("���̺�ε�");
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			PostQuitMessage(0);
		}
	}
}

void StartScene::render()
{

}