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
	_geForce = IMAGEMANAGER->findImage("������");
	_radeon = IMAGEMANAGER->findImage("�󵥿�");
	_kyoko_i = IMAGEMANAGER->findImage("����1");
	_boss_i = IMAGEMANAGER->findImage("�̽���1");

	_player->init();

	_door_rc = RectMake(100, 450, 180, 200);
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	_bossPhase = INTRO_SCENE;


	// ���̾�α� ����
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
		// ������ ������ ���̾�α�
		if (_string_count < _vScriptStart.size() - 1 && _bossPhase == BEFORE_FIGHT_DIALOG)
		{
			_string_count++;
			if (_string_count >= _vScriptStart.size() - 1)
			{
				_bossPhase = VS_MESUZU;
				_boss_i = IMAGEMANAGER->findImage("�̽���3");
			}

			if (_string_count == 0 || _string_count == 7)
				_kyoko_i = IMAGEMANAGER->findImage("����1");

			if (_string_count == 5)
				_kyoko_i = IMAGEMANAGER->findImage("����2");

			if (_string_count == 10 || _string_count == 11 || _string_count == 12)
				_kyoko_i = IMAGEMANAGER->findImage("����3");

			if (_string_count == 3)
				_kyoko_i = IMAGEMANAGER->findImage("����4");

			if (_string_count == 1 || _string_count == 2 || _string_count == 4)
				_boss_i = IMAGEMANAGER->findImage("�̽���1");

			if (_string_count == 6 || _string_count == 13)
				_boss_i = IMAGEMANAGER->findImage("�̽���2");

			if (_string_count == 8 || _string_count == 9)
				_boss_i = IMAGEMANAGER->findImage("�̽���3");

		}
		//���� ����,��Ŭ �����϶� ī�޶� ��鸲
		if (_boss->getBossDirection() == BOSS_LEFT_JUMPDOWN_END || _boss->getBossDirection() == BOSS_RIGHT_JUMPDOWN_END
			|| _boss->getBossDirection() == BOSS_LEFT_TACKLE || _boss->getBossDirection() == BOSS_RIGHT_TACKLE)
		{
			CAMERAMANAGER->shaking(&camera, 3);
		}
		// ���� ������� ���̾�α�
		if (_string_count_2 < _vScriptEnd.size() - 1 && _bossPhase == AFTER_FIGHT_DIALOG)
		{
			_string_count_2++;
			if (_string_count_2 >= _vScriptEnd.size() - 1)
				_bossPhase = END;

			if (_string_count_2 == 3)
				_kyoko_i = IMAGEMANAGER->findImage("����1");

			if (_string_count_2 == 8)
				_kyoko_i = IMAGEMANAGER->findImage("����2");

			if (_string_count_2 == 0)
				_kyoko_i = IMAGEMANAGER->findImage("����3");

			if (_string_count_2 == 1)
				_kyoko_i = IMAGEMANAGER->findImage("����4");

			if (_string_count_2 == 2 || _string_count_2 == 6)
				_boss_i = IMAGEMANAGER->findImage("�̽���1");

			if (_string_count_2 == 5)
				_boss_i = IMAGEMANAGER->findImage("�̽���2");

			if (_string_count_2 == 0 || _string_count_2 == 1 || _string_count_2 == 11)
				_boss_i = IMAGEMANAGER->findImage("�̽���3");
		}
	}

	if (_bossPhase == VS_MESUZU)
	{
		cout << "�ο����" << endl;	
		// ������ ��Ҵٰ� ����
		if (KEYMANAGER->isOnceKeyDown('O'))
		{
			_bossPhase = AFTER_FIGHT_DIALOG;
		}
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
	_player->render(camera);
	_boss->render(camera);
	_opt->render();

	UI->render();
	_boss->hpRender();
	if (_bossPhase == BEFORE_FIGHT_DIALOG)
	{
		stage1Alpha->alphaRender(getMemDC(), _alpha);
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����ǹ��� �־�");
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

		_kyoko_i->render(getMemDC(), 0, WINSIZEY - 542);
		_boss_i->render(getMemDC(), WINSIZEX - 384, WINSIZEY - 542);
	}

	// ������ �����Ŀ� ��� ���
	if (_bossPhase == AFTER_FIGHT_DIALOG)
	{
		stage1Alpha->alphaRender(getMemDC(), _alpha);
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����ǹ��� �־�");
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
		SCENEMANAGER->changeScene("��������1");
		SOUNDMANAGER->stop("BossSound");
	}
}

void BossStage::attackCollision()
{
	RECT temp;
	//�÷��̾ �����ʿ��� ���� �����Ҷ�
	if (_player->getKyokoPoint().x > _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getAttackRect(), &_boss->getBossRect()))
		{
			_boss->hitDamage(10);
			_boss->rightAttackedMotion();
		}
	}
	//�÷��̾ ���ʿ��� ���� �����Ҷ�
	if (_player->getKyokoPoint().x < _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getAttackRect(), &_boss->getBossRect()))
		{
			_boss->hitDamage(10);
			_boss->leftAttackedMotion();
		}
	}
	//������ �����ʿ��� �����Ҷ�
	if (_player->getKyokoPoint().x > _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getRect(), &_boss->getBossAttackRect()))
		{
			_player->setHit(true);
			_player->setHitRight(false);
		}
	}
	//������ ���ʿ��� �����Ҷ�
	if (_player->getKyokoPoint().x < _boss->getBossPointX())
	{
		if (IntersectRect(&temp, &_player->getRect(), &_boss->getBossAttackRect()))
		{
			_player->setHit(true);
			_player->setHitRight(true);
		}
	}
}
