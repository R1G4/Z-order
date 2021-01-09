#pragma once
#include "singletonBase.h"
#include <map>
class image;
class animation;

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef vector<animation*> arrAnimationbuffer;
	typedef vector<animation*>::iterator iterArrAnimationbuffer;
	typedef map<string, arrAnimationbuffer>				arrAnimations;
	typedef map<string, arrAnimationbuffer>::iterator	iterAnimations;
	typedef vector<map<string, arrAnimationbuffer>> arrTotalAni;
	typedef vector<map<string, arrAnimationbuffer>>::iterator iterarrTotalAni;
	int count;
private:
	arrTotalAni _vTotalAni;
	int buffer=0;
public:
	keyAniManager() {};
	~keyAniManager() {};

	HRESULT init();
	void release();
	//버퍼 없는 버전
	void update();
	//버퍼 있는 버전으루다가
	void render();

	//버퍼 있는 버전
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop,int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj, int buffer);

	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);
	//버퍼+배열 간단 생성 가능 버전
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool loop, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool loop, void* cbFunction, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool loop, void* cbFunction, void* obj, int buffer);




	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);
	animation* findAnimation(string animationKeyName);

	void deleteAll();
};


