#include "stdafx.h"
#include "saveLoad.h"

saveLoad::saveLoad()
{
}

saveLoad::~saveLoad()
{
}

HRESULT saveLoad::init()
{
	_background = IMAGEMANAGER->addImage("���", "savescene/���̺�â.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	

	return S_OK;
}

void saveLoad::release()
{
}

void saveLoad::update()
{
}

void saveLoad::render()
{
	IMAGEMANAGER->findImage("���")->render(getMemDC());
}
