//인명순으로 명언을 저장하고 가져오는 프로그램 
//한 명언인의 명언은 상당히 많은 명언이 있을 것 - 키 하나에 명언을 여러 개 저장 할 수 있어야 한다
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
	// 문자열 리터럴로 생성된 새 명언을 저장한다.
	Quotations& operator<<(const char* quote)
	{
		quotes.emplace_back(quote);
		return *this; 
	}

	// string 객체에서 벡터로 새 명언을 복제한다.
	Quotations& operator<<(const string& quote)
	{
		quotes.push_back(quote); 
		return *this; 
	}
	// 명언을 벡터로 이동한다. 
	// 우측값 참조 매개변수를 인수로 받는다. 
	// 함수의 본체에서 우측값 참조 매개변수를 이름으로 접근할 때
	// 우측값 참조 매개변수는 좌측값이 되므로 move를 사용해야만 
	// 벡터의 puch_back멤버에 우측값으로 전달할 수 있다.
	Quotations& operator<<(string&& quote)
	{
		quotes.push_back(move(quote));
		return *this;
	}
	//인덱스로 지정한 명언을 반환한다.
	string& operator[](size_t index)
	{
		if (index < quotes.size())
			return quotes[index];
		else
			_Xout_of_range("invalid index to quotations");
	}

	size_t size() const { return quotes.size(); }

	//명언의 시작 반복자를 만든다. 
	vector<string>::iterator begin()
	{
		return quotes.begin();
	}

	//명언의 const 시작 반복자를 반환한다. 
	//const 버전의 begin과 end를 정의하지 않았다면 const 루프 변수와 
	//함계 범위 기반 for루프를 사용할 수 없다.
	vector<string>::const_iterator begin() const
	{
		return quotes.begin();
	}

	//명언의 끝 반복자를 만든다. 
	vector<string>::iterator end()
	{
		return quotes.end();
	}

	//명언의 const 끝 반복자를 반환한다. 
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
	map<Name, Quotations> quotations; //이름/ 명언을 쌍을 저장할 컨테이너
	
	cout << "A 명언 추가" << " L 명언 리스트 " << "G 명언 가져오기" << "Q 종료" << endl; 

	Name name{}; 
	string quote{}; 
	char command{}; 

}