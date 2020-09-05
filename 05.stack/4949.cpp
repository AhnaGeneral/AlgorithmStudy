#include<iostream>
#include<string>
#include<stack>
using namespace std; 

void YESORNO(string _str)
{
	stack<char> small;

	for (int i = 0; i < _str.size(); i++)
	{
		if (_str[i] == ')')
		{
			if (!small.empty())
			{
				if (small.top() == '(')
					small.pop();
				else
					small.push(_str[i]); 
			}
			else 
				small.push(_str[i]);
		}
		else if (_str[i] == '(')
		{
			small.push(_str[i]);
		}

		else if (_str[i] == ']')
		{
			if (!small.empty())
			{
				if (small.top() == '[')
					small.pop();
				else
					small.push(_str[i]);
			}
			else
				small.push(_str[i]);
		}
		else if (_str[i] == '[')
		{
			small.push(_str[i]);
		}
	}


	if (small.empty())
	{
		cout << "yes" << "\n";
	}
	else
	{
		cout << "no" << "\n"; 
	}
}

int main()
{
	while (true)
	{
		string str; 
		getline(cin, str, '.');

		if (str.size()==1&&str[0]=='\n')
			return 0; 

		YESORNO(str); 
	}
}