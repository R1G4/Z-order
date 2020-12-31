#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_psh_rc = RectMake(50, 50, 50, 50);		//렉트쟝
	_SCH_rc = RectMake(100, 50, 50, 50);	//렉트쟝
	_KDH_rc = RectMake(150, 50, 50, 50);	//렉트쟝
	_KDK_rc = RectMake(200, 50, 50, 50);	//렉트쟝
	_PJU_rc = RectMake(250, 50, 50, 50);	//렉트쟝
	IMAGEMANAGER->addImage("새배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총알", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 1536, 79, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("버튼", "button.bmp", 0, 0, 122, 62, 1, 2, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("테스트씬", new testScene);
	SCENEMANAGER->addScene("마계씬", new ghostScene);

	SCENEMANAGER->changeScene("마계씬");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	IMAGEMANAGER->findImage("새배경")->render(getMemDC());
	
	
	SCENEMANAGER->render();


	TIMEMANAGER->render(getMemDC());


	HBRUSH brush = CreateSolidBrush(RGB(204, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _psh_rc);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);
	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
	Rectangle(getMemDC(), _SCH_rc);
	SelectObject(getMemDC(), oldBrush2);
	DeleteObject(brush2);
	HBRUSH brush3 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldbrush3 = (HBRUSH)SelectObject(getMemDC(), brush3);
	Rectangle(getMemDC(), _KDH_rc);
	SelectObject(getMemDC(), oldbrush3);
	DeleteObject(brush3);
	HBRUSH brush4 = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbrush4 = (HBRUSH)SelectObject(getMemDC(), brush4);
	Rectangle(getMemDC(), _KDK_rc);
	SelectObject(getMemDC(), oldbrush4);
	DeleteObject(brush4);
	HBRUSH brush5 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldbrush5 = (HBRUSH)SelectObject(getMemDC(), brush5);
	Rectangle(getMemDC(), _PJU_rc);
	SelectObject(getMemDC(), oldbrush5);
	DeleteObject(brush5);
	
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

