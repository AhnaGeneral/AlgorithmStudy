#include<iostream>


int main()
{
	int arr[10]{ 1, 10, 9, 5, 4, 3, 6, 8, 7, 2 };

	// »ğÀÔÁ¤·Ä
	int  j, temp;
	
	for(int i = 0; i <9; ++i)
	{
		j = i;
		while (arr[j] > arr[j + 1])
		{
			temp = arr[j]; 
			arr[j] = arr[j + 1]; 
			arr[j + 1] = temp;
			j--;
		}
	}




	for (int k = 0; k < 10; ++k)
	{
		std::cout << arr[k] << " ";
	}
}