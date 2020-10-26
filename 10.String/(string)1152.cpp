#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

//vector<string> vec; 
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string str; 

	getline(cin, str);
	int count = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
			count++;
	}

	if (str[0] == ' ' && str[str.size() - 1] == ' ')
	{
		count--;
		cout << count; 
		return 0;
	}
	else if (str[0] != ' ' && str[str.size() - 1] != ' ')
	{
		count++; 
		cout << count;
		return 0;
	}

	cout << count; 
	
}