#include "stdafx.h"
#include "bossHPBar.h"

HRESULT bossHPBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_bossHPBarFront = IMAGEMANAGER->addImage("boss_HPBarFront", "boss_HPBarFront.bmp", width, height, true, RGB(255, 0, 255));
	_bossHPBarBack = IMAGEMANAGER->addImage("boss_HPBarBack", "boss_HPBarBack.bmp", width, height, true, RGB(255, 0, 255));

	//게이지의 가로크기는 이미지의 가로크기만큼.
	_width = _bossHPBarFront->getWidth();

	return S_OK;
}

void bossHPBar::release()
{

}

void bossHPBar::update()
{
	_rcBossHP = RectMakeCenter(_x, _y, _bossHPBarFront->getWidth(),
		_bossHPBarBack->getHeight());
}

void bossHPBar::render()
{
	IMAGEMANAGER->render("boss_HPBarBack", getMemDC(),
		_rcBossHP.left + _bossHPBarBack->getWidth() / 2,
		_y + _bossHPBarBack->getHeight() / 2, 0, 0,
		_bossHPBarBack->getWidth(), _bossHPBarBack->getHeight());

	IMAGEMANAGER->render("boss_HPBarFront", getMemDC(),
		_rcBossHP.left + _bossHPBarFront->getWidth() / 2,
		_y + _bossHPBarFront->getHeight() / 2, 0, 0,
		_width, _bossHPBarFront->getHeight());


}

void bossHPBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _bossHPBarBack->getWidth();
}
