#pragma once
#include "gameNode.h"
//#include "schoolGirl.h"

class kyoko;
class enemy : public gameNode
{
protected:
	kyoko* _kyoko;
public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y);

	//virtual HRESULT init(int enemyNum, float x, float y);

	//virtual HRESULT init();


	void setKyokoAddressLink(kyoko* kyoko) { _kyoko = kyoko; }
	//virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);
};
