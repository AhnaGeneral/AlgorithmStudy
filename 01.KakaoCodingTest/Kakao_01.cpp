#include <iostream>
#include <string>
#include <vector>
using namespace std;

int solution(string s); 
void main()
{
     cout << solution("aabbaccc") <<endl ;
     cout << solution("ababcdcdababcdcd"	) << endl;
     cout << solution("abcabcdede") << endl;
     cout << solution("abcabcabcabcdededededede") << endl;
     cout << solution("xababcdcdababcdcd") << endl;
}

int liststr(string s)
{
    int NumberCount = 1;
    int minCount = s.length();
    int strLenght = s.length();
    string resultstr;
    vector<string> VecResult; 
    string zeroArray; 

    for (int k = 1; k <= strLenght / 2; k++)
    {
        NumberCount = 1;
        for (int j = 0; j < s.length(); j += k)
        {
            VecResult.push_back(s.substr(j, k));
        }
        zeroArray = VecResult[0];
        int i = 1;
        for (i = 1; i < VecResult.size(); i++)
        {
            if (VecResult[i] == zeroArray)
            {
                NumberCount++;
            }
            else
            {
                if (NumberCount != 1) resultstr += to_string(NumberCount);
                resultstr += zeroArray;
                zeroArray = VecResult[i];
                NumberCount = 1; 
            }
        }
        if (NumberCount != 1)  resultstr += to_string(NumberCount);
            resultstr += zeroArray;
          
            if (minCount > resultstr.length())
                minCount = resultstr.length();
            else
                minCount = minCount;
        resultstr.clear(); 
        VecResult.clear();
        zeroArray.clear();
    }

    return minCount;
}
int solution(string s) 
{
    int answer = 0;
    answer = liststr(s);
    return answer;
}