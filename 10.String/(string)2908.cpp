#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string a, b; 
	cin >> a >> b; 

	string _a, _b;

	for (auto i = a.rbegin(); i < a.rend(); i++) { _a.push_back(*i); }
	for (auto i = b.rbegin(); i < b.rend(); i++) { _b.push_back(*i); }

	int _aint, _bint; 
	_aint = stoi(_a); _bint = stoi(_b); 
	
	if (_aint > _bint) cout << _aint;
	else cout << _bint; 
	//cout << _aint << endl;
	//cout << _bint << endl;

}