#include<iostream>
#include<vector>
#include<tuple>
using namespace std; 

vector<int> bellman(501); 
vector<int> check(501); 
vector<tuple<int, int, int>> edge;
int N, M; 

int main()
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 

	cin >> N >> M; 
	for (int i = 0; i << M; i++)
	{
		int A, B, C; 
		cin >> A >> B >> C; 
		edge.push_back(make_tuple(A, B, C));
	}
	
	bellman[1] = 0; 

	for (int i = 2; i <= N; i++)
		bellman[i] = 987654321; 

	for (int i = 1; i <= N; i++)
		for (int j = 0; j < edge.size(); j++)
		{
			int here = get<0>(edge[j]);
			int there = get<1>(edge[j]); 
			int weight = get<2>(edge[j]); 

			if (bellman[here] == 987654321) continue; 
			if (bellman[there] > bellman[here] + weight)
				bellman[there] = bellman[here] + weight;
		}

	//∞À¡ı
	check = bellman; 

	for (int i = 0; i < edge.size(); i++)
	{
		int here = get<0>(edge[i]);
		int there = get<1>(edge[i]); 
		int weight = get<2>(edge[i]); 

		if (check[here] == 987654321) continue; 

		if (check[there] > check[here] + weight)
			check[there] = check[here] + weight; 
	}

	bool flag = true; 
	
	for (int i = 2; i <= N; i++)
		if (check[i] != bellman[i])
		{
			flag = false;
			break; 
		}

	if (flag) {
		for (int i = 2; i <= N; i++) {
			if (bellman[i] == 987654321) {
				cout << -1 << '\n';
			}
			else {
				cout << bellman[i] << '\n';
			}
		}
	}
	else {
		cout << -1 << '\n';
	}

	return 0;
}