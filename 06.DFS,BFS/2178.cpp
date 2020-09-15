#include <iostream>
#include <queue>

using namespace std; 

bool map[100][100];
int Check[100][100]; 
                // down,  up  ,right , left
int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} }; 
int _row, _col;
queue<pair<int, int>> Queue; 

void BFS()
{
    int cur_y = 0, cur_x = 0; 
    Queue.push(pair<int, int>(cur_y, cur_x));
    Check[cur_y][cur_x] = 1;

    while (!Queue.empty())
    {
        cur_y = Queue.front().first;
        cur_x = Queue.front().second;
        Queue.pop();

        for (int i = 0; i < 4; i++)
        {
           int next_y = cur_y + dir[i][0]; 
           int next_x = cur_x + dir[i][1];

            if ((map[next_y][next_x]) && (Check[next_y][next_x] == 0)
                && (next_y >= 0 && next_y < _row && next_x >= 0 && next_x < _col)) // 이거 때문에 틀렸음
            {
                Check[next_y][next_x] = Check[cur_y][cur_x] + 1; 
                Queue.push(pair<int, int>(next_y, next_x));
            }
        }
    }
    //return Check[]

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int row, col;
    cin >> row >> col;
    _row = row; 
    _col = col; 
    for (int i = 0; i < row; i++)
    {
          string data;
          cin >> data;
            
          for (int j = 0; j < col; j++)
            map[i][j] = int(data[j]-48);
    }

    BFS();

    //for (int i = 0; i < row; i++)
    //{
    //    for (int j = 0; j < col; j++)
    //    {
    //        cout << Check[i][j] << " ";
    //    }
    //    cout << "\n";
    //}

    cout << Check[row - 1][col - 1] << "\n";
    
}