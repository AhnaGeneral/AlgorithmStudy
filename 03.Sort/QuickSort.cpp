#include<iostream>

int data[10]{ 3,7,8,1,5,9,6,10,2,4 }; 

void QuickSort(int* data, int start, int end)
{
	if (start >= end)return; 
	
	int key = start; 
	int i = start + 1; 
	int j = end; 
	int temp;

	while (i <= j)//엇갈리지 않을 때 ! 
	{
		while (data[i] <= data[key]) { i++; }
		while (data[j] >= data[key]&&j>start) { j--; }

		if (i > j)
		{
			temp = data[j]; 
			data[j] = data[key]; 
			data[key] = temp;
		}
		else
		{
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}

	QuickSort(data, start, j - 1);
	QuickSort(data, j +1, end);
}


int main()
{
	QuickSort(data, 0,9);

	for (int k = 0; k < 10; ++k)
	{
		std::cout << data[k] << " ";
	}
}