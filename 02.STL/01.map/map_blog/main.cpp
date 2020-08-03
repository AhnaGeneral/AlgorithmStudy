#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <cctype>
#include <map>
#include <unordered_map>
#include "name.h" 


using namespace std; 
using Entry = pair<const Name, size_t>;

Entry get_entry()
{
	cout << "Enter frist and second names followed by the age";
	Name name{};
	size_t age{};
	cin >> name >> age;
	return make_pair(name, age);
}

void list_entries(const map<Name, size_t>& people)
{
	for (auto& entry : people)
		// 맵의 원소들을 하나씩 차례대로 참조한다. 
		//pair <K,T>  K: frist , T: second 
	{
		cout << "frist name: " << entry.first
			<< "second name: " << entry.second << endl;
	}
}


// ex 02 - pair, tuple 
using Pair_Name = pair<string, string>;
using DOB = tuple<size_t, size_t, size_t>;
using Details = tuple<DOB, size_t, string>;
using Element_type = map<Pair_Name, Details> ::value_type;

using People = map<Pair_Name, Details>; 

void get_people(People& people)
{
	string frist{}, second{}; 
	size_t day{}, month{}, year{}; 
	size_t height{}; 
	string occupation{}; 
	char answer{ 'Y' }; 

	while (toupper(answer) == 'Y')
	{
		cout << "Enter first name and second name" << endl; 
		cin >> frist >> second; 
		cout << "Enter day and month and year" << endl;
		cin >> month >> day >> year; 
		cout << "Hight in inches " << endl;
		cin >> height; 
		cout << "Occupation" << endl;
		getline(cin, occupation, '\n');
		
		people.emplace(make_pair(Pair_Name{ frist, second }, 
			Details{ make_tuple(month, day, year) , height, occupation })); 

		cout << "another ? (Y, N)" << endl; 
		cin >> answer; 
	}
}

void List_DOB_JOB(const People& people)
{
	DOB dob{}; 
	size_t height{};
	string srt{}; 

	for (auto iter = people.begin(); iter != people.end(); ++iter)
	{
		tie(dob, height, srt) = iter->second; 
		cout << iter->first.first << iter->first.second << endl; 
		cout << get<0>(dob) << get<1>(dob) << get<2>(dob) << endl;
		cout << height << srt << endl; 
	}
}


