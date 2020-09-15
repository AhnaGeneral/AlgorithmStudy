#include<iostream>
#include<queue>
#include<string>
#include<algorithm>
using namespace std; 

queue<pair<int, int>> que; 
bool map[51][51];
int check[51][51];

int _count = 0 ; 
vector<int> vec; 
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} }; 

void BFS(int m, int n , int _curY, int _CurX)
{
	//_count = 0; 

	if (check[_curY][_CurX] || map[_curY][_CurX] != 1)
		return; 

	int cur_y = _curY, cur_x = _CurX;
	que.push(pair<int, int>(cur_y, cur_x));
	check[cur_y][cur_x] = 1;
	//if (map[cur_y][cur_x]) _count++;


	while (!que.empty())
	{
		cur_y = que.front().first; 
		cur_x = que.front().second; 
		que.pop(); 

		for (int i = 0; i < 4; i++)
		{
			int next_y = cur_y + dir[i][0];
			int next_x = cur_x + dir[i][1];

			if (   (!check[next_y][next_x]) 
				&& (map[next_y][next_x])
				&& (next_y>=0&&next_y<n)
				&& (next_x >= 0 && next_x < m))
			{
				que.push(pair<int, int>(next_y, next_x));
			    check[next_y][next_x] = 1;	
				//_count++;
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
	
	while (nAmount--)
	{
		for (int i = 0; i < 51; i++)
			for (int j = 0; j < 51; j++)
				map[i][j] = 0; 
		vec.clear(); 

		int m, n, c;
		cin >> m >> n >> c;

		while (c--)
		{
			int x, y;
			cin >> x >> y;
			map[y][x] = 1;
		}


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				BFS(m, n, i, j);
			}
		}

		cout << vec.size() << "\n";
	}
}
