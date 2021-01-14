#include"stdafx.h"
#include"BossStage.h"
void BossStage::zOrder()
{
	_vZorderB.push_back(_player->getShadow().bottom);
	_vZorderB.push_back(_boss->getBossShadow().bottom);
	quickSort(0, _vZorderB.size() - 1);

	for (int i = 0; i < _vZorderB.size(); ++i)
	{
		if (_player->getShadow().bottom == _vZorderB[i])
		{
			_player->render(camera);
		}
		if (_boss->getBossShadow().bottom == _vZorderB[i])
		{
			_boss->render(camera);
		}
	}
	_vZorderB.clear();
}

void BossStage::quickSort(int a, int b)
{
	if (a >= b)return;
	int pivot = _vZorderB[(a + b) / 2];
	int left = a;
	int right = b;
	while (left <= right)
	{
		while (_vZorderB[left] < pivot)++left;
		while (_vZorderB[right] > pivot)--right;
		if (left <= right)
		{
			swap(_vZorderB[left], _vZorderB[right]);
			++left;
			--right;
		}
	}
	quickSort(a, right);
	quickSort(left, b);

}
