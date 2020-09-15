#include<iostream>
#include<queue>
#include<vector>
using namespace std;

bool Visit[1'001][1'001]{ { false,}, };
int  Tomato[1'001][1'001]{0,};
int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int _count = 0; 

queue<pair<int, int>> que; 
vector<pair<int, int>> vec; 

void BFS(vector<pair<int, int>> _pos, int _axleX, int _axleY)
{
	for (auto a : _pos)
	{
		int cur_y = a.first, cur_x = a.second;
		Visit[cur_y][cur_x] = true;
		que.push(pair<int, int>(cur_y, cur_x));
	}

	while (!que.empty())
	{
		_count++;
		for (int j = 0; j < que.size(); j++)
		{
			int next_y = que.front().first;
			int next_x = que.front().second;
			que.pop();
		
			for (int i = 0; i < 4; i++)
			{
				int curs_y = next_y + dir[i][0];
				int curs_x = next_x + dir[i][1];

				if ((curs_y < _axleY && curs_y >= 0)
					&& (curs_x < _axleX && curs_x >= 0)
					&& (!Visit[curs_y][curs_x])
					&& (!Tomato[curs_y][curs_x]))
				{
					Visit[curs_y][curs_x] = true;
					que.push(pair<int, int>(curs_y, curs_x));
				}
				else if ((curs_y < _axleY && curs_y >= 0)
					&& (curs_x < _axleX && curs_x >= 0)
					&& (!Visit[curs_y][curs_x])
					&& (Tomato[curs_y][curs_x] == -1))
				{
					Visit[curs_y][curs_x] = true;
				}

			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int AxleX, AxleY;
	cin >> AxleX >> AxleY;

	for (int i = 0; i < AxleY; i++)
		for (int j = 0; j < AxleX; j++)
		{
			int data;
			cin >> data;

			if (data == 1)
			{
				vec.push_back(pair<int, int>(i, j)); 
			}
			Tomato[i][j] = data;
		}

	BFS(vec, AxleX, AxleY);

	cout << _count << endl;

	for (int i = 0; i < AxleY; i++)
	{
		for (int j = 0; j < AxleX; j++)
		{
			cout << Visit[i][j] << " ";
		}
		cout << "\n"; 
	}
}