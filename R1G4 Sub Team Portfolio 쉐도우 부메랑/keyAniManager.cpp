#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	deleteAll();
}

void keyAniManager::update()
{
	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay())break;
				(*vArrIter)->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
			}
			
		}
	}
}

void keyAniManager::render()
{
}


void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setDefPlayFrame(reverse, loop);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_(cbFunction));
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_(cbFunction));
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop,int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//	for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(arr,arrLen, loop);
	//	vAniBuffer[i]->setFPS(fps);
	//}
		animation* ani = new animation;
		ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		ani->setPlayFrame(arr, arrLen, loop);
		ani->setFPS(fps);
		vAniBuffer.push_back(ani);
	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);
	
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_(cbFunction));
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop,CALLBACK_FUNCTION_(cbFunction));
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(start, end, reverse, loop);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_(cbFunction));
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_(cbFunction));
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);
	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end,reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);
	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);

}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;

	int temp[40];
	ZeroMemory(temp, sizeof(temp));
	int cnt = 0;

	if (start < end)
	{
		for (int i = start; i < end; i++)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	else
	{
		for (int i = start - 1; i >= end; i--)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(temp, cnt, loop);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(temp, cnt, loop);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool loop, void * cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;

	int temp[40];
	ZeroMemory(temp, sizeof(temp));
	int cnt = 0;

	if (start < end)
	{
		for (int i = start; i < end; i++)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	else
	{
		for (int i = start - 1; i >= end; i--)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(temp, cnt, loop, CALLBACK_FUNCTION_(cbFunction));
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(temp, cnt, loop, CALLBACK_FUNCTION_(cbFunction));
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool loop, void * cbFunction, void * obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	arrAnimationbuffer vAniBuffer;
	arrAnimations mAni;

	int temp[40];
	ZeroMemory(temp, sizeof(temp));
	int cnt = 0;

	if (start < end)
	{
		for (int i = start; i < end; i++)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	else
	{
		for (int i = start - 1; i >= end; i--)
		{
			temp[cnt] = i;
			cnt++;
		}
	}
	//for (int i = 0; i < buffer; i++)
	//{
	//	vAniBuffer.push_back(new animation);
	//	vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	//	vAniBuffer[i]->setPlayFrame(temp, cnt, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
	//	vAniBuffer[i]->setFPS(fps);
	//}
	animation* ani = new animation;
	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(temp, cnt, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
	ani->setFPS(fps);
	vAniBuffer.push_back(ani);

	mAni.insert(pair<string, arrAnimationbuffer>(animationKeyName, vAniBuffer));
	_vTotalAni.push_back(mAni);
}

void keyAniManager::start(string animationKeyName)
{
	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName))break;
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->isPlay())continue;
				(*vArrIter)->start();
				return;
			}
		}
	}
}

void keyAniManager::stop(string animationKeyName)
{

	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName))break;
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay())continue;
				(*vArrIter)->stop();
				return;
			}
		}
	}


}

void keyAniManager::pause(string animationKeyName)
{

	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName))break;
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay())continue;
				(*vArrIter)->pause();
				return;
			}
		}
	}

}

void keyAniManager::resume(string animationKeyName)
{

	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName))break;
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->isPlay())continue;
				(*vArrIter)->resume();
				return;
			}
		}
	}

}

animation* keyAniManager::findAnimation(string animationKeyName)
{

	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == animationKeyName))break;
			iterArrAnimationbuffer vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (vArrIter != mIter->second.end())return (*vArrIter);
			}
		}
	}
	return nullptr;
}

void keyAniManager::deleteAll()
{
	iterarrTotalAni vIter;
	iterAnimations mIter;
	for (vIter = _vTotalAni.begin(); vIter != _vTotalAni.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end(); )
		{
			if (mIter->second.size() != 0)
			{
				iterArrAnimationbuffer vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end(); )
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
				mIter->second.clear();
			}
			else mIter++;
		}
	}

}
