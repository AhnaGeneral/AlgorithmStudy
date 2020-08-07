#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>   // istringstream 
#include <algorithm> // replace_if(), for_each()
#include <map>
#include <cctype>    // isalpha()
#include <iterator>  // istream_iterator
using std::string;
using namespace std; 

int main()
{
	cout << "enter some text and enter * to end" << endl; 
	string text_in{}; 
	getline(cin, text_in, '*'); 

	//����ĺ� ���ڴ� �������� ġȯ�Ѵ�. 
	replace_if(std::begin(text_in), end(text_in), 
		[](const char& ch) {return !isalpha(ch); }, ' ');

	istringstream text(text_in); // �ؽ�Ʈ �Է� ���ڿ��� ��Ʈ������
	istream_iterator<string> begin(text);  
	istream_iterator<string> end; 

	map<string, size_t> words; 
	size_t max_len{};  //�ܾ� �ִ� ���� 

	for_each(begin, end, [&max_len, &words](const string& word)
	{
		words[word]++;
		max_len = max(max_len, word.length());
	}); 

	size_t per_line{ 4 }, count{};
	for (const auto& w : words)
	{
		cout << w.first << " " << w.second << endl; 
	}

	

}