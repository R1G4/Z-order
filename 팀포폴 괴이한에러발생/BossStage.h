#pragma once
#include "gameNode.h"
#include "UIManager.h"
#include "opTion.h"
#include "boss.h"
//������ �ϴ� ��� ���Ŀ� ���ʹ̸� ������ �����ϼ�
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

	int _alpha;		// ���ķ�����

	LPCSTR bossVideo;
	// ���̾�α׿�
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

	// ���̵�
	void changeMap();
	void attackCollision();
	void picCollision();
	void zOrder();
	void quickSort(int a,int b);
	//�÷��̾� ���ʹ� �ּ� �ޱ�
	//������ �ϴ� ��� ���Ŀ� ���ʹ̸� ������ �����ϼ�
	void setObjMemory(kyoko* kyoko, enemyManager* em)
	{
		_player = kyoko;
		_em = em;
	}
};

