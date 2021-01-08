#pragma once
#include "enemy.h"
#include "enemyAttack.h"
#define ENEMYSPEED 1.8f;

class schoolGirl : public enemy
{
private:
	enum DIRECTION
	{
		LEFT,
		RIGHT
	};

	enum STATE
	{
		IDLE,
		WALK,
		RUN,
		BLOCK,
		ATTACK,
		COMBO_ATTACK_1,
		COMBO_ATTACK_2,
		COMBO_ATTACK_3,
		HIT,
		DOWNUP,
		KNOCKDOWN,
		DAZED,
		JUMP,
		TAUNT
	};

	struct attackType
	{
		STATE attackKind;
		int comboTimer;
	};

	float _x, _y;
	float _angle;
	image* _schoolGirlImg;
	image* _shadowImg;
	RECT _schoolGirlRc;
	RECT _shadowRc;		
	animation* _motion;
	DIRECTION _direction;
	STATE _state;
	bool _isAction;
	bool _isAttack;
	bool _isRunning;
	bool _isFollow;
	int _questInterval;
	int _questMin;
	enemyAttack* _enemyAttack;

public:
	schoolGirl();
	~schoolGirl();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void move();
	virtual void state();
	//static void MoveCheck(void * obj);
	/*static void setRightIdle(void * obj);
	static void setLeftIdle(void * obj);*/
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);
	virtual void addFrame();

	static void ActionCheck(void * obj);

	static void RunningCheck(void * obj);

	image* getImage() { return _schoolGirlImg; }
	void setImage(image* img) { _schoolGirlImg = img; }

	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }
};

