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

	// lambda to print type info
	// TODO: what is the actual type? use auto for now
	// don't get confused with this template or arg types,
	//	the point is to print types of the other template functions
	template<typename T>
	auto typeInfoToStr = [](const char* sender_info, const T& param)
	{
		string type_const_str = std::is_const<T>::value ? "const " : "";
		string type_ref_str = std::is_reference<T>::value ? "&" : "";
		string type_ptr_str = std::is_pointer<T>::value ? "*" : "";
		string type_type = typeid(T).name();

		string type_info = type_const_str + type_ptr_str + type_type + type_ref_str;

		// need to remove reference to check if const, for whatever type param may be
		using ParamType = typename std::remove_reference<decltype(param)>::type;
		string param_const_str = std::is_const<ParamType>::value ? "const " : "";
		string param_ref_str = std::is_reference<decltype(param)>::value ? "&" : "";
		string param_ptr_str = std::is_pointer<decltype(param)>::value ? "*" : "";
		string param_type = typeid(param).name();

		string param_info = param_const_str + param_ptr_str + param_type + param_ref_str;

		std::cout << sender_info << ": T is " << type_info << ", param is " << param_info << std::endl;
	};

	template<typename T>
	void f_ref(T& param)
	{
		// T is deduced to whatever is passed, regardless of ref/not ref, const-ness is maintained
		typeInfoToStr<T>("f_ref", param);
	}

	template<typename T>
	void f_const_ref(const T& param)
	{
		// T is a const ref, so no longer need to deduce const-ness
		// T is whatever type is pased, param will be const ref to that type
		typeInfoToStr<T>("f_const_ref", param);
	}

	template<typename T>
	void f_universal_ref(T&& param)
	{
		// still a reference, but handles lvalue/rvalue references
		//	lvalue (locator value, known memory location)
		//	rvalue (right side, return value that isn't a reference)
		//	int x = 5; x is lvalue, 5 is rvalue
		// if param is lvalue, T and param are lvalue
		// if param is rvalue.....
		typeInfoToStr<T>("f_universal_ref", param);
	}

	template<typename T>
	void f_by_value(T param)
	{
		// T is whatever type passed in the expression, ignores const/ref
		// param is a copye of the passed expression, a new object
		typeInfoToStr<T>("f_by_value", param);
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

		f_by_value(x);		// T is int&, ParamType is int&
		f_by_value(cx);		// T is const int&, ParamType is const int&
		f_by_value(rx);		// T is const int&, ParamType is const int&
		f_by_value(123);	// T is int, ParamType is int&&
		NewLine();
	}









}