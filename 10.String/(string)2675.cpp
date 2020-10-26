#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T; 
	cin >> T; 
	
	while (T--)
	{
		int R;
		cin >> R;

		string str;
		cin >> str;

		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 0; j < R; j++)
			{
				cout << str[i];
			}
		}
		cout << "\n"; 
		
	}
}