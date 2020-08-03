#ifndef NAME_H
#define NAME_H

#include <string>
#include <ostream>
#include <iostream> 
using namespace std; 

class Name
{
private:
	string fristname{}; 
	string secondname{}; 
	
public:
	Name(string frist, string second)
		: fristname{ frist }, secondname{ second }{};
	Name() = default; 
	
	bool operator<(const Name& name) const 
	{
		return (secondname < name.secondname || ((secondname == name.secondname) && (fristname < name.fristname)));
	}
	
	bool operator==(const Name& name) const
	{
		return (secondname == name.secondname) && (fristname == name.fristname);
	}

	size_t hash() const { return std::hash<std::string>()(fristname + secondname); };
	friend istream& operator>>(istream& is, Name& name);
	friend ostream& operator<<(ostream& out, const Name& name);

	
};

inline istream& operator>>(istream& is, Name& name)
{
	is >> name.fristname >> name.secondname;
	return is;
}

inline ostream& operator<<(ostream& out, const Name& name)
{
	out << name.fristname << " " << name.secondname; 
	return out; 
}

class Hash_Name
{
public:
	size_t operator()(const Name& name)const { return name.hash(); };
};
#endif