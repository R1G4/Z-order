#include "stdafx.h"
#include "ship.h"

HRESULT ship::init(const char* imageName, int x, int y)
{
	_image = IMAGEMANAGER->findImage(imageName);

	_x = x;
	_y = y;

	_angle = 0.0f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_speed = 0.0f;
	_radius = _image->getFrameWidth() / 2;

	return S_OK;
}

void ship::release()
{
}

void ship::update()
{
	keyControl();
	move();
}

void ship::render()
{
	draw();
}

void ship::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	char str[128];
	sprintf_s(str, "%d도, %3.2f", int(_angle * 180 / PI), _speed);
	TextOut(getMemDC(), _rc.left, _rc.top - 15, str, strlen(str));
}

void ship::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_angle += 0.08f;
		if (_angle >= PI2) _angle -= PI2;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_angle -= 0.08f;
		if (_angle <= 0) _angle += PI2;
	}

	if(KEYMANAGER->isStayKeyDown(VK_UP)) _speed += 0.02f;
	if(KEYMANAGER->isStayKeyDown(VK_DOWN)) _speed -= 0.02f;
}

void ship::move()
{
	int frame;		//각도에 해당하는 프레임 찾아주려고
	float angle;	//각도

	angle = _angle + PI16;
	
	frame = int(angle / PI8);
	_image->setFrameX(frame);

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * 100;

	_x += cosf(_angle) * _speed * moveSpeed;
	_y += -sinf(_angle) * _speed * moveSpeed;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}
