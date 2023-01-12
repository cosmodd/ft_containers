#pragma once

#include <cstddef>
#include <iterator>

namespace ft
{

	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef typename std::ptrdiff_t						difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef typename std::ptrdiff_t						difference_type;
		typedef T											value_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class Iter>
	class reverse_iterator
	{
		public:
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
			reverse_iterator():
				current(iterator_type())
			{}

			explicit reverse_iterator(iterator_type x):
				current(x)
			{}

			template <class U> reverse_iterator(const reverse_iterator<U> &other):
				current(other.current)
			{}

			template <class U> reverse_iterator& operator=(const reverse_iterator<U> &other)
			{ current = other.current; }

			iterator_type	base() const
			{
				return current;
			}

			reference	operator*() const
			{ return *(current - 1); }

			// `std::addressof` returns the actual address avoiding overloads of `operator&`
			pointer		operator->() const
			{ return std::addressof(operator*()); }

			reference	operator[](difference_type n) const
			{ return current[-n-1]; }

			reverse_iterator&	operator++()		// ++it
			{
				--current;
				return *this;
			}

			reverse_iterator	operator++(int)		// it++
			{
				reverse_iterator	copy;

				--current;
				return (copy);
			}

			reverse_iterator	operator+(difference_type n)
			{
				return reverse_iterator(current - n);
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return *this;
			}

			reverse_iterator&	operator--()		// --it
			{
				++current;
				return *this;
			}

			reverse_iterator	operator--(int)		// it--
			{
				reverse_iterator	copy;

				++current;
				return (copy);
			}

			reverse_iterator	operator-(difference_type n)
			{
				return reverse_iterator(current + n);
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return *this;
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

}
