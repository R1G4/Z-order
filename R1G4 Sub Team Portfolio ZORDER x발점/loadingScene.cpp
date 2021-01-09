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
	_back = IMAGEMANAGER->addImage("����", "image/loading/loadingBack.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addFrameImage("�ε����", "image/loading/�ε�.bmp", 1395, 220, 5, 1, true, RGB(255, 0, 255));

	//_loadingBar = new progressBar;
	//_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	//_loadingBar->setGauge(0, 0);

	//�����带 ����غ���
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadFunction,		//������ ����� �Լ� ��
		this,				//������ �Ű�����(this�� �θ� �� Ŭ����)
		NULL,				//�������� Ư��(��ٸ���, �ٷ� ����(NULL�̸� ��� �ش�))
		NULL				//������ ���� �� �������� ID �Ѱ��� ������ NULL�� �д�
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

	//�ε��� �� �Ǹ�
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("��������1");
	}
}

void loadingScene::render()
{
	//�׸����� �̹��� ��θ� �ؽ�Ʈ�� �����൵ �ǰ�

	_back->render(getMemDC());
	_background->aniRender(getMemDC(), WINSIZEX - 279, WINSIZEY - 220, _loading);

}



DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//���⿡�ٰ�
	//�̹����Ŵ�����, ���� �Ŵ��� �Ἥ
	//add ���ָ� �ȴ�.

	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	//���� �������� BGM�߰�
	SOUNDMANAGER->addSound("MainStage", "sound/BGM/River City Girls OST - Detention.mp3", true, true);
	SOUNDMANAGER->addSound("BossSound", "sound/BGM/River City Girls OST - Boss Misuzu.mp3", true, true);
	//���� �������� ���߰�
	IMAGEMANAGER->addImage("Stage1", "image/map/0.bmp", 2154, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage1Pic", "image/map/0Pic.bmp", 2154, 884, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2", "image/map/1.bmp", 3494, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Stage2Pic", "image/map/1Pic.bmp", 3494, 884, false, RGB(255, 0, 255));

	//���� �������� ���߰�
	IMAGEMANAGER->addImage("StageBoss", "image/map/boss.bmp", 1830, 884, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("StageBossPic", "image/map/bossPic.bmp", 1830, 884, false, RGB(255, 0, 255));

	//���� �̹��� �߰�
	IMAGEMANAGER->addFrameImage("����_�Ϲ�", "image/kyoko/idle_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ȱ�", "image/kyoko/walk_1.bmp", 0, 0, 3600, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�޸���", "image/kyoko/run_1.bmp", 0, 0, 4800, 400, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "image/kyoko/jump_1.bmp", 0, 0, 900, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����1", "image/kyoko/attack_1_1.bmp", 0, 0, 1800, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����2", "image/kyoko/attack_2_1.bmp", 0, 0, 2100, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����3", "image/kyoko/attack_3_3.bmp", 0, 0, 2700, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_������", "image/kyoko/attack_strong_2.bmp", 0, 0, 3000, 600, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����ű", "image/kyoko/mahaKick_2.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ǰ�1", "image/kyoko/attacked_1_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_�ǰ�2", "image/kyoko/attacked_2_1.bmp", 0, 0, 1200, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_����", "image/kyoko/dead_1.bmp", 0, 0, 6600, 400, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׸���", "image/kyoko/shadow.bmp", 100, 30, true, RGB(255, 0, 255));

	//���ʹ� �̹��� �߰�
	IMAGEMANAGER->addImage("Girl_Shadow", "image/SchoolGirl size200/SchoolGirl_Shadow.bmp", 110, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Idle", "image/SchoolGirl size200/Girl_Idle.bmp", 0, 0, 1320, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Walk", "image/SchoolGirl size200/Girl_Walk.bmp", 0, 0, 1394, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Run", "image/SchoolGirl size200/Girl_Run.bmp", 0, 0, 1780, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Block", "image/SchoolGirl size200/Girl_Block.bmp", 0, 0, 460, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Attack", "image/SchoolGirl size200/Girl_Attack.bmp", 0, 0, 1934, 420, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack1", "image/SchoolGirl size200/Girl_ComboAttack1.bmp", 0, 0, 1505, 430, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack2", "image/SchoolGirl size200/Girl_ComboAttack2.bmp", 0, 0, 1470, 440, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack3", "image/SchoolGirl size200/Girl_ComboAttack3.bmp", 0, 0, 2700, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Hit", "image/SchoolGirl size200/Girl_Hit.bmp", 0, 0, 1626, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Downup", "image/SchoolGirl size200/Girl_Downup.bmp", 0, 0, 7013, 380, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Dazed", "image/SchoolGirl size200/Girl_Dazed.bmp", 0, 0, 656, 410, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Jump", "image/SchoolGirl size200/Girl_Jump.bmp", 0, 0, 432, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Knockdown", "image/SchoolGirl size200/Girl_Knockdown.bmp", 0, 0, 4361, 380, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Taunt", "image/SchoolGirl size200/Girl_Taunt.bmp", 0, 0, 4015, 420, 26, 2, true, RGB(255, 0, 255));

	//������Ʈ �̹��� �߰�
	IMAGEMANAGER->addImage("chair", "image/object/chair.bmp", 179, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�±��", "image/object/Lgidoong.bmp", 153, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/object/Rgidoong.bmp", 153, 720, true, RGB(255, 0, 255));


	//UI IMAGE
	IMAGEMANAGER->addImage("HPUI", "image/kyoko/UI/hp_ui.bmp", 600, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPBar", "image/kyoko/UI/hpbar.bmp", 26, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MahaGauge", "image/kyoko/UI/mahagauge_1.bmp", 362, 18, true, RGB(255, 0, 255));


	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		//���⿡ ���Ϲ� ���������� �̹����� ���� �� ���ҽ� ���� �߰��ض�

		//CPU ��� �����Ŵ°ǵ�
		//�̰� �Ȱɸ� �ʹ� �������� �� �����̸� �Ѿ���� (1000������)
		Sleep(1);

		loadingHelper->_currentCount++;
	}


	return 0;
}
