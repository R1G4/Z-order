#include "stdafx.h"
#include "stage3.h"



HRESULT stage3::init(int slot)
{
	saveSlot = slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(3);
	_opt->setSlot(saveSlot);
	stage3 = IMAGEMANAGER->findImage("Stage3");
	stage3Pic = IMAGEMANAGER->findImage("Stage3Pic");
	STATUSMANAGER->setHp(24);
	STATUSMANAGER->setHpBar("HPBar");
	_player = new kyoko;
	_player->init();

	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("좌기둥");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 150, Lobj.img->getHeight());

	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	alpha = 255;
	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{
	pixelCollision();
	_opt->update();
	UI->update();
	
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &Lobj.rc))
	{
		alpha = 100;
	}
	else alpha = 255;


	_player->update();
	KEYANIMANAGER->update();
	cout << _player->getKyokoPoint().x << endl;
	cout << _player->getKyokoPoint().y << endl;

	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage3);
}

void stage3::render()
{
	stage3->render(getMemDC(), 0, 0, camera);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		
		stage3Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), Lobj.rc, camera);
	}
	
	_player->render(camera);
	Lobj.img->alphaRender(getMemDC(), Lobj.x, Lobj.y, alpha, camera);
	UI->render();
	_opt->render();
}

void stage3::pixelCollision()
{
	//아래에서 위로 박을때
	for (int i = _player->getShadow().top; i <= _player->getShadow().top; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage3Pic")->getMemDC(), _player->getShadow().left, i);
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage3Pic")->getMemDC(), _player->getShadow().left, i);
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage3Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage3Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
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

