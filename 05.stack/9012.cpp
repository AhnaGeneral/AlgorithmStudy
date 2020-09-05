#include <iostream>
#include <stack>
#include <string>
using namespace std;


void YesOrNo(string _str)
{
	stack<char> sta;

	for (int i = 0; i < _str.size(); i++)
	{
		if (_str[i] == ')')
		{
			if (!sta.empty())
			{
				if (sta.top() == '(')
					sta.pop();
				else
					sta.push(_str[i]);
			}
			else
			{
				sta.push(_str[i]);
			}
		}
		else
		{
			sta.push(_str[i]);
		}
	}

	if (sta.empty())
	{
		cout << "YES" <<"\n";
	}
	else
	{
		cout << "NO" << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false); 
	cin.tie(0); 

	int nAmount;
	cin >> nAmount; 

	for (int i = 0; i < nAmount; i++)
	{
		string str; 
		cin >> str;
		YesOrNo(str); 
	}
}