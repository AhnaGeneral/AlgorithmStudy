#include<iostream>
#include<stack>
#include<list>

using namespace std;

int nAmount;
stack<int> sta;
list<char> vec;
int _count = 1; 
int TrueandFalse = 1; 
void SequenceFunc(int _data, int _i)
{
        if (sta.top() == _data)
        {
            vec.push_back('-');
            //cout << "-" << "\n";
            sta.pop();
        }
        else if(sta.top()<_data)
        {
            while (true)
            {
                sta.push(_count++);
                vec.push_back('+');
                if (sta.top() == _data)
                {
                    vec.push_back('-');
                    sta.pop();
                    break;
                }
            }
        }
        else 
        {
            TrueandFalse = 0; 
        }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); 

    cin >> nAmount; 
    sta.push(0);

    for (int i = 0; i < nAmount; i++)
    {
        int data;
        cin >> data; 

        if (nAmount < data)
        {
            cout << "NO" << "\n";
            return 0;
        }

        SequenceFunc(data, i);
    }

    if(TrueandFalse==0)
    { 
        cout << "NO" << "\n";
    }
    else
    {
        for (auto iter = vec.begin(); iter != vec.end(); )
        {
            cout << *iter << "\n"; 
            iter++; 
        }
    }
}