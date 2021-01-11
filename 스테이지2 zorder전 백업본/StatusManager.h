#pragma once
struct HPBar {
	int hp;
	image* img;
};
class StatusManager :
	public singletonBase<StatusManager>
{
private:
	int HP;
	int mahaGauge;
	vector<HPBar*> _vHPBar;
	vector<HPBar*>::iterator _viHPBar;
public:
	void setHpBar(string strkey);
	int getHp() { return HP; }
	void setHp(int Hp) { HP = Hp; }
	vector<HPBar*> getHpBar() { return _vHPBar; }
	vector<HPBar*>::iterator getHpBarIter() { return _viHPBar; }
	void damaged(int damage);
	void heal(int heal,string strkey);
};

