#pragma once
#include <iostream>
#include <type_traits>
#include <string>

using namespace std;
// Item 1 is about how templates deduce types
// template functions are functions where a placeholder is used instead of a specific type for function parameters/arguments
// template<typename T>		// T is the arg type
// void f(ParamType param); // ParamType is the type of the function parameter, it can vary from T in a few ways (e.g. as a reference or not, const or not)
// ...
// f(expr)					// f is the function, expr is what's passed as an arg to the function

namespace item_1 {
	
	void NewLine()
	{
		std::cout << std::endl;
	}

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
	void f_ref(T& param)
	{
		// T is deduced to whatever is passed, regardless of ref/not ref, const-ness is maintained

		std::cout << "f_ref: T is " << GetTypeInfo<T>() << ", param is " << GetTypeInfo<decltype(param)>() << std::endl;

	}

	template<typename T>
	void f_const_ref(const T& param)
	{
		// T is a const ref, so no longer need to deduce const-ness
		// T is whatever type is passed, param will be const ref to that type

		std::cout << "f_const_ref: T is " << GetTypeInfo<T>() << ", param is " << GetTypeInfo<decltype(param)>() << std::endl;
	}

	template<typename T>
	void f_universal_ref(T&& param)
	{
		// still a reference, but handles lvalue/rvalue references
		// && is rvalue ref
		//	lvalue (locator value, known memory location)
		//	rvalue (right side, return value that isn't a reference)
		//	int x = 5; x is lvalue, 5 is rvalue
		// if param is lvalue, T and param are lvalue
		// if param is rvalue.....

		std::cout << "f_universal_ref: T is " << GetTypeInfo<T>() << ", param is " << GetTypeInfo<decltype(param)>() << std::endl;

	}

	template<typename T>
	void f_ptr(T* param)
	{
		std::cout << "f_ptr: T is " << GetTypeInfo<T>() << ", param is " << GetTypeInfo<decltype(param)>() << std::endl;
	}

	template<typename T>
	void f_by_value(T param)
	{
		// T is whatever type passed in the expression, ignores const/ref
		// param is a copy of the passed expression, a new object
	
		std::cout << "f_by_value: T is " << GetTypeInfo<T>() << ", param is " << GetTypeInfo<decltype(param)>() << std::endl;

	}

	void Run()
	{
		int x = 123;
		const int cx = x;
		const int& rx = x;

		f_ref(x);	// T is int, ParamType is int&
		f_ref(cx);	// T is const int, ParamType is const int&
		f_ref(rx);  // T is int, ParamType is const int&
		NewLine();

		f_const_ref(x);		// T is int, ParamType is const int&
		f_const_ref(cx);	// T is int, ParamType is const int&
		f_const_ref(rx);	// T is int, ParamType is const int&
		NewLine();

		f_universal_ref(x);		// T is int&, ParamType is int&
		f_universal_ref(cx);	// T is const int&, ParamType is const int&
		f_universal_ref(rx);	// T is const int&, ParamType is const int&
		f_universal_ref(123);	// T is int, ParamType is int&&
		NewLine();

		int* px = &x;
		const int* cpx = &x;
		const int* cpcx = &cx;

		f_ptr(&x);				// T is int, param is int*
		f_ptr(&cx);
		f_ptr(&rx);

		f_ptr(px);
		f_ptr(cpx);				// T is const int, param is const int*
		f_ptr(cpcx);
		NewLine();

		f_by_value(x);		// both int
		f_by_value(cx);		// both int
		f_by_value(rx);		// both int
		f_by_value(123);	// both int
		NewLine();

		// arrays
		char letters[] = { 'h', 'e', 'l', 'l', 'o', '!' };
		const char* hello = "Hello";
		f_by_value(hello);
		f_by_value(letters);

		f_ref(hello);
		f_ref(letters);

		f_const_ref(hello);
		f_const_ref(letters);

		f_universal_ref(hello);
		f_universal_ref(letters);
		f_universal_ref("what's up?");

		f_ptr(hello);
		f_ptr(letters);
		NewLine();

		// functions
		f_ref(NewLine);
		f_const_ref(NewLine);
		f_universal_ref(NewLine);
		f_by_value(NewLine);

		NewLine();
	}









}