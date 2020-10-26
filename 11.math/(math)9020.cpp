#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//bool sosu[123457];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//그 소수의 배수이니? 배수이면 몫 만큼 나열
	//그 소수의 배수가 아니다?  
	
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