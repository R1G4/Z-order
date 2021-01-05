#pragma once
#include "gameNode.h"
#include "jump.h"

#define KYOKOSPEED 2.5f

enum KYOKODIRECTION
{
	KYOKODIRECTION_RIGHT_IDLE,				KYOKODIRECTION_LEFT_IDLE,
	KYOKODIRECTION_RIGHT_WALK,				KYOKODIRECTION_LEFT_WALK,
	KYOKODIRECTION_RIGHT_RUN,				KYOKODIRECTION_LEFT_RUN,
	KYOKODIRECTION_RIGHT_JUMP,				KYOKODIRECTION_LEFT_JUMP,
	KYOKODIRECTION_RIGHT_JUMP_MOVE,			KYOKODIRECTION_LEFT_JUMP_MOVE,
	KYOKODIRECTION_RIGHT_JUMP_TOP,			KYOKODIRECTION_LEFT_JUMP_TOP,
	KYOKODIRECTION_RIGHT_JUMP_TOP_MOVE,		KYOKODIRECTION_LEFT_JUMP_TOP_MOVE,
	KYOKODIRECTION_RIGHT_JUMP_DOWN,			KYOKODIRECTION_LEFT_JUMP_DOWN,
	KYOKODIRECTION_RIGHT_JUMP_DOWN_MOVE,	KYOKODIRECTION_LEFT_JUMP_DOWN_MOVE,
	KYOKODIRECTION_RIGHT_ATTACK_1,			KYOKODIRECTION_LEFT_ATTACK_1,
	KYOKODIRECTION_RIGHT_ATTACK_2,			KYOKODIRECTION_LEFT_ATTACK_2,
	KYOKODIRECTION_RIGHT_ATTACK_3,			KYOKODIRECTION_LEFT_ATTACK_3,
	KYOKODIRECTION_RIGHT_ATTACK_STRONG,		KYOKODIRECTION_LEFT_ATTACK_STRONG,
	KYOKODIRECTION_RIGHT_MAHAKICK,			KYOKODIRECTION_LEFT_MAHAKICK,
	KYOKODIRECTION_RIGHT_ATTACKED_1,		KYOKODIRECTION_LEFT_ATTACKED_1,
	KYOKODIRECTION_RIGHT_ATTACKED_2,		KYOKODIRECTION_LEFT_ATTACKED_2,
	KYOKODIRECTION_RIGHT_DEAD,				KYOKODIRECTION_LEFT_DEAD
};

class kyoko : public gameNode
{
private:
	KYOKODIRECTION _kyokoDirection;

	image* _image;

	float _x, _y;
	RECT _rc;					// 충돌용 렉트
	RECT _image_rc;				// 랜딩용 렉트
	animation* _kyokoMotion;

	jump* _jump;

public:
	kyoko() {};
	~kyoko() {};

	HRESULT init();
	void release();
	void update();
	void render();

	static void rightFire(void* obj);
	static void leftFire(void* obj);

	static void rightJump(void* obj);
	static void leftJump(void* obj);
	static void rightMoveJump(void* obj);
	static void leftMoveJump(void* obj);

	void addImage();
	void addMotionAni();
	void moveMotion();
	void attackMotion();
	void jumpMotion();

	KYOKODIRECTION getKyokoDirection() { return _kyokoDirection; }
	void setKyokoDirection(KYOKODIRECTION direction) { _kyokoDirection = direction; }

	animation* getKyokoMotion() { return _kyokoMotion; }
	void setKyokoMotion(animation* ani) { _kyokoMotion = ani; }
};

