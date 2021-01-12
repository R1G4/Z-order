#include "stdafx.h"
#include "stage2.h"

HRESULT stage2::init()
{
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);
	_opt->setSlot(saveSlot);

	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->setKyokoMemory(_player);
	_em->init(2);
	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("�±��");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("����");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	alpha = 255;
	return S_OK;
}

HRESULT stage2::init(int slot)
{
	saveSlot = slot;
	_opt = new opTion;
	_opt->init();
	_opt->setStageName(2);
	_opt->setSlot(saveSlot);
	stage2 = IMAGEMANAGER->findImage("Stage2");
	stage2Pic = IMAGEMANAGER->findImage("Stage2Pic");
	_player = new kyoko;
	_player->init();
	_em = new enemyManager;
	_em->setKyokoMemory(_player);
	_em->init(2);
	Lobj.x = WINSIZEX / 2 - 230;
	Lobj.y = 82;
	Lobj.img = IMAGEMANAGER->findImage("�±��");
	Lobj.rc = RectMake(Lobj.x, Lobj.y, 100, Lobj.img->getHeight());

	Robj.x = WINSIZEX / 2 + 1950;
	Robj.y = 82;
	Robj.img = IMAGEMANAGER->findImage("����");
	Robj.rc = RectMake(Robj.x, Robj.y, 100, Robj.img->getHeight());
	UI = new UIManager;
	UI->setKyokoMemory(_player);
	UI->init();

	alpha = 255;
	return S_OK;

}

void stage2::release()
{
}

void stage2::update()
{
	_opt->update();
	UI->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();
	pixelCollision();
	AttackCollision();
	_player->update();
	_em->update();
	camera = CAMERAMANAGER->CameraMake(_player->getShadow().left, _player->getShadow().top, BOTH, stage2);
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &Lobj.rc))
	{
		alpha = 100;
	}
	else if (IntersectRect(&temp, &_player->getRect(), &Robj.rc))
	{
		alpha = 100;
	}
	else alpha = 255;
}

void stage2::render()
{
	stage2->render(getMemDC(), 0, 0, camera);

	//������ ����~
	for (int i = 0; i < _em->getVItem().size(); i++)
	{
		item* _item = _em->getVItem()[i];
		_item->render(camera);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		stage2Pic->render(getMemDC(), 0, 0, camera);
		Rectangle(getMemDC(), Lobj.rc, camera);
		Rectangle(getMemDC(), Robj.rc, camera);

		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			enemy* enemy = _em->getVEnemy()[i];
			//�浹��
			Rectangle(getMemDC(), enemy->getDebugRect(), camera);
			//�׸���
			Rectangle(getMemDC(), enemy->getDebugShadowRc(), camera);
			//����
			HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			Rectangle(getMemDC(), enemy->getDebugAttackRc(), camera);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(brush);

		}
	}
	zOrder();
	Lobj.img->alphaRender(getMemDC(), Lobj.x, Lobj.y, alpha, camera);
	Robj.img->alphaRender(getMemDC(), Robj.x, Robj.y, alpha, camera);
	UI->render();
	_opt->render();

}

void stage2::pixelCollision()
{
	//�Ʒ����� ���� ������
	for (int i = _player->getShadow().top; i <= _player->getShadow().top; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i + _player->getShadow().bottom - _player->getShadow().top - 10);
			_player->setNoSpeed(true);
			break;
		}

	}

	//������ �Ʒ��� ������
	for (int i = _player->getShadow().bottom; i >= _player->getShadow().bottom; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), _player->getShadow().left, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0))
		{
			_player->setKyokoPoint(_player->getKyokoPoint().x, i - _player->getShadow().bottom + _player->getShadow().top + 10);
			_player->setNoSpeed(true);
			break;
		}
	}

	//�����ʿ��� �������� ������
	for (int i = _player->getShadow().left; i <= _player->getShadow().left; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i + (_player->getShadow().right - _player->getShadow().left) / 2 + 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}

	//���ʿ��� ���������� ������
	for (int i = _player->getShadow().right; i >= _player->getShadow().right; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Stage2Pic")->getMemDC(), i, (_player->getShadow().bottom + _player->getShadow().top) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) || (r == 0 && g == 255 && b == 0) || (r == 0 && g == 0 && b == 255))
		{
			_player->setKyokoPoint(i - (_player->getShadow().right - _player->getShadow().left) / 2 - 10, _player->getKyokoPoint().y);
			_player->setNoSpeed(true);
			break;
		}

	}
}


