#pragma once
#include "gameNode.h"
#include "soundTestScene.h"
#include "testScene.h"
#include "ghostScene.h"

class playGround : public gameNode
{
private:
	RECT _psh_rc;
	RECT _SCH_rc;
	RECT _KDH_rc;
	RECT _KDK_rc;
	RECT _PJU_rc;
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};

