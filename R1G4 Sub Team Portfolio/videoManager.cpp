#include "videoManager.h"
#include "stdafx.h"

void videoManager::startVideo(LPCSTR videoName)
{
	timeCount = 0;
	_video = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, videoName);
	MoveWindow(_video, 0, 0, WINSIZEX, WINSIZEY, FALSE);
	MCIWndPlay(_video);
	isPlay = true;
}

void videoManager::endVideo()
{
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{
		timeCount++;
		if (timeCount > 100)
		{
			MCIWndClose(_video);
			MCIWndDestroy(_video);
			_video = 0;
			isPlay = false;
			return;
		}
	}
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video))
	{
		MCIWndClose(_video);
		MCIWndDestroy(_video);
		_video = 0;
		isPlay = false;
		return;
	}
}

void videoManager::endVideo(string sceneName)
{
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{
		timeCount++;
		if (timeCount > 100)
		{
			MCIWndClose(_video);
			MCIWndDestroy(_video);
			_video = 0;
			isPlay = false;
			return;
		}
	}
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video))
	{
		MCIWndClose(_video);
		MCIWndDestroy(_video);
		_video = 0;
		isPlay = false;
		SCENEMANAGER->changeScene(sceneName);
	}
}

bool videoManager::checkPlay()
{
	return isPlay;
}
