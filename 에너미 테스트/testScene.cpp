#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	_kindsName.push_back("Girl");
	_kindsName.push_back("Boy");
	_kindsName.push_back("MT");
	_kindsName.push_back("CheerLeader");

	_image = IMAGEMANAGER->addFrameImage("Girl_Idle", "SchoolGirl size200/Girl_Idle.bmp", 0, 0, 1320, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Walk", "SchoolGirl size200/Girl_Walk.bmp", 0, 0, 1394, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Run", "SchoolGirl size200/Girl_Run.bmp", 0, 0, 1780, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Block", "SchoolGirl size200/Girl_Block.bmp", 0, 0, 460, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Attack", "SchoolGirl size200/Girl_Attack.bmp", 0, 0, 1934, 420, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack1", "SchoolGirl size200/Girl_ComboAttack1.bmp", 0, 0, 1505, 430, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack2", "SchoolGirl size200/Girl_ComboAttack2.bmp", 0, 0, 1470, 440, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_ComboAttack3", "SchoolGirl size200/Girl_ComboAttack3.bmp", 0, 0, 2700, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Hit", "SchoolGirl size200/Girl_Hit.bmp", 0, 0, 1626, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Downup", "SchoolGirl size200/Girl_Downup.bmp", 0, 0, 7013, 380, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Dazed", "SchoolGirl size200/Girl_Dazed.bmp", 0, 0, 656, 410, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Jump", "SchoolGirl size200/Girl_Jump.bmp", 0, 0, 432, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Knockdown", "SchoolGirl size200/Girl_Knockdown.bmp", 0, 0, 4361, 380, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Girl_Taunt", "SchoolGirl size200/Girl_Taunt.bmp", 0, 0, 4015, 420, 26, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("Boy_Idle", "SchoolBoy size200/Boy_Idle.bmp", 0, 0, 1200, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Walk", "SchoolBoy size200/Boy_Walk.bmp", 0, 0, 1460, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Run", "SchoolBoy size200/Boy_Run.bmp", 0, 0, 1970, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Block", "SchoolBoy size200/Boy_Block.bmp", 0, 0, 420, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Attack", "SchoolBoy size200/Boy_Attack.bmp", 0, 0, 1598, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack1", "SchoolBoy size200/Boy_ComboAttack1.bmp", 0, 0, 1892, 540, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack2", "SchoolBoy size200/Boy_ComboAttack2.bmp", 0, 0, 766, 460, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_ComboAttack3", "SchoolBoy size200/Boy_ComboAttack3.bmp", 0, 0, 1830, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Hit", "SchoolBoy size200/Boy_Hit.bmp", 0, 0, 1536, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Downup", "SchoolBoy size200/Boy_Downup.bmp", 0, 0, 7027, 400, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Dazed", "SchoolBoy size200/Boy_Dazed.bmp", 0, 0, 620, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Jump", "SchoolBoy size200/Boy_Jump.bmp", 0, 0, 468, 480, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Knockdown", "SchoolBoy size200/Boy_Knockdown.bmp", 0, 0, 4945, 400, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boy_Taunt", "SchoolBoy size200/Boy_Taunt.bmp", 0, 0, 1704, 420, 11, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("MT_Idle", "MT size200/MT_Idle.bmp", 0, 0, 1634, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Walk", "MT size200/MT_Walk.bmp", 0, 0, 1984, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Run", "MT size200/MT_Run.bmp", 0, 0, 1933, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Block", "MT size200/MT_Block.bmp", 0, 0, 486, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Attack", "MT size200/MT_Attack.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack1", "MT size200/MT_ComboAttack1.bmp", 0, 0, 1992, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack2", "MT size200/MT_ComboAttack2.bmp", 0, 0, 2216, 430, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_ComboAttack3", "MT size200/MT_ComboAttack3.bmp", 0, 0, 4068, 450, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Hit", "MT size200/MT_Hit.bmp", 0, 0, 523, 380, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Downup", "MT size200/MT_Downup.bmp", 0, 0, 8919, 440, 31, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Dazed", "MT size200/MT_Dazed.bmp", 0, 0, 618, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Jump", "MT size200/MT_Jump.bmp", 0, 0, 612, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Knockdown", "MT size200/MT_Knockdown.bmp", 0, 0, 8056, 440, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MT_Taunt", "MT size200/MT_Taunt.bmp", 0, 0, 558, 400, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("CheerLeader_Idle", "CheerLeader size200/CheerLeader_Idle.bmp", 0, 0, 2133, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Walk", "CheerLeader size200/CheerLeader_Walk.bmp", 0, 0, 2499, 400, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Run", "CheerLeader size200/CheerLeader_Run.bmp", 0, 0, 1291, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Block", "CheerLeader size200/CheerLeader_Block.bmp", 0, 0, 457, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Attack", "CheerLeader size200/CheerLeader_Attack.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack1", "CheerLeader size200/CheerLeader_ComboAttack1.bmp", 0, 0, 1138, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack2", "CheerLeader size200/CheerLeader_ComboAttack2.bmp", 0, 0, 1715, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_ComboAttack3", "CheerLeader size200/CheerLeader_ComboAttack3.bmp", 0, 0, 6577, 600, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Hit", "CheerLeader size200/CheerLeader_Hit.bmp", 0, 0, 1445, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Downup", "CheerLeader size200/CheerLeader_Downup.bmp", 0, 0, 8265, 400, 28, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Dazed", "CheerLeader size200/CheerLeader_Dazed.bmp", 0, 0, 554, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Jump", "CheerLeader size200/CheerLeader_Jump.bmp", 0, 0, 776, 500, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CheerLeader_Knockdown", "CheerLeader size200/CheerLeader_Knockdown.bmp", 0, 0, 6482, 400, 22, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("CheerLeader_Taunt", "CheerLeader size200/CheerLeader_Taunt.bmp", 0, 0, 558, 400, 4, 2, true, RGB(255, 0, 255));
	
	_direction = LEFT;
	_state = IDLE;
	_isIdle = false;
	_selectedKind = GIRL;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());
	
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightIdle", "Girl_Idle", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftIdle", "Girl_Idle", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightWalk", "Girl_Walk", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftWalk", "Girl_Walk",  24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightRun", "Girl_Run", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftRun", "Girl_Run", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightBlock", "Girl_Block", 0, 3, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftBlock", "Girl_Block", 6, 3, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightAttack", "Girl_Attack", 0, 8, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftAttack", "Girl_Attack", 16, 8, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack1", "Girl_ComboAttack1", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack1", "Girl_ComboAttack1", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack2", "Girl_ComboAttack2", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack2", "Girl_ComboAttack2", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightComboAttack3", "Girl_ComboAttack3", 0, 12, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftComboAttack3", "Girl_ComboAttack3", 24, 12, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightHit", "Girl_Hit", 0, 9, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftHit", "Girl_Hit", 18, 9, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightDownup", "Girl_Downup", 0, 27, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftDownup", "Girl_Downup", 54, 27, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightDazed", "Girl_Dazed", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftDazed", "Girl_Dazed", 8, 4, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightJump", "Girl_Jump", 0, 3, 4, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftJump", "Girl_Jump", 6, 3, 4, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightKnockdown", "Girl_Knockdown", 0, 17, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftKnockdown", "Girl_Knockdown", 34, 17, 8, false, setLeftIdle, this, 10); 
	KEYANIMANAGER->addArrayFrameAnimation("Girl_RightTaunt", "Girl_Taunt", 0, 26, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Girl_LeftTaunt", "Girl_Taunt", 52, 26, 8, false, setLeftIdle, this, 10); 

	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightIdle", "Boy_Idle", 0, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftIdle", "Boy_Idle", 16, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightWalk", "Boy_Walk", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftWalk", "Boy_Walk", 24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightRun", "Boy_Run", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftRun", "Boy_Run", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightBlock", "Boy_Block", 0, 3, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftBlock", "Boy_Block", 6, 3, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightAttack", "Boy_Attack", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftAttack", "Boy_Attack", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightComboAttack1", "Boy_ComboAttack1", 0, 9, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftComboAttack1", "Boy_ComboAttack1", 18, 9, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightComboAttack2", "Boy_ComboAttack2", 0, 4, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftComboAttack2", "Boy_ComboAttack2", 8, 4, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightComboAttack3", "Boy_ComboAttack3", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftComboAttack3", "Boy_ComboAttack3", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightHit", "Boy_Hit", 0, 9, 2, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftHit", "Boy_Hit", 18, 9, 2, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightDownup", "Boy_Downup", 0, 27, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftDownup", "Boy_Downup", 54, 27, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightDazed", "Boy_Dazed", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftDazed", "Boy_Dazed", 8, 4, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightJump", "Boy_Jump", 0, 3, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftJump", "Boy_Jump", 6, 3, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightKnockdown", "Boy_Knockdown", 0, 19, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftKnockdown", "Boy_Knockdown", 38, 19, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_RightTaunt", "Boy_Taunt", 0, 11, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("Boy_LeftTaunt", "Boy_Taunt", 22, 11, 8, false, setLeftIdle, this, 10);

	KEYANIMANAGER->addArrayFrameAnimation("MT_RightIdle", "MT_Idle", 0, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftIdle", "MT_Idle", 20, 10, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightWalk", "MT_Walk", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftWalk", "MT_Walk", 24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightRun", "MT_Run", 0, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftRun", "MT_Run", 16, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightBlock", "MT_Block", 0, 3, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftBlock", "MT_Block", 6, 3, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightAttack", "MT_Attack", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftAttack", "MT_Attack", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightComboAttack1", "MT_ComboAttack1", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftComboAttack1", "MT_ComboAttack1", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightComboAttack2", "MT_ComboAttack2", 0, 8, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftComboAttack2", "MT_ComboAttack2", 16, 8, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightComboAttack3", "MT_ComboAttack3", 0, 14, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftComboAttack3", "MT_ComboAttack3", 28, 14, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightHit", "MT_Hit", 0, 3, 2, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftHit", "MT_Hit", 6, 3, 2, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightDownup", "MT_Downup", 0, 31, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftDownup", "MT_Downup", 62, 31, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightDazed", "MT_Dazed", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftDazed", "MT_Dazed", 8, 4, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightJump", "MT_Jump", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftJump", "MT_Jump", 8, 4, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightKnockdown", "MT_Knockdown", 0, 28, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftKnockdown", "MT_Knockdown", 56, 28, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_RightTaunt", "MT_Taunt", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("MT_LeftTaunt", "MT_Taunt", 8, 4, 8, false, setLeftIdle, this, 10);

	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightIdle", "CheerLeader_Idle", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftIdle", "CheerLeader_Idle", 24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightWalk", "CheerLeader_Walk", 0, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftWalk", "CheerLeader_Walk", 24, 12, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightRun", "CheerLeader_Run", 0, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftRun", "CheerLeader_Run", 16, 8, 10, true, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightBlock", "CheerLeader_Block", 0, 3, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftBlock", "CheerLeader_Block", 6, 3, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightAttack", "CheerLeader_Attack", 0, 6, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftAttack", "CheerLeader_Attack", 12, 6, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightComboAttack1", "CheerLeader_ComboAttack1", 0, 6, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftComboAttack1", "CheerLeader_ComboAttack1", 12, 6, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightComboAttack2", "CheerLeader_ComboAttack2", 0, 7, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftComboAttack2", "CheerLeader_ComboAttack2", 14, 7, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightComboAttack3", "CheerLeader_ComboAttack3", 0, 22, 10, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftComboAttack3", "CheerLeader_ComboAttack3", 44, 22, 10, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightHit", "CheerLeader_Hit", 0, 9, 2, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftHit", "CheerLeader_Hit", 18, 9, 2, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightDownup", "CheerLeader_Downup", 0, 28, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftDownup", "CheerLeader_Downup", 56, 28, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightDazed", "CheerLeader_Dazed", 0, 4, 8, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftDazed", "CheerLeader_Dazed", 8, 4, 8, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightJump", "CheerLeader_Jump", 0, 3, 2, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftJump", "CheerLeader_Jump", 6, 3, 2, false, setLeftIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_RightKnockdown", "CheerLeader_Knockdown", 0, 22, 2, false, setRightIdle, this, 10);
	KEYANIMANAGER->addArrayFrameAnimation("CheerLeader_LeftKnockdown", "CheerLeader_Knockdown", 44, 22, 2, false, setLeftIdle, this, 10);

	_motion = KEYANIMANAGER->findAnimation("Girl_LeftIdle");
	_motion->start();
	return S_OK;
}

void testScene::release()
{

}

void testScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_motion->stop();
		_selectedKind = GIRL;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
		_motion->start();
	
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_motion->stop();
		_selectedKind = BOY;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
		_motion->start();
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_motion->stop();
		_selectedKind = MT;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
		_motion->start();
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_motion->stop();
		_selectedKind = CHEERLEADER;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_direction = RIGHT;
		if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
		{
			_state = RUN;
			_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Run");
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightRun");
		}
		else
		{
			_state = WALK;
			_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Walk");
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightWalk");
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_direction = RIGHT;
		_state = IDLE;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightIdle");
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_direction = LEFT;
		if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
		{
			_state = RUN;
			_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Run");
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftRun");
		}
		else
		{
			_state = WALK;
			_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Walk");
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftWalk");
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = LEFT;
		_state = IDLE;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
		_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_state = BLOCK;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Block");
		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftBlock");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightBlock");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_state = ATTACK;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Attack");
		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftAttack");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightAttack");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{

		_state = COMBO_ATTACK_1;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_ComboAttack1");

		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftComboAttack1");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightComboAttack1");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		_state = COMBO_ATTACK_2;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_ComboAttack2");
		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftComboAttack2");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightComboAttack2");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_state = COMBO_ATTACK_3;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_ComboAttack3");
		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftComboAttack3");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightComboAttack3");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_state = HIT;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Hit");
		switch (_direction)
		{
			case LEFT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftHit");
				break;
			case RIGHT:
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightHit");
				break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_state = DOWNUP;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Downup");
		switch (_direction)
		{
		case LEFT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftDownup");
			break;
		case RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightDownup");
			break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_state = KNOCKDOWN;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Knockdown");
		switch (_direction)
		{
		case LEFT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftKnockdown");
			break;
		case RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightKnockdown");
			break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_state = DAZED;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Dazed");
		switch (_direction)
		{
		case LEFT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftDazed");
			break;
		case RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightDazed");
			break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_state = DAZED;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Jump");
		switch (_direction)
		{
		case LEFT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftJump");
			break;
		case RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightJump");
			break;
		}
		_motion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('Q') && _selectedKind != CHEERLEADER)
	{
		_state = TAUNT;
		_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Taunt");
		switch (_direction)
		{
		case LEFT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftTaunt");
			break;
		case RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightTaunt");
			break;
		}
		_motion->start();
	}
	switch (_direction)
	{
		case RIGHT:
			if (!_motion->isPlay())
			{
				_state = IDLE;
				_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_RightIdle");
				_motion->start();
			}
			else
			{
				switch (_state)
				{
				case IDLE:
					break;
				case WALK:
					_x += SPEED;
					break;
				case RUN:
					_x += SPEED * 1.5;
					break;
				}
			}
			break;
		case LEFT:
			if (!_motion->isPlay())
			{
				_state = IDLE;
				_image = IMAGEMANAGER->findImage(_kindsName[_selectedKind] + "_Idle");
				_motion = KEYANIMANAGER->findAnimation(_kindsName[_selectedKind] + "_LeftIdle");
				_motion->start();
			}
			else
			{
				switch (_state)
				{
					case IDLE:
						break;
					case WALK:
						_x -= SPEED;
						break;
					case RUN:
						_x -= SPEED * 1.5;
						break;
				}
			}
			break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	KEYANIMANAGER->update();
}

void testScene::render()
{
	switch (_selectedKind)
	{
	case GIRL:
		switch (_state)
		{
		case ATTACK:
			_image->aniRender(getMemDC(), _rc.left, _rc.top - 10, _motion);
			break;
		case COMBO_ATTACK_1:
			_image->aniRender(getMemDC(), _rc.left, _rc.top - 10, _motion);
			break;
		case COMBO_ATTACK_2:
			_image->aniRender(getMemDC(), _rc.left, _rc.top - 20, _motion);
			break;
		default:
			_image->aniRender(getMemDC(), _rc.left, _rc.top, _motion);
			break;
		}
		break;
	case BOY:
		switch (_state)
		{
			case COMBO_ATTACK_1:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 30, _motion);
				break;
			case COMBO_ATTACK_2:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 17, _motion);
				break;
			case JUMP:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 40, _motion);
				break;
			default:
				_image->aniRender(getMemDC(), _rc.left, _rc.top, _motion);
				break;
		}
		break;
	case MT:
		switch (_state)
		{
			case DOWNUP:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 20, _motion);
				break;
			case KNOCKDOWN:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 20, _motion);
				break;
			case COMBO_ATTACK_2:
				switch (_direction)
				{
					case LEFT:
						_image->aniRender(getMemDC(), _rc.left - 3, _rc.top - 10, _motion);
						break;
					case RIGHT:
						_image->aniRender(getMemDC(), _rc.left + 3, _rc.top - 10, _motion);
						break;
				}
				
				break;
			case COMBO_ATTACK_3:
				_image->aniRender(getMemDC(), _rc.left, _rc.top - 25, _motion);
				break;
			default:
				_image->aniRender(getMemDC(), _rc.left, _rc.top, _motion);
				break;
		}
		break;
	case CHEERLEADER:
		switch (_state)
		{
		case COMBO_ATTACK_3:
			_image->aniRender(getMemDC(), _rc.left, _rc.top - 50, _motion);
			break;
		case JUMP:
			_image->aniRender(getMemDC(), _rc.left, _rc.top - 50, _motion);
			break;
		default:
			_image->aniRender(getMemDC(), _rc.left, _rc.top, _motion);
			break;
		}
		
		break;
	}
}

void testScene::setRightIdle(void* obj)
{
	testScene* k = (testScene*)obj;
}

void testScene::setLeftIdle(void* obj)
{
	testScene* k = (testScene*)obj;
}
