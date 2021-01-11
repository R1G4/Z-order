#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_back = IMAGEMANAGER->addImage("검정", "image/loading/loadingBack.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addFrameImage("로딩배경", "image/loading/로딩.bmp", 1395, 220, 5, 1, true, RGB(255, 0, 255));

	//_loadingBar = new progressBar;
	//_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	//_loadingBar->setGauge(0, 0);

	//쓰레드를 사용해보자
	CreateThread(
		NULL,				//스레드의 보안속성(자식윈도우가 존재할때)
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드 크기와 동일)
		threadFunction,		//스레드 사용할 함수 명
		this,				//스레드 매개변수(this로 두면 본 클래스)
		NULL,				//스레드의 특성(기다릴지, 바로 실행(NULL이면 요게 해당))
		NULL				//스레드 생성 후 스레드의 ID 넘겨줌 보통은 NULL로 둔다
	);

	_loading = new animation;
	_loading->init(_background->getWidth(), _background->getHeight(),
		_background->getFrameWidth(), _background->getFrameHeight());
	_loading->setDefPlayFrame(false, true);
	_loading->setFPS(1);

	_loading->start();

	return S_OK;
}

HRESULT loadingScene::init(int SceneNum)
{
	nextScene = SceneNum;
	_back = IMAGEMANAGER->addImage("검정", "image/loading/loadingBack.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addFrameImage("로딩배경", "image/loading/로딩.bmp", 1395, 220, 5, 1, true, RGB(255, 0, 255));

	//_loadingBar = new progressBar;
	//_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	//_loadingBar->setGauge(0, 0);

	//쓰레드를 사용해보자
	CreateThread(
		NULL,				//스레드의 보안속성(자식윈도우가 존재할때)
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드 크기와 동일)
		threadFunction,		//스레드 사용할 함수 명
		this,				//스레드 매개변수(this로 두면 본 클래스)
		NULL,				//스레드의 특성(기다릴지, 바로 실행(NULL이면 요게 해당))
		NULL				//스레드 생성 후 스레드의 ID 넘겨줌 보통은 NULL로 둔다
	);

	_loading = new animation;
	_loading->init(_background->getWidth(), _background->getHeight(),
		_background->getFrameWidth(), _background->getFrameHeight());
	_loading->setDefPlayFrame(false, true);
	_loading->setFPS(1);

	_loading->start();

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loading->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);


	//_loadingBar->update();
	//_loadingBar->setGauge(_currentCount, LOADINGMAX);

	//로딩이 다 되면
	if (_currentCount == LOADINGMAX)
	{
		switch (nextScene)
		{
		case 0:
			STATUSMANAGER->setHp(24);
			STATUSMANAGER->setHpBar("HPBar");
			SCENEMANAGER->changeScene("스테이지1");
			break;
		case 1:
			SCENEMANAGER->changeScene("보스스테이지");
			break;
		case 2:
			SCENEMANAGER->changeScene("타이틀");
			break;
		}
	}
}

void loadingScene::render()
{
	//그림파일 이미지 경로를 텍스트로 보여줘도 되고

	_back->render(getMemDC());
	_background->aniRender(getMemDC(), WINSIZEX - 279, WINSIZEY - 220, _loading);

}



DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//여기에다가
	//이미지매니저나, 사운드 매니저 써서
	//add 해주면 된다.

	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	//메인 스테이지 BGM추가
	SOUNDMANAGER->addSound("MainStage", "sound/BGM/River City Girls OST - Detention.mp3", true, true);
	SOUNDMANAGER->addSound("BossSound", "sound/BGM/River City Girls OST - Boss Misuzu.mp3", true, true);
	//메인 스테이지 맵추가
	IMAGEMANAGER->addImage("Stage1", "image/map/0.bmp", 2154, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage1Pic", "image/map/0Pic.bmp", 2154, 884, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2", "image/map/1.bmp", 3494, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2Pic", "image/map/1Pic.bmp", 3494, 884, false, RGB(255, 0, 255));

	//보스 스테이지 맵추가
	IMAGEMANAGER->addImage("StageBoss", "image/map/boss.bmp", 1830, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("StageBossPic", "image/map/bossPic.bmp", 1830, 884, false, RGB(255, 0, 255));

	//쿄코 이미지 추가
	IMAGEMANAGER->addFrameImage("쿄코_일반", "image/kyoko/idle_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_걷기", "image/kyoko/walk_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_달리기", "image/kyoko/run_1.bmp", 0, 0, 4800, 400, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_점프", "image/kyoko/jump_1.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격1", "image/kyoko/attack_1_1.bmp", 0, 0, 1800, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격2", "image/kyoko/attack_2_1.bmp", 0, 0, 2100, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_공격3", "image/kyoko/attack_3_3.bmp", 0, 0, 2700, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_대쉬공격", "image/kyoko/attack_dash.bmp", 0, 0, 2400, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_점프공격", "image/kyoko/attack_jump.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_강공격", "image/kyoko/attack_strong_2.bmp", 0, 0, 3000, 600, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_마하킥", "image/kyoko/mahaKick_2.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_피격1", "image/kyoko/attacked_1_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_피격2", "image/kyoko/attacked_2_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿄코_죽음", "image/kyoko/dead_1.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그림자", "image/kyoko/shadow.bmp", 100, 30, true, RGB(255, 0, 255));

	//에너미 이미지 추가
	EFFECTMANAGER->addEffect("Enemy_Point", "image/enemy/Effect/point.bmp", 560, 70, 70, 70, 1, 0.4f, 1000);
	EFFECTMANAGER->addEffect("Enemy_Stern", "image/enemy/Effect/stun.bmp", 420, 54, 70, 54, 1, 0.4f, 1000);

	IMAGEMANAGER->addImage("Boy_Shadow", "image/enemy/SchoolBoy/Boy_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Idle", "image/enemy/SchoolBoy/Boy_Idle.bmp", 0, 0, 1200, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Walk", "image/enemy/SchoolBoy/Boy_Walk.bmp", 0, 0, 1460, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Run", "image/enemy/SchoolBoy/Boy_Run.bmp", 0, 0, 1876, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Block", "image/enemy/SchoolBoy/Boy_Block.bmp", 0, 0, 420, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Attack", "image/enemy/SchoolBoy/Boy_Attack.bmp", 0, 0, 1598, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack1", "image/enemy/SchoolBoy/Boy_ComboAttack1.bmp", 0, 0, 1892, 540, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack2", "image/enemy/SchoolBoy/Boy_ComboAttack2.bmp", 0, 0, 766, 460, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack3", "image/enemy/SchoolBoy/Boy_ComboAttack3.bmp", 0, 0, 1830, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Hit", "image/enemy/SchoolBoy/Boy_Hit.bmp", 0, 0, 1536, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Downup", "image/enemy/SchoolBoy/Boy_Downup.bmp", 0, 0, 7027, 400, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Dazed", "image/enemy/SchoolBoy/Boy_Dazed.bmp", 0, 0, 620, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Jump", "image/enemy/SchoolBoy/Boy_Jump.bmp", 0, 0, 468, 480, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Knockdown", "image/enemy/SchoolBoy/Boy_Knockdown.bmp", 0, 0, 4945, 400, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Taunt", "image/enemy/SchoolBoy/Boy_Taunt.bmp", 0, 0, 1704, 420, 11, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Girl_Shadow", "image/enemy/SchoolGirl/Girl_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Idle", "image/enemy/SchoolGirl/Girl_Idle.bmp", 0, 0, 1320, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Walk", "image/enemy/SchoolGirl/Girl_Walk.bmp", 0, 0, 1394, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Run", "image/enemy/SchoolGirl/Girl_Run.bmp", 0, 0, 1780, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Block", "image/enemy/SchoolGirl/Girl_Block.bmp", 0, 0, 460, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Attack", "image/enemy/SchoolGirl/Girl_Attack.bmp", 0, 0, 1934, 420, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack1", "image/enemy/SchoolGirl/Girl_ComboAttack1.bmp", 0, 0, 1505, 430, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack2", "image/enemy/SchoolGirl/Girl_ComboAttack2.bmp", 0, 0, 1470, 440, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack3", "image/enemy/SchoolGirl/Girl_ComboAttack3.bmp", 0, 0, 2700, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Hit", "image/enemy/SchoolGirl/Girl_Hit.bmp", 0, 0, 1626, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Downup", "image/enemy/SchoolGirl/Girl_Downup.bmp", 0, 0, 7013, 380, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Knockdown", "image/enemy/SchoolGirl/Girl_Knockdown.bmp", 0, 0, 4361, 380, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Dazed", "image/enemy/SchoolGirl/Girl_Dazed.bmp", 0, 0, 656, 410, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Jump", "image/enemy/SchoolGirl/Girl_Jump.bmp", 0, 0, 432, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Taunt", "image/enemy/SchoolGirl/Girl_Taunt.bmp", 0, 0, 4015, 420, 26, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("MT_Shadow", "image/enemy/MT/MT_Shadow.bmp", 112, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Idle", "image/enemy/MT/MT_Idle.bmp", 0, 0, 1634, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Walk", "image/enemy/MT/MT_Walk.bmp", 0, 0, 1984, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Run", "image/enemy/MT/MT_Run.bmp", 0, 0, 1933, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Block", "image/enemy/MT/MT_Block.bmp", 0, 0, 486, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Attack", "image/enemy/MT/MT_Attack.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack1", "image/enemy/MT/MT_ComboAttack1.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack2", "image/enemy/MT/MT_ComboAttack2.bmp", 0, 0, 2216, 430, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack3", "image/enemy/MT/MT_ComboAttack3.bmp", 0, 0, 4068, 450, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Hit", "image/enemy/MT/MT_Hit.bmp", 0, 0, 523, 380, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Downup", "image/enemy/MT/MT_Downup.bmp", 0, 0, 8919, 440, 31, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Dazed", "image/enemy/MT/MT_Dazed.bmp", 0, 0, 618, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Jump", "image/enemy/MT/MT_Jump.bmp", 0, 0, 612, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Knockdown", "image/enemy/MT/MT_Knockdown.bmp", 0, 0, 8056, 440, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Taunt", "image/enemy/MT/MT_Taunt.bmp", 0, 0, 558, 400, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("CheerLeader_Shadow", "image/enemy/CheerLeader/CheerLeader_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Idle", "image/enemy/CheerLeader/CheerLeader_Idle.bmp", 0, 0, 2133, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Walk", "image/enemy/CheerLeader/CheerLeader_Walk.bmp", 0, 0, 2499, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Run", "image/enemy/CheerLeader/CheerLeader_Run.bmp", 0, 0, 1291, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Block", "image/enemy/CheerLeader/CheerLeader_Block.bmp", 0, 0, 457, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Attack", "image/enemy/CheerLeader/CheerLeader_Attack.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack1", "image/enemy/CheerLeader/CheerLeader_ComboAttack1.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack2", "image/enemy/CheerLeader/CheerLeader_ComboAttack2.bmp", 0, 0, 1715, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack3", "image/enemy/CheerLeader/CheerLeader_ComboAttack3.bmp", 0, 0, 6577, 600, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Hit", "image/enemy/CheerLeader/CheerLeader_Hit.bmp", 0, 0, 1445, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Downup", "image/enemy/CheerLeader/CheerLeader_Downup.bmp", 0, 0, 8265, 400, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Dazed", "image/enemy/CheerLeader/CheerLeader_Dazed.bmp", 0, 0, 554, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Jump", "image/enemy/CheerLeader/CheerLeader_Jump.bmp", 0, 0, 776, 500, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Knockdown", "image/enemy/CheerLeader/CheerLeader_Knockdown.bmp", 0, 0, 6482, 400, 22, 2, true, RGB(255, 0, 255));

	//오브젝트 이미지 추가
	IMAGEMANAGER->addImage("chair", "image/object/chair.bmp", 179, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("좌기둥", "image/object/Lgidoong.bmp", 153, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("우기둥", "image/object/Rgidoong.bmp", 153, 720, true, RGB(255, 0, 255));


	//UI IMAGE
	IMAGEMANAGER->addImage("HPUI", "image/kyoko/UI/hp_ui.bmp", 600, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPBar", "image/kyoko/UI/hpbar.bmp", 26, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MahaGauge", "image/kyoko/UI/mahagauge_1.bmp", 362, 18, true, RGB(255, 0, 255));


	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		//여기에 와일문 돌리지말고 이미지랑 사운드 등 리소스 파일 추가해라

		//CPU 잠깐 정지거는건데
		//이거 안걸면 너무 빨라가지고 눈 깜빡이면 넘어가버림 (1000개여도)
		Sleep(1);

		loadingHelper->_currentCount++;
	}


	return 0;
}
