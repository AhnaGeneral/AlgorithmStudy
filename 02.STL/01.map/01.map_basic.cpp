#include <iostream>
#include <map>           //map, multimap 
#include <utility>       //pair, make_pair
#include <unordered_map> // unordered_map, unordered_multimap 

using namespace std; 

int main()
{
	map<string, size_t> people{ make_pair("Ann", 25), make_pair("Bill", 46) }; 
	
	// auto pr = make_pair("Fred", 22); 
	// make_pair<>()함수 템플릿의 타입 인수가 인수 타입에서 추론 되기 떄문에  pair<const char*, int>타입이 된다.
	auto pr = make_pair<string, size_t>(string{ "Fred" }, 22); // 변환을 원하지 않으면..
	auto ret_pr = people.insert(pr); // pr객체는 insert()연산에서 컨테이너 원소 타입으로 암묵적으로 변환된다. 

	cout << ret_pr.first->first << " " << ret_pr.first->second << " " << boolalpha << ret_pr.second << endl;

	ret_pr = people.insert(make_pair("Bill", 48)); //이미 있는 것을 넣으면 ? 
	cout << ret_pr.first->first << " " << ret_pr.first->second << " " << boolalpha << ret_pr.second << endl;
	
	// 이미 있는 키에 추가를 하고 싶을 때 
	if (!ret_pr.second) //원소가 있다면 value값만 바꾸는 방법
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
	// 인수 표현식에서 생성되는 initializer_list<> 객체 
	// initializer_list의 첫번째 타입은 반드시 const이여야 한다. 

}