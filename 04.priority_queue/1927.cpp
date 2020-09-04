#include <iostream>
#include <vector>
using namespace std; 

#define max_size 100'001 

int Heap[max_size]{ 0, };
int gHeapsize = 0; 
std::vector<int> result;
void Min_Heapify(int _index)
{
	//  2 x index 오른쪽 자식, 2 x index + 1 왼쪽 자식 확인
	if (Heap[(2 * _index)] == 0 && Heap[(2 * _index) + 1] == 0)
		return; 
	else
	{
		int miniIndex;
		if (Heap[(2 * _index)] == 0)
		{
			miniIndex = (2 * _index) + 1; 
		}
		else if((Heap[(2 * _index)+1] == 0))
		{
			miniIndex = (2 * _index);

		}
		else 
		{
		     miniIndex = Heap[(2 * _index)] < Heap[(2 * _index) + 1] ? (2 * _index) : (2 * _index) + 1;
		}
		if (Heap[_index] > Heap[miniIndex])
		{
			int temp = Heap[_index];
			Heap[_index] = Heap[miniIndex];
			Heap[miniIndex] = temp;
			Min_Heapify(miniIndex); 
		}
	}
}


void MaxHeapInsert(int _data)
{
	gHeapsize = gHeapsize + 1; 
	Heap[gHeapsize] = _data; 
	int Q = gHeapsize; 
	while (Q > 1 && Heap[Q / 2] > Heap[Q])
	{
		int temp = Heap[Q / 2];
		Heap[Q / 2] = Heap[Q]; 
		Heap[Q] = temp; 
		Q = Q / 2; 
	}
}

int HeapExtractMax()
{
	if (gHeapsize == 0)
		return 0; 
	else 
	{
		int temp = Heap[1];
		Heap[1] = Heap[gHeapsize];
		Heap[gHeapsize] = 0;
		Min_Heapify(1);

		gHeapsize -= 1;
		return temp;
	}
}

int main(void)
{
	int nAmount;

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	std::cin >> nAmount; 
	
	for (int i = 0; i < nAmount; i++)
	{
		int data; 
		std::cin >> data; 
		
		if(data!=0)
		{
			MaxHeapInsert(data);
		}
		else
		{
			std::cout << HeapExtractMax() <<"\n";
		}
	}
}
