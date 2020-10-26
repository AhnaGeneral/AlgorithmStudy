#include<iostream>
using namespace std; 
int zero, one; 
pair<int,int> arr[41]; 

pair<int, int> fibona(int n)
{
	if (n == 0) { return make_pair(1, 0); }
	if (n == 1) { return make_pair(0, 1); }
	if (arr[n] != make_pair(0, 0)) { return arr[n]; }
	return arr[n] = make_pair(fibona(n - 1).first + fibona(n - 2).first,
		fibona(n - 1).second + fibona(n - 2).second);
}
int main(void)
{
	ios_base::sync_with_stdio(false); 
	cin.tie(); 
	
	int T; 
	cin >> T;


	while (T--)
	{
		int data; 
		cin >> data; 
		cout << fibona(data).first <<" "<< fibona(data).second <<"\n";
	}
	
}