int main()
{
	//// ex 01 
	//map<Name, size_t> people { {{"Ann", "Dante"}, 25 }, 
	//{{"Bill", "Hook"}, 30}, {{"Sun", "mee"}, 43} };
	//
	//cout << "The initial contents of the map is" << endl; 
	//list_entries(people); 
	//
	//char answer{ 'Y' }; 

	//while (toupper(answer) == 'Y')
	//{
	//	Entry entry{ get_entry() };
	//	
	//	auto pr = people.insert(entry); 

	//	if (!pr.second)
	//	{
	//		cout << "already present. update (Y, N)" << endl; 
	//		cin >> answer; 
	//		if (toupper(answer) == 'Y')
	//		{
	//			pr.first->second = entry.second; 
	//		}
	//	}
	//	cout << "another ? (Y, N)" << endl; 
	//	cin >> answer;
	//}
	//
	//list_entries(people);

	//cout << "\n 예제2 Pair_tuple" << endl;
	//// ex 02
	//People Pair_tuple_People; //using을 사용하여 간단한 자료형 생성
	//
	//get_people(Pair_tuple_People);
	//List_DOB_JOB(Pair_tuple_People);


	// ex03
	//cout << "\n 예제3 multimap" << endl;

	////map과 마찬가지로 키/값이 쌍으로 정렬되고 저장되며 중복 키를 허용하지 않는다.
	////기본 함수 객체도 Less<K>이다. 
	////insert는 하나 이상의 원소를 삽입하며, 항상 실행에 성공한다. 

	//multimap <string, string > pets;
	//auto iter = pets.insert(pair<string, string>{string{ "dog" }, string{ "Fang" }});
	//iter = pets.insert(iter, make_pair("dog", "Rover")); //Fang앞에 삽입
	//iter = pets.insert(make_pair("dog", "Ahna")); //Fang뒤에 삽입
	////emplace, emplace_hint둘다 삽입된 원소를 가리키는 반복자이다. 
	////힌트는 첫번째 인수가 가리키는 위치 앞 또는 가장 가까운 위치에 새 원소를 생성한다.
	//iter = pets.emplace("rabbit", "Flopsy");
	//iter = pets.emplace_hint(iter, "rabbit", "Mopsy"); //Flopsy앞에 삽입 

	////multimap에서는 키 하나가 원소 하나만 가리키는 것이 아니므로 첨자 연산자는 지원하지 않는다. == 
	////같은 이유로 map 컨테이너에 있는 at()함수도 multimap에서는 사용할수 없다.
	////find()멤버 함수는 인수로 전달된 키와 동등한 원소 하나를 가리키는 반복자를 반환한다. 
	//iter = pets.find("rabbit");

	//if (iter != pets.end()) cout << iter->second << endl;
	//// rabbit의 키에는 두개의 값이 있는데 하나만 나올 것이다. 
	//// multimap에서는 이럴때 equal_range를 사용해보자
	//auto iters = pets.equal_range("rabbit");
	//// equal_range에서 반환된 pair<frist: 인수보다 작지 않은 키를 갖는 첫번째 원소를 가리키는 반복자>
	//if (iters.first != pets.end())
	//{
	//	for (auto pr = iters.first; pr != iters.second; ++pr)
	//	{
	//		cout << pr->second << endl;
	//	}
	//}

	////같은 결과를 얻기 위해 
	//auto upper = pets.upper_bound("rabbit");
	//auto lower = pets.lower_bound("rabbit");

	//if (upper != lower)
	//{
	//	for (auto pr = lower; pr != upper; ++pr)
	//	{
	//		cout << pr->second << endl;
	//	}
	//}

	////또 중복된게 몇개 있는지 확인 하려면 count()와 distance() 함수를 사용하자
	//cout << pets.count("rabbit") << endl;
	//cout << distance(lower, upper) << endl;


	//ex4 unordered_map, unordered_multimap 
	//일단 이 컨테이너의 원소들은 정렬되지 않는다. 
	//원소의 위치는 키에 대한 해시 값을 사용해서 정해지므로 사용하는 키의 타입을
	//지원하는 해시 함수가 반드시 필요하다.
	//직접 정의한 클래스 타입의 객체를 키로 사용한다면 이 객체를 위한 해시함수가 구현되어야 한다
	//STL에서 hash<T>특수화호 지원되는 타입의 객체가 키라면 컨테이너는 키에 대한 해시값을 생성하는데 
	// 이 특수화를 사용할 수 있다. 
	//키를 이용하면 검색하지 않아도 비순차에 있는 객체에 접근할수 있으므로 
	//원소를 순차 맵 컨테이너 보다 더 빠르게 가져올수 있다.

	//일반적으로 원소(객체)들은 해시 테이블에 저장되고 
	//테이블에 저장되는 항목들은 버킷이라고 부른다. 
	//버킷에는 원소를 여러개 담을수 있다. 
	//해시 값에 따라 버킷을 선택하게 되는데 , 이는 해시 값의 범위가 버킷 개수보다 횔씬 크기 때문이다. 

	unordered_map<Name, size_t, Hash_Name> hash_unordered_people
	{
		{{{"Sum","mee"}, 26}, {{"Sum","ger"}, 32},{{"kun","hun"}, 28},{{"kim","ah"}, 11} }, 100, Hash_Name()
	};

	//두번째 인수는 버킷의 개수를 설정한다. 
	//버킷 개수 조정하기 
	hash_unordered_people.rehash(150);
	cout << "버킷 개수:" << hash_unordered_people.bucket_count() << endl;

	auto iter = hash_unordered_people.insert(pair<Name, size_t>({ "hum","papa" }, 60));

	//hash_unordered_people.insert 
	//({ { "hum","ggf" }, 60 },
	//	{ { "hdsjk","mama" }, 55 });

	//버킷에 접근하기 
	auto unorderediter = hash_unordered_people.begin(1); //두 번째 버킷에 대한 반복자를 반환한다.

	size_t index{ 0 };

	cout << hash_unordered_people.bucket_size(hash_unordered_people.bucket({ "hum","papa" })) << endl;

	for (auto i = hash_unordered_people.begin(index); i != hash_unordered_people.end(index); ++i)
		cout << i->first << " is " << i->second << endl; 
	
}
