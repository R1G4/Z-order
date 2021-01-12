#pragma once

#include "gameNode.h"
class item : public gameNode
{
	public:

	//아이템 종류 혹은 상태
	enum ITEM_KINDS
	{
		APPLE,
		BOONGER,
		BURGER,
		MINT,
		SHRIMP,
		REMOVE
	};

	ITEM_KINDS _item;
	int _heal;

	//아이템 렉트
	RECT _itemRc;

	//아이템 이미지
	image* _itemImg;

	//좌표
	float _x, _y, _arriveY;

	//점프 효과 관련
	float _gravity;
	float _jumpPower;
	public:
	item();
	~item();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void removeEnemy(int i);
	virtual void render(POINT camera);

	//렉트
	RECT getRect() { return _itemRc; }

	//체력회복
	int getHeal() { return _heal; }

	//아이템 상태 혹은 종류
	ITEM_KINDS getItemState() { return _item; }
	void ItemRemove() { _item = REMOVE; }
};

