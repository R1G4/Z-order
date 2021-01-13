#include"stdafx.h"
#include"stage3.h"
void stage3::zOrder()
{
	_vZorder3.push_back(_player->getShadow().bottom);

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		_vZorder3.push_back(_em->getVEnemy()[i]->getShadowRc().bottom);
	}

	//정렬
	quickSort(0, _vZorder3.size() - 1);

	//랜더
	for (int i = 0; i < _vZorder3.size(); ++i)
	{
		if (_player->getShadow().bottom == _vZorder3[i])
		{
			_player->render(camera);
		}

		for (int k = 0; k < _em->getVEnemy().size(); ++k)
		{
			if (_em->getVEnemy()[k]->getShadowRc().bottom == _vZorder3[i])
			{
				_em->getVEnemy()[k]->render(camera);
			}
		}

	}
	_vZorder3.clear();

}

void stage3::quickSort(int a, int b)
{
	if (a >= b)return;
	int pivot = _vZorder3[(a + b) / 2];
	int left = a;
	int right = b;
	while (left <= right)
	{
		while (_vZorder3[left] < pivot)++left;
		while (_vZorder3[right] > pivot)--right;
		if (left <= right)
		{
			swap(_vZorder3[left], _vZorder3[right]);
			++left;
			--right;
		}
	}
	quickSort(a, right);
	quickSort(left, b);


}
