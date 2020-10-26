#include <iostream>
#include <string>
using namespace std;

int arr[26];
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int count = 3;
	for (int j = 1, i = 0; i < 26; i++, j++ )
	{
		if (count <= 9&&count!=8)
		{
			if (j > 3)
			{
				j = 1;
				count++;
			}
		}
		else
		{
			if (j > 4)
			{
				j = 1;
				count++;
			}
		}
		
		arr[i] = count; 
	}

	string str; 
	cin >> str; 
	
	int result = 0; 

	for (int i = 0; i < str.size(); i++)
	{
		//char chr = tolower(str[i]); 
		//int ichr = chr - 97; 
		result += arr[str[i]-'A'];
	}

	cout << result; 
}