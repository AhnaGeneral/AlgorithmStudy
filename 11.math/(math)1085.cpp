#include<iostream>
using namespace std;


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	
	int x, y, w, h; 
	cin >> x >> y >> w >> h;
	int minx = 0, miny; 
	minx = (w - x > x ? x : w - x); 
	miny = (h - y > y ? y : h - y);

	cout << (minx > miny ? miny : minx);

}