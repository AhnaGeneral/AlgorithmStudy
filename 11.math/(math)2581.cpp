#include <iostream>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0);

	int M, N; 
	cin >> N >> M; 
	int count = 0;
	int min;
	int sum = 0;

	if (N == M)
	{
		cout << -1;
		return 0;
	}

	for (int i = N; i <= M; i++)
	{
		if (i == 1)continue;
		if (i == 2)
		{
			min = 2;  sum += 2;
			count++;
			continue;
		}
		bool sosu = false;
		for (int j = 2; j < i; j++)
		{
			if (i % j == 0)sosu = true;
		}
		if (!sosu)
		{
			if (!count)min = i;
			sum += i;
			count++;
		}
	}
	if (!sum)
		cout << -1;
	else 
	  cout << sum <<"\n"<< min;
}