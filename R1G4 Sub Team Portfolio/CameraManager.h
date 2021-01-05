#pragma once
#include"image.h"
#include"singletonBase.h"

enum XY
{
	X,
	Y,
	BOTH
};
enum DEST
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class CameraManager:public singletonBase<CameraManager>
{
private:
	XY WantToBase;
	DEST dest;
	int _time=0;
	int interval=0;
	bool _isShaking = false;
	bool _isLock;
public:
	CameraManager();
	~CameraManager();
	/*캐릭터 중점 기준으로 카메라를 만들고 싶을 때 사용할 함수
	WantToBase는 원하는 축 기준. X축을 중점으로하고 싶다면 X, Y축을 중점으로한다면 Y, 캐릭터가 항상 중앙으로 향하고 싶다면 BOTH
	backgroundW는 배경 width, backgroundH는 배경 Height*/
	POINT CameraMake(int CharacterX,int CharacterY,XY WantToBase,int backgroundW,int backgroundH);
	//좀더 세분화된 카메라를 만들고 싶을 때(아직 미구현)
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, int backgroundW, int backgroundH, int seperate, DEST dest);
	//더 간편하게 img변수만 넣으면 실행 건웅
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, image* img);
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, image* img, int seperate, int check);
	//미니맵 만들고 싶을 때 사용. background이미지와 캐릭터 이미지, 미니맵크기를 담당할 렉트를 넣으면 됨
	RECT miniMapMake(image* img, image* CharacterImg,RECT rc);
	//카메라를 따라 움직이는 미니맵을 만들고 싶은데 아직 미구현
	void miniMapMake(POINT camera, int sizeX, int sizeY,image* characterImg,image* backImg);
	//카메라 포인터 넣고, 흔들고 싶은 강도를 넣으면됨
	void shaking(POINT *camera,int power );
	//시간 설정. 특정 조건에서만 실행되도록 해야합니다 안그러면 무한히 흔들립니다
	void setTime(int time);
	void isChainLock(bool ONOFF);
	bool getIsChainLock() { return _isLock; }
};

