#include "AStar.h"


CAStar::CNode::CNode()
{
}

CAStar::CNode::CNode(int _posX, int _posY, CNode* _pParent, CPosition _EndPos)
{
	m_Point.X = _posX;
	m_Point.Y = _posY;
	pParent = _pParent;
	m_cEndPos = _EndPos;

	if (pParent == nullptr)
	{
		//부모가 없으면 지나간 거리 0
		G = 0;
	}
	//십자 방향인 경우
	else if (
		(pParent->m_Point.X - 1 == m_Point.X && pParent->m_Point.Y == m_Point.Y) ||
		(pParent->m_Point.X + 1 == m_Point.X && pParent->m_Point.Y == m_Point.Y) ||
		(pParent->m_Point.X == m_Point.X && pParent->m_Point.Y - 1 == m_Point.Y) ||
		(pParent->m_Point.X == m_Point.X && pParent->m_Point.Y + 1 == m_Point.Y))
	{
		G = pParent->G + 10;
	}
	else if (
		(pParent->m_Point.X - 1 == m_Point.X && pParent->m_Point.Y + 1 == m_Point.Y) ||
		(pParent->m_Point.X - 1 == m_Point.X && pParent->m_Point.Y - 1 == m_Point.Y) ||
		(pParent->m_Point.X + 1 == m_Point.X && pParent->m_Point.Y - 1 == m_Point.Y) ||
		(pParent->m_Point.X + 1 == m_Point.X && pParent->m_Point.Y + 1 == m_Point.Y))
		{
		G = pParent->G + 14;
	    }
	else 
	{
		cout << "부모 설정 오류" << endl; 
		F = -100000;  H = -100000; G = -100000;
	}

	H = (abs(m_cEndPos.X - m_Point.X)) + (abs(m_cEndPos.Y - m_Point.Y)) * 10; 
	
	F = G + H;
}


CAStar::CNode::~CNode()
{
}

CAStar::CMap::CMap()
{
	// 맵의 크기를 불러옴
	char csizeX[4], csizeY[4];
	GetPrivateProfileStringA("MAP", "sizeX", "", csizeX, sizeof(csizeX) - 1, "Data/Map.txt");
	GetPrivateProfileStringA("MAP", "sizeY", "", csizeY, sizeof(csizeY) - 1, "Data/Map.txt");
	m_sizeX = atoi(csizeX); m_sizeY = atoi(csizeY);

	// 맵 크기 할당
	m_ppMap = new int* [m_sizeX]; // 행 할당
	for (int i = 0; i < m_sizeX; i++) // 열 할당
	{
		m_ppMap[i] = new int[m_sizeY];
	}

	FILE* stream = fopen("Data/Map.txt", "rt"); 
	// 맵의 자료를 불러옴 0=지나갈 수 있는 곳 , 1=장애물
	
	if (stream == nullptr)
	{
		cout << " 못 읽었어" << endl;
	}
	for (int i = 0; i < m_sizeX; i++)
	{
		for (int j = 0; j < m_sizeY; j++)
		{
			fscanf(stream, "%d", &m_ppMap[i][j]);
		}
	}
	fclose(stream);
}

CAStar::CMap::~CMap()
{
	for (int i = 0; i < m_sizeX; i++)
	{
		delete[] m_ppMap[i]; // 맵의 열 동적할당 해제, 열은 행의 갯수만큼 동적할당 되었으므로 sizeX만큼 반복
	}
	delete[] m_ppMap; // 맵의 행 동적할당 해제
}

void CAStar::CMap::Copy(CMap* _pmap)
{
	// 맵 크기 복사
	m_sizeX = _pmap->m_sizeX;
	m_sizeY = _pmap->m_sizeY;

	for (int i = 0; i < m_sizeX; i++)
	{
		for (int j = 0; j < m_sizeY; j++)
		{
			m_ppMap[i][j] = _pmap->m_ppMap[i][j];
		}
	}
}

void CAStar::CMap::PrintMap()
{
	for (int i = 0; i < m_sizeX; i++)
	{
		for (int j = 0; j < m_sizeY; j++)
		{
			printf("%d ", m_ppMap[i][j]);
		}
		printf("\n");
	}
}

