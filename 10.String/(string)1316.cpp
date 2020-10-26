#include <iostream>
#include <string>
#include <vector>
using namespace std; 
struct arr
{
	int count;
	bool control; 
};
arr ar[26];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N;
	cin >> N; 
	


	int count = 0; 
	bool result = false; 
	while (N--)
	{
		string str; 
		cin >> str; 
		
		for (int i = 0; i < 26; i++)
		{
			ar[i].count = 0;
			ar[i].control = false;
		}

		for (int i = 0; i < str.size(); i++)
		{
			int index = str[i] - 97; //a 
			int nexindex = str[i + 1] - 97;//b

			if (ar[index].control)
			{
				result = true; 
			}
			if (index != nexindex)
			{
				ar[index].control = true; 
			}
			//ar[index].count++; 
		}
		if (!result)
			count++; 
		result = false; 
	}

	cout << count; 
}