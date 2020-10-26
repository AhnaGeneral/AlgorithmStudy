#include<iostream>
using namespace std; 
long long fiboArr[91]; 

long long fibona(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1; 
	if (n == 2) return 1; 
	if (fiboArr[n] != 0) return fiboArr[n];
	return fiboArr[n] = fibona(n - 1) + fibona(n - 2);
}

int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 

	int N; 
	cin >> N;

	cout << fibona(N); 
}