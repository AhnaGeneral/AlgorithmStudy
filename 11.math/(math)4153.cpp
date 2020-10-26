#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	while (true)
	{
		vector<int> vec;
		int a, b, c;
		cin >> a >> b >> c;
		if (!a && !b && !c )return 0; 
		vec.resize(3);
		vec[0] = a; vec[1] = b; vec[2] = c;
		sort(vec.begin(), vec.end(), [](int a, int b) {return a > b; });

		if (pow(vec[0], 2) == pow(vec[1], 2) + pow(vec[2], 2))
			cout << "right" << "\n";
		else
			cout << "wrong" << "\n";
	}
}