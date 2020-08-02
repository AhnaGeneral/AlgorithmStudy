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
	
	//< ������
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

// map �����̳ʿ��� ��ü�� Ű�� ����Ϸ��� operator<()�� �ݵ�� �����ؾ� �Ѵ�. 
// map�� ���ҵ��� pair<const Name, size_t>Ÿ���� �Ǵ� ���� �̿��ϸ� ��Ī�� 
// ������ �ڵ带 �����ϰ� �� ���ִ�. 
using Entry = pair <const Name, size_t>; //Entry�� map������ Ÿ������ ����� �� �ִ�. 

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
			// �ʿ� �̹� ������ ������Ʈ�ؾ� �ϴ��� �˻� 
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
	//map ���� at()�� ȣ���ϴ� ������ try ��Ͽ� �� �ʿ䰡 �ִ�. ���ܰ� ���� ���µ� �����ϰ� ����
	//������ ���α׷��� ����ȴ�. 
};
	

