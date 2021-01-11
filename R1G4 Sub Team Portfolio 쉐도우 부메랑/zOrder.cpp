#include "stdafx.h"
#include "zOrder.h"

zOrder::zOrder()
{
}

zOrder::~zOrder()
{
}


void zOrder::addZorder(HDC hdc, image* img, animation* ani, ObjectType type, int x, int z, float jumpPower)
{
	OrderObject obj;
	obj.hdc = hdc;
	obj.img = img;
	obj.ani = ani;
	obj.obType = type;
	obj.x = x;
	obj.z = z;
	obj.jumpPower = jumpPower;
	obj.frameX = -1;
	obj.frameY = -1;
	vZpoint.push_back(obj);
}

void zOrder::addZorder(HDC hdc, image * img, animation * ani, ObjectType type, int x, int z, float jumpPower, int frameX, int frameY)
{
	OrderObject obj;
	obj.hdc = hdc;
	obj.img = img;
	obj.ani = ani;
	obj.obType = type;
	obj.x = x;
	obj.z = z;
	obj.jumpPower = jumpPower;
	obj.frameX =frameX;
	obj.frameY = frameY;
	vZpoint.push_back(obj);

}

void zOrder::addZorder(HDC hdc, image * img, ObjectType type, int x, int z, float jumpPower, int frameX, int frameY)
{
	OrderObject obj;
	obj.hdc = hdc;
	obj.img = img;
	obj.ani = NULL;
	obj.obType = type;
	obj.x = x;
	obj.z = z;
	obj.jumpPower = jumpPower;
	obj.frameX = frameX;
	obj.frameY = frameY;
	vZpoint.push_back(obj);
}

void zOrder::addZorder(HDC hdc, image * img, ObjectType type, int x, int z, float jumpPower)
{
	OrderObject obj;
	obj.hdc = hdc;
	obj.img = img;
	obj.ani = NULL;
	obj.obType = type;
	obj.x = x;
	obj.z = z;
	obj.jumpPower = jumpPower;
	obj.frameX = -1;
	obj.frameY = -1;
	vZpoint.push_back(obj);
}

void zOrder::quickSort(int a,int b)
{
	if (a >= b)return;
	int pivot = vZpoint[(a+b)/2].z;
	int left = a;
	int right = b;
	while (left <= right)
	{
		while (vZpoint[left].z < pivot)++left;
		while (vZpoint[right].z > pivot)--right;
		if (left <= right)
		{
			swap(vZpoint[left], vZpoint[right]);
			++left; 
			--right;
		}
	}
	quickSort(a, right);
	quickSort(left, b);
	
}


void zOrder::swap(OrderObject obj1,OrderObject obj2)
{
	OrderObject temp = obj1;
	obj1 = obj2;
	obj2 = temp;
}

void zOrder::render(POINT camera)
{
	quickSort(0, vZpoint.size() - 1);
	int index = -1;
	for (int i = 0; i < vZpoint.size(); ++i)
	{
		if (vZpoint[i].obType == PLAYER)
		{
			index = i;
			break;
		}
	}
	if (index >= 0)
	{
		for (int i = 0; i < vZpoint.size(); ++i)
		{
			if (vZpoint[i].z == vZpoint[index].z&&index < i)
			{
				swap(vZpoint[i], vZpoint[index]);
			}
		}
	}

	for (int i = 0; i < vZpoint.size(); ++i)
	{
		if (vZpoint[i].img == nullptr)
		{
			continue;
		}
		else if (vZpoint[i].obType == OBJECT)
		{
			vZpoint[i].img->alphaRender(vZpoint[i].hdc, vZpoint[i].x - vZpoint[i].img->getWidth() / 2, vZpoint[i].z - vZpoint[i].img->getHeight() - vZpoint[i].jumpPower, 100,camera);
			continue;
		}
		if (vZpoint[i].ani != nullptr)
		{
			vZpoint[i].img->aniRender(vZpoint[i].hdc, vZpoint[i].x - vZpoint[i].img->getWidth() / 2, vZpoint[i].z - vZpoint[i].img->getHeight() / 2 - vZpoint[i].jumpPower, vZpoint[i].ani,camera);
		}
		else if (vZpoint[i].frameX > -1 && vZpoint[i].frameY > -1)
		{
			vZpoint[i].img->frameRender(vZpoint[i].hdc, vZpoint[i].x - vZpoint[i].img->getFrameWidth() / 2, vZpoint[i].z - vZpoint[i].img->getFrameHeight() / 2 - vZpoint[i].jumpPower,
				camera, vZpoint[i].frameX, vZpoint[i].frameY);
		}
		else
		{
			vZpoint[i].img->render(vZpoint[i].hdc, vZpoint[i].x - vZpoint[i].img->getWidth() / 2, vZpoint[i].z - vZpoint[i].img->getHeight() / 2 - vZpoint[i].jumpPower, camera);
		}
	}
	vZpoint.clear();
}
