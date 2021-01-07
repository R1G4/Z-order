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

	//저장된 탭 등장
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
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	tab[0].img->render(getMemDC(), tab[0].rc.left, tab[0].rc.top);
	tab[1].img->render(getMemDC(), tab[1].rc.left, tab[1].rc.top);
	tab[2].img->render(getMemDC(), tab[2].rc.left, tab[2].rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), tab[i].rc);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		//저장이 됐다? -> "New Game"에서 "리버시티 고등학교"로 키값을 바꿔줌
		char str[256];
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HFONT myFont = CreateFont(60, 0, 60, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "배달의민족 주아");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
		sprintf_s(str, "New Game");
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), tab[i].x + 155, tab[i].y + 60 + i * 200, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(brush);

		//저장이 됐다? -> "--"에서 저장된 스테이지("Stage 1" "Stage 2" "Stage 3")으로 키값을 바꿔줌
		HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 255));
		HBRUSH oldBrush1 = (HBRUSH)SelectObject(getMemDC(), brush1);
		HFONT myFont1 = CreateFont(40, 0, 60, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "배달의민족 주아");
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
	IMAGEMANAGER->addImage("배경", "savescene/세이브창.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//비선택
	IMAGEMANAGER->addImage("A_off", "savescene/파일A_off.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("B_off", "savescene/파일B_off.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("C_off", "savescene/파일C_off.bmp", 485, 199, true, RGB(255, 0, 255));

	//선택
	IMAGEMANAGER->addImage("A_on", "savescene/파일A_on.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("B_on", "savescene/파일B_on.bmp", 485, 199, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("C_on", "savescene/파일C_on.bmp", 485, 199, true, RGB(255, 0, 255));

	//스테이지 맵 아이콘
	//비선택
	IMAGEMANAGER->addImage("1_off", "savescene/맵/stage1_off.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2_off", "savescene/맵/stage2_off.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3_off", "savescene/맵/stage3_off.bmp", 114, 130, true, RGB(255, 0, 255));

	//선택
	IMAGEMANAGER->addImage("1_on", "savescene/맵/stage1_on.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2_on", "savescene/맵/stage2_on.bmp", 114, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3_on", "savescene/맵/stage3_on.bmp", 114, 130, true, RGB(255, 0, 255));
}

void saveLoad::selecttab()
{
	for (int i = 0; i < 3; i++)
	{
		//파일A
		if (tab[0].select == false)
		{
			tab[0].img = IMAGEMANAGER->findImage("A_off");
		}
		else
		{
			tab[0].img = IMAGEMANAGER->findImage("A_on");
		}

		//파일B
		if (tab[1].select == false)
		{
			tab[1].img = IMAGEMANAGER->findImage("B_off");
		}
		else
		{
			tab[1].img = IMAGEMANAGER->findImage("B_on");
		}

		//파일C
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
}

