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
		// ���� ���ҵ��� �ϳ��� ���ʴ�� �����Ѵ�. 
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

	//cout << "\n ����2 Pair_tuple" << endl;
	//// ex 02
	//People Pair_tuple_People; //using�� ����Ͽ� ������ �ڷ��� ����
	//
	//get_people(Pair_tuple_People);
	//List_DOB_JOB(Pair_tuple_People);


	// ex03
	//cout << "\n ����3 multimap" << endl;

	////map�� ���������� Ű/���� ������ ���ĵǰ� ����Ǹ� �ߺ� Ű�� ������� �ʴ´�.
	////�⺻ �Լ� ��ü�� Less<K>�̴�. 
	////insert�� �ϳ� �̻��� ���Ҹ� �����ϸ�, �׻� ���࿡ �����Ѵ�. 

	//multimap <string, string > pets;
	//auto iter = pets.insert(pair<string, string>{string{ "dog" }, string{ "Fang" }});
	//iter = pets.insert(iter, make_pair("dog", "Rover")); //Fang�տ� ����
	//iter = pets.insert(make_pair("dog", "Ahna")); //Fang�ڿ� ����
	////emplace, emplace_hint�Ѵ� ���Ե� ���Ҹ� ����Ű�� �ݺ����̴�. 
	////��Ʈ�� ù��° �μ��� ����Ű�� ��ġ �� �Ǵ� ���� ����� ��ġ�� �� ���Ҹ� �����Ѵ�.
	//iter = pets.emplace("rabbit", "Flopsy");
	//iter = pets.emplace_hint(iter, "rabbit", "Mopsy"); //Flopsy�տ� ���� 

	////multimap������ Ű �ϳ��� ���� �ϳ��� ����Ű�� ���� �ƴϹǷ� ÷�� �����ڴ� �������� �ʴ´�. == 
	////���� ������ map �����̳ʿ� �ִ� at()�Լ��� multimap������ ����Ҽ� ����.
	////find()��� �Լ��� �μ��� ���޵� Ű�� ������ ���� �ϳ��� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�. 
	//iter = pets.find("rabbit");

	//if (iter != pets.end()) cout << iter->second << endl;
	//// rabbit�� Ű���� �ΰ��� ���� �ִµ� �ϳ��� ���� ���̴�. 
	//// multimap������ �̷��� equal_range�� ����غ���
	//auto iters = pets.equal_range("rabbit");
	//// equal_range���� ��ȯ�� pair<frist: �μ����� ���� ���� Ű�� ���� ù��° ���Ҹ� ����Ű�� �ݺ���>
	//if (iters.first != pets.end())
	//{
	//	for (auto pr = iters.first; pr != iters.second; ++pr)
	//	{
	//		cout << pr->second << endl;
	//	}
	//}

	////���� ����� ��� ���� 
	//auto upper = pets.upper_bound("rabbit");
	//auto lower = pets.lower_bound("rabbit");

	//if (upper != lower)
	//{
	//	for (auto pr = lower; pr != upper; ++pr)
	//	{
	//		cout << pr->second << endl;
	//	}
	//}

	////�� �ߺ��Ȱ� � �ִ��� Ȯ�� �Ϸ��� count()�� distance() �Լ��� �������
	//cout << pets.count("rabbit") << endl;
	//cout << distance(lower, upper) << endl;


	//ex4 unordered_map, unordered_multimap 
	//�ϴ� �� �����̳��� ���ҵ��� ���ĵ��� �ʴ´�. 
	//������ ��ġ�� Ű�� ���� �ؽ� ���� ����ؼ� �������Ƿ� ����ϴ� Ű�� Ÿ����
	//�����ϴ� �ؽ� �Լ��� �ݵ�� �ʿ��ϴ�.
	//���� ������ Ŭ���� Ÿ���� ��ü�� Ű�� ����Ѵٸ� �� ��ü�� ���� �ؽ��Լ��� �����Ǿ�� �Ѵ�
	//STL���� hash<T>Ư��ȭȣ �����Ǵ� Ÿ���� ��ü�� Ű��� �����̳ʴ� Ű�� ���� �ؽð��� �����ϴµ� 
	// �� Ư��ȭ�� ����� �� �ִ�. 
	//Ű�� �̿��ϸ� �˻����� �ʾƵ� ������� �ִ� ��ü�� �����Ҽ� �����Ƿ� 
	//���Ҹ� ���� �� �����̳� ���� �� ������ �����ü� �ִ�.

	//�Ϲ������� ����(��ü)���� �ؽ� ���̺� ����ǰ� 
	//���̺� ����Ǵ� �׸���� ��Ŷ�̶�� �θ���. 
	//��Ŷ���� ���Ҹ� ������ ������ �ִ�. 
	//�ؽ� ���� ���� ��Ŷ�� �����ϰ� �Ǵµ� , �̴� �ؽ� ���� ������ ��Ŷ �������� Ȼ�� ũ�� �����̴�. 

	unordered_map<Name, size_t, Hash_Name> hash_unordered_people
	{
		{{{"Sum","mee"}, 26}, {{"Sum","ger"}, 32},{{"kun","hun"}, 28},{{"kim","ah"}, 11} }, 100, Hash_Name()
	};

	//�ι�° �μ��� ��Ŷ�� ������ �����Ѵ�. 
	//��Ŷ ���� �����ϱ� 
	hash_unordered_people.rehash(150);
	cout << "��Ŷ ����:" << hash_unordered_people.bucket_count() << endl;

	auto iter = hash_unordered_people.insert(pair<Name, size_t>({ "hum","papa" }, 60));

	//hash_unordered_people.insert 
	//({ { "hum","ggf" }, 60 },
	//	{ { "hdsjk","mama" }, 55 });

	//��Ŷ�� �����ϱ� 
	auto unorderediter = hash_unordered_people.begin(1); //�� ��° ��Ŷ�� ���� �ݺ��ڸ� ��ȯ�Ѵ�.

	size_t index{ 0 };

	cout << hash_unordered_people.bucket_size(hash_unordered_people.bucket({ "hum","papa" })) << endl;

	for (auto i = hash_unordered_people.begin(index); i != hash_unordered_people.end(index); ++i)
		cout << i->first << " is " << i->second << endl; 
	
}
