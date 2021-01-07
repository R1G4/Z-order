#pragma once
#include "gameNode.h"
#include "fun.h"
#include "button.h"

#define SPEED 2.5f

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

enum KINDS
{
	GIRL = 0,
	BOY,
	MT,
	CHEERLEADER
};

class testScene : public gameNode
{
private:
	DIRECTION _direction;
	STATE _state;
	image* _image;
	float _x, _y;
	RECT _rc;
	animation* _motion;
	bool _isIdle;
	vector<string> _kindsName;
	KINDS _selectedKind;

public:
	testScene() {};
	~testScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void setRightIdle(void * obj);

	static void setLeftIdle(void * obj);

	void setIdleCehck(bool isIdle) { _isIdle = isIdle; }

	image* getImage() { return _image; }
	void setImage(image* image) { _image = image; }

	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }
};

