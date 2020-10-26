#include <iostream>
#include <string>
#include <vector>
using namespace std;
int alphaArr[26]; 

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	string str; 
	cin >> str; 
	
	vector<pair<int, int>> vec;
	for (int i = 0; i <= 26; i++) alphaArr[i] = -1;

	for (int i = 0; i < str.size(); i++)
	{
		int al = static_cast<int>(str[i]) - 97;
		if (alphaArr[al] != -1)
		{
			if (alphaArr[al] > i)
			{
				alphaArr[al] = i;
			}
		}
		else {
			alphaArr[al] = i;
		}
	}

	for (int i = 0; i < 26; i++)cout << alphaArr[i]<<" ";
	 

	
}