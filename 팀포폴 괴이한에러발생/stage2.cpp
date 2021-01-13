#include "stdafx.h"
#include "stage2.h"
#include "kyoko.h"
#include "enemyManager.h"

HRESULT stage2::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);
	_opt->setSlot(saveSlot);

	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");
	
	//플레이어 위치 초기화
	_player->init();
	//스테이지에 따른 에너미 생성
	_em->setEnemy(2);
	//플레이어 주소 받아오기
	_em->setKyokoMemory(_player);

	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("좌기둥");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("우기둥");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();
	_opt->setEnemyAddressLink(_em);
	_opt->setKyokoAddressLink(_player);
	alpha = 255;
	return S_OK;
}

HRESULT stage2::init(int slot)
{
	saveSlot = slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);
	_opt->setSlot(saveSlot);
	SOUNDMANAGER->play("MainStage", _opt->getVolume());
	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");	

	//플레이어 위치 초기화
	_player->init();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage2);
	//스테이지에 따른 에너미 생성
	_em->setEnemy(2);
	//플레이어 주소 받아오기
	_em->setKyokoMemory(_player);

	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("좌기둥");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("우기둥");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();
	_door_rc = RectMake(1000, 300, 200, 200);
	alpha = 255;
	return S_OK;

}

void stage2::release()
{
}

void stage2::update()
{
	SOUNDMANAGER->setVolume(_opt->getVolume());
	_opt->update();
	UI->update();
	ItemCollision();
	pixelCollision();
	AttackCollision();
	_player->update();
	_em->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage2);
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &Lobj.rc))
	{
		alpha = 100;
	}
	else if (IntersectRect(&temp, &_player->getRect(), &Robj.rc))
	{
		alpha = 100;
	}
	else alpha = 255;
	changeScene();
}

void stage2::render()
{
	stage2->render(getMemDC(), 0, 0, camera);

	//아이템 랜더~
	for (int i = 0; i < _em->getVItem().size(); i++)
	{
		item* _item = _em->getVItem()[i];
		_item->render(camera);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage2Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), Lobj.rc, camera);
		Rectangle(getMemDC(), Robj.rc, camera);
		Rectangle(getMemDC(), _door_rc, camera);
		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			enemy* enemy = _em->getVEnemy()[i];
			//충돌용
			Rectangle(getMemDC(), enemy->getDebugRect(), camera);
			//그림자
			Rectangle(getMemDC(), enemy->getDebugShadowRc(), camera);
			//공격
			HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			Rectangle(getMemDC(), enemy->getDebugAttackRc(), camera);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(brush);

		}
	}
	zOrder();
	Lobj.img->alphaRender(getMemDC(), Lobj.x, Lobj.y, alpha, camera);
	Robj.img->alphaRender(getMemDC(), Robj.x, Robj.y, alpha, camera);
	UI->render();
	_opt->render();

}

void stage2::changeScene()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow()) && KEYMANAGER->isStayKeyDown('Z'))
	{
		SOUNDMANAGER->stop("MainStage");
		SCENEMANAGER->changeScene("Stage3", saveSlot);
	}

}

void stage2::pixelCollision()
{
	//아래에서 위로 박을때
	for (int i = _player->getShadow().top; i <= _player->getShadow().top; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i + _player->getShadow().bottom - _player->getShadow().top - 10);
			_player->setNoSpeed(true);
			break;
		}

	}

	//위에서 아래로 박을떄
	for (int i = _player->getShadow().bottom; i >= _player->getShadow().bottom; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i - _player->getShadow().bottom + _player->getShadow().top + 10);
			_player->setNoSpeed(true);
			break;
		}
	}

	//오른쪽에서 왼쪽으로 박을때
	for (int i = _player->getShadow().left; i <= _player->getShadow().left; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i + (_player->getShadow().right - _player->getShadow().left) / 2 + 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

	//왼쪽에서 오른쪽으로 박을때
	for (int i = _player->getShadow().right; i >= _player->getShadow().right; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i - (_player->getShadow().right - _player->getShadow().left) / 2 - 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

	//에너미 충돌
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		bool isCollision = false;
		//아래에서 위로 박을때
		for (int j = _em->getVEnemy()[i]->getShadowRc().top; j <= _em->getVEnemy()[i]->getShadowRc().top; j++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y - 3);
				isCollision = true;
				break;
			}
		}

		//위에서 아래로 박을떄
		for (int j = _em->getVEnemy()[i]->getShadowRc().bottom; j >= _em->getVEnemy()[i]->getShadowRc().bottom; j--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y + 3);
				isCollision = true;
				break;
			}
		}

		//오른쪽에서 왼쪽으로 박을때
		for (int j = _em->getVEnemy()[i]->getShadowRc().left; j <= _em->getVEnemy()[i]->getShadowRc().left; j++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x + 3, _em->getVEnemy()[i]->getEnemyPoint().y);
				isCollision = true;
				break;
			}

		}

		//왼쪽에서 오른쪽
		for (int j = _em->getVEnemy()[i]->getShadowRc().right; j >= _em->getVEnemy()[i]->getShadowRc().right; j--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
			{
				_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x - 3, _em->getVEnemy()[i]->getEnemyPoint().y);
				isCollision = true;
				break;
			}
		}
		_em->getVEnemy()[i]->setCollision(isCollision);
	}
}

