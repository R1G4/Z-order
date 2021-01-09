#include "stdafx.h"
#include "enemyManager.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	//추후 에너미매니저가 아닌 다른곳으로 옮겨야함
	setEnemytempState();
	return S_OK;
}

void enemyManager::release()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();
	}
}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->setKyokoAddressLink(_kyoko);
		(*_viEnemy)->update();
	}
}

void enemyManager::setEnemytempState()
{
	//테스트, x,y지정하여 막 뿌려도 됨

	//임시로 생성중
	enemy* _en1;
	_en1 = new schoolGirl;
	//좌표x, 좌표y, 초기 상태 , 초기 방향( 0 == Left, 1= Right)
	//init(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));
	_en1->init(300, 500, enemy::IDLE, enemy::LEFT);
	_vEnemy.push_back(_en1);

	enemy* _en2;
	_en2 = new schoolBoy;
	_en2->init(1700, 550, enemy::IDLE, enemy::LEFT);
	_vEnemy.push_back(_en2);

	enemy* _en3;
	_en3 = new schoolBoy;
	_en3->init(1700, 600, enemy::IDLE);
	_vEnemy.push_back(_en3);

	enemy* _en4;
	_en4 = new MT;
	_en4->init(1700, 650);
	_vEnemy.push_back(_en4);

	enemy* _en5;
	_en5 = new cheerLeader;
	_en5->init(1600, 600, enemy::TAUNT);
	_vEnemy.push_back(_en5);
}

void enemyManager::setEnemyState2()
{
	//테스트, x,y지정하여 막 뿌려도 됨

	//임시로 생성중
	enemy* _en1;
	_en1 = new schoolGirl;
	//좌표x, 좌표y, 초기 상태 , 초기 방향( 0 == Left, 1= Right)
	//init(float x, float y, STATE state = IDLE, DIRECTION direction = (DIRECTION)RND->getFromIntTo(0, 2));
	_en1->init(300, 500, enemy::IDLE, enemy::LEFT);
	_vEnemy.push_back(_en1);

	enemy* _en2;
	_en2 = new schoolBoy;
	_en2->init(1700, 550, enemy::IDLE, enemy::LEFT);
	_vEnemy.push_back(_en2);

	enemy* _en3;
	_en3 = new schoolBoy;
	_en3->init(1700, 600, enemy::IDLE);
	_vEnemy.push_back(_en3);

	enemy* _en4;
	_en4 = new MT;
	_en4->init(1700, 650);
	_vEnemy.push_back(_en4);

	enemy* _en5;
	_en5 = new cheerLeader;
	_en5->init(1600, 600, enemy::TAUNT);
	_vEnemy.push_back(_en5);
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

void enemyManager::render(POINT camera)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render(camera);
	}
}

//충돌처리인데 혹시몰라서 여기에 잠깐 백업
//for (int i = 0; i < _em->getVEnemy().size(); i++)
//{
//	bool isCollision = false;
//	//아래에서 위로 박을때
//	for (int j = _em->getVEnemy()[i]->getShadowRc().top; j <= _em->getVEnemy()[i]->getShadowRc().top; j++)
//	{
//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
//		{
//			_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y - 1);
//			isCollision = true;
//			break;
//		}
//	}
//
//	//위에서 아래로 박을떄
//	for (int j = _em->getVEnemy()[i]->getShadowRc().bottom; j >= _em->getVEnemy()[i]->getShadowRc().bottom; j--)
//	{
//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), _em->getVEnemy()[i]->getShadowRc().left, j);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
//		{
//
//			_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x, _em->getVEnemy()[i]->getEnemyPoint().y + 1);
//			isCollision = true;
//			break;
//		}
//	}
//
//	//오른쪽에서 왼쪽으로 박을때
//	for (int j = _em->getVEnemy()[i]->getShadowRc().left; j <= _em->getVEnemy()[i]->getShadowRc().left; j++)
//	{
//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
//		{
//			_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x + 1, _em->getVEnemy()[i]->getEnemyPoint().y);
//			isCollision = true;
//			break;
//		}
//
//	}
//
//	//왼쪽에서 오른쪽
//	for (int j = _em->getVEnemy()[i]->getShadowRc().right; j >= _em->getVEnemy()[i]->getShadowRc().right; j--)
//	{
//		//_em->getVEnemy()[i]->setState(enemy::IDLE);
//		//_em->getVEnemy()[i]->getMotion()->stop();
//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage1Pic")->getMemDC(), j, (_em->getVEnemy()[i]->getShadowRc().bottom + _em->getVEnemy()[i]->getShadowRc().top) / 2);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
//		{
//			_em->getVEnemy()[i]->setEnemyPoint(_em->getVEnemy()[i]->getEnemyPoint().x - 1, _em->getVEnemy()[i]->getEnemyPoint().y);
//			isCollision = true;
//			break;
//		}
//	}
//	_em->getVEnemy()[i]->setCollision(isCollision);
//}