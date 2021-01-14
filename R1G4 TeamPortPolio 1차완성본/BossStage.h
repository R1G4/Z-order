#pragma once
#include "gameNode.h"
#include "UIManager.h"
#include "opTion.h"
#include "boss.h"
//보스가 일단 없어서 추후에 에너미를 보스로 변경하셈
class kyoko;
class enemyManager;

enum BossPhase
{
	INTRO_SCENE,
	BEFORE_FIGHT_DIALOG,
	VS_MESUZU,
	AFTER_FIGHT_DIALOG,
	END
};

class BossStage : public gameNode
{

private:
	RECT _door_rc;
	UIManager* UI;
	POINT camera;
	kyoko* _player;
	boss* _boss;
	image* stage1;
	image* stage1Pic;
	image* stage1Alpha;

	image* _radeon;
	image* _geForce;
	image* _kyoko_i;
	image* _kyoko_si;
	image* _boss_i;

	enemyManager* _em;
	opTion* _opt;

	BossPhase _bossPhase;

	int _alpha;		// 알파랜더용

	LPCSTR bossVideo;
	// 다이얼로그용
	int _string_count;
	int _string_count_2;
	vector<string> _vScriptStart;
	vector<string> _vScriptEnd;
	vector<int> _vZorderB;
public:
	
	HRESULT init();
	void release();
	void update();
	void render();

	// 맵이동
	void changeMap();
	void attackCollision();
	void picCollision();
	void zOrder();
	void quickSort(int a,int b);
	//플레이어 에너미 주소 받기
	//보스가 일단 없어서 추후에 에너미를 보스로 변경하셈
	void setObjMemory(kyoko* kyoko, enemyManager* em)
	{
		_player = kyoko;
		_em = em;
	}
};

