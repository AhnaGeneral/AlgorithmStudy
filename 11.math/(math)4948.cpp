#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 
//bool sosu[123457];

int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0);
	//
	//sosu[1] = true;
	//for (int i = 2; i * i <= 123456; i++)
	//{
	//	for (int k = i * i; k <= 123456; k += i)
	//	{
	//		sosu[k] = true;
	//	}
	//}
	
	while(true)
	{
	    int data;
		cin >> data;
		if (!data) return 0; 
		vector<bool> vec(false); 
		vec.resize(data * 2 + 1);

		vec[1] = true;
		for (int i = 2; i * i <= (data * 2); i++)
			for (int k = i * i; k <= (data * 2); k+=i)
				vec[k] = true; 

		cout << count(vec.begin() + data + 1, vec.end(), false)<< "\n";
		vec.clear();
	} 
	
}