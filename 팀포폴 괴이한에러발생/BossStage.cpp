#include "stdafx.h"
#include "BossStage.h"
#include "kyoko.h"
#include "enemyManager.h"

HRESULT BossStage::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(4);
	_boss = new boss;
	_boss->init();
	_boss->setKyokoAddressLink(_player);


	bossVideo = "video/bossani wmv.wmv";
	VIDEOMANAGER->startVideo(bossVideo);
	SOUNDMANAGER->play("BossIntroSound", _opt->getVolume());
	stage1 = IMAGEMANAGER->findImage("StageBoss");
	stage1Pic = IMAGEMANAGER->findImage("StageBossPic");
	stage1Alpha = IMAGEMANAGER->findImage("StageBossAlpha");
	_geForce = IMAGEMANAGER->findImage("지포스");
	_radeon = IMAGEMANAGER->findImage("라데온");
	_kyoko_i = IMAGEMANAGER->findImage("쿄코1");
	_kyoko_si = IMAGEMANAGER->findImage("쿄코1그림자");
	_boss_i = IMAGEMANAGER->findImage("미스즈1");

	_player->init();
	_player->setKyokoPoint(WINSIZEX / 2, 1000);
	_door_rc = RectMake(100, 450, 180, 200);
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	_bossPhase = INTRO_SCENE;


	// 다이얼로그 저장
	if (TXTDATA->canLoadFile("dialog/DialogStart.txt", ';'))
		_vScriptStart = TXTDATA->txtLoad("dialog/DialogStart.txt", ";");

	if (TXTDATA->canLoadFile("dialog/DialogEnd.txt", ';'))
		_vScriptEnd = TXTDATA->txtLoad("dialog/DialogEnd.txt", ";");

	_alpha = 200;

	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage1);
	if (_bossPhase == VS_MESUZU)
	{
		_player->update();
		_boss->update();
		attackCollision();
		UI->update();
		_opt->update();
		changeMap();
		picCollision();
	}
	VIDEOMANAGER->endVideo();
	if (!VIDEOMANAGER->checkPlay() && _bossPhase == INTRO_SCENE)
	{
		_bossPhase = BEFORE_FIGHT_DIALOG;
		SOUNDMANAGER->stop("BossIntroSound");
		SOUNDMANAGER->play("BossSound", _opt->getVolume());
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		// 보스전 시작전 다이어로그
		if (_string_count < _vScriptStart.size() - 1 && _bossPhase == BEFORE_FIGHT_DIALOG)
		{
			_string_count++;
			if (_string_count >= _vScriptStart.size() - 1)
			{
				_bossPhase = VS_MESUZU;
				_boss_i = IMAGEMANAGER->findImage("미스즈3");
			}

			if (_string_count == 0 || _string_count == 7)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코1");

			if (_string_count == 5)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코2");

			if (_string_count == 10 || _string_count == 11 || _string_count == 12)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코3");

			if (_string_count == 3)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코4");

			if (_string_count == 0 || _string_count == 7)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코1그림자");

			if (_string_count == 5)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코2그림자");

			if (_string_count == 10 || _string_count == 11 || _string_count == 12)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코3그림자");

			if (_string_count == 3)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코4그림자");

			if (_string_count == 1 || _string_count == 2 || _string_count == 4)
				_boss_i = IMAGEMANAGER->findImage("미스즈1");

			if (_string_count == 6 || _string_count == 13)
				_boss_i = IMAGEMANAGER->findImage("미스즈2");

			if (_string_count == 8 || _string_count == 9)
				_boss_i = IMAGEMANAGER->findImage("미스즈3");

		}
		// 보스 잡고난다음 다이어로그
		if (_string_count_2 < _vScriptEnd.size() - 1 && _bossPhase == AFTER_FIGHT_DIALOG)
		{
			_string_count_2++;
			if (_string_count_2 >= _vScriptEnd.size() - 1)
				_bossPhase = END;

			if (_string_count_2 == 3)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코1");

			if (_string_count_2 == 8)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코2");

			if (_string_count_2 == 0)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코3");

			if (_string_count_2 == 1)
				_kyoko_i = IMAGEMANAGER->findImage("쿄코4");

			if (_string_count_2 == 3)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코1그림자");

			if (_string_count_2 == 8)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코2그림자");

			if (_string_count_2 == 0)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코3그림자");

			if (_string_count_2 == 1)
				_kyoko_si = IMAGEMANAGER->findImage("쿄코4그림자");

			if (_string_count_2 == 2 || _string_count_2 == 6)
				_boss_i = IMAGEMANAGER->findImage("미스즈1");

			if (_string_count_2 == 5)
				_boss_i = IMAGEMANAGER->findImage("미스즈2");

			if (_string_count_2 == 0 || _string_count_2 == 1 || _string_count_2 == 11)
				_boss_i = IMAGEMANAGER->findImage("미스즈3");
		}
	}

	if (_bossPhase == VS_MESUZU)
	{
		cout << "싸움시작" << endl;
		// 보스를 잡았다고 가정
		if (KEYMANAGER->isOnceKeyDown('O'))
		{
			_bossPhase = AFTER_FIGHT_DIALOG;
		}
	}

	// 여기다가 세이브로드창으로 돌아가게 해주심됨다
	if (_player->getDeadLastFrame())
	{
		SOUNDMANAGER->stop("BossSound");
		SCENEMANAGER->changeScene("세이브로드");
	}
}

