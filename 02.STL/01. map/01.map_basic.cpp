#include <iostream>
#include <map>           //map, multimap 
#include <utility>       //pair, make_pair
#include <unordered_map> // unordered_map, unordered_multimap 

using namespace std; 

int main()
{
	map<string, size_t> people{ make_pair("Ann", 25), make_pair("Bill", 46) }; 
	
	// auto pr = make_pair("Fred", 22); 
	// make_pair<>()�Լ� ���ø��� Ÿ�� �μ��� �μ� Ÿ�Կ��� �߷� �Ǳ� ������  pair<const char*, int>Ÿ���� �ȴ�.
	auto pr = make_pair<string, size_t>(string{ "Fred" }, 22); // ��ȯ�� ������ ������..
	auto ret_pr = people.insert(pr); // pr��ü�� insert()���꿡�� �����̳� ���� Ÿ������ �Ϲ������� ��ȯ�ȴ�. 

	cout << ret_pr.first->first << " " << ret_pr.first->second << " " << boolalpha << ret_pr.second << endl;

	ret_pr = people.insert(make_pair("Bill", 48)); //�̹� �ִ� ���� ������ ? 
	cout << ret_pr.first->first << " " << ret_pr.first->second << " " << boolalpha << ret_pr.second << endl;
	
	// �̹� �ִ� Ű�� �߰��� �ϰ� ���� �� 
	if (!ret_pr.second) //���Ұ� �ִٸ� value���� �ٲٴ� ���
		ret_pr.first->second = 48; 

	ret_pr = people.insert(pair<string, size_t>{"Bill", 48});


	map<string, size_t> crowd{ {"May", 55}, {"pat", 66}, {"Al", 22} }; 
	auto iter = begin(people); 
	advance(iter, 2);
	crowd.insert(++begin(people), iter);

	for (const auto& p : crowd)
	{
		cout << p.first << " " << p.second << endl;
	}

	crowd.insert({ {"Bert",44}, {"Ellen", 59} });
	// �μ� ǥ���Ŀ��� �����Ǵ� initializer_list<> ��ü 
	// initializer_list�� ù��° Ÿ���� �ݵ�� const�̿��� �Ѵ�. 

}