// ==========================
//      Astar 내부 함수 
// ==========================
list<CAStar::CPosition*> CAStar::FindPath
(CMap* _Navi, CPosition _StartPos, CPosition _EndPos)
{
	// (상, 하, 좌, 우) 4방향 시계방향 탐색 후 결과에 따라 우상 우하 좌하 좌상 탐색.
	list<CNode*> openNode, closeNode;
	CNode* sNode;
	list<CPosition*>path;

	//시작 지점을 열린 노드에 추가.
	openNode.push_back(new CNode(_StartPos.X, _StartPos.Y, nullptr, _EndPos)); 
	list<CNode*>::iterator iter; 

	while ((openNode.end() != openNode.begin() /*열린 노드가 비거나 (열린노드의 시작 == 끝)*/)
		&& (openNode.end() == FindNode(_EndPos.X, _EndPos.Y, &openNode))/*목적지에 도착 (열린노드에서 값이 발견)*/)
	{
		//열린 노드 중 F값이 제일 작은 노드의 주소를 찾아서 iter에 전달
		iter = FindNextNode(&openNode); 
		sNode = *iter; // 열린 노드 중 F값이 제일 작은 노드를 SNode에 저장

		//선택된 sNode 주변의 8개의 방향 노드를 탐색 한다. 
		//값이 수정 될 수 있는 것은 항상 열린 노드이므로 열린 노드를 넘긴다.
		ExploreNode(_Navi, sNode, &openNode, &closeNode, _EndPos); 

		closeNode.push_back(sNode); // 현재 탐색한 노드를 닫힌 노드에 추가
		openNode.erase(iter); //닫힌 노드에 추가한 노드를 열린 노드에서 제거 
	}

	if (openNode.end() != openNode.begin()) // 길을 찾은 경우
	{   //목적지의 노드를 찾아서 iter에 저장
		iter = FindNode(_EndPos.X, _EndPos.Y, &openNode); 
		for (sNode = *iter; sNode->pParent != nullptr; sNode = sNode->pParent)
		{
			path.push_back(new CPosition(sNode->m_Point.X, sNode->m_Point.Y));
		} path.push_back(new CPosition(sNode->m_Point.X, sNode->m_Point.Y)); 
		//부모가 NULL일 때까지 path에 경로를 저장
		path.reverse(); //목적지점으로부터 역순으로 입력했으므로 다시 역순으로 뒤집어 출발지점이 첫번째가 되도록한다.

		//길을 찾은 경우 동적할당 해제 
		iter = openNode.begin();
		for (; iter != openNode.end(); iter++)
		{
			delete* iter; // 열린 노드 동적할당 해제
		}
		iter = closeNode.begin();
		for (; iter != closeNode.end(); iter++)
		{
			delete* iter; // 닫힌 노드 동적할당 해제
		}

		return path; // 길을 찾은 경우 리턴
	}

	//길을 찾지 못한 경우 동적할당 해제 
	iter = closeNode.begin();
	for (; iter != closeNode.end(); iter++)
	{
		delete* iter; // 닫힌 노드 동적할당 해제
	}
	return path;
}

list<CAStar::CNode*>::iterator CAStar::FindNextNode(list<CNode*>* pOpenNode)
{
	list<CNode*>::iterator iter = (*pOpenNode).begin();

	int minValue = 20000000; //현재 제일 작은 값을 저장 
	int order = 0;

	for (int i = 1; iter != (*pOpenNode).end(); i++, iter++)
	{
		if ((*iter)->F <= minValue)
		{
			minValue = (*iter)->F;
			order = i;
		}
	}

	iter = (*pOpenNode).begin();

	for (int i = 1; i < order; i++)
	{
		iter++; 
	}

	return iter; 
}

list<CAStar::CNode*>::iterator CAStar::FindNode(int _posX, int _posY, list<CNode*>* NodeList)
{  
	list<CAStar::CNode*>::iterator iter = NodeList->begin();

	for (int i = 1; iter != NodeList->end(); i++, iter++)
	{
		if ((*iter)->m_Point.X == _posX && (*iter)->m_Point.Y== _posY)
		{
			return iter;
		}
	}
	return NodeList->end();
}

