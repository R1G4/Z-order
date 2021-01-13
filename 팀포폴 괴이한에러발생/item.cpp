#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}


HRESULT item::init(float x, float y)
{
	//아이템 랜덤으로 초기화
	_item = (ITEM_KINDS)RND->getFromIntTo(APPLE, SHRIMP + 1);
	_x = x;
	_y = y;
	_arriveY = y - 10; //그림자 위치에서 보정
	_gravity = 0.11f;
	_jumpPower = 5.6f;
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	switch (_item)
	{
		case item::APPLE:
			_itemImg = IMAGEMANAGER->findImage("Apple");
			_heal = 1;
			break;
		case item::BOONGER:
			_itemImg = IMAGEMANAGER->findImage("Boonger");
			_heal = 2;
			break;
		case item::BURGER:
			_itemImg = IMAGEMANAGER->findImage("Burger");
			_heal = 3;
			break;
		case item::MINT:
			_itemImg = IMAGEMANAGER->findImage("Mint");
			_heal = 5;
			break;
		case item::SHRIMP:
			_itemImg = IMAGEMANAGER->findImage("Shrimp");
			_heal = 4;
			break;
	}

	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (_arriveY > _y)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
}

void item::removeEnemy(int i)
{
}

void item::render(POINT camera)
{
	_itemImg->render(getMemDC(), _itemRc.left, _itemRc.top, camera);
}
