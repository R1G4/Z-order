#pragma once
#include "gameNode.h"
#include "jump.h"

#define KYOKOSPEED 5.0f


enum KYOKODIRECTION
{
	KYOKODIRECTION_RIGHT_IDLE,				KYOKODIRECTION_LEFT_IDLE,
	KYOKODIRECTION_RIGHT_WALK,				KYOKODIRECTION_LEFT_WALK,
	KYOKODIRECTION_RIGHT_RUN,				KYOKODIRECTION_LEFT_RUN,
	KYOKODIRECTION_RIGHT_JUMP,				KYOKODIRECTION_LEFT_JUMP,
	KYOKODIRECTION_RIGHT_JUMP_WALK,			KYOKODIRECTION_LEFT_JUMP_WALK,
	KYOKODIRECTION_RIGHT_JUMP_RUN,			KYOKODIRECTION_LEFT_JUMP_RUN,
	KYOKODIRECTION_RIGHT_JUMP_TOP,			KYOKODIRECTION_LEFT_JUMP_TOP,
	KYOKODIRECTION_RIGHT_JUMP_TOP_WALK,		KYOKODIRECTION_LEFT_JUMP_TOP_WALK,
	KYOKODIRECTION_RIGHT_JUMP_TOP_RUN,		KYOKODIRECTION_LEFT_JUMP_TOP_RUN,
	KYOKODIRECTION_RIGHT_JUMP_DOWN,			KYOKODIRECTION_LEFT_JUMP_DOWN,
	KYOKODIRECTION_RIGHT_JUMP_DOWN_WALK,	KYOKODIRECTION_LEFT_JUMP_DOWN_WALK,
	KYOKODIRECTION_RIGHT_JUMP_DOWN_RUN,		KYOKODIRECTION_LEFT_JUMP_DOWN_RUN,
	KYOKODIRECTION_RIGHT_ATTACK_1,			KYOKODIRECTION_LEFT_ATTACK_1,
	KYOKODIRECTION_RIGHT_ATTACK_2,			KYOKODIRECTION_LEFT_ATTACK_2,
	KYOKODIRECTION_RIGHT_ATTACK_3,			KYOKODIRECTION_LEFT_ATTACK_3,
	KYOKODIRECTION_RIGHT_ATTACK_STRONG,		KYOKODIRECTION_LEFT_ATTACK_STRONG,
	KYOKODIRECTION_RIGHT_MAHAKICK,			KYOKODIRECTION_LEFT_MAHAKICK,
	KYOKODIRECTION_RIGHT_ATTACKED_1,		KYOKODIRECTION_LEFT_ATTACKED_1,
	KYOKODIRECTION_RIGHT_ATTACKED_2,		KYOKODIRECTION_LEFT_ATTACKED_2,
	KYOKODIRECTION_RIGHT_DEAD,				KYOKODIRECTION_LEFT_DEAD
};

struct HPBAR : public gameNode
{
	int num;
	image* image;
};

class kyoko : public gameNode
{
private:
	KYOKODIRECTION _kyokoDirection;

	image* _image;
	image* _shadow;
	image* _hpUI;
	image* _mahaGauge;

	vector<HPBAR*> _hp;
	vector<HPBAR*>::iterator _ihp;

	int _z_count;				// 연속 공격 카운트
	int _r_count;				// 달리기용 카운트
	int _maha_count;			// 마하킥 게이지카운트
	float _x, _y;				// 그림자 위치
	float _i_x, _i_y;			// 이미지 위치
	float _speed;
	
	RECT _rc;					// 충돌용 렉트
	RECT _image_rc;				// 랜딩용 렉트
	RECT _shadow_rc;			// 그림자용 렉트 (z-order)
	RECT _m_gauge_rc;			// 마하킥 게이지 렉트
	
	RECT _black_rc[2];

	animation* _kyokoMotion;

	jump* _jump;
	jump* _shadow_jump;

	bool _isJump;				// 점프용 bool
	bool _isMoving;				// 이동용 bool
	bool _isAttack;				// 공격용 bool
	bool _isMahaKick;			// 게이지 채우기용 bool
	bool _isRunning;			// 달리기용 bool
public:
	kyoko() {};
	~kyoko() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);

	static void rightFire(void* obj);
	static void leftFire(void* obj);

	static void rightJump(void* obj);
	static void leftJump(void* obj);
	static void rightMoveJump(void* obj);
	static void leftMoveJump(void* obj);

	void addMotionAni();
	void moveMotion();
	void attackMotion();
	void jumpMotion();

	KYOKODIRECTION getKyokoDirection() { return _kyokoDirection; }
	void setKyokoDirection(KYOKODIRECTION direction) { _kyokoDirection = direction; }

	void setJumpSpeed(float speed) { _speed = speed; }
	float getJumpSpeed() { return _speed; }

	animation* getKyokoMotion() { return _kyokoMotion; }
	void setKyokoMotion(animation* ani) { _kyokoMotion = ani; }
	RECT getShadow() { return _shadow_rc; }
	RECT getRect() { return _rc; }
	POINT getKyokoPoint() {
		POINT _point;
		_point.x = _x;
		_point.y = _y;
		return _point;
	}
};

