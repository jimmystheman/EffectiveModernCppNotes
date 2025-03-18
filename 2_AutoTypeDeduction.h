#pragma once
#include "common.h"
// this item follows up nicely to Item 1, about how the keyword "auto" when declaring a variable will deduce the type
/*
 - auto deduces types similarly to template function deductions
 - auto plays the role of T, and the type specifier for the variable acts as ParamType

 e.g.
 template<typename T>
 void f(ParamType param);
 ...
 f(expr);
 ---

 const/ref can be deduced similarly to template functions
 universtal references deduce similarly
 arrays/functions decay into pointers, const char array decays into const char*

 declarations vs initializer lists


int x = 27 is same as auto x1 = 27
but int x{27} is not the same as auto x{27} (the latter is an initializer list, x is std::initializer_list<int>

that's it for c++11, but c++14 allows function return type to be auto
auto for a function/lambda return is similar to a template function deduction, but doesn't work when returning a braced initializer
 
 */

namespace item_2 {

	void someFunction(int x, double y)
	{
		cout << "x = " << x << ", y = " << y;
	}


	void Run()
	{
		auto x = 27;
		const auto cx = x;
		const auto& rx = x;
		PrintLine("x", GetTypeInfo<decltype(x)>());		// int
		PrintLine("cx", GetTypeInfo<decltype(cx)>());	// const int
		PrintLine("rx", GetTypeInfo<decltype(rx)>());	// const int&

		auto y(27);
		auto z{ 27 }; // some compilers treat this as an int, not an initilizer_list<int>, like mine!!
		auto w = { 27 };
		PrintLine("y", GetTypeInfo<decltype(y)>());	// int
		PrintLine("z", GetTypeInfo<decltype(z)>());	// int
		PrintLine("w", GetTypeInfo<decltype(w)>());	// initializer_list<int>


		auto&& uref_x = x;
		auto&& uref_cx = cx;
		auto&& uref_num = 27;

		PrintLine("uref_x", GetTypeInfo<decltype(uref_x)>());		// int&
		PrintLine("uref_cx", GetTypeInfo<decltype(uref_cx)>());		// const int&
		PrintLine("uref_num", GetTypeInfo<decltype(uref_num)>());	// int&&
	
		const char name[] = "Jimmy Haviland";
		auto auto_name = name;
		auto& ref_name = name;
		const auto& cref_name = name;
		auto&& uref_name = name;
		auto&& uref_name2 = "Jimbo";
		PrintLine("name", GetTypeInfo<decltype(name)>());				// const char[]
		PrintLine("auto_name", GetTypeInfo<decltype(auto_name)>());		// const char*
		PrintLine("ref_name", GetTypeInfo<decltype(ref_name)>());		// const char (&)[15], a reference to an array, including its size
		PrintLine("cref_name", GetTypeInfo<decltype(cref_name)>());		// const char (&)[15]
		PrintLine("uref_name", GetTypeInfo<decltype(uref_name)>());		// const char (&)[15], lvalue
		PrintLine("uref_name2", GetTypeInfo<decltype(uref_name2)>());	// const char (&&)[6], rvalue
		PrintLine("uref_name2", TypeId<decltype(uref_name2)>());		// const char (&&)[6], rvalue


		auto f1 = someFunction;		// f1 where the func decays into pointer to func, void(*)(int, double)
		auto& f2 = someFunction;	// f2 where it's a ref to a function, void (&)(int, double)
		PrintLine("some function", GetTypeInfo<decltype(someFunction)>());
		PrintLine("f1", GetTypeInfo<decltype(f1)>());
		PrintLine("f2", GetTypeInfo<decltype(f2)>());
	}

}