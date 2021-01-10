#pragma once
#include "enemy.h"

class MT : public enemy
{
	enemy* _enemy;
	float _speed;
public:
	MT();
	~MT();

	virtual HRESULT init(float x, float y, STATE state , DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void move();
	virtual void state();

	//에너미 초기 이미지 및 애니메이션 셋팅
	virtual void addFrame();

	//특정 에너미 도발 후 정상 패턴으로 복귀 체크
	static void ActionCheck(void * obj);
};