#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <list>
#include <Cmath>
#include <Windows.h>
using namespace std; 



class CAStar
{
public :
	struct CPosition
	{
	public:
		int X;
		int Y; 

	public:
		CPosition() {}
		CPosition(int _posX, int _posY) : X(_posX), Y(_posY) {}

		void SetPosition(int _posX, int _posY)
		{
			X = _posX; 
			Y = _posY; 
		}
	};

	struct CNode
	{
	public:
		CPosition m_Point;
		CPosition m_cEndPos;

		int F, G, H; 
		CNode* pParent; 
		CNode(int _posX, int _posY, CNode* _pParent, CPosition _EndPos); 
		CNode(); 
		~CNode(); 
	};

	struct CMap
	{
	public:
		int m_sizeX; 
		int m_sizeY; 
		int** m_ppMap; 
	
	public:
		CMap(); 
		~CMap(); 

		void Copy(CMap* _pmap); // ��������
		void PrintMap(); 
	};

private: //�����Լ�
	list<CPosition*> FindPath (CMap* _Navi, CPosition _StartPos, CPosition _EndPos);
	
	list<CNode*>::iterator FindNextNode(list<CNode*>* pOpenNode); 
	//���³�� �� ����� ���� ���� ��ġ�� ã�Ƽ� ��ȯ�Ѵ�.
	list<CNode*>::iterator FindNode(int _posX, int _posY, list<CNode*>* NodeList);
	//��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ�Ѵ�. ������ end()��ȯ
	void ExploreNode(CMap* _Navi, CNode* _Node,
		list<CNode*>*_OpenNode, list<CNode*> *_CloseNode, CPosition EndPos);

public:
	void FindPath();
	CPosition GetPos(int order);
	list<CPosition*> GetPath() { return path; }
	void SetFree(int _PosX, int _PosY); 
	void SetObstacle(int _posX, int PoxY); //�ش� ��ǥ�� ��ֹ��� ��ġ 
	void PrintPath();
	void PrintMap(); 
	void PrintNavi(); 

private:
	CMap m_Navi; 
	CMap m_printNavi; 

private:
	CPosition m_StartPos, m_EndPos;
	list<CPosition*> path; 
	list<CPosition*>::iterator iter; 

public:
	CAStar(CPosition _StartPos, CPosition _EndPos)
	{
		m_StartPos.X = _StartPos.X; 
		m_StartPos.Y = _StartPos.Y;
		m_EndPos.X = _EndPos.X;
		m_EndPos.Y = _EndPos.Y;

		FindPath(); 
	}
	~CAStar()
	{
		iter = path.begin();
		for (; iter != path.end(); iter++)
		{
			delete* iter;
		}
	}
};

