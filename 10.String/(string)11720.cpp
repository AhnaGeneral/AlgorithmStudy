#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int N; 
	cin >> N; 

	string str; 
	cin >> str; 

	int sum = 0; 
	for (int i = 0; i < N; i++)
	{
		sum += static_cast<int>(str[i])-48; 
	}

	cout << sum; 
}