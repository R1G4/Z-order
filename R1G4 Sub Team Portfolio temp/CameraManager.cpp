#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

POINT CameraManager::CameraMake(int CharacterX,int CharacterY,XY WantToBase,int backgroundW,int backgroundH)
{
	if (!_isLock)
	{
		switch (WantToBase)
		{
			POINT CPoint;
		case X:
			CPoint.x = CharacterX - WINSIZEX / 2;
			CPoint.y = 0;
			if (CPoint.x < 0)CPoint.x = 0;
			if (CPoint.x > backgroundW - WINSIZEX)CPoint.x = backgroundW - WINSIZEX;
			return CPoint;
			break;
		case Y:
			CPoint.x = 0;
			CPoint.y = CharacterY - WINSIZEY / 2;
			if (CPoint.y < 0)CPoint.y = 0;
			if (CPoint.y > backgroundH - WINSIZEY)CPoint.y = backgroundH - WINSIZEY;
			return CPoint;
			break;
		case BOTH:
			CPoint.x = CharacterX - WINSIZEX / 2;
			CPoint.y = CharacterY - WINSIZEY / 2;
			if (CPoint.x < 0)CPoint.x = 0;
			if (CPoint.x > backgroundW - WINSIZEX)CPoint.x = backgroundW - WINSIZEX;
			if (CPoint.y < 0)CPoint.y = 0;
			if (CPoint.y > backgroundH - WINSIZEY)CPoint.y = backgroundH - WINSIZEY;
			return CPoint;
			break;
		}
	}
}

POINT CameraManager::CameraMake(int CharacterX, int CharacterY, XY WantToBase, int backgroundW, int backgroundH, int seperate,DEST dest)
{

	switch (WantToBase)
	{
		POINT CPoint;
	case X:
		if (CharacterX < WINSIZEX / seperate&&dest==RIGHT)
		{
			CPoint.x = CharacterX - (WINSIZEX / seperate)*(seperate - 1);
			CPoint.y = 0;
		}
		if (CharacterX > WINSIZEX / seperate&&dest==LEFT)
		{
			CPoint.x = CharacterX - (WINSIZEX / seperate);
			CPoint.y = 0;

		}
		if (CPoint.x < 0)CPoint.x = 0;
		if (CPoint.x > backgroundW - WINSIZEX)CPoint.x = backgroundW - WINSIZEX;
		return CPoint;
		break;
	case Y:
		CPoint.x = 0;
		CPoint.y = CharacterY - (WINSIZEX / seperate)*(seperate - 1);
		if (CPoint.y < 0)CPoint.y = 0;
		if (CPoint.y > backgroundH - WINSIZEY)CPoint.y = backgroundH - WINSIZEY;
		return CPoint;
		break;
	case BOTH:
		if (CharacterX > WINSIZEX/seperate&&dest==RIGHT)
		{
			CPoint.x = CharacterX - (WINSIZEX / seperate)*(seperate - 1);
		}
		if (CharacterX < WINSIZEX / seperate&&dest==LEFT)
		{
			CPoint.x = CharacterX - (WINSIZEX / seperate);
		}
		CPoint.y = CharacterY - (WINSIZEX / seperate)*(seperate - 1);
		if (CPoint.x < 0)CPoint.x = 0;
		if (CPoint.x > backgroundW - WINSIZEX)CPoint.x = backgroundW - WINSIZEX;
		if (CPoint.y < 0)CPoint.y = 0;
		if (CPoint.y > backgroundH - WINSIZEY)CPoint.y = backgroundH - WINSIZEY;
		return CPoint;
		break;
	}
}

POINT CameraManager::CameraMake(int CharacterX, int CharacterY, XY WantToBase, image * img)
{
	switch (WantToBase)
	{
		POINT CPoint;
	case X:
		CPoint.x = CharacterX - WINSIZEX / 2;
		CPoint.y = 0;
		if (CPoint.x < 0)CPoint.x = 0;
		if (CPoint.x > img->getWidth() - WINSIZEX)CPoint.x = img->getWidth() - WINSIZEX;
		return CPoint;
		break;
	case Y:
		CPoint.x = 0;
		CPoint.y = CharacterY - WINSIZEY / 2;
		if (CPoint.y < 0)CPoint.y = 0;
		if (CPoint.y > img->getHeight() - WINSIZEY)CPoint.y = img->getHeight() - WINSIZEY;
		return CPoint;
		break;
	case BOTH:
		CPoint.x = CharacterX - WINSIZEX / 2;
		CPoint.y = CharacterY - WINSIZEY / 2-100;
		if (CPoint.x < 0)CPoint.x = 0;
		if (CPoint.x > img->getWidth() - WINSIZEX)CPoint.x = img->getWidth() - WINSIZEX;
		if (CPoint.y < 0)CPoint.y = 0;
		if (CPoint.y > img->getHeight()- WINSIZEY)CPoint.y = img->getHeight() - WINSIZEY;
		return CPoint;
		break;
	}
}

POINT CameraManager::CameraMake(int CharacterX, int CharacterY, XY WantToBase, image * img, int seperate, int check)
{
	return POINT();
}
//�̴ϸʸ���� ����̹����� ĳ�����̹���, �׸��� �̴ϸ��� �׷��� rect�� �־��ָ� �׷��ݴϴ�. �ٸ� �̰��� ��ü������������ ����������Ͽ��⿡ �����ϼž��մϴ�.
RECT CameraManager::miniMapMake(image* img,image* CharacterImg,RECT rc)
{
	RECT mini;
	image* mapImg;
	float widLatio;
	float heiLatio;
	widLatio=img->getWidth()/(rc.right-rc.left);
	heiLatio = img->getHeight() / (rc.bottom - rc.top);
	//mapImg = img;
	//mapImg->getWidth() = mapImg->getWidth() / widLatio;
	mini = RectMake(CharacterImg->getX() / widLatio, CharacterImg->getY() / heiLatio,
		CharacterImg->getFrameWidth() / widLatio, CharacterImg->getFrameHeight()/widLatio);
	return mini;
}
//ī�޶� ������ �ְ�, ���� ���� ������ �������
void CameraManager::shaking(POINT* camera, int power)
{
	POINT Ptemp;
	Ptemp = *camera;
	interval++;
	if (_isShaking)
	{
		if (interval > 1)
		{
			Ptemp.x += power;
			Ptemp.y += power;
			*camera = Ptemp;
		}
		if (interval > 2)
		{
			Ptemp.x -= power;
			Ptemp.y -= power;
			*camera = Ptemp;
			interval = 0;
		}
	}
	_time--;
	if (_time < 0)_isShaking = false;
}
//�ð� ����. Ư�� ���ǿ����� ����ǵ��� �ؾ��մϴ� �ȱ׷��� ������ ��鸳�ϴ�
void CameraManager::setTime(int time)
{
	_time = time;
	_isShaking = true;
}
//ī�޶������ ���� �뵵. ī�޶� ����ũ �տ� if���� �����ν� ī�޶� �������� ���� �� ����.
void CameraManager::isChainLock(bool ONOFF)
{
	_isLock = ONOFF;
}
//ī�޶� ���� �����̴� �̴ϸ�?
//void CameraManager::miniMapMake(POINT camera, int sizeX, int sizeY, image* characterImg, image* backImg)
//{
//	if (camera.x < 0)camera.x = 0;
//	if (camera.y < 0)camera.y = 0;
//	float widLatio;
//	float heiLatio;
//	RECT minibase = RectMake(camera.x, camera.y, sizeX, sizeY);
//	RECT
//		
//
//}
