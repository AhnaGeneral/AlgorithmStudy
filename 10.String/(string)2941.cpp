#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string str[8]{ "c=", "c-","dz=","d-","lj", "nj", "s=", "z=" };

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string strs;
	cin >> strs;
	int count = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int index = 0; //0 
			if (strs[i+ index] == str[j][index])
			{
				index++; //1
				if (strs[i + index] == str[j][index])
				{
					if (j == 2)
					{
						
					    index++; //2
						if (strs[i + index] != str[j][index])
						{
							index = 0;
						}
					}
				}
				else
				{
					index = 0;
				}
			}
			else
			{
				index = 0;
			}
			i += index;
		}
		count++;
	}

	cout << count; 

}