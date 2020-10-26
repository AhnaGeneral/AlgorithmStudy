#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//bool sosu[123457];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//�� �Ҽ��� ����̴�? ����̸� �� ��ŭ ����
	//�� �Ҽ��� ����� �ƴϴ�?  
	
	int C; 
	cin >> C; 
	while (C--)
	{
		int data; 
		cin >> data;
		vector<bool> vec;
		vec.resize(data + 1); 

		for (int i = 2; i * i <= data; i++)
			for (int k = i * i; k <= data; k += i)
				vec[k] = true;

		for (int i = data/2; i > 0; i--)
		{
			if (vec[i] == false && vec[data - i] == false)
			{
				cout << i << " " << data - i << "\n";
				break;
			}
		}
	}
} 