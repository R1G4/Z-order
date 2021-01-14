#pragma once
#include "gameNode.h"

class bossHPBar : public gameNode
{
private:
	RECT _rcBossHP;
	float _x, _y;
	float _width;
	image* _bossHPBarFront;
	image* _bossHPBarBack;


public:
	bossHPBar() {};
	~bossHPBar() {};

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};

