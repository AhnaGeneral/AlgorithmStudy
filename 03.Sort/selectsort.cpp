#include<iostream>


int main()
{
	int arr[10]{ 1, 10, 9, 5, 4, 3, 6, 8, 7, 2 }; 
	
	//선택정렬
	int i, j, min , temp, index; 

	for (i = 0; i < 10; i++)
	{
		min = 999; 
		for (j = i; j < 10; j++)
		{
			if (min > arr[j])
			{
				min = arr[j]; 
				index = j; 
			}
		}

		temp = arr[i]; 
		arr[i] = arr[index]; 
		arr[index] = temp;
	}


	for (int k = 0; k < 10; ++k)
	{
		std::cout << arr[k] << " ";
	}
}