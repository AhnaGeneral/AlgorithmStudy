#include "AStar.h"

void main()
{
	CAStar::CPosition A(0, 0);
	CAStar::CPosition B(0, 4);

	CAStar astar(A, B);

	astar.PrintNavi();
}