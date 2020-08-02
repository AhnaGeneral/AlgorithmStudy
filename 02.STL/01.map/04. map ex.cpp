//�θ������ ����� �����ϰ� �������� ���α׷� 
//�� ������� ����� ����� ���� ����� ���� �� - Ű �ϳ��� ����� ���� �� ���� �� �� �־�� �Ѵ�
#include<iostream>
#include<vector>
#include<string>
#include<exception> //out_of_range 
#include<sstream>
#include<map>
#include<cctype>

using namespace std; 

class Name
{
private:
	string frist;
	string second;

	friend ostream& operator<<(ostream& out, const Name& name);
	friend istream& operator>>(istream& is, Name& name); 
};
inline ostream& operator <<(ostream& out, const Name& name)
{
	out << name.frist << name.second; 
	return out;
}
inline istream& operator>>(istream& is, Name& name)
{
	is >> name.frist >> name.second; 
	return is;
}

class Quotations
{
private: 
	vector<string> quotes; 
public:
	// ���ڿ� ���ͷ��� ������ �� ����� �����Ѵ�.
	Quotations& operator<<(const char* quote)
	{
		quotes.emplace_back(quote);
		return *this; 
	}

	// string ��ü���� ���ͷ� �� ����� �����Ѵ�.
	Quotations& operator<<(const string& quote)
	{
		quotes.push_back(quote); 
		return *this; 
	}
	// ����� ���ͷ� �̵��Ѵ�. 
	// ������ ���� �Ű������� �μ��� �޴´�. 
	// �Լ��� ��ü���� ������ ���� �Ű������� �̸����� ������ ��
	// ������ ���� �Ű������� �������� �ǹǷ� move�� ����ؾ߸� 
	// ������ puch_back����� ���������� ������ �� �ִ�.
	Quotations& operator<<(string&& quote)
	{
		quotes.push_back(move(quote));
		return *this;
	}
	//�ε����� ������ ����� ��ȯ�Ѵ�.
	string& operator[](size_t index)
	{
		if (index < quotes.size())
			return quotes[index];
		else
			_Xout_of_range("invalid index to quotations");
	}

	size_t size() const { return quotes.size(); }

	//����� ���� �ݺ��ڸ� �����. 
	vector<string>::iterator begin()
	{
		return quotes.begin();
	}

	//����� const ���� �ݺ��ڸ� ��ȯ�Ѵ�. 
	//const ������ begin�� end�� �������� �ʾҴٸ� const ���� ������ 
	//�԰� ���� ��� for������ ����� �� ����.
	vector<string>::const_iterator begin() const
	{
		return quotes.begin();
	}

	//����� �� �ݺ��ڸ� �����. 
	vector<string>::iterator end()
	{
		return quotes.end();
	}

	//����� const �� �ݺ��ڸ� ��ȯ�Ѵ�. 
	vector<string>::const_iterator end() const
	{
		return quotes.end();
	}
};

inline Name Get_name()
{
	Name name{};

	cout<< "Enter frist name and second name";
	cin >> name;
	return name;
}

inline string Get_quote(const Name& name)
{
	cout << "enter the quotation for" << name << "Enter* to end"; 
	string quote; 
	getline(cin, quote, '*');

	return quote; 
}

int main()
{
	map<Name, Quotations> quotations; //�̸�/ ����� ���� ������ �����̳�
	
	cout << "A ��� �߰�" << " L ��� ����Ʈ " << "G ��� ��������" << "Q ����" << endl; 

	Name name{}; 
	string quote{}; 
	char command{}; 

}