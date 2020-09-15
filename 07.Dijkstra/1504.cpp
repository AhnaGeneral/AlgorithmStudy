// 1번 정점에서 -> N번 정점 
// 조건 : 임의로 주어진 두 정점을 반드시 통과 (v1 ≠ v2, v1 ≠ N, v2 ≠ 1)
// 한번 이동했던 정점은 물론, 한번 이동했던 간선도 다시 이동할 수 있다
// 반드시 최단 경로로 이동해야 한다는 사실
#include<iostream>
#include<queue>
#include<vector>
using namespace std; 
#define PAIR_INT pair<int,int> 
#define inf 10'000'000
int dist[801]; 
vector<PAIR_INT>vec[200'001];

void dijkstra(int start)
{
	dist[start] = 0; 
	priority_queue<PAIR_INT, vector<PAIR_INT>, greater<PAIR_INT>> pq;
	pq.push(make_pair(0, start)); 

	while (!pq.empty())
	{
		int next = pq.top().second; 
		int distance = pq.top().first; 

		pq.pop(); 

		//if (distance > dist[next]) continue; 
		for (int i = 0; i < vec[next].size(); i++)
		{
			int position = vec[next][i].second; // 2 -> 3
			int nextdist = vec[next][i].first + distance; //distance // 1 ~ 2
			    // 1 ~ 3       // 1 ~ 2 + 2 ~ 3
			if (dist[position] > nextdist)
			{
				dist[position] = nextdist;

				pq.push(make_pair(nextdist, position));
			}
		}
	}
}


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, E, a, b, c, v1, v2;

	cin >> N >> E;

	for (int i = 1; i <= N; i++)
	{
		dist[i] = inf;
	}
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b >> c;
		vec[a].push_back(make_pair(c, b)); 
		vec[b].push_back(make_pair(c, a)); 
	}

	dijkstra(1);
	
	cin >> v1 >> v2;

	int shorest_dist1_v1 = dist[v1]; //1~v1까지 가는 최단경로
	int shorest_dist1_v2 = dist[v2]; //1~v2까지 가는 최단경로
	
	for (int i = 1; i <= N; i++)
	{
		dist[i] = inf; 
	}
	
	dijkstra(v1);
	int shorest_distv1_v2 = dist[v2]; 
	int shorest_distv1_N = dist[N]; 

	for (int i = 1; i <= N; i++)
	{
		dist[i] = inf;
	}

	dijkstra(v2);
	int shorest_distv2_v1 = dist[v1];
	int shorest_distv2_N = dist[N];
	
	int start_v1_v2_N = shorest_dist1_v1 + shorest_distv1_v2 + shorest_distv2_N; 
	int start_v2_v1_N = shorest_dist1_v2 + shorest_distv2_v1 + shorest_distv1_N;
	
	if (start_v1_v2_N >start_v2_v1_N)
		if (start_v2_v1_N >= inf || start_v2_v1_N < 0)
			cout << -1 << "\n";
		else
			cout << start_v2_v1_N;
	else 
		if (start_v1_v2_N >= inf || start_v1_v2_N < 0)
			cout << -1 << "\n";
		else
			cout << start_v1_v2_N;


	
}