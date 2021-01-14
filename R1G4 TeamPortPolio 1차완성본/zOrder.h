#pragma once
#include "singletonBase.h"
enum ObjectType {
	PLAYER,
	ENEMY,
	OBJECT,
	SHADOW
};
struct OrderObject {
	HDC hdc;
	image* img;
	animation* ani;
	ObjectType obType;
	int x, z;
	float jumpPower;
	int frameX, frameY;
};
class zOrder :
	public singletonBase<zOrder>
{
private:
	vector<OrderObject> vZpoint;
	vector<OrderObject>::iterator viZpoint;
public:
	zOrder();
	~zOrder();
	void render(POINT camera);
	void addZorder(HDC hdc,image* img,animation* ani,ObjectType type,int x,int z,float jumpPower);
	void addZorder(HDC hdc, image* img, animation* ani, ObjectType type, int x, int z, float jumpPower, int frameX, int frameY);
	void addZorder(HDC hdc, image* img, ObjectType type, int x, int z, float jumpPower, int frameX, int frameY);
	void addZorder(HDC hdc, image* img, ObjectType type, int x, int z, float jumpPower);
	void addZorder(HDC hdc,  ObjectType type, int x, int z);
	void quickSort(int a, int b);
	void swap(OrderObject obj1, OrderObject obj2);
};