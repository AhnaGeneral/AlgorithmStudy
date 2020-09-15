#include<iostream>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;

queue<pair<int, int>> que;
bool map[25][25];
int check[25][25];
int visit[25][25];
//int countmap[25][25];
int _count;
vector<int> vec;
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

void BFS(int _amount, int _curY, int _CurX)
{
	_count = 0;

	if (check[_curY][_CurX] || map[_curY][_CurX] != 1)
		return;

	int cur_y = _curY, cur_x = _CurX;
	que.push(pair<int, int>(cur_y, cur_x));
	check[cur_y][cur_x] = 1;
	if (map[cur_y][cur_x]) _count++;


	while (!que.empty())
	{
		cur_y = que.front().first;
		cur_x = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_y = cur_y + dir[i][0];
			int next_x = cur_x + dir[i][1];

			if ((!check[next_y][next_x])
				&& (map[next_y][next_x])
				&& (next_y >= 0 && next_y < _amount)
				&& (next_x >= 0 && next_x < _amount))
			{
				que.push(pair<int, int>(next_y, next_x));
				check[next_y][next_x] = 1;
				_count++;
				//	countmap[next_y][next_x] = check[cur_x][cur_y] + 1;
			}
		}
	}
	vec.push_back(_count);

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nAmount;
	cin >> nAmount;

	for (int i = 0; i < nAmount; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < nAmount; j++)
		{
			map[i][j] = str[j] - 48;
		}
	}

	for (int i = 0; i < nAmount; i++)
	{

		for (int j = 0; j < nAmount; j++)
		{
			BFS(nAmount, i, j);
		}
	}

	cout << vec.size() << "\n";

	sort(vec.begin(), vec.end());

	for (auto a : vec)
	{
		cout << a << "\n";
	}

}
