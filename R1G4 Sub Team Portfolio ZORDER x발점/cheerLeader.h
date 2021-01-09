#pragma once
#include "enemy.h"

class cheerLeader :public enemy
{
	enemy* _enemy;
	float _speed;
public:
	cheerLeader();
	~cheerLeader();

	virtual HRESULT init(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void move();
	virtual void state();

	//���ʹ� �ʱ� �̹��� �� �ִϸ��̼� ����
	virtual void addFrame();

	//Ư�� ���ʹ� ���� �� ���� �������� ���� üũ
	static void ActionCheck(void * obj);
};