void BossStage::render()
{
	stage1->render(getMemDC(), 0, 0, camera);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage1Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), _door_rc, camera);
	}
	zOrder();

	UI->render();
	_player->deadRender();
	_opt->render();


	if (_bossPhase == BEFORE_FIGHT_DIALOG)
	{
		stage1Alpha->alphaRender(getMemDC(), _alpha);
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "배달의민족 주아");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		strcpy_s(str, _vScriptStart[_string_count].c_str());
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetBkMode(getMemDC(), TRANSPARENT);
		TextOut(getMemDC(), 50, WINSIZEY - 65, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);


		if (_string_count == 0 ||
			_string_count == 3 ||
			_string_count == 5 ||
			_string_count == 7 ||
			_string_count == 10 ||
			_string_count == 11 ||
			_string_count == 12)
			_geForce->render(getMemDC(), 50, WINSIZEY - 65);
		else
			_radeon->render(getMemDC(), 60, WINSIZEY - 75);

		_kyoko_si->alphaRender(getMemDC(), -10, WINSIZEY - 452, 200, camera);
		_kyoko_i->render(getMemDC(), 0, WINSIZEY - 542);

		_boss_i->render(getMemDC(), WINSIZEX - 384, WINSIZEY - 542);
	}

	// 보스전 끝난후에 대사 출력
	if (_bossPhase == AFTER_FIGHT_DIALOG)
	{
		stage1Alpha->alphaRender(getMemDC(), _alpha);
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "배달의민족 주아");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		strcpy_s(str, _vScriptEnd[_string_count_2].c_str());
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetBkMode(getMemDC(), TRANSPARENT);
		TextOut(getMemDC(), 50, WINSIZEY - 65, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);

		if (_string_count_2 == 1 ||
			_string_count_2 == 3 ||
			_string_count_2 == 8)
			_geForce->render(getMemDC(), 50, WINSIZEY - 65);
		else
			_radeon->render(getMemDC(), 50, WINSIZEY - 75);

		_kyoko_i->render(getMemDC(), 0, WINSIZEY - 542);
		_boss_i->render(getMemDC(), WINSIZEX - 384, WINSIZEY - 542);
	}

}

