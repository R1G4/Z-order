#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	RECT rc;
	POINT camera;
	image* backGround;
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