void stage2::AttackCollision()
{
	RECT _temp;

	if (!_player->getHit())
	{
		for (int i = 0; i < _em->getVEnemy().size(); i++)
		{
			// �÷��̾� �浹��Ʈ�� �� ���ݷ�Ʈ�� �´�����
			if (IntersectRect(&_temp, &_player->getRect(), &_em->getVEnemy()[i]->getDebugAttackRc()))
			{
				cout << "�ƾ�" << endl;
				_player->setHit(true);
				// ���� �÷��̾�� ���ʿ� ������ ���� Ÿ���� ������ �����ʿ� ������ ������ Ÿ���� ������
				if (_em->getVEnemy()[i]->getRect().left <= _player->getRect().left)
					_player->setHitRight(false);
				else 
					_player->setHitRight(true);

			}
			// �÷��̾� �浹��Ʈ�� ������ ��Ʈ�� �´�����
			for (int j = 0; j < _em->getVItem().size(); j++)
			{
				if (IntersectRect(&_temp, &_player->getRect(), &_em->getVItem()[j]->getRect()))
				{
					//������ ����
					_em->getVItem()[j]->ItemRemove();
					//�����ۿ� ���� ü�� ȸ��
					STATUSMANAGER->heal(_em->getVItem()[j]->getHeal(), "HPBar");
				}
			}
		}
	}
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		//getEnemyRect�� �浹�� getRect�� �ٲܱ�? �ǰ� ������ ���ʹ� �̹��� ��Ʈ�� �ϴ� �ݴ���⿡���� �´� ���� �߻� ���� �����ؼ� �����ؾ���
		if (IntersectRect(&_temp, &_player->getAttackRect(), &_em->getVEnemy()[i]->getEnemyRect()))
		{
			switch (_player->getKyokoDirection())
			{
				case	KYOKODIRECTION_RIGHT_ATTACK_1:
				case	KYOKODIRECTION_RIGHT_ATTACK_2:
				case	KYOKODIRECTION_RIGHT_ATTACK_DASH:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK:
				case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN:
					//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
					if (!_em->getVEnemy()[i]->block(enemy::LEFT))
						//������ ���� ���ߴٸ� �ǰ� üũ
						_em->getVEnemy()[i]->hit(enemy::LEFT);
					break;
				case	KYOKODIRECTION_RIGHT_ATTACK_3:
				case	KYOKODIRECTION_RIGHT_ATTACK_STRONG:
				case	KYOKODIRECTION_RIGHT_MAHAKICK:
					//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
					if (!_em->getVEnemy()[i]->block(enemy::LEFT))
						//������ ���� ���ߴٸ� �ٿ� üũ
						_em->getVEnemy()[i]->downup(enemy::LEFT);
					break;
				case	KYOKODIRECTION_LEFT_ATTACK_1:
				case	KYOKODIRECTION_LEFT_ATTACK_2:
				case	KYOKODIRECTION_LEFT_ATTACK_DASH:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK:
				case	KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN:
					//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
					if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
						//������ ���� ���ߴٸ� �ǰ� üũ
						_em->getVEnemy()[i]->hit(enemy::RIGHT);
					break;
				case	KYOKODIRECTION_LEFT_ATTACK_3:
				case	KYOKODIRECTION_LEFT_ATTACK_STRONG:
				case	KYOKODIRECTION_LEFT_MAHAKICK:
					//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
					if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
						//������ ���� ���ߴٸ� �ٿ� üũ
						_em->getVEnemy()[i]->downup(enemy::RIGHT);
					break;
			}

		}
	}
}
#pragma region ���� �ڵ忡 ������ ������ �Ʒ��� ��ó�� ��
//switch (_player->getKyokoDirection())
//{
//case	KYOKODIRECTION_RIGHT_ATTACK_1:
//case	KYOKODIRECTION_RIGHT_ATTACK_2:
//case	KYOKODIRECTION_RIGHT_ATTACK_DASH:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_WALK:
//case	KYOKODIRECTION_RIGHT_ATTACK_JUMP_RUN:
//case	KYOKODIRECTION_LEFT_ATTACK_1:
//case	KYOKODIRECTION_LEFT_ATTACK_2:
//case	KYOKODIRECTION_LEFT_ATTACK_DASH:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP_WALK:
//case	KYOKODIRECTION_LEFT_ATTACK_JUMP_RUN:
//	if (_player->getKyokoPoint().x <= _em->getVEnemy()[i]->getEnemyPoint().x)
//	{
//		//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
//		if (!_em->getVEnemy()[i]->block(enemy::LEFT))
//			//������ ���� ���ߴٸ� �ǰ� üũ
//			_em->getVEnemy()[i]->hit(enemy::LEFT);
//	}
//	else
//	{
//		//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
//		if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
//			//������ ���� ���ߴٸ� �ǰ� üũ
//			_em->getVEnemy()[i]->hit(enemy::RIGHT);
//	}
//	break;
//case	KYOKODIRECTION_RIGHT_ATTACK_3:
//case	KYOKODIRECTION_RIGHT_ATTACK_STRONG:
//case	KYOKODIRECTION_RIGHT_MAHAKICK:
//case	KYOKODIRECTION_LEFT_ATTACK_3:
//case	KYOKODIRECTION_LEFT_ATTACK_STRONG:
//case	KYOKODIRECTION_LEFT_MAHAKICK:
//	if (_player->getKyokoPoint().x <= _em->getVEnemy()[i]->getEnemyPoint().x)
//	{
//		//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
//		if (!_em->getVEnemy()[i]->block(enemy::LEFT))
//			//������ ���� ���ߴٸ� �ٿ� üũ
//			_em->getVEnemy()[i]->downup(enemy::LEFT);
//	}
//	else
//	{
//		//�÷��̾��� ������ ���ʹ̰� ���Ҵ��� üũ
//		if (!_em->getVEnemy()[i]->block(enemy::RIGHT))
//			//������ ���� ���ߴٸ� �ٿ� üũ
//			_em->getVEnemy()[i]->downup(enemy::RIGHT);
//	}
//	break;
#pragma endregion
