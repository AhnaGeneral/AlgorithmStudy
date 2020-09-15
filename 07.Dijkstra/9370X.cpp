// ��Ȯ�� ������ 
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
	// first = �Ÿ��� �־��ִµ� �켱���� ť�� first�� ���� �񱳿����� �ϱ⶧��
	
	while (!pq.empty())
	{
		int next = pq.top().second; // ex) start = 1 
		int nextdist = pq.top().first; // {W:0, D:1} 1~1��
		pq.pop();
		                    // ex) size = 2
		for (int i = 0; i < vec[next].size(); i++)
		{
			// ex) vec[1] {W:3,D:2}, {W:4, D:3}
			int pos = vec[next][i].second; // 2
			int posdist = vec[next][i].first + nextdist; //����ġ = �Ÿ� 
			              // ex) [index = 1] 1 ~ 2���� 

			//dist�� start���� �� ��帶���� �ִܰŸ��� �����ϴ� ����Ʈ
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
	int T; // �׽�Ʈ ���� 
	cin >> T; 
	while (--T)
	{
		int n, m, t; // ������, ����, ������ �ĺ�
		cin >> n >> m >> t;

		int s, g, h; // ����� g,h ���� ůů
		cin >> s >> g >> h;

		for (int i = 0; i < m; i++)
		{
			int a, b, d; //a�� b���̿� ���� d
			cin >> a >> b >> d;
		}

		for (int i = 0; i < t; i++)
		{
			int x; //t���� ������ �ĺ��� 
				   //t���� �������� ���� �ٸ� ��ġ�̸� ��� s�� ���� �ʴ�.
			cin >> x;
			tdist.push_back(x);
		}
		// ������ ���̿��� ���ΰ� ���ƺ��� 1���̴�. 
		// m���� �� �߿��� g�� h ������ ���θ� ��Ÿ�� ���� �����Ѵ�.
		// ���� �� ���δ� ������ �ĺ��� �� ��� 1���� ���ϴ� �ִ� ����� �Ϻ��̴�.

		// [idea]
		// ========================================
		dijkstra(s);
		int distS_G = dist[g]; 
		int distS_H = dist[h]; 

		for (auto T_dist : tdist)
		{
			tdistsave.push_back(make_pair(dist[T_dist], T_dist));
			//s���� �����ִܰŸ��� ������ �ȴ�
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

	
		//  s���� �׳� �ִܰŸ��� ���ؼ� ( dist[t1] >= 1��  ) ? 1�� : 1��Ż�� 

		
	
	}
}