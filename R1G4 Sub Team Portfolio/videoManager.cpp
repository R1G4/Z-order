#include "videoManager.h"
#include "stdafx.h"

void videoManager::startVideo(LPCSTR videoName)
{
	cout << timeCount<<endl;
	currentVideo = videoName;
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
		subtimeCount++;
		if(subtimeCount%30==0)timeCount++;
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

void videoManager::endVideo(bool change)
{
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video))
	{
		MCIWndPlayFrom(_video, 3000);
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		MCIWndClose(_video);
		MCIWndDestroy(_video);
		_video = 0;
		isPlay = false;
	}
}

void videoManager::endVideo(LPCSTR videoName)
{
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{
		subtimeCount++;
		if(subtimeCount%30==0)timeCount++;
		if (timeCount > 100)
		{
			MCIWndClose(_video);
			MCIWndDestroy(_video);
			_video = 0;
			isPlay = false;
			startVideo(videoName);
			return;
		}
	}
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video))
	{
		MCIWndClose(_video);
		MCIWndDestroy(_video);
		_video = 0;
		isPlay = false;
		startVideo(videoName);
		return;
	}
}

bool videoManager::checkPlay()
{
	return isPlay;
}
