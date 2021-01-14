#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	vHPreal = STATUSMANAGER->getHpBar();
	viHPreal = STATUSMANAGER->getHpBarIter();
	_hpUI = IMAGEMANAGER->findImage("HPUI");
	_maha_count = _kyoko->getMaha();
	_mahaGauge = IMAGEMANAGER->findImage("MahaGauge");
	_m_gauge_rc = RectMake(_mahaGauge->getX(), _mahaGauge->getY(), _maha_count, _mahaGauge->getHeight());
	_black_rc[0] = RectMake(0, 0, WINSIZEX, 82);
	_black_rc[1] = RectMake(0, WINSIZEY - 82, WINSIZEX, 82);

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	vHPreal = STATUSMANAGER->getHpBar();
	viHPreal = STATUSMANAGER->getHpBarIter();

	_maha_count = _kyoko->getMaha();

}

void UIManager::render()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _black_rc[0]);
	Rectangle(getMemDC(), _black_rc[1]);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	_hpUI->render(getMemDC(), 0, 0);
	_mahaGauge->render(getMemDC(), 189, 88, 0, 0, _maha_count, 18);
	for (viHPreal = vHPreal.begin(); viHPreal != vHPreal.end(); ++viHPreal)
	{
		(*viHPreal)->img->render(getMemDC(), 190 + (*viHPreal)->hp * 14, 56);
	}
	
}
