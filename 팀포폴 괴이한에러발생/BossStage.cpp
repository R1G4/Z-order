#include "stdafx.h"
#include "BossStage.h"
#include "kyoko.h"
#include "enemyManager.h"

HRESULT BossStage::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(4);

	bossVideo = "video/bossani wmv.wmv";
	VIDEOMANAGER->startVideo(bossVideo);
	SOUNDMANAGER->play("BossSound", _opt->getVolume());
	stage1 = IMAGEMANAGER->findImage("StageBoss");
	stage1Pic = IMAGEMANAGER->findImage("StageBossPic");
	stage1Alpha = IMAGEMANAGER->findImage("StageBossAlpha");

	_player->init();

	_door_rc = RectMake(100, 450, 180, 200);
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	_isStartScript = false;
	_isEndScript = false;

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
	if (_isEndScript)
	{
		_player->update();
		UI->update();
		_opt->update();
		changeMap();
	}
	VIDEOMANAGER->endVideo();
	if (!VIDEOMANAGER->checkPlay())_isStartScript = true;
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _string_count < _vScriptStart.size() - 1 && _isStartScript)
	{
		cout << _string_count << endl;
		cout << _vScriptStart.size() << endl;
		_string_count++;
		if (_string_count >= 14)
		{
			_isEndScript = true;
			_isStartScript = false;
		}
	}
	if (_isEndScript)
		cout << "싸움시작" << endl;
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

	_opt->render();

	UI->render();
	if (!_isEndScript)
	{
		stage1Alpha->alphaRender(getMemDC(), _alpha);
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "배달의민족 주아");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		strcpy_s(str, _vScriptStart[_string_count].c_str());
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), 50, WINSIZEY -70, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);
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
