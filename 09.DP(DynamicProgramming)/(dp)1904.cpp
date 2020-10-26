#include <iostream>
#include <vector>
using namespace std; 

vector<int> vec; 

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N; 
	cin >> N;
	int size = 1;
	//int index = 1;

	while (N--)
	{
		for (int i = 0; i < size; i++)
		{
			int data; 
			cin >> data; 
			vec.push_back(data);
		}
		size++;
	}

	// 
	cout << vec.size();
}