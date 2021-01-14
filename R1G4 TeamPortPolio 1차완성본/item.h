#pragma once

#include "gameNode.h"
class item : public gameNode
{
public:

	//������ ���� Ȥ�� ����
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

	//������ ��Ʈ
	RECT _itemRc;

	//������ �̹���
	image* _itemImg;

	//��ǥ
	float _x, _y;
	float _arriveY;	//ó���� �ʱ�ȭ�� y��ǥ

	//���� ȿ�� ����
	float _gravity;		//�߷�
	float _jumpPower;	//�����Ŀ�

public:
	item();
	~item();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);

	//��Ʈ
	RECT getRect() { return _itemRc; }

	//ü��ȸ��
	int getHeal() { return _heal; }

	//������ ���� Ȥ�� ����
	ITEM_KINDS getItemState() { return _item; }
	bool ItemAcheive();
};

