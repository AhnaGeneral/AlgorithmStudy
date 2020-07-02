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
		//�θ� ������ ������ �Ÿ� 0
		G = 0;
	}
	//���� ������ ���
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
		cout << "�θ� ���� ����" << endl; 
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
	// ���� ũ�⸦ �ҷ���
	char csizeX[4], csizeY[4];
	GetPrivateProfileStringA("MAP", "sizeX", "", csizeX, sizeof(csizeX) - 1, "Data/Map.txt");
	GetPrivateProfileStringA("MAP", "sizeY", "", csizeY, sizeof(csizeY) - 1, "Data/Map.txt");
	m_sizeX = atoi(csizeX); m_sizeY = atoi(csizeY);

	// �� ũ�� �Ҵ�
	m_ppMap = new int* [m_sizeX]; // �� �Ҵ�
	for (int i = 0; i < m_sizeX; i++) // �� �Ҵ�
	{
		m_ppMap[i] = new int[m_sizeY];
	}

	FILE* stream = fopen("Data/Map.txt", "rt"); 
	// ���� �ڷḦ �ҷ��� 0=������ �� �ִ� �� , 1=��ֹ�
	
	if (stream == nullptr)
	{
		cout << " �� �о���" << endl;
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
		delete[] m_ppMap[i]; // ���� �� �����Ҵ� ����, ���� ���� ������ŭ �����Ҵ� �Ǿ����Ƿ� sizeX��ŭ �ݺ�
	}
	delete[] m_ppMap; // ���� �� �����Ҵ� ����
}

