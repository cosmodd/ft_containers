#pragma once

#include <iostream>

namespace ft
{

	template <class T>
	struct true_type
	{
		// ------------------------------------------------------------------ //
		// . Type definitions                                                 //
		// ------------------------------------------------------------------ //

		// The type of the value
		typedef bool		value_type;

		// ------------------------------------------------------------------ //
		// . Member variables                                                 //
		// ------------------------------------------------------------------ //

		// The value of the type
		static const bool	value = true;

		// ------------------------------------------------------------------ //
		// . Member functions                                                 //
		// ------------------------------------------------------------------ //

		// Handles the implicit conversion to bool ( e.g.: if (ft::is_integral<int>) )
		operator bool() const { return true;}
	};

	template <class T>
	struct is_integral
	{
		typedef	bool		value_type;
		static const bool	value = false;
		operator bool() const { return false;}
	};

	template<> struct is_integral<bool>: public true_type<bool> {};
	template<> struct is_integral<char>: public true_type<char> {};
	template<> struct is_integral<signed char>: public true_type<signed char> {};
	template<> struct is_integral<unsigned char>: public true_type<unsigned char> {};
	template<> struct is_integral<wchar_t>: public true_type<wchar_t> {};
	template<> struct is_integral<char16_t>: public true_type<char16_t> {};
	template<> struct is_integral<char32_t>: public true_type<char32_t> {};
	template<> struct is_integral<short>: public true_type<short> {};
	template<> struct is_integral<unsigned short>: public true_type<unsigned short> {};
	template<> struct is_integral<int>: public true_type<int> {};
	template<> struct is_integral<unsigned int>: public true_type<unsigned int> {};
	template<> struct is_integral<long>: public true_type<long> {};
	template<> struct is_integral<unsigned long>: public true_type<unsigned long> {};
	template<> struct is_integral<long long>: public true_type<long long> {};
	template<> struct is_integral<unsigned long long>: public true_type<unsigned long long> {};

}
