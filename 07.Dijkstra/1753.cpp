#include <iostream>
#include <queue>
#include <vector>
using namespace std; 
#define max_vertex 20'001 
#define inf 10'000'000

vector<pair<int, int>> vec[max_vertex];
//vector<int> dir;
int dist[max_vertex]; 

void Dijkstra(int start)
{
	dist[start] = 0;
	//d[start] = 0; 
	// 0, INF, INF, INF, INF, INF ..... 

	priority_queue<pair<int, int>> pq;

	pq.push(make_pair(0, start)); 


	while (!pq.empty())
	{
	    int distance = -pq.top().first;  //2. 0 (거리) 
	    int start = pq.top().second; // 1. start 

	    pq.pop(); 
		
		if (dist[start] < distance) continue;
		for (int i = 0; i < vec[start].size(); i++) 
		{
			int position = vec[start][i].first; // 어디가니?  
			int nextdistance = vec[start][i].second + distance; // A - B - C 

			if (dist[position] > nextdistance)
			{
				dist[position] = nextdistance;
			    pq.push(make_pair(-nextdistance, position));
			}
		}
	}

}
int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 

	int V, E; 
	cin >> V>> E; 
	int start; 
	cin >> start; 
	
	for (int i = 1; i <= V; i++)
	{
		dist[i]=(inf);
	}
	
	for (int i = 0; i < E; i++)
	{
		int u, v, w; 
		cin >> u >> v >> w; 
		vec[u].push_back(make_pair(v, w)); 
	}

	Dijkstra(start); 
	
	for (int i = 1; i <= V; i++)
	{
		if (dist[i] == inf)
			cout << "INF" << "\n"; 
		else 
		cout << dist[i] << "\n";
	}
}