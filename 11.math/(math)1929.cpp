#include<iostream>
using namespace std;

bool sosu[1'000'001];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	
	int N, M;
	cin >> N >> M;
	sosu[1] = true;
	for (int i = 2; i * i <= M; i++)
	{
		for (int k = i * i; k <= M; k += i)
			sosu[k] = true;// ¼Ò¼öx
	}
	
	for (int i = N; i <= M; i++)
	{
		if (!sosu[i]) cout << i << "\n";
	}

}