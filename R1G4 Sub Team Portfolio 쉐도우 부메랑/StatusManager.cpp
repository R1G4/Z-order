#include "stdafx.h"
#include "StatusManager.h"

void StatusManager::setHpBar(string strkey)
{
	for (int i = 0; i < HP; i++)
	{
		HPBar* hp1;
		hp1 = new HPBar;
		hp1->img = IMAGEMANAGER->findImage(strkey);
		hp1->hp = i;
		_vHPBar.push_back(hp1);
	}
}

void StatusManager::damaged(int damage)
{
	HP -= damage;
	for (int i = 0; i < damage; i++)
	{
		_vHPBar.pop_back();
	}
}

void StatusManager::heal(int heal,string strkey)
{
	HP += heal;
	if (HP > 24)HP = 24;
	for (int i = _vHPBar.size(); i < HP; i++)
	{
		
		HPBar* hp1;
		hp1 = new HPBar;
		hp1->img = IMAGEMANAGER->findImage(strkey);
		hp1->hp = i;
		_vHPBar.push_back(hp1);
	}
}

