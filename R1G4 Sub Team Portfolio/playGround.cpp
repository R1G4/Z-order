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

	INIDATA->addData("동현", "드립력", "120000");
	INIDATA->addData("동현", "드립절제력", "0");
	INIDATA->addData("동현", "드립조절잘해", "13");

	INIDATA->addData("창훈", "수면절제력", "20");
	INIDATA->addData("창훈", "식욕절제력", "1");

	INIDATA->iniSave("25기");

	_str = INIDATA->loadDataString("25기", "동현", "드립력");
	_test = INIDATA->loadDataInterger("25기", "창훈", "수면절제력");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	

	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

