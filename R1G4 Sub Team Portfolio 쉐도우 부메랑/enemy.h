#pragma once
#include "gameNode.h"
#include "enemyAttack.h"

class kyoko;
class enemy : public gameNode
{
protected:
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

	kyoko* _kyoko;
	float _x, _y;			//에너미 좌표
	float _angle;			//에너미 이동 각도
	image* _enemyImg;		//에너미 이미지
	image* _shadowImg;		//그림자 이미지
	RECT _enemyRc;			//에너미 렉트
	RECT _shadowRc;			//그림자 렉트
	animation* _motion;		//선택된 애니메이션
	DIRECTION _direction;	//에너미 방향
	STATE _state;			//에너미 상태
	bool _isAction;			//특정 에너미 도발 종료 후 패턴 시작
	bool _isAttack;			//공격 구분
	bool _isRunning;		//달리기 구분
	bool _isFollow;			//추적 구분
	int _questTimer;		//탐색 및 휴식 난수
	int _questMin;			//최소 탐색 간격 난수
	enemyAttack* _enemyAttack;	//에너미 공격 클래스

		//에너미 이미지
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

	//에너미 애니메이션
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
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y, bool isTaunt = false, int direction = RND->getFromIntTo(0, 2));

	//virtual HRESULT init(float x, float y);
	void setKyokoAddressLink(kyoko* kyoko) { _kyoko = kyoko; }
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);

	//그 외 일단 추가한 겟터 셋터
	image* getImage() { return _enemyImg; }
	void setImage(image* img) { _enemyImg = img; }

	RECT getRect() { return _enemyRc; }

	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }
};
