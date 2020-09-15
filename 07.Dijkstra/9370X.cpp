// 미확인 도착지 
#include <iostream>
#include <vector>
#include <queue>

using namespace std; 
#define PAIRINT  pair<int, int> 
#define inf 10'000'000

int dist[2'001]; 
vector<PAIRINT> vec[2'001];
vector<int> tdist; 
vector<PAIRINT> tdistsave; 
void dijkstra(int start)
{
	dist[start] = 0; 
	priority_queue<PAIRINT, vector<PAIRINT>, greater<PAIRINT>> pq;
	pq.push(make_pair(0, start));
	// first = 거리를 넣어주는데 우선순위 큐는 first를 먼저 비교연산을 하기때문
	
	while (!pq.empty())
	{
		int next = pq.top().second; // ex) start = 1 
		int nextdist = pq.top().first; // {W:0, D:1} 1~1로
		pq.pop();
		                    // ex) size = 2
		for (int i = 0; i < vec[next].size(); i++)
		{
			// ex) vec[1] {W:3,D:2}, {W:4, D:3}
			int pos = vec[next][i].second; // 2
			int posdist = vec[next][i].first + nextdist; //가중치 = 거리 
			              // ex) [index = 1] 1 ~ 2까지 

			//dist란 start에서 각 노드마다의 최단거리를 저장하는 리스트
			if (dist[pos]/* [start ~> 2] */ > posdist)
			{
				dist[pos] = posdist; 
				pq.push(make_pair(posdist, pos)); 
			}
		}
	}
}


int main(void)
{
	int T; // 테스트 갯수 
	cin >> T; 
	while (--T)
	{
		int n, m, t; // 교차로, 도로, 목적지 후보
		cin >> n >> m >> t;

		int s, g, h; // 출발지 g,h 냄새 킁킁
		cin >> s >> g >> h;

		for (int i = 0; i < m; i++)
		{
			int a, b, d; //a와 b사이에 길이 d
			cin >> a >> b >> d;
		}

		for (int i = 0; i < t; i++)
		{
			int x; //t개의 목적지 후보들 
				   //t개의 지점들은 서로 다른 위치이며 모두 s와 같지 않다.
			cin >> x;
			tdist.push_back(x);
		}
		// 교차로 사이에는 도로가 많아봐야 1개이다. 
		// m개의 줄 중에서 g와 h 사이의 도로를 나타낸 것이 존재한다.
		// 또한 이 도로는 목적지 후보들 중 적어도 1개로 향하는 최단 경로의 일부이다.

		// [idea]
		// ========================================
		dijkstra(s);
		int distS_G = dist[g]; 
		int distS_H = dist[h]; 

		for (auto T_dist : tdist)
		{
			tdistsave.push_back(make_pair(dist[T_dist], T_dist));
			//s에서 보통최단거리가 저장이 된다
		}
		// ========================================
		dijkstra(g); 
		int distG_H = dist[h]; 
		vector<PAIRINT> StartG;

		for (int i = 0; i < tdist.size(); i++)
		{
			StartG.push_back(make_pair(tdist[i], dist[tdist[i]]));
		}
		// ========================================
		dijkstra(h);
		int distH_G = dist[g];
		vector<PAIRINT> StartH;

		for (int i = 0; i < tdist.size(); i++)
		{
			StartH.push_back(make_pair(tdist[i], dist[tdist[i]]));
		}
		//  1. s-> g~h ->t1 , 2. s-> g~h->t2 

		int case1 = distS_G + distG_H; 
		int case2 = distS_H + distH_G;

		vector<pair<PAIRINT,int>> result; 

		for (int i = 0; i < StartG.size(); i++)
		{
			result.push_back(make_pair(make_pair(tdist[i], case1 + StartH[i].second),1)); 
			result.push_back(make_pair(make_pair(tdist[i], case2 + StartG[i].second),0));
		}

	
		//  s에서 그냥 최단거리를 구해서 ( dist[t1] >= 1번  ) ? 1번 : 1번탈락 

		
	
	}
}