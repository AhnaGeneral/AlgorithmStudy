#include <iostream>
#include <string>
using namespace std; 

int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0);

		string str;
		cin >> str;

		if (isalpha(str[0]))
		{
			cout << static_cast<int>(str[0]);
		}
		else
		{
			cout << static_cast<int>(str[0]);

		}
	
}