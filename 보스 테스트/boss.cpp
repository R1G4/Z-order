#include "stdafx.h"
#include "boss.h"



HRESULT boss::init()
{
	setImage();
	_bossState = BOSS_LEFT_IDLE;
	_pahse = PAHSE_1;
	//_aaaState = AAA_LEFT_IDLE;

	_currentFrameX = _currentFrameY = 0;
	_bossHP = _maxHP = 100;
	_count = _index = _count2 = 0;
	_count3 = _attackCount = 0;
	_jumpPower = _gravity = 0;
	_speed = 1.5;
	_angle = PI / 2;
	_angle2 = PI / 2;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;


	_boss->setX(_x);
	_boss->setY(_y);
	_bossShadow->setX(_x);
	_bossShadow->setY(_y + 180);

	_aaa->setX(WINSIZEX / 2 - 500);		//image _aaa, _rcAAA는 플레이어 대신해서 충돌테스트 하려고 만든거. 삭제해도됌
	_aaa->setY(WINSIZEY / 2 - 100);
	_rcAAA = RectMake(_aaa->getX(), _aaa->getY(), _aaa->getFrameWidth(), _aaa->getFrameHeight());

	_playerX = 200;
	_playerY = 200;

	_rcBoss = RectMakeCenter(_x, _y, _boss->getFrameWidth(), _boss->getFrameHeight());
	_rcBossShadow = RectMakeCenter(_x, _y, _bossShadow->getWidth(), _bossShadow->getHeight());
	_rcNear = RectMakeCenter(_boss->getX(), _boss->getY(), 600, 400);
	_rcMiddle = RectMakeCenter(_boss->getX(), _boss->getY(), 800, 500);
	_rcFar = RectMakeCenter(_boss->getX(), _boss->getY(), 1000, 600);
	_rcPlayer = RectMakeCenter(_playerX, _playerY, 200, 200);
	_rcAttack = RectMake(0, 0, 0, 0);
	_rcBossAttack = RectMake(0, 0, 0, 0);
	//IMAGEMANAGER->addFrameImage("boss_idle", "boss_idle.bmp", 0, 0, 3300, 600, 11, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss_tackle", "boss_tackle.bmp", 0, 0, 4500, 600, 15, 2, true, RGB(255, 0, 255));

	//int bossIdle[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	//KEYANIMANAGER->addArrayFrameAnimation("boss_idle2", "boss_idle", bossIdle, 11, 10, true);	//이름 잘보기

	/*int bossRightTackle[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("boss_Rirghttackle2", "boss_tackle", bossRightTackle, 15, 10, true);

	int bossLeftTackle[] = { 14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("boss_tackle2", "boss_tackle", bossLeftTackle, 15, 10, true);*/


	KEYANIMANAGER->addArrayFrameAnimation("boss_leftIdle", "boss_idle", 21, 11, 10, true,10);	//11프레임부터 21까지. fps 10 < 프레임 읽는 속도 
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightIdle", "boss_idle", 0, 10, 10, true, 10);	//0프레임부터 10까지. 프레임 루프 true or false, 버퍼 10은 뭔지모름
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftWalk", "boss_walk", 19, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightWalk", "boss_walk", 0, 9, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftSlap", "boss_slap", 27, 14, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightSlap", "boss_slap", 0, 13, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftElbow", "boss_elbow", 21, 11, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightElbow", "boss_elbow", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDie", "boss_die", 25, 13, 8, false, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDieEND", "boss_die", 13, 17, 5, true, 10);	//END는 일단 테스트용으로. 프레임 연결 방법생각해야함
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDie", "boss_die", 0, 12, 8, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDieEND", "boss_die", 8, 12, 5, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftPunch", "boss_punch", 53, 27, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightPunch", "boss_punch", 0, 26, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftTackle", "boss_tackle", 29, 15, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightTackle", "boss_tackle", 0, 14, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftDown", "boss_down", 43, 22, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightDown", "boss_down", 0, 21, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftJump", "boss_jump", 15, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightJump", "boss_jump", 0, 7, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftRoar", "boss_roar", 23, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightRoar", "boss_roar", 0, 11, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftTaunt", "boss_taunt", 45, 23, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightTaunt", "boss_taunt", 0, 22, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetUp", "boss_getUp", 29, 15, 5, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetUp", "boss_getUp", 0, 14, 5, true, 10);
	//KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit", "boss_getHit", 17, 9, 10, true);		//맞는모션 전체. 일단 1,2,3,타 맞는 모션 따로 해놔서 주석
	//KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit", "boss_getHit", 0, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_1", "boss_getHit_1", 3, 2, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_1", "boss_getHit_1", 0, 1, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_2", "boss_getHit_2", 3, 2, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_2", "boss_getHit_2", 0, 1, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_leftGetHit_3", "boss_getHit_3", 19, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("boss_rightGetHit_3", "boss_getHit_3", 0, 9, 10, true, 10);


	KEYANIMANAGER->addArrayFrameAnimation("aaa_leftIdle", "idle", 12, 23, 10, true, 10);	//11프레임부터 0까지.
	KEYANIMANAGER->addArrayFrameAnimation("aaa_rightIdle", "idle", 0, 11, 10, true, 10);	//0프레임부터 



	_bossMotion = KEYANIMANAGER->findAnimation("boss_leftIdle");


	_bossHPBar = new bossHPBar;
	_bossHPBar->init(WINSIZEX / 2, WINSIZEY / 2 + 300, 437, 35);
	_bossHPBar->setGauge(_bossHP, _maxHP);


	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	RECT _temp;
	KEYANIMANAGER->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		_rcPlayer.left -= 5, _rcPlayer.right -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	_rcPlayer.left += 5, _rcPlayer.right += 5;				
	if (KEYMANAGER->isStayKeyDown(VK_UP))		_rcPlayer.top -= 5, _rcPlayer.bottom -= 5;			//플레이어 대체 테스트용. 삭제해도 무방
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))		_rcPlayer.top += 5, _rcPlayer.bottom += 5;		

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		_aaa->setX(_aaa->getX() - 5), _rcAAA.left -= 5, _rcAAA.right -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	_aaa->setX(_aaa->getX() + 5), _rcAAA.left += 5, _rcAAA.right += 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP))		_aaa->setY(_aaa->getY() - 5), _rcAAA.top -= 5, _rcAAA.bottom -= 5;	//플레이어 대체 테스트용. 삭제해도 무방
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))		_aaa->setY(_aaa->getY() + 5), _rcAAA.top += 5, _rcAAA.bottom += 5;				


	if (KEYMANAGER->isOnceKeyDown('Q')) _rcAttack = RectMakeCenter(_rcAAA.right + 100, _rcAAA.bottom - 25, 150, 100);	//보스 맞았을때 테스트용. 

	if (KEYMANAGER->isOnceKeyUp('Q')) _rcAttack = RectMakeCenter(0, 0, 0, 0);		//보스 맞았을때 테스트용. 

	switch (_bossState)
	{
	case BOSS_LEFT_IDLE:_boss = IMAGEMANAGER->findImage("boss_idle"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftIdle"); _bossMotion->resume(); break;
	case BOSS_RIGHT_IDLE:_boss = IMAGEMANAGER->findImage("boss_idle"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightIdle"); _bossMotion->resume(); break;
	case BOSS_RIGHT_TACKLE:_boss = IMAGEMANAGER->findImage("boss_tackle"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightTackle"); _bossMotion->resume(); break;
	case BOSS_LEFT_TACKLE:_boss = IMAGEMANAGER->findImage("boss_tackle"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftTackle"); _bossMotion->resume(); break;
	case BOSS_LEFT_WALK:_boss = IMAGEMANAGER->findImage("boss_walk"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftWalk"); _bossMotion->resume(); break;
	case BOSS_RIGHT_WALK:_boss = IMAGEMANAGER->findImage("boss_walk"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightWalk"); _bossMotion->resume(); break;
	case BOSS_LEFT_SLAP:_boss = IMAGEMANAGER->findImage("boss_slap"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftSlap"); _bossMotion->resume(); break;
	case BOSS_RIGHT_SLAP:_boss = IMAGEMANAGER->findImage("boss_slap"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightSlap"); _bossMotion->resume(); break;
	case BOSS_LEFT_ELBOW:_boss = IMAGEMANAGER->findImage("boss_elbow"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftElbow"); _bossMotion->resume(); break;
	case BOSS_RIGHT_ELBOW:_boss = IMAGEMANAGER->findImage("boss_elbow"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightElbow"); _bossMotion->resume(); break;
	case BOSS_LEFT_PUNCH:_boss = IMAGEMANAGER->findImage("boss_punch"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftPunch"); _bossMotion->resume(); break;
	case BOSS_RIGHT_PUNCH:_boss = IMAGEMANAGER->findImage("boss_punch"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightPunch"); _bossMotion->resume(); break;
	case BOSS_LEFT_DIE:_boss = IMAGEMANAGER->findImage("boss_die"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftDie"); _bossMotion->resume(); break;
	case BOSS_LEFT_DIE_END:_boss = IMAGEMANAGER->findImage("boss_die"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftDieEND"); _bossMotion->resume(); break;
	case BOSS_RIGHT_DIE:_boss = IMAGEMANAGER->findImage("boss_die"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightDie"); _bossMotion->resume(); break;
	case BOSS_RIGHT_DIE_END:_boss = IMAGEMANAGER->findImage("boss_die"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightDieEND"); _bossMotion->resume(); break;
	case BOSS_LEFT_DOWN:_boss = IMAGEMANAGER->findImage("boss_down"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftDown"); _bossMotion->resume(); break;
	case BOSS_RIGHT_DOWN:_boss = IMAGEMANAGER->findImage("boss_down"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightDown"); _bossMotion->resume(); break;
	case BOSS_LEFT_GETUP:_boss = IMAGEMANAGER->findImage("boss_getUp"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetUp"); _bossMotion->resume(); break;
	case BOSS_RIGHT_GETUP:_boss = IMAGEMANAGER->findImage("boss_getUp"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetUp"); _bossMotion->resume(); break;
	case BOSS_LEFT_JUMP:_boss = IMAGEMANAGER->findImage("boss_jump"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftJump"); _bossMotion->resume(); break;
	case BOSS_RIGHT_JUMP:_boss = IMAGEMANAGER->findImage("boss_jump"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightJump"); _bossMotion->resume(); break;
	case BOSS_LEFT_ROAR:_boss = IMAGEMANAGER->findImage("boss_roar"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftRoar"); _bossMotion->resume(); break;
	case BOSS_RIGHT_ROAR:_boss = IMAGEMANAGER->findImage("boss_roar"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightRoar"); _bossMotion->resume(); break;
	case BOSS_LEFT_TAUNT:_boss = IMAGEMANAGER->findImage("boss_taunt"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftTaunt"); _bossMotion->resume(); break;
	case BOSS_RIGHT_TAUNT:_boss = IMAGEMANAGER->findImage("boss_taunt"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightTaunt"); _bossMotion->resume(); break;
	case BOSS_LEFT_GETHIT:_boss = IMAGEMANAGER->findImage("boss_getHit"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit"); _bossMotion->resume(); break;
	case BOSS_RIGHT_GETHIT:_boss = IMAGEMANAGER->findImage("boss_getHit"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit"); _bossMotion->resume(); break;
	case BOSS_LEFT_GETHIT_1:_boss = IMAGEMANAGER->findImage("boss_getHit_1"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_1"); _bossMotion->resume(); break;
	case BOSS_RIGHT_GETHIT_1:_boss = IMAGEMANAGER->findImage("boss_getHit_1"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_1"); _bossMotion->resume(); break;
	case BOSS_LEFT_GETHIT_2:_boss = IMAGEMANAGER->findImage("boss_getHit_2"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_2"); _bossMotion->resume(); break;
	case BOSS_RIGHT_GETHIT_2:_boss = IMAGEMANAGER->findImage("boss_getHit_2"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_2"); _bossMotion->resume(); break;
	case BOSS_LEFT_GETHIT_3:_boss = IMAGEMANAGER->findImage("boss_getHit_3"); _bossMotion = KEYANIMANAGER->findAnimation("boss_leftGetHit_3"); _bossMotion->resume(); break;
	case BOSS_RIGHT_GETHIT_3:_boss = IMAGEMANAGER->findImage("boss_getHit_3"); _bossMotion = KEYANIMANAGER->findAnimation("boss_rightGetHit_3"); _bossMotion->resume(); break;

	}

	switch (_pahse)
	{
	
	case PAHSE_1:

		if (_aaa->getCenterX() < _x && (_bossState == BOSS_LEFT_IDLE || _bossState == BOSS_RIGHT_IDLE
			|| _bossState == BOSS_LEFT_WALK || _bossState == BOSS_RIGHT_WALK || _bossState == BOSS_LEFT_GETUP || _bossState == BOSS_RIGHT_GETUP || BOSS_LEFT_SLAP))
		{
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
			_bossState = BOSS_LEFT_WALK;
			
			//if ((_rcAAA.bottom - _rcAAA.top) / 2 >= _rcBoss.top && (_rcAAA.bottom - _rcAAA.top) / 2 <= _rcBoss.bottom )
			if (_rcAAA.top >= _rcBoss.top && _rcAAA.bottom <= _rcBoss.bottom && _rcAAA.right >= _rcBoss.left)
			{
				if (IntersectRect(&_temp, &_rcAAA, &_rcBoss) )
				{
					_speed = 0;
					_rcBossAttack = RectMakeCenter(_rcBoss.left - 50, _rcBoss.bottom - 150, 100, 100);
					_bossState = BOSS_LEFT_ELBOW;

					if (IntersectRect(&_temp, &_rcAAA, &_rcBossAttack))
					{
						//_bossState = BOSS_LEFT_TAUNT;
						_bossMotion->isPlay() == false;
						_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
					}
					else
					{
						_count2++;
						if (_count2 % 2 == 0)
						{
							_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
						}
					}

					//_count2 = 0;
				}
				else _speed = 1.5f;	
			}
			else _speed = 1.5f;

			//if (_bossHP < 0)		//보스잡았을때 왼쪽인지 오른쪽인지 상태정의해서 다시하기
			//{
			//	_speed = 0;
			//	_bossState = BOSS_LEFT_DIE;

			//	if (_bossMotion->isPlay() == false)
			//	{
			//		_bossState = BOSS_LEFT_DIE_END;
			//		_bossMotion->pause();
			//	}
			//	else _bossMotion->resume();

			//}
		}

		if (_aaa->getCenterX() > _x && (_bossState == BOSS_LEFT_IDLE || _bossState == BOSS_RIGHT_IDLE
			|| _bossState == BOSS_LEFT_WALK || _bossState == BOSS_RIGHT_WALK || _bossState == BOSS_LEFT_GETUP || _bossState == BOSS_RIGHT_GETUP
			|| _bossState == BOSS_LEFT_ELBOW || _bossState == BOSS_RIGHT_SLAP))
		{
			_bossState = BOSS_RIGHT_WALK;
			_x += cosf(_angle2) * _speed;
			_y += -sinf(_angle2) * _speed;


			//if ((_rcAAA.bottom - _rcAAA.top) / 2 >= _rcBoss.top && (_rcAAA.bottom - _rcAAA.top) / 2 <= _rcBoss.bottom )
			if (_rcAAA.top >= _rcBoss.top && _rcAAA.bottom <= _rcBoss.bottom && _rcAAA.left <= _rcBoss.right)
			{
				if (IntersectRect(&_temp, &_rcAAA, &_rcBoss))
				{
					_speed = 0;
					_bossState = BOSS_RIGHT_SLAP;
					_rcBossAttack = RectMakeCenter(_rcBoss.right + 50, _rcBoss.bottom - 150, 100, 100);
					if (IntersectRect(&_temp, &_rcAAA, &_rcBossAttack))
					{

						_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
					}
					else
					{
						_count3++;
						if (_count3 % 2 == 0)
						{
							_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
						}
					}
					_count3 = 0;
				}
				else _speed = 1.5f;
			}
			else _speed = 1.5f;
		}
		
	case PAHSE_2:
		_bossHP <= 70 && _bossHP >= 30;
	case PAHSE_3:
		_bossHP <= 30;
	default:
		break;
	}

	
	

	if (IntersectRect(&_temp, &_rcAttack, &_rcBoss))
	{
		_jumpPower = 5;
		_gravity = 0.4f;
		if(_bossMotion->isPlay())	_bossState = BOSS_LEFT_GETHIT_3;
		hitDamage(1);
	}

	//_y -= _jumpPower;					//맞았을때 공중에 뜨게 해야하는데 아직 하는중					
	//_jumpPower -= _gravity;

	//if (_rcBoss.bottom <= _rcAAA.bottom)
	//{
	//	_jumpPower = 0;
	//	/*if (_rcBoss.bottom <= _rcPlayer.bottom)
	//	{
	//		_y += 3;
	//	}*/
	//}
	_rcBoss = RectMakeCenter(_x, _y, _boss->getFrameWidth(), _boss->getFrameHeight());
	_rcBossShadow = RectMakeCenter(_x, _y + 180, _bossShadow->getWidth(), _bossShadow->getHeight());


	//다운이나 맞는상태가 아닐때 아래 식 써주기.  << getAngle로 바꿔서 일단 보류 원거리공격 할때 쓸수도있음

	//if (IntersectRect(&_temp, &_rcAAA, &_rcFar))
	//{
	//	if (_rcAAA.right <= _rcBoss.left)
	//	{
	//		_bossState = BOSS_LEFT_PUNCH;
	//		//_aaaState = AAA_LEFT_IDLE;
	//		//_x += -BOSSSPEED - 2;
	//		_rcBoss.left += -BOSSSPEED - 2;		//BOSSSPEED가 1.5인데 -2를 해주면 양수이기 때문에 좌측으로 안감. +=해주고 -1.5 -2 해줌
	//		_rcBoss.right += -BOSSSPEED - 2;
	//		//OffsetRect(&_rcBoss, -BOSSSPEED - 2, 0);
	//		_rcNear.left += -BOSSSPEED - 2;
	//		_rcNear.right += -BOSSSPEED - 2;
	//		_rcFar.left += -BOSSSPEED - 2;
	//		_rcFar.right += -BOSSSPEED - 2;
	//		_rcMiddle.left += -BOSSSPEED - 2;
	//		_rcMiddle.right += -BOSSSPEED - 2;
	//		if (IntersectRect(&_temp, &_rcAAA, &_rcBoss)) _bossState = BOSS_LEFT_TAUNT;
	//	}
	//	if (_rcAAA.left >= _rcBoss.right)
	//	{
	//		_bossState = BOSS_RIGHT_PUNCH;
	//		//_aaaState = AAA_RIGHT_IDLE;
	//		//_x += BOSSSPEED + 2;
	//		_rcBoss.left += BOSSSPEED + 2;
	//		_rcBoss.right += BOSSSPEED + 2;
	//		_rcNear.left += BOSSSPEED + 2;
	//		_rcNear.right += BOSSSPEED + 2;
	//		_rcFar.left += BOSSSPEED + 2;
	//		_rcFar.right += BOSSSPEED + 2;
	//		_rcMiddle.left += BOSSSPEED + 2;
	//		_rcMiddle.right += BOSSSPEED + 2;
	//		if (IntersectRect(&_temp, &_rcAAA, &_rcBoss)) _bossState = BOSS_RIGHT_TAUNT;
	//	}
	//	if (_rcAAA.bottom <= _rcBoss.top)
	//	{
	//		//_y -= BOSSSPEED;
	//		_rcBoss.top -= 1.5;
	//		_rcBoss.bottom -= 1.5;
	//		_rcNear.top -= 1.5;
	//		_rcNear.bottom -= 1.5;
	//		_rcFar.top -= 1.5;
	//		_rcFar.bottom -= 1.5;
	//		_rcMiddle.top -= BOSSSPEED;
	//		_rcMiddle.bottom -= BOSSSPEED;
	//	}
	//	if (_rcAAA.top >= _rcBoss.bottom)
	//	{
	//		//_y += BOSSSPEED;
	//		_rcBoss.top += 1.5;
	//		_rcBoss.bottom += 1.5;
	//		_rcNear.top += 1.5;
	//		_rcNear.bottom += 1.5;
	//		_rcFar.top += 1.5;
	//		_rcFar.bottom += 1.5;
	//		_rcMiddle.top += BOSSSPEED;
	//		_rcMiddle.bottom += BOSSSPEED;
	//	}

	//	//_rcBoss = RectMakeCenter(_x, _y, _boss->getFrameWidth(), _boss->getFrameHeight());
	//}

	////////////////////////////////보스이동, 공격 임시 저장/////////////////////////////////////
	_distance = getDistance(_x, _y, _aaa->getCenterX() , _aaa->getCenterY());
	_angle = getAngle(_x, _y, _aaa->getCenterX() + 200, _aaa->getCenterY() - 30);
	_angle2 = getAngle(_x, _y, _aaa->getCenterX() - 200, _aaa->getCenterY() - 30);


		//if (_aaa->getCenterX() < _x && (_bossState == BOSS_LEFT_IDLE || _bossState == BOSS_RIGHT_IDLE
		//	|| _bossState == BOSS_LEFT_WALK || _bossState == BOSS_RIGHT_WALK || _bossState == BOSS_LEFT_GETUP || _bossState == BOSS_RIGHT_GETUP || BOSS_LEFT_SLAP))
		//{
		//	_bossState = BOSS_LEFT_WALK;
		//	_x += cosf(_angle) * _speed;
		//	_y += -sinf(_angle) * _speed;
		//	

		//	//if ((_rcAAA.bottom - _rcAAA.top) / 2 >= _rcBoss.top && (_rcAAA.bottom - _rcAAA.top) / 2 <= _rcBoss.bottom )
		//	if(_rcAAA.top >= _rcBoss.top && _rcAAA.bottom <= _rcBoss.bottom )
		//	{
		//		if (IntersectRect(&_temp, &_rcAAA, &_rcBoss) /*&& _rcBoss.bottom <= _rcAAA.bottom*/)
		//		{
		//			_speed = 0;
		//			_rcBossAttack = RectMakeCenter(_rcBoss.left - 50, _rcBoss.bottom - 150, 100, 100);
		//			_bossState = BOSS_LEFT_ELBOW;

		//			if (IntersectRect(&_temp, &_rcAAA, &_rcBossAttack))
		//			{
		//				//_bossState = BOSS_LEFT_TAUNT;
		//				_bossMotion->isPlay() == false;
		//				_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
		//			}
		//			else
		//			{
		//				_count2++;
		//				if (_count2 % 2 == 0)
		//				{
		//					_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
		//				}
		//			}
		//			
		//			//_count2 = 0;
		//		}
		//		else
		//		{
		//			//_x += cosf(_angle) * _speed;
		//			//_y += -sinf(_angle) * _speed;
		//			_speed = 1.5f;
		//			
		//		}
		//	}
		//	
		//	if (_bossHP <= 0)
		//	{
		//		_speed = 0;
		//		_bossState = BOSS_LEFT_DIE;

		//		if (_bossMotion->isPlay() == false)
		//		{
		//			_bossState = BOSS_LEFT_DIE_END;
		//			_bossMotion->pause();
		//		}
		//		else _bossMotion->resume();

		//	}
		//}

		//if (_aaa->getCenterX() > _x && (_bossState == BOSS_LEFT_IDLE || _bossState == BOSS_RIGHT_IDLE 
		//	|| _bossState == BOSS_LEFT_WALK || _bossState == BOSS_RIGHT_WALK || _bossState == BOSS_LEFT_GETUP || _bossState == BOSS_RIGHT_GETUP
		//	|| _bossState == BOSS_LEFT_ELBOW || _bossState == BOSS_RIGHT_SLAP))
		//{
		//	_bossState = BOSS_RIGHT_WALK;
		//	_x += cosf(_angle2) * _speed;
		//	_y += -sinf(_angle2) * _speed;

		//	if (IntersectRect(&_temp, &_rcAAA, &_rcBoss))
		//	{
		//		_speed = 0;
		//		_bossState = BOSS_RIGHT_SLAP;
		//		_rcBossAttack = RectMakeCenter(_rcBoss.right + 50, _rcBoss.bottom - 150, 100, 100);
		//		if (IntersectRect(&_temp, &_rcAAA, &_rcBossAttack))
		//		{
		//			_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
		//		}
		//		else
		//		{
		//			_count3++;
		//			if (_count3 % 2 == 0)
		//			{
		//				_rcBossAttack = RectMakeCenter(0, 0, 0, 0);
		//			}
		//		}
		//		_count3 = 0;
		//	}
		//	else _speed = 1.5f;

		//	if (_bossHP <= 0)
		//	{
		//		_speed = 0;
		//		_bossState = BOSS_RIGHT_DIE;

		//		if (_bossMotion->isPlay() == false)
		//		{
		//			_bossState = BOSS_RIGHT_DIE_END;
		//			_bossMotion->pause();
		//		}
		//		else _bossMotion->resume();

		//	}
		//}


if (_bossHP < 70 && _bossHP > 30)
{
	_pahse = PAHSE_2;
}
if (_bossHP < 30 && _bossHP > 1)
{
	_pahse = PAHSE_3;
}
if (_bossHP <= 0)		//보스 잡았을때 좌우측, 모션 다시확인해야함
{
	_speed = 0;
	_bossState = BOSS_LEFT_DIE;

	if (_bossMotion->isPlay() == false)
	{
		_bossState = BOSS_LEFT_DIE_END;
		//_bossMotion->pause();
	}
	else _bossState = BOSS_LEFT_DIE_END; //_bossMotion->resume();
}

	_bossHPBar->setX(WINSIZEX / 2 - 250);
	_bossHPBar->setY(WINSIZEY / 2 + 300);
	_bossHPBar->setGauge(_bossHP, _maxHP);
	_bossHPBar->update();
}

void boss::render()
{
	_bossMap->render(getMemDC(), 0, 0);
	_bossHPImage->render(getMemDC(), WINSIZEX / 2 - 265, WINSIZEY / 2 + 285);
	//Rectangle(getMemDC(), _rcFar);
	//Rectangle(getMemDC(), _rcMiddle);
	//Rectangle(getMemDC(), _rcNear);
	//Rectangle(getMemDC(), _rcPlayer);
	Rectangle(getMemDC(), _rcBoss);
	Rectangle(getMemDC(), _rcAAA);
	Rectangle(getMemDC(), _rcAttack);
	Rectangle(getMemDC(), _rcBossAttack);

	_boss->aniRender(getMemDC(), _rcBoss.left, _rcBoss.top, _bossMotion);
	_bossShadow->render(getMemDC(), _rcBossShadow.left, _rcBossShadow.top);

	_aaa->frameRender(getMemDC(), _aaa->getX(), _aaa->getY());

	_bossHPBar->render();



}

void boss::hitDamage(float damage)
{
	_bossHP -= damage;
}

void boss::setImage()
{
	_boss = IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 0, 0, 3300, 600, 11, 2, true, RGB(255, 0, 255));
	_bossShadow = IMAGEMANAGER->addImage("boss_shadow", "image/boss/boss_shadow.bmp", 200, 70, true, RGB(255, 0, 255));
	_bossMap = IMAGEMANAGER->addImage("boss_map", "image/boss/boss_map.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_bossHPImage = IMAGEMANAGER->addImage("boss_HP", "image/boss/boss_HP.bmp", 560, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_tackle", "image/boss/boss_tackle.bmp", 0, 0, 4500, 600, 15, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss_die", "image/boss/boss_die.bmp", 0, 0, 3900, 600, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_die", "image/boss/boss_die5.bmp", 0, 0, 4576, 576, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_taunt", "image/boss/boss_taunt.bmp", 0, 0, 6900, 600, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_slap", "image/boss/boss_slap.bmp", 0, 0, 5278, 582, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_elbow", "image/boss/boss_elbow.bmp", 0, 0, 2915, 652, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_punch", "image/boss/boss_punch.bmp", 0, 0, 8100, 600, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_wupunch", "image/boss/boss_wupunch.bmp", 0, 0, 11880, 594, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_roar", "image/boss/boss_roar.bmp", 0, 0, 3600, 600, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_tackle", "image/boss/boss_tackle.bmp", 0, 0, 4500, 600, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 0, 0, 2110, 588, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_down", "image/boss/boss_down.bmp", 0, 0, 6600, 450, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jump", "image/boss/boss_jump.bmp", 0, 0, 2400, 660, 8, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss_getUp", "image/boss/boss_getUp.bmp", 0, 0, 4500, 600, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getUp", "image/boss/boss_getUp4.bmp", 0, 0, 4500, 600, 15, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boss_getHit", "image/boss/boss_getHit.bmp", 0, 0, 2700, 600, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit", "image/boss/boss_getHit_1.bmp", 0, 0, 540, 540, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_1", "image/boss/boss_getHit_1.bmp", 0, 0, 540, 540, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_2", "image/boss/boss_getHit_2.bmp", 0, 0, 560, 560, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_getHit_3", "image/boss/boss_getHit_3.bmp", 0, 0, 2700, 540, 10, 2, true, RGB(255, 0, 255));


	_aaa = IMAGEMANAGER->addFrameImage("idle", "idle2.bmp", 0, 0, 2400, 400, 12, 2, true, RGB(255, 0, 255));


}




