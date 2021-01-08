#include "stdafx.h"
#include "saveLoad.h"

saveLoad::saveLoad()
{
}

saveLoad::~saveLoad()
{
}

HRESULT saveLoad::init()
{
	addimage();
	selecttab();
	for (int i = 0; i < 3; i++)
	{
		tab[0].select = true;
		tab[1].select = false;
		tab[2].select = false;
		tab[i].x = WINSIZEX;
		tab[i].y = 60;
	}

	movepower = 50;

	count = 1;

	return S_OK;
}

void saveLoad::release()
{
}

void saveLoad::update()
{
	selecttab();
	key();
	intb++;

	//����� �� ����
	for (int i = 0; i < 3; i++)
	{
		if (tab[i].move == true)tab[i].x -= movepower;

		if (tab[i].x <= WINSIZEX / 2 + 50)
		{
			tab[i].x = WINSIZEX / 2 + 50;
		}
		tab[i].rc = RectMake(tab[i].x, tab[i].y + i * 200, 100, 100);
	}
	if (intb >= 0)
	{
		tab[0].move = true;
	}
	if (intb >= 3)
	{
		tab[1].move = true;
	}
	if (intb >= 6)
	{
		tab[2].move = true;
	}


}

void saveLoad::render()
{
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	tab[0].img->render(getMemDC(), tab[0].rc.left, tab[0].rc.top);
	tab[1].img->render(getMemDC(), tab[1].rc.left, tab[1].rc.top);
	tab[2].img->render(getMemDC(), tab[2].rc.left, tab[2].rc.top);
	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	for (int i = 0; i < 3; i++)
	//	{
	//		Rectangle(getMemDC(), tab[i].rc);
	//	}
	//}
	for (int i = 0; i < 3; i++)
	{
		//������ �ƴ�? -> "New Game"���� "������Ƽ �����б�"�� Ű���� �ٲ���
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(60, 0, 60, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����ǹ��� �־�");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
		sprintf_s(str, "New Game");
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), tab[i].x + 155, tab[i].y + 60 + i * 200, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);

		//������ �ƴ�? -> "--"���� ����� ��������("Stage 1" "Stage 2" "Stage 3")���� Ű���� �ٲ���
		HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush1 = (HBRUSH)SelectObject(getMemDC(), brush1);
		HFONT myFont1 = CreateFont(40, 0, 60, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����ǹ��� �־�");
		HFONT oldFont1 = (HFONT)SelectObject(getMemDC(), myFont1);
		sprintf_s(str, "--");
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), tab[i].x + 160, tab[i].y + 115 + i * 200, str, strlen(str));
		SelectObject(getMemDC(), oldFont1);
		DeleteObject(myFont1);
		SelectObject(getMemDC(), oldBrush1);
		DeleteObject(brush1);
	}

}

void saveLoad::addimage()
{
	IMAGEMANAGER->addImage("���", "image/savescene/���̺�â.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("A_off", "image/savescene/����A_off.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("B_off", "image/savescene/����B_off.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("C_off", "image/savescene/����C_off.bmp", 485, 199, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("A_on", "image/savescene/����A_on.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("B_on", "image/savescene/����B_on.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("C_on", "image/savescene/����C_on.bmp", 485, 199, true, RGB(255, 0, 255));

	//�������� �� ������
	//����
	IMAGEMANAGER->addImage("1_off", "image/savescene/��/stage1_off.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2_off", "image/savescene/��/stage2_off.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3_off", "image/savescene/��/stage3_off.bmp", 114, 130, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("1_on", "image/savescene/��/stage1_on.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2_on", "image/savescene/��/stage2_on.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3_on", "image/savescene/��/stage3_on.bmp", 114, 130, true, RGB(255, 0, 255));
}

void saveLoad::selecttab()
{
	for (int i = 0; i < 3; i++)
	{
		//����A
		if (tab[0].select == false)
		{
			tab[0].img = IMAGEMANAGER->findImage("A_off");
		}
		else
		{
			tab[0].img = IMAGEMANAGER->findImage("A_on");
		}

		//����B
		if (tab[1].select == false)
		{
			tab[1].img = IMAGEMANAGER->findImage("B_off");
		}
		else
		{
			tab[1].img = IMAGEMANAGER->findImage("B_on");
		}

		//����C
		if (tab[2].select == false)
		{
			tab[2].img = IMAGEMANAGER->findImage("C_off");
		}
		else
		{
			tab[2].img = IMAGEMANAGER->findImage("C_on");
		}

		if (count == 1)
		{
			tab[0].select = true;
			tab[1].select = false;
			tab[2].select = false;
		}

		if (count == 2)
		{
			tab[0].select = false;
			tab[1].select = true;
			tab[2].select = false;
		}

		if (count == 3)
		{
			tab[0].select = false;
			tab[1].select = false;
			tab[2].select = true;
		}
	}
}

void saveLoad::key()
{
	if (count > 3) count = 1;
	if (count < 1)count = 3;
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		count++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		count--;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->stop("saveLoad");
		SCENEMANAGER->changeScene("�ε���");
	}
}
