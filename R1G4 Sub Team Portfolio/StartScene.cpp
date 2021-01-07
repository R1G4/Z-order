#include "stdafx.h"
#include "StartScene.h"
/////////////////////////////테스트
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
	//SOUNDMANAGER->play("introToStart", 0.8f);
	if(!SOUNDMANAGER->isPlaySound("introToStart"))	SOUNDMANAGER->play("introToStart", 0.8f);
	
	if(VIDEOMANAGER->getCurrenVideo()!=startVideo)VIDEOMANAGER->endVideo(startVideo);
	else
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			VIDEOMANAGER->endVideo(true);
			SOUNDMANAGER->stop("introToStart");
			SCENEMANAGER->changeScene("세이브로드");
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
