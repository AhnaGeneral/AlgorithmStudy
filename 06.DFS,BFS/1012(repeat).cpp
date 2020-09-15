#include<iostream>
#include<queue>
using namespace std; 

int map[50][50];
int visit[50][50];

queue<pair<int, int>> que; 
int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
                 
bool BFS(pair<int,int> _pos, int _m, int _n)
{	
	int posX = _pos.first;
	int posY = _pos.second; 

	if (visit[posY][posX] || map[posY][posX]!=1) return false;
	
	visit[posY][posX] = 1;
	que.push(make_pair(posX, posY));
	
	while (!que.empty())
	{
		int nextX = que.front().first; 
		int nextY = que.front().second; 
		que.pop(); 
		
		for (int i = 0; i < 4; i++)
		{
			int dirX = nextX + dir[i][0];
			int dirY = nextY + dir[i][1]; 
			
			if (map[dirY][dirX] && !visit[dirY][dirX] 
				&& ((dirX >=0)&&(dirX <_m))
				&& ((dirY >= 0) && (dirY < _n)))
			{
				que.push(make_pair(dirX, dirY));
				visit[dirY][dirX] = 1;
			}
		}
	}
	return true;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nAmount;
	cin >> nAmount;

	while (nAmount--)
	{
		int M, N, K;
		cin >> M >> N >> K;

		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				map[i][j] = 0;
				visit[i][j] = 0; 
			}
		}

		for (int i = 0; i < K; i++)
		{
			//지렁이 위치 초기화 
			int x, y;
			cin >> x >> y;
			map[y][x] = 1;;
		}

		int count =0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				if (BFS(pair<int, int>(j, i), M, N))
					count++; 
		}

		cout << count << "\n"; 
	}
}
