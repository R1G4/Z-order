#pragma once
#include "enemy.h"

class schoolBoy : public enemy
{
	enemy* _enemy;
	float _speed;
public:
	schoolBoy();
	~schoolBoy();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
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
