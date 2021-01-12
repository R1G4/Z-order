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

	//공격 상태 및 공격 프레임에 따른 정보 초기화
	virtual void setAttackInfo();

	//공격 상태 및 공격 프레임 이미지에 따라 렉트 생성
	virtual void setAttackRect(STATE state, DIRECTION direction);

	//에너미 초기 이미지 및 애니메이션 셋팅
	virtual void addFrame();
};
