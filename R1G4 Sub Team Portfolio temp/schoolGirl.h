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

	float _x, _y;			//���ʹ� ��ǥ
	float _angle;			//���ʹ� �̵� ����
	image* _schoolGirlImg;	//���ʹ� �̹���
	image* _shadowImg;		//�׸��� �̹���
	RECT _schoolGirlRc;		//���ʹ� ��Ʈ
	RECT _shadowRc;			//�׸��� ��Ʈ
	animation* _motion;		//���õ� �ִϸ��̼�
	DIRECTION _direction;	//���ʹ� ����
	STATE _state;			//���ʹ� ����
	bool _isAction;			//Ư�� ���ʹ� ���� ���� �� ���� ����
	bool _isAttack;			//���� ����
	bool _isRunning;		//�޸��� ����
	bool _isFollow;			//���� ����
	int _questTimer;		//Ž�� �� �޽� ����
	int _questMin;			//�ּ� Ž�� ���� ����
	enemyAttack* _enemyAttack;	//���ʹ� ���� Ŭ����

	//���ʹ� �̹���
	image* imgIdle;
	image* imgWalk;
	image* imgRun;
	image* imgBlock;
	image* imgAttack;
	image* imgCombo_attack_1;
	image* imgCombo_attack_2;
	image* imgCombo_attack_3;
	image* imgHit;
	image* imgDownup;
	image* imgKnockdown;
	image* imgDazed;
	image* imgJump;
	image* imgTaunt;

	//���ʹ� �ִϸ��̼�
	animation* aniLeftIdle;
	animation* aniLeftWalk;
	animation* aniLeftRun;
	animation* aniLeftBlock;
	animation* aniLeftAttack;
	animation* aniLeftCombo_attack_1;
	animation* aniLeftCombo_attack_2;
	animation* aniLeftCombo_attack_3;
	animation* aniLeftHit;
	animation* aniLeftDownup;
	animation* aniLeftKnockdown;
	animation* aniLeftDazed;
	animation* aniLeftJump;
	animation* aniLeftTaunt;

	animation* aniRightIdle;
	animation* aniRightWalk;
	animation* aniRightRun;
	animation* aniRightBlock;
	animation* aniRightAttack;
	animation* aniRightCombo_attack_1;
	animation* aniRightCombo_attack_2;
	animation* aniRightCombo_attack_3;
	animation* aniRightHit;
	animation* aniRightDownup;
	animation* aniRightKnockdown;
	animation* aniRightDazed;
	animation* aniRightJump;
	animation* aniRightTaunt;
public:
	schoolGirl();
	~schoolGirl();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void move();
	virtual void state();
	virtual void update();
	//virtual void render();
	virtual void render(POINT camera);
	//���ʹ� �ʱ� �̹��� �� �ִϸ��̼� ����
	virtual void addFrame();

	//Ư�� ���ʹ� ���� �� ���� �������� ���� üũ
	static void ActionCheck(void * obj);

	//�ϴ� �Ⱦ�
	static void RunningCheck(void * obj);

	//�� �� �ϴ� �߰��� ���� ����
	image* getImage() { return _schoolGirlImg; }
	void setImage(image* img) { _schoolGirlImg = img; }

	RECT getRect() { return _schoolGirlRc; }

	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }
};