#pragma once
#include "gameNode.h"
#include "bossHPBar.h"
#define BOSSSPEED 1.5f
#define PI 3.141592f


enum BOSSSTATE
{
	BOSS_LEFT_IDLE,			BOSS_LEFT_DOWN,
	BOSS_RIGHT_IDLE,		BOSS_RIGHT_DOWN,
	BOSS_LEFT_WALK,			BOSS_LEFT_GETHIT,
	BOSS_RIGHT_WALK,		BOSS_RIGHT_GETHIT,
	BOSS_LEFT_SLAP,			BOSS_LEFT_GETUP,
	BOSS_RIGHT_SLAP,		BOSS_RIGHT_GETUP,
	BOSS_LEFT_DIE,			BOSS_LEFT_JUMP,
	BOSS_RIGHT_DIE,			BOSS_RIGHT_JUMP,
	BOSS_LEFT_PUNCH,		BOSS_LEFT_ROAR,
	BOSS_RIGHT_PUNCH,		BOSS_RIGHT_ROAR,
	BOSS_LEFT_TACKLE,		BOSS_LEFT_TAUNT,
	BOSS_RIGHT_TACKLE,		BOSS_RIGHT_TAUNT,
	BOSS_LEFT_GETHIT_1,		BOSS_LEFT_GETHIT_2,
	BOSS_RIGHT_GETHIT_1,	BOSS_RIGHT_GETHIT_2,
	BOSS_LEFT_GETHIT_3,		BOSS_LEFT_ELBOW,
	BOSS_RIGHT_GETHIT_3,	BOSS_RIGHT_ELBOW,
	BOSS_LEFT_DIE_END,
	BOSS_RIGHT_DIE_END
};

enum PAHSE
{
	PAHSE_1,
	PAHSE_2,
	PAHSE_3

};


enum AAASTATE
{
	AAA_LEFT_IDLE, AAA_RIGHT_IDLE
};

class boss : public gameNode
{
private:

	image* _boss;
	image* _bossMap;
	image* _bossShadow;
	image* _aaa;			//image _aaa, _rcAAA는 플레이어 대신해서 충돌테스트 하려고 만든거. 삭제해도됌
	image* _bossHPImage;
	RECT _rcAAA;
	RECT _rcBoss;
	RECT _rcBossShadow;
	RECT _rcNear;
	RECT _rcFar;
	RECT _rcMiddle;
	RECT _rcPlayer;
	RECT _rcAttack;
	RECT _rcBossAttack;


	animation* _aaaMotion;
	animation* _bossMotion;
	BOSSSTATE _bossState;
	PAHSE _pahse;
	AAASTATE _aaaState;
	bossHPBar* _bossHPBar;
	float _x, _y;
	float _playerX, _playerY;
	float _distance;
	float _angle, _angle2;
	float _speed;
	float _jumpPower;
	float _gravity;
	int _count, _count2, _count3;
	int _attackCount;
	int _index;
	int _currentFrameX, _currentFrameY;
	float _bossHP, _maxHP;

public:
	boss() {};
	~boss() {};

	virtual HRESULT init();//(const char* imageName);
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void hitDamage(float damage);	

	void setImage();


};

