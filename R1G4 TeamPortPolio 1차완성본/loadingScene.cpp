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

HRESULT loadingScene::init(int SceneNum, int slot)
{

	nextScene = SceneNum;
	saveSlot = slot;
	_back = IMAGEMANAGER->addImage("검정", "image/loading/loadingBack.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addFrameImage("로딩배경", "image/loading/로딩.bmp", 1395, 220, 5, 1, true, RGB(255, 0, 255));


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



	//로딩이 다 되면
	if (_currentCount == LOADINGMAX)
	{
		if (_currentCount == LOADINGMAX)
		{

			STATUSMANAGER->setHpBar("HPBar");
			//changeScene에서 sceneNum를 받아와서 해당 스테이지로 이동시킨다.
			switch (nextScene)
			{
			case 0:
				SCENEMANAGER->changeScene("세이브로드");
				break;
			case 1:
				SCENEMANAGER->changeScene("Stage1", saveSlot);
				break;
			case 2:
				SCENEMANAGER->changeScene("Stage2", saveSlot);
				break;
			case 3:
				SCENEMANAGER->changeScene("Stage3", saveSlot);
				break;
			case 4:
				SCENEMANAGER->changeScene("BossStage");
				break;

			}
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
	loadingHelper->_currentCount = 0;
	//메인 스테이지 BGM추가
	SOUNDMANAGER->addSound("MainStage", "sound/BGM/River City Girls OST - Detention.mp3", true, true);
	SOUNDMANAGER->addSound("BossSound", "sound/BGM/River City Girls OST - Boss Misuzu.mp3", true, true);
	SOUNDMANAGER->addSound("BossIntroSound", "sound/BGM/River City Girls OST - Misuzu Intro Theme.mp3", true, true);

	//메인 스테이지 맵추가
	IMAGEMANAGER->addImage("Stage1", "image/map/0.bmp", 2154, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage1Pic", "image/map/0Pic.bmp", 2154, 884, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2", "image/map/1.bmp", 3494, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2Pic", "image/map/1Pic.bmp", 3494, 884, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage3", "image/map/2.bmp", 1980, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage3Pic", "image/map/2Pic.bmp", 1980, 884, false, RGB(255, 0, 255));

	//보스 스테이지 맵추가
	IMAGEMANAGER->addImage("StageBoss", "image/map/boss.bmp", 3000, 1500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("StageBossPic", "image/map/bossPic.bmp", 3000, 1500, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("StageBossAlpha", "image/map/bossAlpha.bmp", 1830, 884, false, RGB(255, 0, 255));

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
	IMAGEMANAGER->addFrameImage("쿄코_죽음", "image/kyoko/dead_3.bmp", 0, 0, 7700, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그림자", "image/kyoko/shadow.bmp", 100, 30, true, RGB(255, 0, 255));

	// 쿄코 사운드 추가
	SOUNDMANAGER->addSound("강공격_타격", "sound/effect/character/kyoko/강공격 타격.wav", false, false);
	SOUNDMANAGER->addSound("기본공격1_타격", "sound/effect/character/kyoko/기본공격1 타격.wav", false, false);
	SOUNDMANAGER->addSound("기본공격2_타격", "sound/effect/character/kyoko/기본공격2 타격.wav", false, false);
	SOUNDMANAGER->addSound("기본공격3_타격", "sound/effect/character/kyoko/기본공격3 타격.wav", false, false);
	SOUNDMANAGER->addSound("기본공격_소리", "sound/effect/character/kyoko/기본공격1, 2.mp3", false, false);
	SOUNDMANAGER->addSound("기본공격3_소리", "sound/effect/character/kyoko/기본공격3.mp3", false, false);
	SOUNDMANAGER->addSound("달리기_소리", "sound/effect/character/kyoko/달리기.wav", false, true);
	SOUNDMANAGER->addSound("대쉬공격_타격", "sound/effect/character/kyoko/대쉬 약공격 타격.wav", false, false);
	SOUNDMANAGER->addSound("마하킥 타격", "sound/effect/character/kyoko/마하킥 타격.wav", false, false);
	SOUNDMANAGER->addSound("마하킥_소리", "sound/effect/character/kyoko/마하킥.wav", false, false);
	SOUNDMANAGER->addSound("점프_소리", "sound/effect/character/kyoko/점프.wav", false, false);
	SOUNDMANAGER->addSound("점프공격", "sound/effect/character/kyoko/점프공격.wav", false, false);
	SOUNDMANAGER->addSound("죽음", "sound/effect/character/kyoko/죽음.wav", false, false);
	SOUNDMANAGER->addSound("착지", "sound/effect/character/kyoko/착지.wav", false, false);
	SOUNDMANAGER->addSound("피격", "sound/effect/character/kyoko/피격.wav", false, false);

	//아이템
	IMAGEMANAGER->addImage("Apple", "image/item/apple.bmp", 58, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Boonger", "image/item/boonger.bmp", 67, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Burger", "image/item/burger.bmp", 72, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Mint", "image/item/mint.bmp", 58, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Shrimp", "image/item/shrimp.bmp", 57, 60, true, RGB(255, 0, 255));

	//NPC 추가
	IMAGEMANAGER->addFrameImage("NpcBoyIdle", "image/npc/npc_boy.bmp", 0, 0, 396, 480, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NpcBoyReact", "image/npc/npc_boy_react.bmp", 0, 0, 306, 480, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NpcGirlIdle", "image/npc/npc_girl.bmp", 0, 0, 312, 396, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NpcGirlReact", "image/npc/npc_girl_react.bmp", 0, 0, 297, 384, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NpcTeacherIdle", "image/npc/npc_teacher.bmp", 0, 0, 324, 522, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NpcTeacherReact", "image/npc/npc_teacher_react.bmp", 0, 0, 360, 504, 3, 2, true, RGB(255, 0, 255));

	//이펙트 추가
	EFFECTMANAGER->addEffect("Enemy_Point", "image/effect/point.bmp", 560, 70, 70, 70, 1, 0.4f, 10);
	EFFECTMANAGER->addEffect("Enemy_Stun", "image/effect/stun.bmp", 420, 54, 70, 54, 1, 0.4f, 10);

	EFFECTMANAGER->addEffect("crack", "image/effect/crack.bmp", 5733, 256, 819, 256, 1, 0.4f, 10);
	EFFECTMANAGER->addEffect("dash", "image/effect/dash.bmp", 1600, 200, 100, 100, 1, 0.4f, 10);
	EFFECTMANAGER->addEffect("hit", "image/effect/hit.bmp", 808, 100, 101, 100, 14, 0.07f, 10);

	//에너미 추가
	IMAGEMANAGER->addImage("Boy_Shadow", "image/enemy/schoolBoy/Boy_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Idle", "image/enemy/schoolBoy/Boy_Idle.bmp", 0, 0, 1200, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Walk", "image/enemy/schoolBoy/Boy_Walk.bmp", 0, 0, 1460, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Run", "image/enemy/schoolBoy/Boy_Run.bmp", 0, 0, 1876, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Block", "image/enemy/schoolBoy/Boy_Block.bmp", 0, 0, 420, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Attack", "image/enemy/schoolBoy/Boy_Attack.bmp", 0, 0, 1598, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack1", "image/enemy/schoolBoy/Boy_ComboAttack1.bmp", 0, 0, 1892, 540, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack2", "image/enemy/schoolBoy/Boy_ComboAttack2.bmp", 0, 0, 766, 460, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack3", "image/enemy/schoolBoy/Boy_ComboAttack3.bmp", 0, 0, 1830, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Hit", "image/enemy/schoolBoy/Boy_Hit.bmp", 0, 0, 1536, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Downup", "image/enemy/schoolBoy/Boy_Downup.bmp", 0, 0, 7027, 400, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Dazed", "image/enemy/schoolBoy/Boy_Dazed.bmp", 0, 0, 620, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Jump", "image/enemy/schoolBoy/Boy_Jump.bmp", 0, 0, 468, 480, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Knockdown", "image/enemy/schoolBoy/Boy_Knockdown.bmp", 0, 0, 4945, 400, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Taunt", "image/enemy/schoolBoy/Boy_Taunt.bmp", 0, 0, 1704, 420, 11, 2, true, RGB(255, 0, 255));

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

	IMAGEMANAGER->addImage("MT_Shadow", "image/enemy/mt/MT_Shadow.bmp", 112, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Idle", "image/enemy/mt/MT_Idle.bmp", 0, 0, 1634, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Walk", "image/enemy/mt/MT_Walk.bmp", 0, 0, 1984, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Run", "image/enemy/mt/MT_Run.bmp", 0, 0, 1933, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Block", "image/enemy/mt/MT_Block.bmp", 0, 0, 486, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Attack", "image/enemy/mt/MT_Attack.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack1", "image/enemy/mt/MT_ComboAttack1.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack2", "image/enemy/mt/MT_ComboAttack2.bmp", 0, 0, 2216, 430, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack3", "image/enemy/mt/MT_ComboAttack3.bmp", 0, 0, 4068, 450, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Hit", "image/enemy/mt/MT_Hit.bmp", 0, 0, 523, 380, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Downup", "image/enemy/mt/MT_Downup.bmp", 0, 0, 8919, 440, 31, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Dazed", "image/enemy/mt/MT_Dazed.bmp", 0, 0, 618, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Jump", "image/enemy/mt/MT_Jump.bmp", 0, 0, 612, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Knockdown", "image/enemy/mt/MT_Knockdown.bmp", 0, 0, 8056, 440, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Taunt", "image/enemy/mt/MT_Taunt.bmp", 0, 0, 558, 400, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("CheerLeader_Shadow", "image/enemy/cheerLeader/CheerLeader_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Idle", "image/enemy/cheerLeader/CheerLeader_Idle.bmp", 0, 0, 2133, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Walk", "image/enemy/cheerLeader/CheerLeader_Walk.bmp", 0, 0, 2499, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Run", "image/enemy/cheerLeader/CheerLeader_Run.bmp", 0, 0, 1291, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Block", "image/enemy/cheerLeader/CheerLeader_Block.bmp", 0, 0, 457, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Attack", "image/enemy/cheerLeader/CheerLeader_Attack.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack1", "image/enemy/cheerLeader/CheerLeader_ComboAttack1.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack2", "image/enemy/cheerLeader/CheerLeader_ComboAttack2.bmp", 0, 0, 1715, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack3", "image/enemy/cheerLeader/CheerLeader_ComboAttack3.bmp", 0, 0, 6577, 600, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Hit", "image/enemy/cheerLeader/CheerLeader_Hit.bmp", 0, 0, 1445, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Downup", "image/enemy/cheerLeader/CheerLeader_Downup.bmp", 0, 0, 8265, 400, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Dazed", "image/enemy/cheerLeader/CheerLeader_Dazed.bmp", 0, 0, 554, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Jump", "image/enemy/cheerLeader/CheerLeader_Jump.bmp", 0, 0, 776, 500, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Knockdown", "image/enemy/cheerLeader/CheerLeader_Knockdown.bmp", 0, 0, 6482, 400, 22, 2, true, RGB(255, 0, 255));

	//오브젝트 이미지 추가
	IMAGEMANAGER->addImage("chair", "image/object/chair.bmp", 179, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("좌기둥", "image/object/Lgidoong.bmp", 153, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("우기둥", "image/object/Rgidoong.bmp", 153, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지포스", "image/object/geForce.bmp", 100, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("라데온", "image/object/radeon.bmp", 80, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코1", "image/object/kyoko_1.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코2", "image/object/kyoko_2.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코3", "image/object/kyoko_3.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코4", "image/object/kyoko_4.bmp", 386, 460, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("쿄코1그림자", "image/object/kyoko_1_shadow.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코2그림자", "image/object/kyoko_2_shadow.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코3그림자", "image/object/kyoko_3_shadow.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코4그림자", "image/object/kyoko_4_shadow.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미스즈1", "image/object/misuzu_1.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미스즈2", "image/object/misuzu_2.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미스즈3", "image/object/misuzu_3.bmp", 386, 460, true, RGB(255, 0, 255));


	//UI IMAGE
	IMAGEMANAGER->addImage("HPUI", "image/kyoko/UI/hp_ui.bmp", 600, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPBar", "image/kyoko/UI/hpbar.bmp", 26, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MahaGauge", "image/kyoko/UI/mahagauge_1.bmp", 362, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴", "image/menu/phone.bmp", 287, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체크", "image/menu/check.bmp", 65, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("bottomChain", "image/chainLock/bottomChain.bmp", 1280, 818, 1, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("leftChain", "image/chainLock/leftChain.bmp", 794, 720, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rightChain", "image/chainLock/rightChain.bmp", 697, 720, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("topChain", "image/chainLock/topChain.bmp", 1280, 687, 1, 15, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Heart", "image/menu/deathHeart.bmp", 19200, 720, 15, 1, true, RGB(255, 0, 255));

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
