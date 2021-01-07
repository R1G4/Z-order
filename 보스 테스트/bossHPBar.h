#pragma once
#include "gameNode.h"

class bossHPBar : public gameNode
{
private:
	RECT _rcProgress;
	RECT _rcBossHP;
	float _x, _y;
	float _width;

	image* _progressBarFront;		//앞에 나올 게이지 이미지
	image* _progressBarBack;	//뒤에 그려질 게이지 이미지
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

