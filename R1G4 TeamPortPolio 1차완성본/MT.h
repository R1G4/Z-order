#pragma once
#include "enemy.h"

class MT : public enemy
{
	enemy* _enemy;
public:
	MT();
	~MT();

	virtual HRESULT init(float x, float y, STATE state, DIRECTION direction);
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