#pragma once
#include "gameNode.h"

struct tagTab
{
	RECT rc;
	image* img;
	float x, y;
	float movepower;	//���̺� UI ����ÿ� ���ӵ� ����
	float accel;		//���̺� UI ����ÿ� ���ӵ� ����
};

class saveLoad :
	public gameNode
{
private:
	image* _background;
	tagTab tab[3];

public:
	saveLoad();
	~saveLoad();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void addimage();
};

