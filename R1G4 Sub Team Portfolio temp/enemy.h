#pragma once
#include "gameNode.h"

class kyoko;
class enemy : public gameNode
{
protected:
	kyoko* _kyoko;
public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y);
	void setKyokoAddressLink(kyoko* kyoko) { _kyoko = kyoko; }
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);
};
