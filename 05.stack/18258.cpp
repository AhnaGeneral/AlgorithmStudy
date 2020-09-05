#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);


	queue<int> Que;

	int nAmount;
	cin >> nAmount;

	for (int i = 0; i < nAmount; i++)
	{
		string str;
		cin >> str;

		if (str == "push")
		{
			int data;
			cin >> data;

			Que.push(data);
		}
		else if (str == "front")
		{
			if (Que.empty())
			{
				cout << -1 << "\n";
			}
			else
			{
				cout << Que.front() << "\n";
			}
		}
		else if (str == "back")
		{
			if (Que.empty())
			{
				cout << -1 << "\n";
			}
			else
			{
				cout << Que.back() << "\n";
			}
		}
		else if (str == "size")
		{
			cout << Que.size() << "\n";
		}
		else if (str == "pop")
		{
			if (Que.empty())
			{
				cout << -1 << "\n";
			}
			else
			{
				cout << Que.front() << "\n";
				Que.pop();
			}
		}
		else if (str == "empty")
		{
			if (Que.empty())
			{
				cout << 1 << "\n";
			}
			else
			{
				cout << 0 << "\n";

			}
		}
	}
}

