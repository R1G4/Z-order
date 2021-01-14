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
	//������ �������� �ʱ�ȭ
	_item = (ITEM_KINDS)RND->getFromIntTo(APPLE, SHRIMP + 1);

	//��ǥ �ʱ�ȭ
	_x = x;
	_y = _y - 10;

	//���� ��ǥ _y�� ���ϹǷ� ó���� �ʱ�ȭ�� y��ǥ�� �ʿ��ϴ�
	_arriveY = 100;

	//������ ����? ����
	_gravity = 0.11f;
	_jumpPower = 5.6f;
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	//������ ������ �ʱ�ȭ �Ѵ�.
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

	//������ ��Ʈ�� �����Ѵ�.
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	//������ y������ ���ƿö� ������ ����? �� �����Ѵ�.
	if (_arriveY > _y)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}

	//������ ��Ʈ�� �����Ѵ�.
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
}

void item::render(POINT camera)
{
	_itemImg->render(getMemDC(), _itemRc.left, _itemRc.top, camera);
}
