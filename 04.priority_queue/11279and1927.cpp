//ÃÖ´ëÈü ÃÖ¼ÒÈü

#include <iostream>
//#include <deque>
#include <queue>
using namespace std; 
priority_queue<int, vector<int>, greater<int>> prior_que;

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
			prior_que.push(data);
		}
		else
		{
			if (prior_que.empty())
				cout << 0 << "\n";
			else
			{
				cout << prior_que.top() << "\n";
				prior_que.pop();
			}
		}
	}
} 