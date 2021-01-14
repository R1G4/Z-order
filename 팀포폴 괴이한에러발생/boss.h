#pragma once
#include "gameNode.h"
#include "bossHPBar.h"
#define BOSSSPEED 2
#define PI 3.141592f

class kyoko;	//전방선언. cpp에 헤더 걸어주기

enum BOSSDIRECTION
{
	BOSS_LEFT_IDLE, BOSS_LEFT_DOWN,
	BOSS_RIGHT_IDLE, BOSS_RIGHT_DOWN,
	BOSS_LEFT_WALK, BOSS_LEFT_GETHIT,
	BOSS_RIGHT_WALK, BOSS_RIGHT_GETHIT,
	BOSS_LEFT_SLAP, BOSS_LEFT_GETUP,
	BOSS_RIGHT_SLAP, BOSS_RIGHT_GETUP,
	BOSS_LEFT_DIE, BOSS_LEFT_JUMPUP,
	BOSS_RIGHT_DIE, BOSS_RIGHT_JUMPUP,
	BOSS_LEFT_JUMPDOWN, BOSS_LEFT_JUMPDOWN_END,
	BOSS_RIGHT_JUMPDOWN, BOSS_RIGHT_JUMPDOWN_END,
	BOSS_LEFT_PUNCH, BOSS_LEFT_ROAR,
	BOSS_RIGHT_PUNCH, BOSS_RIGHT_ROAR,
	BOSS_LEFT_TACKLE, BOSS_LEFT_TAUNT,
	BOSS_RIGHT_TACKLE, BOSS_RIGHT_TAUNT,
	BOSS_LEFT_GETHIT_1, BOSS_LEFT_GETHIT_2,
	BOSS_RIGHT_GETHIT_1, BOSS_RIGHT_GETHIT_2,
	BOSS_LEFT_GETHIT_3, BOSS_LEFT_ELBOW,
	BOSS_RIGHT_GETHIT_3, BOSS_RIGHT_ELBOW,
	BOSS_LEFT_DIE_END, BOSS_LEFT_DIZZY,
	BOSS_RIGHT_DIE_END, BOSS_RIGHT_DIZZY,
	BOSS_LEFT_GROUNDHIT,
	BOSS_RIGHT_GROUNDHIT
};

enum PAHSE
{
	PAHSE_1,
	PAHSE_2,
	PAHSE_3,
	PAHSE_DEFEAT
};


class boss : public gameNode
{
private:
	struct attackInfo
	{
		int index;
		float plusY;
		float width;
		float height;
	};
	image* _boss;
	image* _bossMap;
	image* _bossShadow;
	image* _bossHPImage;
	kyoko* _player;
	RECT _rcBoss;
	RECT _rcBossShadow;
	RECT _rcNear;
	RECT _rcFar;
	RECT _rcMiddle;
	RECT _rcBossAttack;


	animation* _bossMotion;
	BOSSDIRECTION _bossDirection;
	PAHSE _pahse;
	bossHPBar* _bossHPBar;
	map<BOSSDIRECTION, attackInfo> _mAttackInfo;
	float _x, _y, _x2, _y2;
	float _distance;
	float _angle, _angle2;
	float _speed;
	float _jumpPower;
	float _gravity;
	int _count, _count2, _count3;
	int _attackCount;
	int _index;
	int _rnd;
	int _randomAttack;
	int _currentFrameX, _currentFrameY;
	float _bossHP, _maxHP;
	float _elapsedTime;
	bool _isJump;
	bool _isAttack;
	bool _isAttacked;
	bool _isTackle;
	bool _isJumping;
	bool _isGetUp;
	bool _isDizzy;
	bool _isRoar;
	bool _isAlive;
	int _leftAttackedCount;
	int _rightAttackedCount;

public:
	boss() {};
	~boss() {};

	virtual HRESULT init();
	virtual void release();	//메모리 해제 함수
	virtual void update();//연산 전용
	virtual void render();	//그리기 전용
	void render(POINT camera);
	void move();
	void pahse();




	void setKyokoAddressLink(kyoko* kyoko) { _player = kyoko; }
	void hitDamage(float damage);

	void setImage();
	void setKeyAnimation();
	void jumpUp();
	void tackle();
	void leftAttackedMotion();
	void rightAttackedMotion();
	void leftDizzy();
	void rightDizzy();





	static void setRightIdle(void* obj);
	static void setLeftIdle(void * obj);
	static void leftAttackted(void * obj);
	static void rightAttackted(void * obj);
	static void setLeftDizzy(void * obj);
	static void setRightDizzy(void * obj);

	static void setLeftDieEnd(void * obj);
	static void setRightDieEnd(void * obj);




	//공격 상태 및 공격 프레임에 따른 정보 초기화
	virtual void setAttackInfo();
	virtual void setAttackRect(BOSSDIRECTION direction);
	float getBossPointX() { return _x; }
	float getBossPointY() { return _y; }
	inline RECT getBossRect() { return _rcBoss; }
	inline RECT getBossAttackRect() { return _rcBossAttack; }
};

