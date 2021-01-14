#include "stdafx.h"
#include "tempStage.h"
#include "kyoko.h"
#include "enemyManager.h"
#include "npcManager.h"

HRESULT tempStage::init(int slot)
{
	saveSlot = slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(1);
	_opt->setSlot(saveSlot);

	SOUNDMANAGER->play("MainStage", _opt->getVolume());
	stage1 = IMAGEMANAGER->findImage("Stage1");
	stage1Pic = IMAGEMANAGER->findImage("Stage1Pic");
	
	//플레이어 위치 초기화
	_player->init();
	//스테이지에 따른 에너미 생성
	//플레이어 주소 받아오기
	//스테이지에 따른 NPC 생성
	_nm->setNpc(1);

	//의자 렉트
	chair[0].rc = RectMake(WINSIZEX / 2 - 222, WINSIZEY / 2 + 135, 100, 170);
	chair[1].rc = RectMake(WINSIZEX / 2 + 42, WINSIZEY / 2 + 135, 100, 170);
	chair[2].rc = RectMake(WINSIZEX / 2 + 322, WINSIZEY / 2 + 135, 100, 170);
	chair[3].rc = RectMake(WINSIZEX / 2 + 597, WINSIZEY / 2 + 135, 100, 170);
	chair[4].rc = RectMake(WINSIZEX / 2 - 396, WINSIZEY / 2 + 304, 100, 170);
	chair[5].rc = RectMake(WINSIZEX / 2 - 127, WINSIZEY / 2 + 304, 100, 170);
	chair[6].rc = RectMake(WINSIZEX / 2 + 150, WINSIZEY / 2 + 304, 100, 170);
	chair[7].rc = RectMake(WINSIZEX / 2 + 427, WINSIZEY / 2 + 304, 100, 170);

	//Z 구분용렉트
	tempRcU.rc = RectMake(WINSIZEX / 2 - 157, WINSIZEY / 2 + 238, 100, 10);
	tempRcD.rc = RectMake(WINSIZEX / 2 - 326, WINSIZEY / 2 + 405, 100, 10);

	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	for (int i = 0; i < 8; i++)
	{
		chair[i].img = IMAGEMANAGER->findImage("chair");
	}

	_door_rc = RectMake(1380, 400, 300, 130);
	return S_OK;
}

void tempStage::release()
{

}

void tempStage::update()
{
	UI->update();
	_opt->update();
	pixelCollision();
	AttackCollision();
	_player->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	_nm->update();
	changeMap();

	// 여기다가 세이브로드창으로 돌아가게 해주심됨다
	if (_player->getDeadLastFrame())
	{
		SOUNDMANAGER->stop("MainStage");
		SCENEMANAGER->changeScene("세이브로드");
	}
}

void tempStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);
	_nm->render(camera);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);

		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);
	}
	_player->render(camera);
	for (int i = 0; i < 8; i++)
	{
		chair[i].img->render(getMemDC(), chair[i].rc.left, chair[i].rc.top, camera);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
		for (int i = 0; i < 8; i++) { Rectangle(getMemDC(), chair[i].rc, camera); }
		Rectangle(getMemDC(), tempRcU.rc, camera);
		Rectangle(getMemDC(), tempRcD.rc, camera);		
		Rectangle(getMemDC(), _player->getDebugRect(), camera);
		Rectangle(getMemDC(), _player->getDebugShadow(), camera);

		for (int i = 0; i < _nm->getVNpc().size(); i++)
		{
			npc* npc = _nm->getVNpc()[i];
			Rectangle(getMemDC(), npc->getDebugRect(), camera);
			Rectangle(getMemDC(), npc->getDebugShadowRc(), camera);
		}


		HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		Rectangle(getMemDC(), _player->getDebugAttack(), camera);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
	}
	zOrder();

	UI->render();
	_player->deadRender();
	_opt->render();

}

void tempStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow())&&KEYMANAGER->isStayKeyDown('Z'))
	{
		SOUNDMANAGER->stop("MainStage");
		SCENEMANAGER->changeScene("Stage2",saveSlot);
	}
}

void tempStage::pixelCollision()
{
	//픽셀 콜리쟌 상 하
	for (int i = _player->getShadow().left; i <= _player->getShadow().right; i++)
	{
		//상
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, _player->getShadow().top);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//하
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), i, _player->getShadow().bottom);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 1);
			_player->setNoSpeed(true);

			break;
		}


		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 1);
			_player->setNoSpeed(true);
			break;
		}

	}

	//픽셀 콜리쟌 좌 우
	for (int i = _player->getShadow().top; i <= _player->getShadow().bottom; i++)
	{
		//좌
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().left, i);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//우
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _player->getShadow().right, i);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x + 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
		if ((r1 == 0 && g1 == 255 && b1 == 0) && !_player->getIsJump())
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x + 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
		if ((r2 == 0 && g2 == 255 && b2 == 0) && !_player->getIsJump())
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x - 1, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}
	}

	//의자
	for (int i = _player->getShadow().top + 20; i <= _player->getShadow().bottom + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), (_player->getShadow().right + _player->getShadow().left) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((_player->getKyokoDirection() == KYOKODIRECTION_RIGHT_JUMP || _player->getKyokoDirection() == (KYOKODIRECTION_LEFT_JUMP))
			&& (r == 0 && g == 255 && b == 0))
		{
			if (!_isDesk) {
				_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 50);
				_isDesk = true;
				break;
			}
		}
		else if (!(r == 255 && g == 255 && b == 0) && _player->getIsJump())_isDesk = false;
	}
	for (int i = _player->getShadow().left + 20; i <= _player->getShadow().right - 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(),i, (_player->getShadow().top + _player->getShadow().bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (((r == 255 && g == 255 && b == 0)) && _player->getIsJump())
		{
			_isDesk = true;
		}
		else if (!(r == 255 && g == 255 && b == 0) && _player->getIsJump())_isDesk = false;
	}
}

void tempStage::AttackCollision()
{
	RECT _temp;
	//플레이어와 Npc 상호작용
	if (!_player->getHit())
	{
		for (int i = 0; i < _nm->getVNpc().size(); i++)
		{
			// 플레이어 충돌렉트랑 적 공격렉트랑 맞닿으면
			if (IntersectRect(&_temp, &_player->getAttackRect(), &_nm->getVNpc()[i]->getNpcRc()))
			{
				//플레이어 위치에 따라 반응하는 방향도 다르다.
				if (_nm->getVNpc()[i]->getNpcRc().left <= _player->getRect().left)
					_nm->getVNpc()[i]->setReact(npc::RIGHT);
				else
					_nm->getVNpc()[i]->setReact(npc::LEFT);

			}
		}
	}
}