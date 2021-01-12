#include "stdafx.h"
#include "stage2.h"

HRESULT stage2::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);

	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->setKyokoMemory(_player);
	_em->init(2);
	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("좌기둥");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("우기둥");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	alpha = 255;
	return S_OK;
}

HRESULT stage2::init(int slot)
{
	saveSlot = slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);
	_opt->setSlot(saveSlot);
	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->setKyokoMemory(_player);
	_em->init(2);
	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("좌기둥");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("우기둥");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	alpha = 255;
	return S_OK;

}

void stage2::release()
{
}

void stage2::update()
{
	UI->update();
	_opt->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();
	pixelCollision();
	_player->update();
	_em->update();
	cout << _player->getRect().left;
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage2);
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &Lobj.rc))
	{
		alpha = 100;
	}
	else if (IntersectRect(&temp, &_player->getRect(), &Robj.rc))
	{
		alpha = 100;
	}
	else alpha = 255;
}

void stage2::render()
{
	stage2->render(getMemDC(), 0, 0, camera);
	_opt->render();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage2Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), Lobj.rc, camera);
		Rectangle(getMemDC(), Robj.rc, camera);
	}
	zOrder();
	Lobj.img->alphaRender(getMemDC(), Lobj.x, Lobj.y, alpha, camera);
	Robj.img->alphaRender(getMemDC(), Robj.x, Robj.y, alpha, camera);
	UI->render();

}

void stage2::DeleteProduct()
{
	delete(_player);
	delete(_em);
}

void stage2::pixelCollision()
{
	//아래에서 위로 박을때
	for (int i = _player->getShadow().top; i <= _player->getShadow().top; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i + (_player->getShadow().right - _player->getShadow().left) / 2 + 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

	//왼쪽에서 오른쪽으로 박을때
	for (int i = _player->getShadow().right; i >= _player->getShadow().right; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i - (_player->getShadow().right - _player->getShadow().left) / 2 - 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}
}
