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
	KYOKODIRECTION_RIGHT_ATTACK_DASH,		KYOKODIRECTION_LEFT_ATTACK_DASH,
	KYOKODIRECTION_RIGHT_ATTACK_JUMP,		KYOKODIRECTION_LEFT_ATTACK_JUMP,
	KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK,	KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK,
	KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN,	KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN,
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
	image* _deadCamera;

	int _z_count;				// ���� ���� ī��Ʈ
	int _r_count;				// �޸���� ī��Ʈ
	int _maha_count;			// ����ű ������ī��Ʈ
	int _frame_count;			// ����
	int _attacked_count;		// �ǰ� ī��Ʈ
	int	_currentFrameX;			// ������ ��ȣ X
	int _count_dead;

	string _attack_sound;		// ���� ������ Ÿ������ ���� ����

	float _x, _y;				// �׸��� ��ġ
	float _i_x, _i_y;			// �̹��� ��ġ
	float _speed;

	RECT _rc;					// �浹�� ��Ʈ
	RECT _image_rc;				// ������ ��Ʈ
	RECT _shadow_rc;			// �׸��ڿ� ��Ʈ (z-order)
	RECT _attack_rc;			// ���ݿ� ��Ʈ
	RECT _m_gauge_rc;			// ����ű ������ ��Ʈ

	animation* _kyokoMotion;

	jump* _jump;
	jump* _shadow_jump;

	bool _isJump;				// ������ bool
	bool _isMoving;				// �̵��� bool
	bool _isAttack;				// ���ݿ� bool
	bool _isMahaKick;			// ������ ä���� bool
	bool _isRunning;			// �޸���� bool
	bool _isCollision;			// �ȼ��浹�� bool
	bool _isNextAttack;			// �������ݿ� bool
	bool _isAttacked;			// �ǰݱ��п� bool
	bool _isStartMotionAttaced;	// �ǰݱ��п� bool2
	bool _isRight;				// �ǰݱ��п� bool3
	bool _isDead;				// ������п� bool
	bool _isStartMotionDead;	// ������п� bool2
	bool _getDead;				// ������Ͽ� bool
public:
	kyoko() {};
	~kyoko() {};

	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void deadRender();

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
	void attackedMotion();
	void gameOverMotion();

	KYOKODIRECTION getKyokoDirection() { return _kyokoDirection; }
	void setKyokoDirection(KYOKODIRECTION direction) { _kyokoDirection = direction; }

	void setJumpSpeed(float speed) { _speed = speed; }
	float getJumpSpeed() { return _speed; }

	animation* getKyokoMotion() { return _kyokoMotion; }
	void setKyokoMotion(animation* ani) { _kyokoMotion = ani; }

	RECT getShadow() { return _shadow_rc; }
	RECT getRect() { return _rc; }
	RECT getImageRect() { return _image_rc; }
	RECT getAttackRect() { return _attack_rc; }

	POINT getKyokoPoint() {
		POINT _point;
		_point.x = _x;
		_point.y = _y;
		return _point;
	}
	void setKyokoPoint(float x, float y)
	{
		_x = x;
		_y = y;
	}

	BOOL getIsJump() { return _isJump; }
	BOOL getIsAttack() { return _isAttack; }

	RECT& getDebugShadow() { return _shadow_rc; }
	RECT& getDebugRect() { return _rc; }
	RECT& getDebugAttack() { return _attack_rc; }

	int getMaha() { return _maha_count; }

	void setNoSpeed(bool isCollision) { _isCollision = isCollision; }

	void setHit(bool isAttacked) { _isAttacked = isAttacked; }
	BOOL getHit() { return _isAttacked; }
	void setHitRight(bool isRight) { _isRight = isRight; }

	string getAttackSound() { return _attack_sound; }

	BOOL getDeadLastFrame() { return _getDead; }
};

