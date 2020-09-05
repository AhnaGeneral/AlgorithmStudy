#include <iostream>
#include <stack>
using namespace std;
stack<int> sta; 

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nAmount; 
	cin >> nAmount; 

	for (int i = 0; i < nAmount; i++)
	{
		int data; 
		cin >> data; 

		if (data != 0)
		{
			sta.push(data); 
		}
		else
		{
			sta.pop(); 
		}
	}

	int sum = 0;
	int stalength = sta.size(); 
	for (int i = 0; i <= stalength; ++i)
	{
		if (!sta.empty())
		{
			sum += sta.top();
			sta.pop();
		}
	}
	cout << sum;
}