void CAStar::ExploreNode
(CMap* _Navi, CNode* _Node, 
list<CNode*> *_OpenNode, list<CNode*> *_CloseNode,
CPosition EndPos)
{
	// true == 장애물 있음, false == 장애물 없음
	bool up = true, right = true, down = true, left = true;

	list<CNode*>::iterator iter;
	POINT point;

	// (? 상) 
	point.x = _Node->m_Point.X - 1; point.y = _Node->m_Point.Y;
	if (_Node->m_Point.X > 0/*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 
		up = false; 

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode); 
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos)); 
		}
	}

	//  하) 
	point.x = _Node->m_Point.X + 1  ; point.y = _Node->m_Point.Y;
	if (_Node->m_Point.X < (_Navi->m_sizeX - 1)/*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 
		up = false;

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}
	// 좌 
	point.x = _Node->m_Point.X ; point.y = _Node->m_Point.Y - 1 ;
	if (_Node->m_Point.Y> 0/*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 
		up = false;

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}
	// 우
	point.x = _Node->m_Point.X; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 /*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 
		up = false;

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// 우상
	point.x = _Node->m_Point.X - 1 ; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 && _Node->m_Point.X > 0 
		/*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/
		&& up == false && right == false)
	{

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// 우하
	point.x = _Node->m_Point.X + 1 ; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 
		&& _Node->m_Point.X < _Navi->m_sizeX - 1/*맵상에 존재*/ 
		&& _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/
		&& right == false && down == false)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// 좌하
	point.x = _Node->m_Point.X + 1; point.y = _Node->m_Point.Y + 1;
	if ((_Node->m_Point.X < _Navi->m_sizeX - 1) && (_Node->m_Point.Y > 0)
		/*맵상에 존재*/ && _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/
		&& left == false && down == false)
	{

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// 좌상
	point.x = _Node->m_Point.X - 1; point.y = _Node->m_Point.Y - 1;
	if (_Node->m_Point.X > 0 && _Node->m_Point.Y > 0 /*맵상에 존재*/
		&& _Navi->m_ppMap[point.x][point.y] == 0/*장애물없고*/
		&& left == false && up == false)
	{
		//장애물이 없는 경우에 해당하므로 장애물 false 세팅 
		up = false; 

		//이미 열린 노드에 있을 경우 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//원래 부모를 통해서 갔을 때의 비용보다 현재 노드를 통해서 갔을 때 
				//비용이 더 낮아질 경우 
			{
				(*iter)->pParent = _Node; //현재 노드를 부모로 바꿈
			}
		}
		// 닫힌 노드에 있는 경우 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//상방향에 장애물이 없고 열린 노드및 닫힌노드에 추가 되어 있지 않은 경우 
		//상방향 노드를 열린 노드에 추가하고, 부모는 현재 탐색 노드로 지정
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}
}

void CAStar::FindPath()
{
	path = FindPath(&m_Navi, m_StartPos, m_EndPos); 
	iter = path.begin(); 
}

CAStar::CPosition CAStar::GetPos(int order)
{
	CPosition pos; 
	for (int i = 1; i < order; i++)
	{
		iter++;
	}
	pos.X = (*iter)->X;
	pos.Y = (*iter)->Y;
	iter = path.begin(); 
	return pos; 
}

void CAStar::SetFree(int _PosX, int _PosY)
{
	m_Navi.m_ppMap[_PosX][_PosY] = 0; 
}

void CAStar::SetObstacle(int _posX, int PoxY)
{
	m_Navi.m_ppMap[_posX][PoxY] = 1;
}

void CAStar::PrintPath()
{
	for (int i = 0; iter != path.end(); iter++)
	{
		cout << (*iter)->X << (*iter)->Y << endl;
	}
	iter = path.begin(); // iter 값 원래대로 돌려주기
}

void CAStar::PrintMap()
{
	m_Navi.PrintMap(); 
}

void CAStar::PrintNavi()
{
	m_printNavi.Copy(&m_Navi);

	for (int i = 0; iter != path.end(); iter++) // 맵에서 경로에 해당하는 곳은 7로 표시
	{
		m_printNavi.m_ppMap[(*iter)->X][(*iter)->Y] = 7;
	}
	iter = path.begin(); // iter 값 원래대로 돌려주기

	m_printNavi.PrintMap();
}