void BossStage::changeMap()
{
	RECT temp;
	if (IntersectRect(&temp, &_door_rc, &_player->getShadow()) && KEYMANAGER->isStayKeyDown('Z'))
	{
		delete(_player);
		SCENEMANAGER->changeScene("스테이지1");
		SOUNDMANAGER->stop("BossSound");
	}
}

void BossStage::attackCollision()
{
	RECT temp;
	//플레이어가 오른쪽에서 보스 공격할때
	if (_player->getKyokoPoint().x > _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getAttackRect(), &_boss->getBossRect()))
		{
			_boss->hitDamage(10);
			_boss->rightAttackedMotion();
		}
	}
	//플레이어가 왼쪽에서 보스 공격할때
	if (_player->getKyokoPoint().x < _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getAttackRect(), &_boss->getBossRect()))
		{
			_boss->hitDamage(10);
			_boss->leftAttackedMotion();
		}
	}
	//보스가 오른쪽에서 공격할때
	if (_player->getKyokoPoint().x > _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getRect(), &_boss->getBossAttackRect()))
		{
			_player->setHit(true);
			_player->setHitRight(false);
		}
	}
	//보스가 왼쪽에서 공격할때
	if (_player->getKyokoPoint().x < _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getRect(), &_boss->getBossAttackRect()))
		{
			_player->setHit(true);
			_player->setHitRight(true);
		}
	}
}

void BossStage::picCollision()
{
	//픽셀 콜리쟌 상 하
	for (int i = _player->getShadow().left; i <= _player->getShadow().right; i++)
	{
		//상
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), i, _player->getShadow().top);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//하
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), i, _player->getShadow().bottom);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y + 3);
			_player->setNoSpeed(true);

			break;
		}


		if (r2 == 255 && g2 == 0 && b2 == 0)
		{

			_player->setKyokoPoint(_player->getKyokoPoint().x, _player->getKyokoPoint().y - 3);
			_player->setNoSpeed(true);
			break;
		}

	}

	//픽셀 콜리쟌 좌 우
	for (int i = _player->getShadow().top; i <= _player->getShadow().bottom; i++)
	{
		//좌
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), _player->getShadow().left, i);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//우
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), _player->getShadow().right, i);
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


	//보스관련
	//아래에서 위로 박을때
	//픽셀 콜리쟌 상 하
	for (int i = _boss->getBossShadow().left; i <= _boss->getBossShadow().right; i++)
	{
		//상
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), i, _player->getShadow().top);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//하
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), i, _player->getShadow().bottom);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_boss->setMainPoint(PointMake(_boss->getMainPoint().x, _boss->getMainPoint().y + 3));
			_boss->setShadowPoint(PointMake(_boss->getShadowPoint().x, _boss->getShadowPoint().y + 3));
			break;
		}


		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_boss->setMainPoint(PointMake(_boss->getMainPoint().x, _boss->getMainPoint().y - 3));
			_boss->setShadowPoint(PointMake(_boss->getShadowPoint().x, _boss->getShadowPoint().y - 3));
			break;
		}

	}

	//픽셀 콜리쟌 좌 우
	for (int i = _boss->getBossShadow().top; i <= _boss->getBossShadow().bottom; i++)
	{
		//좌
		COLORREF color1 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), _player->getShadow().left, i);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);
		//우
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("StageBossPic")->getMemDC(), _player->getShadow().right, i);
		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			_boss->setMainPoint(PointMake(_boss->getMainPoint().x + 3, _boss->getMainPoint().y));
			_boss->setShadowPoint(PointMake(_boss->getShadowPoint().x + 3, _boss->getShadowPoint().y));
			break;
		}
		if (r2 == 255 && g2 == 0 && b2 == 0)
		{
			_boss->setMainPoint(PointMake(_boss->getMainPoint().x - 3, _boss->getMainPoint().y));
			_boss->setShadowPoint(PointMake(_boss->getShadowPoint().x - 3, _boss->getShadowPoint().y));
			break;
		}

	}

}

