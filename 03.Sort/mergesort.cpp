#include<iostream>

using namespace std; 

int sorted[10]{};
void merge(int _arr[], int m, int middle, int n)
{
	int i = m;
	int j = middle + 1;
	int k = m;
	while (i <= middle && j <= n)
	{
		if (_arr[i] <= _arr[j])
		{
			sorted[k] = _arr[i];
			k++;
			i++;
		}
		else
		{
			sorted[k] = _arr[j]; 
			k++; 
			j++; 
		}
	}

	if (i >= middle)
	{
		for (int t = j; t <= n; ++t)
		{
			sorted[k] = _arr[t]; 
			k++;
		}
	}
	else
	{
		for (int t = i; t <= middle; ++t)
		{
			sorted[k] = _arr[t];
			k++;
		}
	}
	for (int t = m; t <= n; ++t)
	{
		_arr[t] = sorted[t]; 
	}
}

void mergesort(int _arr[], int start, int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;

		mergesort(_arr, start, middle);
		mergesort(_arr, middle + 1, end);

		merge(_arr, start, middle, end);
	}
}

int main()
{
	int arr[8]{ 7,6,5,8,3,5,9,1 };

	mergesort(arr, 0, 8);

	for (int i = 0; i < 8; ++i)
	{
		std::cout << arr[i]; 
	}
}