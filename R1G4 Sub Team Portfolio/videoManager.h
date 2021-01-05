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
public:
	void startVideo(LPCSTR videoName);
	void endVideo();
	void endVideo(string sceneName);
	bool checkPlay();
};

