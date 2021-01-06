#pragma once
#include "singletonBase.h"
#include<Vfw.h>
#pragma comment(lib,"vfw32.lib")


class videoManager :
	public singletonBase<videoManager>
{
private:
	HWND _video;
	bool isPlay;
	int timeCount;
	int subtimeCount;
	LPCSTR currentVideo;
public:
	void startVideo(LPCSTR videoName);
	void endVideo();
	void endVideo(bool change);
	void endVideo(LPCSTR videoName);
	bool checkPlay();
	LPCSTR getCurrenVideo() { return currentVideo; }
};

