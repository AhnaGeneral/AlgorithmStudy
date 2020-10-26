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

bool v[6]; //�湮�� ��� 
int d[6];  //�Ÿ�

//���� �ּ� �Ÿ��� ������ ������ ��ȯ�Ѵ�.
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

    //ó���̶� �������� ���ص� �Ǵϱ� - 2 
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