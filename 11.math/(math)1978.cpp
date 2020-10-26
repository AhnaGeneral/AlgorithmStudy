#include<iostream>
using namespace std; 

// 에라토스테네스의 체
int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(); 

	int N; 
	cin >> N; 
	int result=0;
	int count = 0; 
	bool bols = false;
	while (N--)
	{
		int data; 
		cin >> data; 
		if (data == 1)continue; 
		if (data == 2)
		{
			count++;
			continue;

		}
		for (int i = 2; i < data; i++)
		{
			if (data % i == 0) bols = true;
		}
		if (!bols) count++;
		bols = false;
	}
	cout << count;
}