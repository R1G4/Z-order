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

	//좌표 초기화
	_x = x;
	_y = _y - 10;

	//기존 좌표 _y는 변하므로 처음에 초기화된 y좌표가 필요하다
	_arriveY = 100;

	//아이템 점프? 관련
	_gravity = 0.11f;
	_jumpPower = 5.6f;
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	//아이템 정보를 초기화 한다.
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

	//아이템 렉트를 생성한다.
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	//기존의 y축으로 돌아올때 까지는 점프? 를 진행한다.
	if (_arriveY > _y)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}

	//아이템 렉트를 생성한다.
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
}

void item::render(POINT camera)
{
	_itemImg->render(getMemDC(), _itemRc.left, _itemRc.top, camera);
}
