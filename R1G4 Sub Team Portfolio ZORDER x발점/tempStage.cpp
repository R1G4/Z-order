#include "stdafx.h"
#include "tempStage.h"

HRESULT tempStage::init()
{
	SOUNDMANAGER->play("MainStage", 0.1);
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->init();
	_em->setKyokoMemory(_player);

	//의자 렉트
	chair[0].rc = RectMake(WINSIZEX / 2 - 222, WINSIZEY / 2 + 135, 100, 170);
	chair[1].rc = RectMake(WINSIZEX / 2 + 42, WINSIZEY / 2 + 135, 100, 170);
	chair[2].rc = RectMake(WINSIZEX / 2 + 322, WINSIZEY / 2 + 135, 100, 170);
	chair[3].rc = RectMake(WINSIZEX / 2 + 597, WINSIZEY / 2 + 135, 100, 170);
	chair[4].rc = RectMake(WINSIZEX / 2 - 396, WINSIZEY / 2 + 304, 100, 170);
	chair[5].rc = RectMake(WINSIZEX / 2 - 127, WINSIZEY / 2 + 304, 100, 170);
	chair[6].rc = RectMake(WINSIZEX / 2 + 150, WINSIZEY / 2 + 304, 100, 170);
	chair[7].rc = RectMake(WINSIZEX / 2 + 427, WINSIZEY / 2 + 304, 100, 170);

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
	_em->update();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	//changeMap();
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);

	//
	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	stage1Pic->render(getMemDC(), 0, 0, camera);
	//	Rectangle(getMemDC(), _door_rc, camera);

	//	Rectangle(getMemDC(), tempRcU.rc, camera);
	//	Rectangle(getMemDC(), tempRcD.rc, camera);
	//}
	//_player->render(camera);
	//_em->render(camera);
	//for (int i = 0; i < 8; i++)
	//{
	//	chair[i].img->render(getMemDC(), chair[i].rc.left, chair[i].rc.top, camera);
	//}
	zOrder();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
		for (int i = 0; i < 8; i++) { Rectangle(getMemDC(), chair[i].rc, camera); }
		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);
	}
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
	//픽셀 콜리쟌 상 하
	for (int i = _player->getShadow().left; i <= _player->getShadow().right; i++)
	{
		//상
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, _player->getShadow().top);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//하
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, _player->getShadow().bottom);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if ((r1 == 255 && g1 == 0 && b1 == 0) || (r1 == 0 && g1 == 255 && b1 == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);
			break;
		}

		if ((r2 == 255 && g2 == 0 && b2 == 0) || (r2 == 0 && g2 == 255 && b2 == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 1);
			_player->setNoSpeed(true);
			break;
		}
	}

	//픽셀 콜리쟌 좌 우
	for (int i = _player->getShadow().top; i <= _player->getShadow().bottom; i++)
	{
		//좌
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().left, i);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//우
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().right, i);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x + 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
		if ((r1 == 0 && g1 == 255 && b1 == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x + 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
		if (r2 == 0 && g2 == 255 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
	}

	//에너미 충돌
	//위의 방식대로 했는데 에너미가 열심히 비벼서 뚫고 지나가기에 일단 그전에 코드를 적용하여 작성하였음
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		bool isCollision = false;
		//아래에서 위로 박을때
		for (int j = _em->getVEnemy()[i]->getShadowRc().top; j <= _em->getVEnemy()[i]->getShadowRc().top; j++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y - 1);
				isCollision = true;
				break;
			}
		}

		//위에서 아래로 박을떄
		for (int j = _em->getVEnemy()[i]->getShadowRc().bottom; j >= _em->getVEnemy()[i]->getShadowRc().bottom; j--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{

				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y + 1);
				isCollision = true;
				break;
			}
		}

		//오른쪽에서 왼쪽으로 박을때
		for (int j = _em->getVEnemy()[i]->getShadowRc().left; j <= _em->getVEnemy()[i]->getShadowRc().left; j++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x + 1, _em->getVEnemy()[i]->getEnemyPoint().y);
				isCollision = true;
				break;
			}

		}

		//왼쪽에서 오른쪽
		for (int j = _em->getVEnemy()[i]->getShadowRc().right; j >= _em->getVEnemy()[i]->getShadowRc().right; j--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x - 1, _em->getVEnemy()[i]->getEnemyPoint().y);
				isCollision = true;
				break;
			}
		}
		_em->getVEnemy()[i]->setCollision(isCollision);
	}
}
