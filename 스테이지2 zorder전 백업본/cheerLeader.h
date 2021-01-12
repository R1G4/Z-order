#pragma once
#include "enemy.h"

class cheerLeader :public enemy
{
	enemy* _enemy;
	float _speed;
	int _hp;
public:
	cheerLeader();
	~cheerLeader();

	virtual HRESULT init(float x, float y, STATE, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void move();
	virtual void state();

	//���� ���� �� ���� �����ӿ� ���� ���� �ʱ�ȭ
	virtual void setAttackInfo();

	//���� ���� �� ���� ������ �̹����� ���� ��Ʈ ����
	virtual void setAttackRect(STATE state, DIRECTION direction);

	//���ʹ� �ʱ� �̹��� �� �ִϸ��̼� ����
	virtual void addFrame();
};
