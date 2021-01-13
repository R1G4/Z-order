#pragma once
#include "gameNode.h"
#include "UIManager.h"

//보스가 일단 없어서 추후에 에너미를 보스로 변경하셈
class kyoko;
class enemyManager;

class BossStage : public gameNode
{

private:
	RECT _door_rc;
	UIManager* UI;
	POINT camera;
	kyoko* _player;
	image* stage1;
	image* stage1Pic;
	image* stage1Alpha;
	enemyManager* _em;

	int _alpha;		// 알파랜더용

	// 다이얼로그용
	bool _isStartScript;
	bool _isEndScript;
	int _string_count;
	vector<string> _vScriptStart;
	vector<string> _vScriptEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 맵이동
	void changeMap();

	//플레이어 에너미 주소 받기
	//보스가 일단 없어서 추후에 에너미를 보스로 변경하셈
	void setObjMemory(kyoko* kyoko, enemyManager* em)
	{
		_player = kyoko;
		_em = em;
	}
};

