#include <iostream>
#include <string>
using namespace std;

int alphaArr[26]; 

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 26; i++)
	{
		alphaArr[i] = 0; 
	}
	
	string str; 
	
	cin >> str; 
	
	for (int i = 0; i < str.size(); i++)
	{
		  int num =  toupper(str[i])-65; // tolower
		  alphaArr[num]++; 
	}
	int index = 0;
	int maxium = -1; 
	bool bols = true; 
	int count = 0; 
	for (int i = 0; i < 26; i++)
	{
		if (alphaArr[i] > maxium)
		{
			if (count)
			{
				count = 0; 
			}

			index = i; 
			maxium = alphaArr[i];
		}

		else if (alphaArr[i] == maxium)
		{
			count++;
		}

		alphaArr[i] = 0;
	}

	if (count)
	{
		cout << "?"; 
	}
	else
	{
		cout << char(index + 65); 
	}
}