void CAStar::CMap::Copy(CMap* _pmap)
{
	// �� ũ�� ����
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
//      Astar ���� �Լ� 
// ==========================
list<CAStar::CPosition*> CAStar::FindPath
(CMap* _Navi, CPosition _StartPos, CPosition _EndPos)
{
	// (��, ��, ��, ��) 4���� �ð���� Ž�� �� ����� ���� ��� ���� ���� �»� Ž��.
	list<CNode*> openNode, closeNode;
	CNode* sNode;
	list<CPosition*>path;

	//���� ������ ���� ��忡 �߰�.
	openNode.push_back(new CNode(_StartPos.X, _StartPos.Y, nullptr, _EndPos)); 
	list<CNode*>::iterator iter; 

	while ((openNode.end() != openNode.begin() /*���� ��尡 ��ų� (��������� ���� == ��)*/)
		&& (openNode.end() == FindNode(_EndPos.X, _EndPos.Y, &openNode))/*�������� ���� (������忡�� ���� �߰�)*/)
	{
		//���� ��� �� F���� ���� ���� ����� �ּҸ� ã�Ƽ� iter�� ����
		iter = FindNextNode(&openNode); 
		sNode = *iter; // ���� ��� �� F���� ���� ���� ��带 SNode�� ����

		//���õ� sNode �ֺ��� 8���� ���� ��带 Ž�� �Ѵ�. 
		//���� ���� �� �� �ִ� ���� �׻� ���� ����̹Ƿ� ���� ��带 �ѱ��.
		ExploreNode(_Navi, sNode, &openNode, &closeNode, _EndPos); 

		closeNode.push_back(sNode); // ���� Ž���� ��带 ���� ��忡 �߰�
		openNode.erase(iter); //���� ��忡 �߰��� ��带 ���� ��忡�� ���� 
	}

	if (openNode.end() != openNode.begin()) // ���� ã�� ���
	{   //�������� ��带 ã�Ƽ� iter�� ����
		iter = FindNode(_EndPos.X, _EndPos.Y, &openNode); 
		for (sNode = *iter; sNode->pParent != nullptr; sNode = sNode->pParent)
		{
			path.push_back(new CPosition(sNode->m_Point.X, sNode->m_Point.Y));
		} path.push_back(new CPosition(sNode->m_Point.X, sNode->m_Point.Y)); 
		//�θ� NULL�� ������ path�� ��θ� ����
		path.reverse(); //�����������κ��� �������� �Է������Ƿ� �ٽ� �������� ������ ��������� ù��°�� �ǵ����Ѵ�.

		//���� ã�� ��� �����Ҵ� ���� 
		iter = openNode.begin();
		for (; iter != openNode.end(); iter++)
		{
			delete* iter; // ���� ��� �����Ҵ� ����
		}
		iter = closeNode.begin();
		for (; iter != closeNode.end(); iter++)
		{
			delete* iter; // ���� ��� �����Ҵ� ����
		}

		return path; // ���� ã�� ��� ����
	}

	//���� ã�� ���� ��� �����Ҵ� ���� 
	iter = closeNode.begin();
	for (; iter != closeNode.end(); iter++)
	{
		delete* iter; // ���� ��� �����Ҵ� ����
	}
	return path;
}

list<CAStar::CNode*>::iterator CAStar::FindNextNode(list<CNode*>* pOpenNode)
{
	list<CNode*>::iterator iter = (*pOpenNode).begin();

	int minValue = 20000000; //���� ���� ���� ���� ���� 
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
	// true == ��ֹ� ����, false == ��ֹ� ����
	bool up = true, right = true, down = true, left = true;

	list<CNode*>::iterator iter;
	POINT point;

	// (? ��) 
	point.x = _Node->m_Point.X - 1; point.y = _Node->m_Point.Y;
	if (_Node->m_Point.X > 0/*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 
		up = false; 

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode); 
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos)); 
		}
	}

	//  ��) 
	point.x = _Node->m_Point.X + 1  ; point.y = _Node->m_Point.Y;
	if (_Node->m_Point.X < (_Navi->m_sizeX - 1)/*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 
		up = false;

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}
	// �� 
	point.x = _Node->m_Point.X ; point.y = _Node->m_Point.Y - 1 ;
	if (_Node->m_Point.Y> 0/*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 
		up = false;

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}
	// ��
	point.x = _Node->m_Point.X; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 /*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 
		up = false;

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// ���
	point.x = _Node->m_Point.X - 1 ; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 && _Node->m_Point.X > 0 
		/*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/
		&& up == false && right == false)
	{

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// ����
	point.x = _Node->m_Point.X + 1 ; point.y = _Node->m_Point.Y + 1;
	if (_Node->m_Point.Y < _Navi->m_sizeY - 1 
		&& _Node->m_Point.X < _Navi->m_sizeX - 1/*�ʻ� ����*/ 
		&& _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/
		&& right == false && down == false)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// ����
	point.x = _Node->m_Point.X + 1; point.y = _Node->m_Point.Y + 1;
	if ((_Node->m_Point.X < _Navi->m_sizeX - 1) && (_Node->m_Point.Y > 0)
		/*�ʻ� ����*/ && _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/
		&& left == false && down == false)
	{

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
		else
		{
			_OpenNode->push_back(new CNode(point.x, point.y, _Node, EndPos));
		}
	}

	// �»�
	point.x = _Node->m_Point.X - 1; point.y = _Node->m_Point.Y - 1;
	if (_Node->m_Point.X > 0 && _Node->m_Point.Y > 0 /*�ʻ� ����*/
		&& _Navi->m_ppMap[point.x][point.y] == 0/*��ֹ�����*/
		&& left == false && up == false)
	{
		//��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ���� 
		up = false; 

		//�̹� ���� ��忡 ���� ��� 
		if (_OpenNode->end() != FindNode(point.x, point.y, _OpenNode))
		{
			iter = FindNode(point.x, point.y, _OpenNode);
			if ((*iter)->G > _Node->G + 10)
				//���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� 
				//����� �� ������ ��� 
			{
				(*iter)->pParent = _Node; //���� ��带 �θ�� �ٲ�
			}
		}
		// ���� ��忡 �ִ� ��� 
		else if (_CloseNode->end() != FindNode(point.x, point.y, _CloseNode))
		{

		}
		//����⿡ ��ֹ��� ���� ���� ���� ������忡 �߰� �Ǿ� ���� ���� ��� 
		//����� ��带 ���� ��忡 �߰��ϰ�, �θ�� ���� Ž�� ���� ����
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
	iter = path.begin(); // iter �� ������� �����ֱ�
}

void CAStar::PrintMap()
{
	m_Navi.PrintMap(); 
}

void CAStar::PrintNavi()
{
	m_printNavi.Copy(&m_Navi);

	for (int i = 0; iter != path.end(); iter++) // �ʿ��� ��ο� �ش��ϴ� ���� 7�� ǥ��
	{
		m_printNavi.m_ppMap[(*iter)->X][(*iter)->Y] = 7;
	}
	iter = path.begin(); // iter �� ������� �����ֱ�

	m_printNavi.PrintMap();
}
