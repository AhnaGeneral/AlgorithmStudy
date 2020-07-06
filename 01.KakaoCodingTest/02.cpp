#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;
string solution(string p);
void main()
{
     cout << solution("(()())()") << endl;
     cout <<solution (")(") << endl;
     cout <<solution ("()))((()") << endl;
     cout <<solution ("") << endl;

}

bool correct(string w)
{
    stack<char> chk_s;
    for (auto& c : w) {
        if (chk_s.empty()) {
            chk_s.push(c);
        }
        else {
            if (c == '(') {
                chk_s.push(c);
            }
            else {
                if (chk_s.top() == '(') {
                    chk_s.pop();
                }
                else {
                    chk_s.push(c);
                }
            }
        }
    }

    return chk_s.empty();
}
string modify(string w)
{
    string tmp = w.substr(1, w.size() - 2);
    string result; 
    if (w.size() == 0)
    {
        return "";
    }
    else 
    {
        for (int i = 0; i < tmp.size(); ++i)
        {
            if (tmp[i] == '(')
                result += ")";
            else if (tmp[i] == ')')
                result += "(";
            //else;
        }
    }

    return result;
}
string solution(string p) {
    string answer = "";
    int countleft =0 , countRight =0; 
    string u, v; 

    if (p.size() == 0)
    {
        return answer;
    }
    else
    {
        for (int i = 0; i < p.size(); ++i)
        {
            if (p[i] == '(')
                countleft++;
            else if (p[i] == ')')
                countRight++;
            
            if (countleft == countRight)
            {
                u = p.substr(0, i+1); 
                v = p.substr(i+1); 
                break;
            }
        }
        if (correct(u))
        {
            return u + solution(v); 
        }
        else
        {
            string empty; 
            empty = "(";
            empty += solution(v);
            empty += ")"; 
            empty += modify(u);
            return empty;
        }
        
    }

    return answer;
}