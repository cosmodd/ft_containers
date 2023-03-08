#pragma once

namespace ft
{

	template < class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		// ------------------------------------------------------------------ //
		//  Constructors                                                      //
		// ------------------------------------------------------------------ //
		// --- Default constructor --- //
		pair(): first(), second() {}

		// --- Copy constructor --- //
		pair(const first_type& x, const second_type& y): first(x), second(y) {}

		template <class U, class V>
		pair(const pair<U, V>& pr): first(pr.first), second(pr.second) {}

		// --- Copy assignment operator --- //
		pair&	operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}
	};

	template< class T1, class T2, class U1, class U2 >
	bool	operator==(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2, class U1, class U2 >
	bool	operator!=(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2, class U1, class U2 >
	bool	operator<(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		// Lexicographical comparison
		// If lhs.first < rhs.first, return true
		// If lhs.first == rhs.first, return lhs.second < rhs.second
		// If lhs.first > rhs.first, return false

		return lhs.first < rhs.first || ( !(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2, class U1, class U2 >
	bool	operator<=(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		return !(rhs < lhs); // Same thing as !(lhs > rhs)
	}

	template< class T1, class T2, class U1, class U2 >
	bool	operator>(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		return rhs < lhs; // Same thing as (lhs > rhs)
	}

	template< class T1, class T2, class U1, class U2 >
	bool	operator>=(const pair<T1, T2> &lhs, const pair<U1, U2> &rhs)
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2 >
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}
}