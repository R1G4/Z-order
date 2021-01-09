#include "stdafx.h"
#include "tempStage.h"

HRESULT tempStage::init()
{
	SOUNDMANAGER->play("MainStage", 0.1);
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	_player = new kyoko;
	_player->init();
	//_em = new enemyManager;
	//_em->init();
	//_em->setKyokoMemory(_player);

	//의자 렉트
	chair[0].rc = RectMake(WINSIZEX / 2 - 222, WINSIZEY / 2 + 135, 100, 100);
	chair[1].rc = RectMake(WINSIZEX / 2 + 42, WINSIZEY / 2 + 128, 100, 100);
	chair[2].rc = RectMake(WINSIZEX / 2 + 322, WINSIZEY / 2 + 135, 100, 100);
	chair[3].rc = RectMake(WINSIZEX / 2 + 597, WINSIZEY / 2 + 135, 100, 100);
	chair[4].rc = RectMake(WINSIZEX / 2 - 396, WINSIZEY / 2 + 304, 100, 100);
	chair[5].rc = RectMake(WINSIZEX / 2 - 127, WINSIZEY / 2 + 304, 100, 100);
	chair[6].rc = RectMake(WINSIZEX / 2 + 150, WINSIZEY / 2 + 304, 100, 100);
	chair[7].rc = RectMake(WINSIZEX / 2 + 427, WINSIZEY / 2 + 304, 100, 100);

	//Z 구분용렉트
	tempRcU.rc = RectMake(WINSIZEX / 2 - 157, WINSIZEY / 2 + 238, 100, 10);
	tempRcD.rc = RectMake(WINSIZEX / 2 - 326, WINSIZEY / 2 + 405, 100, 10);


	for (int i = 0; i < 8; i++)
	{
		chair[i].img = IMAGEMANAGER->findImage("chair");
	}

	_door_rc = RectMake(1380, 400, 300, 130);

	return S_OK;
}

void tempStage::release()
{

}

void tempStage::update()
{
	pixelCollision();
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	//_em->update();
	KEYANIMANAGER->update();
	changeMap();
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);

	for (int i = 0; i < 8; i++)
	{
		chair[i].img->render(getMemDC(), chair[i].rc.left, chair[i].rc.top, camera);

	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);

		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);
	}
	_player->render(camera);
	//	_em->render(camera);

	//ZORDER->render(camera);
}

void tempStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow()))
	{
		delete(_player);
		SCENEMANAGER->changeScene("스테이지2");
		SOUNDMANAGER->stop("MainStage");
	}
}

void tempStage::pixelCollision()
{
	//아래에서 위로 박을때
	for (int i = _player->getShadow().top; i <= _player->getShadow().top; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i + _player->getShadow().bottom - _player->getShadow().top - 10);
			_player->setNoSpeed(true);
			break;
		}

	}

	//위에서 아래로 박을떄
	for (int i = _player->getShadow().bottom; i >= _player->getShadow().bottom; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i - _player->getShadow().bottom + _player->getShadow().top + 10);
			_player->setNoSpeed(true);
			break;
		}
	}

	//오른쪽에서 왼쪽으로 박을때
	for (int i = _player->getShadow().left; i <= _player->getShadow().left; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(i + (_player->getShadow().right - _player->getShadow().left) / 2 + 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

	//왼쪽에서 오른쪽으로 박을때
	for (int i = _player->getShadow().right; i >= _player->getShadow().right; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(i - (_player->getShadow().right - _player->getShadow().left) / 2 - 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

}
