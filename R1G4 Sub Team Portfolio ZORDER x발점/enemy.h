#pragma once
#include "gameNode.h"
#include "enemyAttack.h"
#include "effect.h"

class kyoko;
class enemy : public gameNode
{
public:
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

	enum DIRECTION
	{
		LEFT,
		RIGHT
	};
protected:
	struct attackInfo
	{
		int startIndex;
		int endIndex;
		float plusY;
		float width;
		float height;
		int damage;
		bool isTouch;
	};
	map<STATE, attackInfo> _mAttackInfo;
	multimap<STATE, attackInfo> _mmAttackInfo;
	kyoko* _kyoko;
	float _x, _y;			//���ʹ� ��ǥ
	float _angle;			//���ʹ� �̵� ����
	image* _enemyImg;		//���ʹ� �̹���
	image* _shadowImg;		//�׸��� �̹���
	RECT _rc;				//�浹�� ��Ʈ
	RECT _enemyRc;			//���ʹ� ��Ʈ
	RECT _shadowRc;			//�׸��� ��Ʈ
	RECT _attackRc;			//���ݿ� ��Ʈ
	animation* _motion;		//���õ� �ִϸ��̼�
	DIRECTION _direction;	//���ʹ� ����
	STATE _state;			//���ʹ� ����
	bool _isAction;			//Ư�� ���ʹ� ���� ���� �� ���� ����
	bool _isAttack;			//���� ����
	bool _isRunning;		//�޸��� ����
	bool _isFollow;			//���� ����
	bool _isCollision;
	int _questTimer;		//Ž�� �� �޽� ����
	int _questMin;			//�ּ� Ž�� ���� ����
	enemyAttack* _enemyAttack;	//���ʹ� ���� ���� Ŭ����

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

private:

public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));

	//virtual HRESULT init(float x, float y);
	void setKyokoAddressLink(kyoko* kyoko) { _kyoko = kyoko; }
	virtual void release();
	virtual void update();
	virtual void render();
	void effectPoint(DIRECTION direction);
	void effectStun(DIRECTION direction);;
	virtual void render(POINT camera);

	//�� �� �ϴ� �߰��� ���� ����

	//�̹���
	image* getImage() { return _enemyImg; }
	void setImage(image* img) { _enemyImg = img; }

	//��Ʈ
	RECT getRect() { return _rc; }
	RECT getEnemyRect() { return _enemyRc; }
	RECT getShadowRc() { return _shadowRc; }

	//����׿� ��Ʈ
	RECT& getDebugRect() { return _rc; }
	RECT& getDebugEnemyRect() { return _enemyRc; }
	RECT& getDebugShadowRc() { return _shadowRc; }
	RECT& getDebugAttackRc() { return _attackRc; }

	//����
	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	//����
	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	//�ִϸ��̼�
	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }

	//�浹����
	bool getCollision() { return _isCollision; }
	void setCollision(bool isCollision) { _isCollision = isCollision; }

	//��ǥ
	POINT getEnemyPoint()
	{
		POINT _point;
		_point.x = _x;
		_point.y = _y;
		return _point;
	}
	void setEnemyPoint(float x, float y)
	{
		_x = x;
		_y = y;
	}
};
