#pragma once
#include "gameNode.h"
#include "enemyAttack.h"
#include "effect.h"

class kyoko;
class enemy : public gameNode
{
public:
	//에너미 상태
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
		TAUNT,
		DEAD,
		REMOVE
	};

	//에너미가 바라보는 방향
	enum DIRECTION
	{
		LEFT,
		RIGHT
	};
protected:

	//공격용 렉트 관련 구조체
	struct attackInfo
	{
		int index;		//공격 렉트가 생성 될 애니메이션 인덱스
		float plusY;	//이미지 크기가 달리지는 경우를 대비해 y축 보정 값
		float width;	//공격용 렉트 넓이
		float height;	//공격용 렉트 높이
	};

	map<STATE, attackInfo> _mAttackInfo;	//공격용 렉트 관련 정보를 담아둔 맵
	kyoko* _kyoko;			//플레이어
	image* _enemyImg;		//에너미 이미지
	image* _shadowImg;		//그림자 이미지
	RECT _rc;				//충돌용 렉트
	RECT _enemyRc;			//에너미 렉트
	RECT _shadowRc;			//그림자 렉트
	RECT _attackRc;			//공격용 렉트
	animation* _motion;		//선택된 애니메이션
	DIRECTION _direction;	//에너미 방향
	STATE _state;			//에너미 상태
	float _x, _y;			//에너미 좌표
	float _angle;			//에너미 이동 각도
	float _speed;			//에너미 이동 속도
	float _pushPower;		//밀린 힘
	float _pushDecrease;	//밀린 힘의 감소
	int _questTimer;		//탐색 및 휴식 난수
	int _questMin;			//최소 탐색 간격 난수
	int _hp;				//에너미 체력
	int _alphaInterval;		//투명도 간격
	int _alphaValue;		//투명도
	bool _isAction;			//특정 에너미 도발 종료 후 패턴 시작
	bool _isAttack;			//공격 구분
	bool _isRunning;		//달리기 구분
	bool _isFollow;			//추적 구분
	bool _isCollision;		//충돌 구분
	bool _isPush;
	bool _isBounce;
	enemyAttack* _enemyAttack;	//에너미 공격 패턴 클래스

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
	//LEFT
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

	//Right
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
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT camera);

	//플레이어의 주소를 받아온다.
	void setKyokoAddressLink(kyoko* kyoko) { _kyoko = kyoko; }

	//에너미 방어
	bool block(DIRECTION _direction);

	//에너미 머리 위에 느낌표 보여주기
	void effectPoint(DIRECTION direction);

	//에너미 머리 위에 스턴 상태 보여주기
	void effectStun(DIRECTION direction);;

	//에너미 피격 상태일때
	void hit(DIRECTION _direction);

	//에너미 피격으로 다운 상태일때
	void downup(DIRECTION _direction);

	//에너미 넉다운 상태일때
	void knockdown(DIRECTION _direction);

	//에너미 제거되기 직전 투명도 조절
	void setAlpha();

	//특정 에너미 도발 후 정상 패턴으로 복귀 체크
	static void actionCheck(void * obj);

	//왼쪽 스턴 상태 결정
	static void leftStun(void * obj);

	//오른쪽 스턴 상태 결정
	static void rightStun(void * obj);

	//에너미 죽은 상태
	static void  setDead(void * obj);


	//그 외 일단 추가한 겟터 셋터

	//이미지
	image* getImage() { return _enemyImg; }
	void setImage(image* img) { _enemyImg = img; }

	//렉트
	RECT getRect() { return _rc; }
	RECT getEnemyRect() { return _enemyRc; }
	RECT getShadowRc() { return _shadowRc; }

	//디버그용 렉트
	RECT& getDebugRect() { return _rc; }
	RECT& getDebugEnemyRect() { return _enemyRc; }
	RECT& getDebugShadowRc() { return _shadowRc; }
	RECT& getDebugAttackRc() { return _attackRc; }

	//방향
	DIRECTION getDirection() { return _direction; }
	void setDirection(DIRECTION direction) { _direction = direction; }

	//현재 상태
	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	//애니메이션
	animation* getMotion() { return _motion; }
	void setMotion(animation* motion) { _motion = motion; }

	//충돌여부
	bool getCollision() { return _isCollision; }
	void setCollision(bool isCollision) { _isCollision = isCollision; }

	//스턴 이미지와 애니메이션
	image* getImgDazed() { return imgDazed; }
	animation* getAniLeftDazed() { return aniLeftDazed; }
	animation* getAniRightDazed() { return aniRightDazed; }

	bool getPushCheck() { return _isPush; }
	void setBounce();

	//좌표
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
