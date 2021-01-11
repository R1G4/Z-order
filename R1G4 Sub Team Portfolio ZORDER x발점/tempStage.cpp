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
	stageLock = RectMake(1380, 0, 640, WINSIZEY);
	return S_OK;
}

void tempStage::release()
{

}

void tempStage::update()
{
	UI->update();
	RECT temp;

	pixelCollision();
	_player->update();
	//if(!_isDesk)camera = CAMERAMANAGER->CameraMake((_player->getRect().left+_player->getRect().right)/2, _player->getRect().bottom, BOTH, stage1);
	//else camera = CAMERAMANAGER->CameraMake((_player->getShadow().left + _player->getShadow().right) / 2, _player->getShadow().top, BOTH, stage1);
	if(!CAMERAMANAGER->getIsChainLock())camera = CAMERAMANAGER->CameraMake((_player->getShadow().left + _player->getShadow().right) / 2, _player->getShadow().top, BOTH, stage1);
	if (_isDesk||_player->getIsJump())CAMERAMANAGER->isChainLock(true);
	if (IntersectRect(&temp, &_player->getShadow(), &stageLock))
	{
		_isChainLock = true;
		CAMERAMANAGER->isChainLock(true);
		if (_em->getVEnemy().size < 1)_isChainLock = false;
	}
	if(!_isDesk&&!_isChainLock)CAMERAMANAGER->isChainLock(false);
	_em->update();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	//changeMap();
	
	if (IntersectRect(&temp, &_player->getAttackRect(), &chair[1].rc) && _player->getIsAttack())
	{
		cout << "타격" << endl;
	}
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

		HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _player->getDebugAttack(), camera);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
	}
	zOrder();
	UI->render();

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

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);

			break;
		}
		if ((r1 == 0 && g1 == 255 && b1 == 0) && !_player->getIsJump() && !_isDesk)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);
			//_isDesk = true;
			break;
		}
	//	else _isDesk = false;

		if (r1 == 255 && g1 == 255 && b1 == 0)
		{
			if (_player->getShadow().top <= _player->getRect().bottom)
			{

			}
		}

		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 1);
			_player->setNoSpeed(true);
			break;
		}
		if ((r2 == 0 && g2 == 255 && b2 == 0) && !_player->getIsJump() && !_isDesk)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 1);
			_player->setNoSpeed(true);
	//		_isDesk = true;
			break;
		}
	//	else _isDesk = false;
		if (r2 == 255 && g2 == 255 && b2 == 0)
		{
			if (_player->getShadow().top <= _player->getRect().bottom)
			{

			}
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
		if ((r1 == 0 && g1 == 255 && b1 == 0) && !_player->getIsJump()&&!_isDesk)
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
		if ((r2 == 0 && g2 == 255 && b2 == 0) && !_player->getIsJump() && !_isDesk)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
	}
	//책상위에 올라가는지 판단 
	for (int i = _player->getShadow().top+20; i <=  _player->getShadow().bottom+5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((_player->getKyokoDirection()== KYOKODIRECTION_RIGHT_JUMP|| _player->getKyokoDirection()==(KYOKODIRECTION_LEFT_JUMP) )
			&& (r == 0 && g == 255 && b == 0))
		{
			if (!_isDesk) {
				_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 50);
				_isDesk = true;
				break;
			}
		}
		else if (_isDesk)
		{
			for (int i = 0; i < 100; i++)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
			}
			
		}
		else if(!(r == 255 && g == 255 && b == 0)&&_player->getIsJump())_isDesk = false;
		//if ((/*(r == 0 && g == 255 && b == 0)||*/(r == 255 && g == 255 && b == 0) )&& _player->getIsJump())
		//{
		//	_isDesk = true;
		//}
		//else if ((r == 0 && g == 255 && b == 0) && _player->getIsJump())
		//{
		//	if (!_isDesk) {
		//		_player->setShadow(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 50);
		//		_isDesk = true;
		//		break;
		//	}
		//}
		//if (_isDesk&&_player->getIsJump())_isDesk = false;
	}
	for (int i = _player->getShadow().left+20; i <= _player->getShadow().right-20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(),/* (_player->getShadow().right + _player->getShadow().left) / 2*/i, (_player->getShadow().top + _player->getShadow().bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((/*(r == 0 && g == 255 && b == 0)||*/(r == 255 && g == 255 && b == 0)) && _player->getIsJump())
		{
			_isDesk = true;
		}
		//else if (!(r == 255 && g == 255 && b == 0) && _isDesk)
		//{
		//	cout << "??";
		//	//_player->setKyokoPoint(_player->getKyokoPoint().x+1, _player->getKyokoPoint().y +1);
		//	
		//}
		else if (!(r == 255 && g == 255 && b == 0) && _player->getIsJump())_isDesk = false;

		//else if ((r == 0 && g == 255 && b == 0) && _player->getIsJump())
		//{
		//	if (!_isDesk) {
		//		_player->setShadow(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 50);
		//		_isDesk = true;
		//		break;
		//	}
		//}
		//if (_isDesk&&_player->getIsJump())_isDesk = false;
	}

	//if(!_isDesk)
	//{
	//	
	//if (_isDesk)
	//{
	//	for (int i = _player->getShadow().top; i <= _player->getShadow().bottom; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);
	//		if (!(r == 255 && g == 255 && b == 0)||!(r==0&&g==255&&b==0))
	//		{
	//			_isDesk = false;
	//			//for (int j = 0; j < 8;j++)
	//			//{
	//			//	RECT temp;
	//			//	if (IntersectRect(&temp, &_player->getShadow(), &chair[j].rc))
	//			//	{
	//			//		if (chair[j].rc.right < (_player->getShadow().right + _player->getShadow().left) / 2)_player->setShadow(-10, 0);
	//			//		if (chair[j].rc.right > (_player->getShadow().right + _player->getShadow().left) / 2)_player->setShadow(+10, 0);
	//			//		break;
	//			//	}
	//			//}
	//		}
	//		
	//	}
	//}
	//for (int i = _player->getShadow().top; i <= _player->getShadow().bottom; ++i)
	//{
	//	COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);
	//	 if (((r == 0 && g == 255 && b == 0) || (r == 255 && g == 255 && b == 0)) && _player->getIsJump())
	//	{
	//		_isDesk = true;
	//	}
	//	else if (!(r == 255 && g == 255 && b == 0))
	//	{
	//		_isDesk = false;

	//	}
	//}
	//for (int i = _player->getRect().bottom+50; i <= _player->getRect().bottom+100; ++i)
	//{
	//	COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);
	//	if (_player->getIsJump() && (r == 255 && g == 255 && b == 0))
	//	{
	//		_isDesk = true;
	//		_player->setShadow(20);
	//		break;
	//	}
	//	else if (!(r == 255 && g == 255 && b == 0))
	//	{
	//		_isDesk = false;

	//	}
	//}

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
