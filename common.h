#pragma once
#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

template<typename Type>
string GetTypeInfo()
{
	// remove ref to check for const, and typeid ignores ref/const anyway
	using BaseType = typename std::remove_reference<Type>::type;
	string type_const_str = std::is_const<BaseType>::value ? "const " : "";

	string ref_or_ptr{ };
	if (std::is_lvalue_reference<Type>::value)
	{
		ref_or_ptr = "&";
	}
	else if (std::is_rvalue_reference<Type>::value)
	{
		ref_or_ptr = "&&";
	}
	else if (std::is_pointer<Type>::value)
	{
		//ref_or_ptr = "*";
		// my compiler adds an asterisk
	}

	string type_type = typeid(BaseType).name();

	return type_const_str + type_type + ref_or_ptr;
}

template<typename T>
string TypeId()
{
	return typeid(T).name();
}

void PrintLine(const string& varname, const string& str)
{
	cout << varname << " is " << str << endl;
}