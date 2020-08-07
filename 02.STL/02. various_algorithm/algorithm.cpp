// all_of() : 알고리즘 번위의 모든 원소에 대해 조건자가 true를 반환하면 true를 반환한다.
// any_of() : 알고리즘 번위의 원소에 대해 조건자가 true를 반환하면 true를 반환한다.
// none_of(): 알고리즘 범위의 모든 목이 false를 반환하면 true를 반환한다. 

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_set>
#include <deque>
#include <set>
using namespace std;

//●사전 순서로 범위 비교하기 
//두 문자열의 알파벳 순서는 첫 번째 문자부터 비교하면서 수행한다. 
//두 문자열의 길이가 같고 모든 문자가 같다면 두 문자열은 같다. 
//lexicographical_compare() : 첫 번째 범위가 사전 순으로 두번째 범위보다 작다면 true, 그렇지 않다면 false

void main()
{
	vector<string> phrase01{ "the", "tigers","of","wrath" };
	vector<string> phrase02{ "the", "horses","of","instrcution" };

	auto less = lexicographical_compare(begin(phrase01), end(phrase01), begin(phrase02), end(phrase02));
	copy(begin(phrase01), end(phrase01), ostream_iterator<string>{cout, " "});
	cout << (less ? "are" : "are not") << "less than";
	copy(begin(phrase02), end(phrase02), ostream_iterator<string>{cout, " "});
	cout << endl;

	cout << "======범위의 순열======" << endl;
	vector<int> range{ 1,2,3,4 };
	//do
	//{
	//	copy(begin(range), end(range), ostream_iterator<int>(cout, " "));
	//	cout << endl;
	//} while (next_permutation(begin(range), end(range)));

	cout << "======범위의 복제======" << endl; 
	vector<string> names{ "AI", "Beth","Carol", "Dan","Eve", "Fred", "George" }; 
	unordered_set<string> more_name{ "Janet", "John" };

	copy_n(begin(names) + 1, 3, inserter(more_name, begin(more_name)));
	copy_n(begin(names) + 1, 3, ostream_iterator<string>{cout, " "});

	size_t max_length = 4; 
	copy_if(names.begin(), names.end(), inserter(more_name, begin(more_name))
		, [max_length](const string& s) {return s.length() <= max_length; });

	//cout << "\n입력스트림 반복자를 copy_if()알고리즘의 원본으로 쓸수도 있다." << endl; 
	//copy_if(istream_iterator<string>{cin}, istream_iterator<string>{},
	//	inserter((more_name), begin(more_name)), 
	//	[max_length](const string& s) {return s.length <= max_length; });

	cout << "======역순으로 복제하기======" << endl;
	//1. copy_backward() : 마지막 원소에서 첫번째 원소 순서로 복!제! 한다. 
	//                     복제 이므로 원본은 변하지 않는다.
	//  * 조건 : 증감이 가능 한 양방향 반복자 이어야 한다. 
	//          복제를 하기 전에 대상에 원소들이 먼저 있어야 한다. 즉 대상 범위는 원본 범위
	//          만큼의 원소를 갖거나 더 많은 원소를 갖고 있어야 한다. 
	//  * 반환 : 복제한 마지막 원소를 가리키는 반복자를 반환하고, 이는 새 위치에서 해당 범위의 시작 반복자가 된다.
	
	deque<string> song{ "jingle", "bells", "jingle", "all", "the", "way" };
	song.resize(song.size() + 2);//원소 두 개를 추가 
	copy_backward(song.begin(), song.begin() + 6, song.end()); 
	copy(song.begin(), song.end(), ostream_iterator<string>(cout, " ")); 

	
	cout << "======원소 순서를 뒤집어서 복제하기======" << endl;
	
	string sentence; 
	cout << "Enter a sentence or Ctrl+Z to end"; 
	getline(cin, sentence);
	//if (cin.eof())break; //Ctrl+Z를 읽으면 입력 스트림에 eof를 성정하고 루프를 종료한다. 
	                     //eof는 fstream 객체가 EOF를 만나면 상수 -1로서 참값을 반환한다. 
	                     //파일의 끝에 도달하면 eof가 반환 된다. 
	string only_letters; 
	copy_if(sentence.begin(), sentence.end(), back_inserter(only_letters), [](char ch) {return isalpha(ch); });
	//back_insert로 생성된 back_insert_iterator객체를 사용하여 only_letter에 추가한다. 
	for_each(only_letters.begin(), only_letters.end(), [](char& ch) { ch = toupper(ch); }); 
	//for_each()로 only_letters애 있는 문자가 대문자가 변환된다. 
	
	string reversed; //뒤집은 복제본을 만든다.
	reverse_copy(only_letters.begin(), only_letters.end(), back_inserter(reversed));
	//같은 결과가 나오는 코드 ! 
	//string reversed{only_letter};
	//reverse((reversed.begin(), reversed.end())

	cout << '"' << sentence << '"' << (only_letters == reversed ? "is" : "is not") << "a palindrome" << endl;
	copy(reversed.begin(), reversed.end(), ostream_iterator<char>(cout, " "));

	cout << "\n======인접한 중복 원소를 제거하고 범위를 복제하기======" << endl;
	// unique_copy() 
	// 범위를 다은 범위로 복제할 때 인접한 중복 원소를 제거함.
	// 같은 원소인지 결정하기 위해 == 연산자를 기본으로 사용한다. 
	// 원소 범위가 정렬되어 있다면 모든 중복 원소가 제거된다.
	// 출력 : 대상 범위의 마지막 원소에서 하나 더 뒤를 가리키는 출력 반복자를 반환한다. 
	string text{ "have    you     seen     how      green     the treeeeeeeees seem?" }; 
	string result; 
	auto iter = unique_copy(text.begin(), text.end(), back_inserter(result)); 
	//return = back_insert_iterator
	copy(result.begin(), result.end(), ostream_iterator<char>(cout, " ")); 
	
	cout << "\n반복되는 공백지우기!" << endl; 
	unique_copy(text.begin(), text.end(), back_inserter(result), [](char& ch1, char& ch2) {return ch1 == ' ' && ch1 == ch2; });
	copy(result.begin(), result.end(), ostream_iterator<char>(cout, ""));

	cout << "\n======범위에서 인접한 중복을 제거하기======" << endl;
	
	vector<string>words{ "one", "two", "two", "three", "four" }; 
	auto end_iter = unique(words.begin(), words.end()); 
	copy(words.begin(), end_iter, ostream_iterator<string>(cout, ""));
	// unique 
	// * 입력범위에서는 어떤 원소도 제거되지 않았다. 즉, 전체범위는 그대로 유지된다. 
	//   end_iter대신 word.end()를 사용했다면 어떤한 보장도 없다 원소들은 지워지지 않고 그대로 
	//   있을 가능성이 크다 범위 안에서는... 
	//   그래서 erase()함수로 잘라내는 것이 좋다. 
	words.erase(end_iter, words.end());

	cout << "\n======범위를 회전하기======" << endl;
	// rotate()
	// 원소들의 순차열을 왼쪽으로 회전시킨다. 
	// 3개의 인자를 받는데 1. 처음 시작 원소 2. 첫번째 원소가 될 원소를 가리키고 3. 범위의 끝원소 
	// 원소들은 원형을 유지하므로 새 첫번째 원소 범위가 범위의 시작이 될 때까지 돌린다. 
	vector<string> rotate_words{ "one", "two", "two", "three", "four", "five", "six" };
	auto enditer = rotate(rotate_words.begin(), rotate_words.begin() + 4, rotate_words.end());
	copy(rotate_words.begin(), rotate_words.end(), ostream_iterator<string>(cout, " "));
	cout << "return iter?" << *enditer << endl;

	cout << "\nrotate_copy" << endl; 
	vector<string> rotate_copy_words{ "one", "two", "two", "three", "four", "five", "six" };
	auto fstart = find(rotate_copy_words.begin(), rotate_copy_words.end(), "two");
	auto fend = find(rotate_copy_words.begin(), rotate_copy_words.end(), "six");
	vector<string> word_copy_rotate; 
	rotate_copy(fstart, fstart + 3, fend, back_inserter(word_copy_rotate));
	copy(word_copy_rotate.begin(), word_copy_rotate.end(), ostream_iterator<string>(cout, " "));

	cout << "\n======범위를 이동하기======" << endl;
	// move 
	// 처음 두 입력 반복자로 지정한 범위를 세번째 인수, 출력 반복자로 전의한 대상의 시작 지범에 이동한다. 
	// 반환 : 이동한 마지막 원소에서 하나 더 뒤를 가리키는 반복자를 반환
	// 이동 연산이므로 원소들의 입력 범위가 이동 연산 이후에 그대로 남아 있는지 보장되지 않는다. 
	// 이동 연산 이후에는 원본 원소를 사용하면 안된다. 
	// 원본 범위가 대체되거나 파괴될 때도 move()알고리즘을 사용해야 한다. 

	vector<int> date{ 1,2,3,4,5,6,7,8 }; 
	move(date.begin() + 2, date.end(), date.begin());
	date.erase(date.end() - 2, date.end()); 
	copy(date.begin(), date.end(), ostream_iterator<int>(cout, " ")); 

	// 이동 연산의 대상 범위가 원본 범위 안에 있다면 move는 올바르게 동작하지 않는다. 
	// 이럴 때는 move_backward() 알고리즘을 사용해야 한다. 
	deque<int> deque_date{ 1,2,3,4,5,6,7,8 };
	move_backward(deque_date.begin(), deque_date.end() - 2, deque_date.end()); 
	deque_date[0] = deque_date[1] = 0; 
	copy(deque_date.begin(), deque_date.end(), ostream_iterator<int>(cout, " "));

	// swap_range()를 이용하여 두 범위를 교환 할 수도 있다. 
	// 두 범위의 길이는 같아야 한다. 
	using Name = pair<string, string>; 
	vector<Name> people{ Name{"sun", "mee"}, make_pair<string, string>("ah","na"),
		pair<string, string>("he", "mee"), Name{"Jo", "king"} };
	list<Name>folks{ Name{"Stan","Down"},Name{"Dan","Druff"},Name{"corr","upt"} }; 
	swap_ranges(begin(people), begin(people) + 2, begin(folks));
	for_each(begin(people), end(people), [](const Name& name) {cout << name.first << name.second << endl; });
	for_each(begin(folks), end(folks), [](const Name& name) {cout << name.first << name.second << endl; });
	// utility헤더에 정의된 swap()은 template<typename T1, typename T2> void swap(std::pair<T1, T2> left, std::pair<T1, T2> right);
	// 

	cout << "\n======범위에서 원소들을 제거하기======" << endl;
	// 컨텍스트를 모르면서 번위에서 원소들을 제거하는것은 불가능하다. 
	// remove() 
	deque<double> samples{ 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.0, 6.7 }; 
	samples.erase(remove(begin(samples), end(samples), 0.0), end(samples)); 
	copy(samples.begin(), samples.end(), ostream_iterator<double>(cout, " "));
	
	// remove_copy()
	// 원본 범위를 남겨 두고 선택한 원소들을 제거한 복제본을 새 범위로 만들고 싶을 때는 remove_copy()
	deque<double> copy_samples{ 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.0, 6.7 };
	vector<double> edited_sample; 
	remove_copy(copy_samples.begin(), copy_samples.end(), back_inserter(edited_sample), 0.0f); 
	//0.0이 아닌 원소들만 edited_sample에 복!제!된다. 

	// remove_if()
	set<Name> blacklist{ Name{"AL","Bedo"}, Name{"Ann","ounce"}, Name{"Jo","King"} }; 
	deque<Name>candidate{ Name{"Stan", "Down"}, Name{"AL","Eedo"},Name{"Ann","ounce"}, Name{"Jo","King"}, Name{"Ah","na"} }; 
	candidate.erase(remove_if(candidate.begin(), candidate.end(),
		[&blacklist](const Name& name) {return blacklist.count(name); }), candidate.end()); 
	for_each(candidate.begin(), candidate.end(), [](const Name& name) {cout << name.first << name.second << endl; });

	// remove_copy_if()
	// resultsdeque에 컨테이너를 수정하지 않고 결과를 넣는것만 빼면 remove_if와 같다.
	deque<Name> resultsdeque;
	//remove_copy_if(candidate.begin(), candidate.end(), back_inserter(resultsdeque),
	//	[&blacklist](const Name& name) {return blacklist.count(name); }); 
	//for_each(resultsdeque.begin(), resultsdeque.end(), [](const Name& name) {cout << name.first << name.second << endl; });







}






