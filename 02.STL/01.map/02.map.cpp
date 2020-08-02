#include <iostream>
#include <map>           //map, multimap 
#include <utility>       //pair, make_pair
#include <unordered_map> // unordered_map, unordered_multimap 
#include <ostream>
#include <istream>
using namespace std; 

#ifndef NAME_H
#define NAME_H
class Name
{
private:
	string frist; 
	string second; 

public:
	Name(const string& name1, const string& name2) : frist(name1), second(name2) {}
	Name() = default; 
	
	//< 연산자
	bool operator<(const Name& name)const
	{
		return second < name.second || ((second == name.second) && frist < name.frist);
	}
	friend istream& operator >> (istream& in, Name& name); 
	friend ostream& operator << (ostream& out, const Name& name);
};

inline istream& operator>>(istream& in, Name& name)
{
	in >> name.frist >> name.second; 
	return in; 
}

inline ostream& operator<<(ostream& out, const Name& name)
{
	out << name.frist << " " + name.second; 
	return out; 
}
#endif 

// map 컨테이너에서 객체를 키로 사용하려면 operator<()를 반드시 정의해야 한다. 
// map에 원소들은 pair<const Name, size_t>타입이 되는 점을 이용하면 별칭을 
// 정의해 코드를 간결하게 할 수있다. 
using Entry = pair <const Name, size_t>; //Entry를 map원소의 타입으로 사용할 수 있다. 

Entry get_entry()
{
	cout << "Entry frist and second names followed by the age"; 
	Name name{}; 
	size_t age{}; 
	
	cin >> name >> age; 
	return make_pair(name, age);
}

void list_entried(const map<Name, size_t>& people)
{
	for (auto& entry : people)
	{
		cout << left << entry.first << right << entry.second << endl; 
	}
}

int main()
{
	map<Name, size_t> people{ make_pair<Name, size_t>({ "Ann", "Anneo" }, 25),
		make_pair<Name, size_t>({ "ann", "gnneo" }, 45), {{"sun", "mee"}, 50} };

	list_entried(people);

	char answer{ 'Y' }; 

	while (toupper(answer) == 'Y')
	{
		Entry entry{ get_entry() }; 

		auto pr = people.insert(entry); 

		if (!pr.second)
		{
			// 맵에 이미 있으면 업데이트해야 하는지 검사 
			std::cout << "key " << pr.first->first << "already present. "
				"Do you want to update the age (Y or N)"; 

			cin >> answer; 
			if (toupper(answer) == 'Y')
				pr.first->second = entry.second; 


		}
		std::cout << "replay? Y, N"; 
		cin >> answer; 
	}

	Name key; 

	try
	{
		key = Name{ "Sunmi", "Ahna" }; 
		auto value = people.at(key); 
		cout << key << "is age" << value << endl; 

		key = Name{ "Ann", "Anneo" };
		value = people.at(key);
		cout << key << "is age" << value << endl;
	}
	catch (const std::out_of_range& e)
	{
		cerr << e.what() << endl << key << "was not found" << endl; 
	}
	//map 에서 at()을 호출하는 문장은 try 블록에 둘 필요가 있다. 예외가 던져 졌는데 적절하게 잡지
	//않으면 프로그램이 종료된다. 
};
	

