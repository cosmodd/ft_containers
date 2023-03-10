#pragma once

#include <iostream>

#include "iterator_traits.hpp"

namespace ft
{

	// https://devdocs.io/cpp/iterator/reverse_iterator
	template <class Iter>
	class reverse_iterator
	{
		public:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //

			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;

		private:

		protected:
			iterator_type	current;

		public:

			// -------------------------------------------------------------- //
			//  Constructors/Destructors + assignment                         //
			// -------------------------------------------------------------- //

			reverse_iterator():
				current()
			{}

			explicit reverse_iterator(iterator_type x):
				current(x)
			{}

			template <class U> reverse_iterator(const reverse_iterator<U> &other):
				current(other.base())
			{}

			template <class U> reverse_iterator& operator=(const reverse_iterator<U> &other)
			{
				current = other.base();
				return *this;
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //

			// Returns a copy of the underlying iterator.
			iterator_type	base() const
			{
				return current;
			}

			// -------------------------------------------------------------- //
			//  Operators overload                                            //
			// -------------------------------------------------------------- //

			// Returns a reference to the element at the current position
			// and moves the iterator to the previous element.
			reference	operator*() const
			{
				Iter	temp = current;
				return *--temp;
			}

			// Returns a pointer to the element at the current position
			// using the operator*().
			pointer		operator->() const
			{
				return &(operator*());
			}

			// Returns a reference to the element at the given offset
			reference	operator[](difference_type n) const
			{
				return current[-n-1];
			}

			// Moves the iterator to the next element and returns itself.
			reverse_iterator&	operator++()		// ++it
			{
				--current;
				return *this;
			}

			// Returns a copy of the current reverse iterator and moves the
			// current iterator to the next element.
			reverse_iterator	operator++(int)		// it++
			{
				reverse_iterator	copy(*this);

				--current;
				return (copy);
			}

			// Returns a copy of the current reverse iterator moved by n
			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(current - n);
			}

			// Moves the current reverse iterator by n
			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return *this;
			}

			// Moves the iterator to the previous element and returns itself.
			reverse_iterator&	operator--()		// --it
			{
				++current;
				return *this;
			}

			// Returns a copy of the current reverse iterator and moves the
			// current iterator to the previous element.
			reverse_iterator	operator--(int)		// it--
			{
				reverse_iterator	copy(*this);

				++current;
				return (copy);
			}

			// Returns a copy of the current reverse iterator moved by n
			reverse_iterator	operator-(difference_type n) const
			{
				return reverse_iterator(current + n);
			}

			// Moves the current reverse iterator by n
			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return *this;
			}

	};

	/* Comparison Operators */
	/* https://devdocs.io/cpp/iterator/reverse_iterator/operator_cmp */

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}

	/* Arithmetic operators */

	// https://devdocs.io/cpp/iterator/reverse_iterator/operator_plus_
	// Allows the following operation:
	// ft::reverse_iterator<Iterator>::difference_type + ft::reverse_iterator<Iterator>
	template< class Iterator >
	ft::reverse_iterator<Iterator> operator+( typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& it )
	{
		return it.operator+(n);
	}

	// https://devdocs.io/cpp/iterator/reverse_iterator/operator-
	// Allows the following operation:
	// const ft::reverse_iterator<Iterator> - const ft::reverse_iterator<Iterator>
	template< class Iterator >
	typename ft::reverse_iterator<Iterator>::difference_type operator-( const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs )
	{
		return rhs.base() - lhs.base();
	}

	// https://gcc.gnu.org/onlinedocs/gcc-12.2.0/libstdc++/api/a19885_source.html#l00610
	// https://cplusplus.github.io/LWG/issue280
	// Allows the following operation:
	// const ft::reverse_iterator<IterL> - const ft::reverse_iterator<IterR>
	template < class IterL, class IterR >
	typename ft::reverse_iterator<IterR>::difference_type operator-( const ft::reverse_iterator<IterL>& lhs, const ft::reverse_iterator<IterR>& rhs )
	{
		return rhs.base() - lhs.base();
	}

}
