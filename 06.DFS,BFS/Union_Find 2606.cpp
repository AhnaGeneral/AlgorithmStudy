
//UnionFind 

#include<iostream>
using namespace std;

int aParent[101]{0,};

int GetParent(int _x)
{
	if (aParent[_x] == _x) return _x;
	
	else
	{
		return aParent[_x] = GetParent(aParent[_x]);
	}
}

void UnionFind(int _x, int _y)
{
	 _x = GetParent(_x);
	 _y = GetParent(_y);
	
	if (_x > _y) aParent[_x] = _y;
	else aParent[_y] = _x;
}

int main()
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 


	int nAmount; 
	cin >> nAmount;
	
	int pairSize; 
	cin >> pairSize;

	for (int i = 1; i <= nAmount; i++)
		aParent[i] = i;

	for (int i = 0; i < pairSize; i++)
	{
		int d1, d2;
		cin >> d1 >> d2; 
		UnionFind(d1, d2); 
	}
		
	int _bias = GetParent(1); 

	int count{ 0 }; 

	for (int i = 0; i < nAmount; i++)
	{
		if (1 != (i + 1))
		{
			if (_bias == GetParent(i + 1))
				count++;
		}
	}

	cout << count; 
}
