#include"stdafx.h"
#include"tempStage.h"
void tempStage::zOrder()
{
	_vZorder.push_back(_player->getShadow().bottom);

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		_vZorder.push_back(_em->getVEnemy()[i]->getShadowRc().bottom);
	}

	//����
	quickSort(0, _vZorder.size() - 1);

	//����
	for (int i = 0; i < _vZorder.size(); ++i)
	{
		if (_player->getShadow().bottom == _vZorder[i])
		{
			_player->render(camera);
		}

		for (int k = 0; k < _em->getVEnemy().size(); ++k)
		{
			if (_em->getVEnemy()[k]->getShadowRc().bottom == _vZorder[i])
			{
				_em->getVEnemy()[k]->render(camera);
			}
		}

	}
	_vZorder.clear();

}
void tempStage::quickSort(int a, int b)
{
	if (a >= b)return;
	int pivot = _vZorder[(a + b) / 2];
	int left = a;
	int right = b;
	while (left <= right)
	{
		while (_vZorder[left] < pivot)++left;
		while (_vZorder[right] > pivot)--right;
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			++left;
			--right;
		}
	}
	quickSort(a, right);
	quickSort(left, b);

}