// all_of() : �˰��� ������ ��� ���ҿ� ���� �����ڰ� true�� ��ȯ�ϸ� true�� ��ȯ�Ѵ�.
// any_of() : �˰��� ������ ���ҿ� ���� �����ڰ� true�� ��ȯ�ϸ� true�� ��ȯ�Ѵ�.
// none_of(): �˰��� ������ ��� ���� false�� ��ȯ�ϸ� true�� ��ȯ�Ѵ�. 

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

//�ܻ��� ������ ���� ���ϱ� 
//�� ���ڿ��� ���ĺ� ������ ù ��° ���ں��� ���ϸ鼭 �����Ѵ�. 
//�� ���ڿ��� ���̰� ���� ��� ���ڰ� ���ٸ� �� ���ڿ��� ����. 
//lexicographical_compare() : ù ��° ������ ���� ������ �ι�° �������� �۴ٸ� true, �׷��� �ʴٸ� false

void main()
{
	vector<string> phrase01{ "the", "tigers","of","wrath" };
	vector<string> phrase02{ "the", "horses","of","instrcution" };

	auto less = lexicographical_compare(begin(phrase01), end(phrase01), begin(phrase02), end(phrase02));
	copy(begin(phrase01), end(phrase01), ostream_iterator<string>{cout, " "});
	cout << (less ? "are" : "are not") << "less than";
	copy(begin(phrase02), end(phrase02), ostream_iterator<string>{cout, " "});
	cout << endl;

	cout << "======������ ����======" << endl;
	vector<int> range{ 1,2,3,4 };
	//do
	//{
	//	copy(begin(range), end(range), ostream_iterator<int>(cout, " "));
	//	cout << endl;
	//} while (next_permutation(begin(range), end(range)));

	cout << "======������ ����======" << endl; 
	vector<string> names{ "AI", "Beth","Carol", "Dan","Eve", "Fred", "George" }; 
	unordered_set<string> more_name{ "Janet", "John" };

	copy_n(begin(names) + 1, 3, inserter(more_name, begin(more_name)));
	copy_n(begin(names) + 1, 3, ostream_iterator<string>{cout, " "});

	size_t max_length = 4; 
	copy_if(names.begin(), names.end(), inserter(more_name, begin(more_name))
		, [max_length](const string& s) {return s.length() <= max_length; });

	//cout << "\n�Է½�Ʈ�� �ݺ��ڸ� copy_if()�˰����� �������� ������ �ִ�." << endl; 
	//copy_if(istream_iterator<string>{cin}, istream_iterator<string>{},
	//	inserter((more_name), begin(more_name)), 
	//	[max_length](const string& s) {return s.length <= max_length; });

	cout << "======�������� �����ϱ�======" << endl;
	//1. copy_backward() : ������ ���ҿ��� ù��° ���� ������ ��!��! �Ѵ�. 
	//                     ���� �̹Ƿ� ������ ������ �ʴ´�.
	//  * ���� : ������ ���� �� ����� �ݺ��� �̾�� �Ѵ�. 
	//          ������ �ϱ� ���� ��� ���ҵ��� ���� �־�� �Ѵ�. �� ��� ������ ���� ����
	//          ��ŭ�� ���Ҹ� ���ų� �� ���� ���Ҹ� ���� �־�� �Ѵ�. 
	//  * ��ȯ : ������ ������ ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�ϰ�, �̴� �� ��ġ���� �ش� ������ ���� �ݺ��ڰ� �ȴ�.
	
	deque<string> song{ "jingle", "bells", "jingle", "all", "the", "way" };
	song.resize(song.size() + 2);//���� �� ���� �߰� 
	copy_backward(song.begin(), song.begin() + 6, song.end()); 
	copy(song.begin(), song.end(), ostream_iterator<string>(cout, " ")); 

	
	cout << "======���� ������ ����� �����ϱ�======" << endl;
	
	string sentence; 
	cout << "Enter a sentence or Ctrl+Z to end"; 
	getline(cin, sentence);
	//if (cin.eof())break; //Ctrl+Z�� ������ �Է� ��Ʈ���� eof�� �����ϰ� ������ �����Ѵ�. 
	                     //eof�� fstream ��ü�� EOF�� ������ ��� -1�μ� ������ ��ȯ�Ѵ�. 
	                     //������ ���� �����ϸ� eof�� ��ȯ �ȴ�. 
	string only_letters; 
	copy_if(sentence.begin(), sentence.end(), back_inserter(only_letters), [](char ch) {return isalpha(ch); });
	//back_insert�� ������ back_insert_iterator��ü�� ����Ͽ� only_letter�� �߰��Ѵ�. 
	for_each(only_letters.begin(), only_letters.end(), [](char& ch) { ch = toupper(ch); }); 
	//for_each()�� only_letters�� �ִ� ���ڰ� �빮�ڰ� ��ȯ�ȴ�. 
	
	string reversed; //������ �������� �����.
	reverse_copy(only_letters.begin(), only_letters.end(), back_inserter(reversed));
	//���� ����� ������ �ڵ� ! 
	//string reversed{only_letter};
	//reverse((reversed.begin(), reversed.end())

	cout << '"' << sentence << '"' << (only_letters == reversed ? "is" : "is not") << "a palindrome" << endl;
	copy(reversed.begin(), reversed.end(), ostream_iterator<char>(cout, " "));

	cout << "\n======������ �ߺ� ���Ҹ� �����ϰ� ������ �����ϱ�======" << endl;
	// unique_copy() 
	// ������ ���� ������ ������ �� ������ �ߺ� ���Ҹ� ������.
	// ���� �������� �����ϱ� ���� == �����ڸ� �⺻���� ����Ѵ�. 
	// ���� ������ ���ĵǾ� �ִٸ� ��� �ߺ� ���Ұ� ���ŵȴ�.
	// ��� : ��� ������ ������ ���ҿ��� �ϳ� �� �ڸ� ����Ű�� ��� �ݺ��ڸ� ��ȯ�Ѵ�. 
	string text{ "have    you     seen     how      green     the treeeeeeeees seem?" }; 
	string result; 
	auto iter = unique_copy(text.begin(), text.end(), back_inserter(result)); 
	//return = back_insert_iterator
	copy(result.begin(), result.end(), ostream_iterator<char>(cout, " ")); 
	
	cout << "\n�ݺ��Ǵ� ���������!" << endl; 
	unique_copy(text.begin(), text.end(), back_inserter(result), [](char& ch1, char& ch2) {return ch1 == ' ' && ch1 == ch2; });
	copy(result.begin(), result.end(), ostream_iterator<char>(cout, ""));

	cout << "\n======�������� ������ �ߺ��� �����ϱ�======" << endl;
	
	vector<string>words{ "one", "two", "two", "three", "four" }; 
	auto end_iter = unique(words.begin(), words.end()); 
	copy(words.begin(), end_iter, ostream_iterator<string>(cout, ""));
	// unique 
	// * �Է¹��������� � ���ҵ� ���ŵ��� �ʾҴ�. ��, ��ü������ �״�� �����ȴ�. 
	//   end_iter��� word.end()�� ����ߴٸ� ��� ���嵵 ���� ���ҵ��� �������� �ʰ� �״�� 
	//   ���� ���ɼ��� ũ�� ���� �ȿ�����... 
	//   �׷��� erase()�Լ��� �߶󳻴� ���� ����. 
	words.erase(end_iter, words.end());

	cout << "\n======������ ȸ���ϱ�======" << endl;
	// rotate()
	// ���ҵ��� �������� �������� ȸ����Ų��. 
	// 3���� ���ڸ� �޴µ� 1. ó�� ���� ���� 2. ù��° ���Ұ� �� ���Ҹ� ����Ű�� 3. ������ ������ 
	// ���ҵ��� ������ �����ϹǷ� �� ù��° ���� ������ ������ ������ �� ������ ������. 
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

	cout << "\n======������ �̵��ϱ�======" << endl;
	// move 
	// ó�� �� �Է� �ݺ��ڷ� ������ ������ ����° �μ�, ��� �ݺ��ڷ� ������ ����� ���� ������ �̵��Ѵ�. 
	// ��ȯ : �̵��� ������ ���ҿ��� �ϳ� �� �ڸ� ����Ű�� �ݺ��ڸ� ��ȯ
	// �̵� �����̹Ƿ� ���ҵ��� �Է� ������ �̵� ���� ���Ŀ� �״�� ���� �ִ��� ������� �ʴ´�. 
	// �̵� ���� ���Ŀ��� ���� ���Ҹ� ����ϸ� �ȵȴ�. 
	// ���� ������ ��ü�ǰų� �ı��� ���� move()�˰����� ����ؾ� �Ѵ�. 

	vector<int> date{ 1,2,3,4,5,6,7,8 }; 
	move(date.begin() + 2, date.end(), date.begin());
	date.erase(date.end() - 2, date.end()); 
	copy(date.begin(), date.end(), ostream_iterator<int>(cout, " ")); 

	// �̵� ������ ��� ������ ���� ���� �ȿ� �ִٸ� move�� �ùٸ��� �������� �ʴ´�. 
	// �̷� ���� move_backward() �˰����� ����ؾ� �Ѵ�. 
	deque<int> deque_date{ 1,2,3,4,5,6,7,8 };
	move_backward(deque_date.begin(), deque_date.end() - 2, deque_date.end()); 
	deque_date[0] = deque_date[1] = 0; 
	copy(deque_date.begin(), deque_date.end(), ostream_iterator<int>(cout, " "));

	// swap_range()�� �̿��Ͽ� �� ������ ��ȯ �� ���� �ִ�. 
	// �� ������ ���̴� ���ƾ� �Ѵ�. 
	using Name = pair<string, string>; 
	vector<Name> people{ Name{"sun", "mee"}, make_pair<string, string>("ah","na"),
		pair<string, string>("he", "mee"), Name{"Jo", "king"} };
	list<Name>folks{ Name{"Stan","Down"},Name{"Dan","Druff"},Name{"corr","upt"} }; 
	swap_ranges(begin(people), begin(people) + 2, begin(folks));
	for_each(begin(people), end(people), [](const Name& name) {cout << name.first << name.second << endl; });
	for_each(begin(folks), end(folks), [](const Name& name) {cout << name.first << name.second << endl; });
	// utility����� ���ǵ� swap()�� template<typename T1, typename T2> void swap(std::pair<T1, T2> left, std::pair<T1, T2> right);
	// 

	cout << "\n======�������� ���ҵ��� �����ϱ�======" << endl;
	// ���ؽ�Ʈ�� �𸣸鼭 �������� ���ҵ��� �����ϴ°��� �Ұ����ϴ�. 
	// remove() 
	deque<double> samples{ 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.0, 6.7 }; 
	samples.erase(remove(begin(samples), end(samples), 0.0), end(samples)); 
	copy(samples.begin(), samples.end(), ostream_iterator<double>(cout, " "));
	
	// remove_copy()
	// ���� ������ ���� �ΰ� ������ ���ҵ��� ������ �������� �� ������ ����� ���� ���� remove_copy()
	deque<double> copy_samples{ 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.0, 6.7 };
	vector<double> edited_sample; 
	remove_copy(copy_samples.begin(), copy_samples.end(), back_inserter(edited_sample), 0.0f); 
	//0.0�� �ƴ� ���ҵ鸸 edited_sample�� ��!��!�ȴ�. 

	// remove_if()
	set<Name> blacklist{ Name{"AL","Bedo"}, Name{"Ann","ounce"}, Name{"Jo","King"} }; 
	deque<Name>candidate{ Name{"Stan", "Down"}, Name{"AL","Eedo"},Name{"Ann","ounce"}, Name{"Jo","King"}, Name{"Ah","na"} }; 
	candidate.erase(remove_if(candidate.begin(), candidate.end(),
		[&blacklist](const Name& name) {return blacklist.count(name); }), candidate.end()); 
	for_each(candidate.begin(), candidate.end(), [](const Name& name) {cout << name.first << name.second << endl; });

	// remove_copy_if()
	// resultsdeque�� �����̳ʸ� �������� �ʰ� ����� �ִ°͸� ���� remove_if�� ����.
	deque<Name> resultsdeque;
	//remove_copy_if(candidate.begin(), candidate.end(), back_inserter(resultsdeque),
	//	[&blacklist](const Name& name) {return blacklist.count(name); }); 
	//for_each(resultsdeque.begin(), resultsdeque.end(), [](const Name& name) {cout << name.first << name.second << endl; });







}