void stage2::ItemCollision()
{
	RECT _temp;
	// 플레이어 충돌렉트랑 아이템 렉트랑 맞닿으면
	for (int j = 0; j < _em->getVItem().size(); j++)
	{
		if (IntersectRect(&_temp, &_player->getRect(), &_em->getVItem()[j]->getRect()))
		{
			//아이템 제거
			_em->getVItem()[j]->ItemRemove();
			//아이템에 따라 체력 회복
			STATUSMANAGER->heal(_em->getVItem()[j]->getHeal(), "HPBar");
		}
	}
}

void stage2::AttackCollision()
{
	RECT _temp;

	if (!_player->getHit())
	{
		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			// 플레이어 충돌렉트랑 적 공격렉트랑 맞닿으면
			if (IntersectRect(&_temp, &_player->getRect(), &_em->getVEnemy()[i]->getDebugAttackRc()))
			{
				//cout << "아야" << endl;
				_player->setHit(true);
				// 적이 플레이어보다 왼쪽에 있으면 왼쪽 타격이 나오게 오른쪽에 있으면 오른쪽 타격이 나오게
				// 플레이어 피격 시 에너미 공격 렉트에서 이펙트 발생
				if (_em->getVEnemy()[i]->getRect().left <= _player->getRect().left)
				{
					EFFECTMANAGER->play("hit",
										_em->getVEnemy()[i]->getDebugAttackRc().right,
										(_em->getVEnemy()[i]->getDebugAttackRc().top + _em->getVEnemy()[i]->getDebugAttackRc().bottom) / 2);
					_player->setHitRight(false);
				}
				else
				{
					EFFECTMANAGER->play("hit",
										_em->getVEnemy()[i]->getDebugAttackRc().left,
										(_em->getVEnemy()[i]->getDebugAttackRc().top + _em->getVEnemy()[i]->getDebugAttackRc().bottom) / 2);
					_player->setHitRight(true);
				}

			}
		}
	}
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		//getEnemyRect를 충돌용 getRect로 바꿀까? 피격 범위를 에너미 이미지 렉트로 하니 반대방향에서도 맞는 현상 발생 추후 생각해서 수정해야함
		if (IntersectRect(&_temp, &_player->getAttackRect(), &_em->getVEnemy()[i]->getEnemyRect()))
		{
			switch (_player->getKyokoDirection())
			{
				case	KYOKODIRECTION_RIGHT_ATTACK_1:
				case	KYOKODIRECTION_RIGHT_ATTACK_2:
				case	KYOKODIRECTION_RIGHT_ATTACK_DASH:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN:
					//해당 상태가 아닐 시에만 피격 이펙트 발생
					if (_em->getVEnemy()[i]->getDirection() != enemy::HIT
						&& _em->getVEnemy()[i]->getDirection() != enemy::DEAD
						&& _em->getVEnemy()[i]->getDirection() != enemy::REMOVE)
					{
						// 에너미 피격시 에너미 (좌표x + 보정 값) 와 캐릭터 중간y좌표에 이펙트 발생
						EFFECTMANAGER->play("hit",
											_em->getVEnemy()[i]->getEnemyPoint().x + 10,
											(_em->getVEnemy()[i]->getEnemyRect().top + _em->getVEnemy()[i]->getEnemyRect().bottom) / 2);
					}
					//플레이어의 공격을 에너미가 막았는지 체크
					if (!_em->getVEnemy()[i]->block(enemy::LEFT))
						//공격을 막지 못했다면 피격 체크
						_em->getVEnemy()[i]->hit(enemy::LEFT);
					break;
				case	KYOKODIRECTION_RIGHT_ATTACK_3:
				case	KYOKODIRECTION_RIGHT_ATTACK_STRONG:
				case	KYOKODIRECTION_RIGHT_MAHAKICK:
					//해당 상태가 아닐 시에만 피격 이펙트 발생
					if (_em->getVEnemy()[i]->getDirection() != enemy::HIT
						&& _em->getVEnemy()[i]->getDirection() != enemy::DEAD
						&& _em->getVEnemy()[i]->getDirection() != enemy::REMOVE)
					{
						// 에너미 피격시 에너미 (좌표x + 보정 값) 와 캐릭터 중간y좌표에 이펙트 발생
						EFFECTMANAGER->play("hit",
											_em->getVEnemy()[i]->getEnemyPoint().x + 10,
											(_em->getVEnemy()[i]->getEnemyRect().top + _em->getVEnemy()[i]->getEnemyRect().bottom) / 2);
						//플레이어의 공격을 에너미가 막았는지 체크
						if (!_em->getVEnemy()[i]->block(enemy::LEFT))
							//공격을 막지 못했다면 다운 체크
							_em->getVEnemy()[i]->downup(enemy::LEFT);
					}
					break;
				case	KYOKODIRECTION_LEFT_ATTACK_1:
				case	KYOKODIRECTION_LEFT_ATTACK_2:
				case	KYOKODIRECTION_LEFT_ATTACK_DASH:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN:
					//해당 상태가 아닐 시에만 피격 이펙트 발생
					if (_em->getVEnemy()[i]->getDirection() != enemy::HIT
						&& _em->getVEnemy()[i]->getDirection() != enemy::DEAD
						&& _em->getVEnemy()[i]->getDirection() != enemy::REMOVE)
					{
						// 에너미 피격시 에너미 (좌표x + 보정 값) 와 캐릭터 중간y좌표에 이펙트 발생
						EFFECTMANAGER->play("hit",
											_em->getVEnemy()[i]->getEnemyPoint().x - 10,
											(_em->getVEnemy()[i]->getEnemyRect().top + _em->getVEnemy()[i]->getEnemyRect().bottom) / 2);
						//플레이어의 공격을 에너미가 막았는지 체크
						if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
							//공격을 막지 못했다면 피격 체크
							_em->getVEnemy()[i]->hit(enemy::RIGHT);
					}
					break;
				case	KYOKODIRECTION_LEFT_ATTACK_3:
				case	KYOKODIRECTION_LEFT_ATTACK_STRONG:
				case	KYOKODIRECTION_LEFT_MAHAKICK:
					//해당 상태가 아닐 시에만 피격 이펙트 발생
					if (_em->getVEnemy()[i]->getDirection() != enemy::HIT
						&& _em->getVEnemy()[i]->getDirection() != enemy::DEAD
						&& _em->getVEnemy()[i]->getDirection() != enemy::REMOVE)
					{
						// 에너미 피격시 에너미 (좌표x + 보정 값) 와 캐릭터 중간y좌표에 이펙트 발생
						EFFECTMANAGER->play("hit",
											_em->getVEnemy()[i]->getEnemyPoint().x - 10,
											(_em->getVEnemy()[i]->getEnemyRect().top + _em->getVEnemy()[i]->getEnemyRect().bottom) / 2);
						//플레이어의 공격을 에너미가 막았는지 체크
						if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
							//공격을 막지 못했다면 다운 체크
							_em->getVEnemy()[i]->downup(enemy::RIGHT);
					}
					break;
			}
		}
	}
}
#pragma region 위의 코드에 문제가 있을시 아래로 대처할 것
//switch (_player->getKyokoDirection())
//{
//case	KYOKODIRECTION_RIGHT_ATTACK_1:
//case	KYOKODIRECTION_RIGHT_ATTACK_2:
//case	KYOKODIRECTION_RIGHT_ATTACK_DASH:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN:
//case	KYOKODIRECTION_LEFT_ATTACK_1:
//case	KYOKODIRECTION_LEFT_ATTACK_2:
//case	KYOKODIRECTION_LEFT_ATTACK_DASH:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN:
//	if (_player->getKyokoPoint().x <= _em->getVEnemy()[i]->getEnemyPoint().x)
//	{
//		//플레이어의 공격을 에너미가 막았는지 체크
//		if (!_em->getVEnemy()[i]->block(enemy::LEFT))
//			//공격을 막지 못했다면 피격 체크
//			_em->getVEnemy()[i]->hit(enemy::LEFT);
//	}
//	else
//	{
//		//플레이어의 공격을 에너미가 막았는지 체크
//		if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
//			//공격을 막지 못했다면 피격 체크
//			_em->getVEnemy()[i]->hit(enemy::RIGHT);
//	}
//	break;
//case	KYOKODIRECTION_RIGHT_ATTACK_3:
//case	KYOKODIRECTION_RIGHT_ATTACK_STRONG:
//case	KYOKODIRECTION_RIGHT_MAHAKICK:
//case	KYOKODIRECTION_LEFT_ATTACK_3:
//case	KYOKODIRECTION_LEFT_ATTACK_STRONG:
//case	KYOKODIRECTION_LEFT_MAHAKICK:
//	if (_player->getKyokoPoint().x <= _em->getVEnemy()[i]->getEnemyPoint().x)
//	{
//		//플레이어의 공격을 에너미가 막았는지 체크
//		if (!_em->getVEnemy()[i]->block(enemy::LEFT))
//			//공격을 막지 못했다면 다운 체크
//			_em->getVEnemy()[i]->downup(enemy::LEFT);
//	}
//	else
//	{
//		//플레이어의 공격을 에너미가 막았는지 체크
//		if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
//			//공격을 막지 못했다면 다운 체크
//			_em->getVEnemy()[i]->downup(enemy::RIGHT);
//	}
//	break;
#pragma endregion
