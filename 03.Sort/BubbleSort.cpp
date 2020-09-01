#include<iostream>


int main()
{
	int arr[10]{ 1, 10, 9, 5, 4, 3, 6, 8, 7, 2 };

	//선택정렬
	int tmp;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 -i - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1]; 
				arr[j + 1] = tmp;
			}
		}
	}


	for (int k = 0; k < 10; ++k)
	{
		std::cout << arr[k] << " ";
	}
}