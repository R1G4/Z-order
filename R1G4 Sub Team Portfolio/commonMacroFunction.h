#pragma once
//======================================
// ## 20.11.12 ## CommonMacroFunction ##
//======================================

//Line
//       선긋기함수 (뿌릴DC, 시작X, 시작Y, 끝X, 끝Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };

	return pt;
}

//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x , y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2) , y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

//Rectangle
//x,y좌표를 기준으로 크기만큼 사각형이 생성됨
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
inline void Rectangle(HDC hdc, RECT& rc, POINT camera)
{
	Rectangle(hdc, rc.left - camera.x, rc.top - camera.y, rc.right - camera.x, rc.bottom - camera.y);
}
inline void RectangleMake(HDC hdc, int x, int y, int width, int height, POINT camera)
{
	Rectangle(hdc, x - camera.x, y - camera.y, (x - camera.x) + width, (y - camera.y) + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height, POINT camera)
{
	Rectangle(hdc, (x - camera.x) - (width / 2), (y - camera.y) - (height / 2), (x - camera.x) + (width / 2), (y - camera.y) + (height / 2));
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
inline void Ellipse(HDC hdc, RECT& rc, POINT camera)
{
	Ellipse(hdc, rc.left - camera.x, rc.top - camera.y, rc.right - camera.x, rc.bottom - camera.y);
}
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height, POINT camera)
{
	Ellipse(hdc, (x - camera.x) - (width / 2), (y - camera.y) - (height / 2), (x - camera.x) + (width / 2), (y - camera.y) + (height / 2));
}
inline void EllipseMake(HDC hdc, int x, int y, int width, int height, POINT camera)
{
	Ellipse(hdc, x - camera.x, y - camera.y, (x - camera.x) + width, (y - camera.y) + height);
}