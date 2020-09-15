#include<iostream>
#include<map>
using namespace std; 

int number = 6; 
int INF = 10'000'000; 

int a[6][6] =
{
    {0,2,5,1,INF, INF},
    {2,0,3,2, INF, INF},
    {5,3,0,3,1,5},
    {1,2,3,0,1, INF},
    {INF,INF,1,1,0,2},
    {INF,INF,5,INF,2,0}
}; 

bool v[6]; //방문한 노드 
int d[6];  //거리

//가장 최소 거리를 가지는 정점을 반환한다.
int getSmallIndex()
{
    int min = INF; 
    int index = 0; 
    
    for (int i = 0; i < number; i++)
    {
        if (d[i] < min & !v[i])
        {
            min = d[i]; 
            index = i; 
        }
    }
    return index;
}

void dijkstra(int start)
{
    for (int i = 0; i < number; i++)
    {
        d[i] = a[start][i]; 
    }

    v[start] = true; 

    //처음이랑 마지막은 안해도 되니깐 - 2 
    for (int i = 0; i < number - 2; i++)
    {
        int current = getSmallIndex(); 
        v[current] = true; 

        for (int j = 0; j < number; j++)
        {
            if (!v[j])
            {
                if (d[j] > a[current][j] + d[current])
                {
                    d[j] = a[current][j] + d[current];
                }
            }
        }
    }
}

int main(void)
{
    dijkstra(0); 
    for (int i = 0; i < number; i++)
    {
        printf("%d", d[i]); 
    }
}