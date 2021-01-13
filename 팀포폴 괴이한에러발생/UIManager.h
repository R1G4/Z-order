#pragma once
#include "gameNode.h"
#include "kyoko.h"
class UIManager :
	public gameNode
{
private:
	image* _hpUI;
	image* _mahaGauge;
	RECT _m_gauge_rc;
	int _maha_count;
	RECT _black_rc[2];
	kyoko* _kyoko;

	vector<HPBar*> vHPreal;
	vector<HPBar*>::iterator viHPreal;
public:
	void setKyokoMemory(kyoko* kyoko) { _kyoko = kyoko; }
	UIManager();
	~UIManager();
	HRESULT init();
	void release();
	void update();
	void render();
	RECT getBlack1() { return _black_rc[0]; }
	RECT getBlack2() { return _black_rc[1]; }
};

