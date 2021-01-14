#include"stdafx.h"
#include"stage2.h"
void stage2::zOrder()
{
	_vZorder2.push_back(_player->getShadow().bottom);

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		_vZorder2.push_back(_em->getVEnemy()[i]->getShadowRc().bottom);
	}

	//정렬
	quickSort(0, _vZorder2.size() - 1);

	//랜더
	for (int i = 0; i < _vZorder2.size(); ++i)
	{
		if (_player->getShadow().bottom == _vZorder2[i])
		{
			_player->render(camera);
		}

		for (int k = 0; k < _em->getVEnemy().size(); ++k)
		{
			if (_em->getVEnemy()[k]->getShadowRc().bottom == _vZorder2[i])
			{
				_em->getVEnemy()[k]->render(camera);
			}
		}

	}
	
	_vZorder2.clear();

}
void stage2::quickSort(int a, int b)
{
	if (a >= b)return;
	int pivot = _vZorder2[(a + b) / 2];
	int left = a;
	int right = b;
	while (left <= right)
	{
		while (_vZorder2[left] < pivot)++left;
		while (_vZorder2[right] > pivot)--right;
		if (left <= right)
		{
			swap(_vZorder2[left], _vZorder2[right]);
			++left;
			--right;
		}
	}
	quickSort(a, right);
	quickSort(left, b);

}