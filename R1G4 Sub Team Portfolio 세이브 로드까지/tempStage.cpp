#include "stdafx.h"
#include "tempStage.h"

HRESULT tempStage::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(1);
	
	SOUNDMANAGER->play("MainStage", _opt->getVolume());
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->init(1);
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

	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	for (int i = 0; i < 8; i++)
	{
		chair[i].img = IMAGEMANAGER->findImage("chair");
	}

	_door_rc = RectMake(1380, 400, 300, 130);

	return S_OK;
}

HRESULT tempStage::init(int slot)
{
	saveSlot=slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(1);
	_opt->setSlot(saveSlot);
	
	SOUNDMANAGER->play("MainStage", _opt->getVolume());
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->init(1);
	_em->setKyokoMemory(_player);
	
	_opt->setKyokoAddressLink(_player);
	_opt->setEnemyAddressLink(_em);
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

	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

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
	UI->update();

	SOUNDMANAGER->setVolume(_opt->getVolume());
	pixelCollision();
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	_em->update();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	changeMap();
	_opt->update();
}

void tempStage::render()
{

	stage1->render(getMemDC(), 0, 0, camera);


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);

		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);
	}
	_player->render(camera);
	_em->render(camera);
	for (int i = 0; i < 8; i++)
	{
		chair[i].img->render(getMemDC(), chair[i].rc.left, chair[i].rc.top, camera);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
		for (int i = 0; i < 8; i++) { Rectangle(getMemDC(), chair[i].rc, camera); }
		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);
		Rectangle(getMemDC(), _player->getDebugRect(), camera);
		Rectangle(getMemDC(), _player->getDebugShadow(), camera);

		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{

			enemy* enemy = _em->getVEnemy()[i];
			//충돌용
			Rectangle(getMemDC(), enemy->getDebugRect(), camera);
			//그림자
			Rectangle(getMemDC(), enemy->getDebugShadowRc(), camera);
			//공격
			HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			Rectangle(getMemDC(), enemy->getDebugAttackRc(), camera);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(brush);

		}

		HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _player->getDebugAttack(), camera);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
	}
	zOrder();
	_opt->render();
	UI->render();

}

void tempStage::DeleteProduct()
{
	delete(_player);
	delete(_em);
}

void tempStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow())&&KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//DeleteProduct();
		delete(_player);
		delete(_em);
		SCENEMANAGER->changeScene("Stage2",saveSlot);
		//SOUNDMANAGER->stop("MainStage");
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

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);

			break;
		}
		if (r1 == 0 && g1 == 255 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);

			break;
		}


		if (r2 == 0 && g2 == 255 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 1);
			_player->setNoSpeed(true);
			break;
		}
		if (r2 == 0 && g2 == 255 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
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
		if ((r1 == 0 && g1 == 255 && b1 == 0) && !_player->getIsJump())
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
		if ((r2 == 0 && g2 == 255 && b2 == 0) && !_player->getIsJump())
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
	}

	//으자
	for (int i = _player->getShadow().top + 20; i <= _player->getShadow().bottom + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((_player->getKyokoDirection() == KYOKODIRECTION_RIGHT_JUMP || _player->getKyokoDirection() == (KYOKODIRECTION_LEFT_JUMP))
			&& (r == 0 && g == 255 && b == 0))
		{
			if (!_isDesk) {
				_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 50);
				_isDesk = true;
				break;
			}
		}
		else if (!(r == 255 && g == 255 && b == 0) && _player->getIsJump())_isDesk = false;
	}
	for (int i = _player->getShadow().left + 20; i <= _player->getShadow().right - 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, (_player->getShadow().top + _player->getShadow().bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (((r == 255 && g == 255 && b == 0)) && _player->getIsJump())
		{
			_isDesk = true;
		}
		else if (!(r == 255 && g == 255 && b == 0) && _player->getIsJump())_isDesk = false;
	}



	//에너미 충돌
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
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y - 3);
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
