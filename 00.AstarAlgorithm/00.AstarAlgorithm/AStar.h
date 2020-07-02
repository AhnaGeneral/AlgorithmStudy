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

		void Copy(CMap* _pmap); // 얕은복사
		void PrintMap(); 
	};

private: //내부함수
	list<CPosition*> FindPath (CMap* _Navi, CPosition _StartPos, CPosition _EndPos);
	
	list<CNode*>::iterator FindNextNode(list<CNode*>* pOpenNode); 
	//오픈노드 중 비용이 제일 적은 위치를 찾아서 반환한다.
	list<CNode*>::iterator FindNode(int _posX, int _posY, list<CNode*>* NodeList);
	//노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환한다. 없으면 end()반환
	void ExploreNode(CMap* _Navi, CNode* _Node,
		list<CNode*>*_OpenNode, list<CNode*> *_CloseNode, CPosition EndPos);

public:
	void FindPath();
	CPosition GetPos(int order);
	list<CPosition*> GetPath() { return path; }
	void SetFree(int _PosX, int _PosY); 
	void SetObstacle(int _posX, int PoxY); //해당 좌표에 장애물을 설치 
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

