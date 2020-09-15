// DFS와 BFS구현하기 !!!!
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std; 

#define max_size  1'001

bool visit[max_size]{false,};
bool DFSvisit[max_size]{ false, };

stack<int> sta; 
vector<int> vec[max_size]; 
queue<int> que;

void DFS(int _start)
{
	DFSvisit[_start] = true;
	cout << _start << " ";
	int _size = vec[_start].size();

	for (int i = 0; i < _size; i++)
	{
		if (!DFSvisit[vec[_start][i]])
		{
			DFS(vec[_start][i]);
		}
	}
}

void BFS(int _start)
{
	que.push(_start); 
	visit[_start] = true;
	cout << _start << " "; 

	while (!que.empty())
	{
		int next = que.front(); 
		que.pop(); 

		for (int i = 0; i < vec[next].size(); i++)
		{
			if (!visit[vec[next][i]]) 
			{
				que.push(vec[next][i]);
				visit[vec[next][i]] = true;
				cout << vec[next][i] << " ";
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nNumber, nEdge, start;

	cin >> nNumber;
	cin >> nEdge;
	cin >> start;

	for (int i = 0; i < nEdge; i++)
	{
		int d1, d2; 
		cin >> d1 >> d2;
		vec[d2].push_back(d1);
		vec[d1].push_back(d2);
	}
	
	for(int i =1; i<=nNumber; i++)
	sort(vec[i].begin(), vec[i].end());

	DFS(start);
	cout << "\n";
	BFS(start);

}