#include <iostream>
#include <vector>
#include <queue>
using namespace std; 

priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int>> min_heap; 

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nAmount;
	cin >> nAmount;

	for (int i = 1; i <= nAmount; i++)
	{
		int data;
		cin >> data;

		if (max_heap.size() > min_heap.size()) min_heap.push(data);
		else max_heap.push(data);

		//if (i % 2 == 0)//Â¦¼ö 
		//{
		//	min_heap.push(data);
		//}
		//else
		//{
		//	max_heap.push(data);
		//}

		if ((!min_heap.empty()) && (!max_heap.empty()) 
			&& (min_heap.top() < max_heap.top()))
		{
			int _min = min_heap.top();
			int _max = max_heap.top();
			min_heap.pop(); max_heap.pop();
			max_heap.push(_max); min_heap.push(_min);
		}

		cout << max_heap.top() << "\n";
	}
}





