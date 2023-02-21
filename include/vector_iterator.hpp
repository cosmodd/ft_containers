#pragma once

#include <iostream>
#include <iterator>

namespace ft
{

	// --- Vector Iterator class --- //
	template <class T>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T>
	{

		public:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

		private:
			pointer		_ptr;

		public:
			// -------------------------------------------------------------- //
			//  Constructors/Destructors + assignment                         //
			// -------------------------------------------------------------- //
			vector_iterator():
				_ptr(NULL)
			{}

			vector_iterator(pointer ptr):
				_ptr(ptr)
			{}

			vector_iterator(const vector_iterator &other):
				_ptr(other._ptr)
			{}

			// --- Conversion to const_iterator --- //
			// This is a conversion operator which allows the iterator to be
			// converted to a const_iterator. This is needed for the const
			// version of the vector.
			// e.g.: vector<int>::const_iterator it = vec.begin();
			operator vector_iterator<const value_type>() const
			{
				return (vector_iterator<const value_type>(_ptr));
			}

			// --- Destructor --- //
			~vector_iterator()
			{}

			// --- Assignment --- //
			vector_iterator &operator=(const vector_iterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //
			// --- Dereference --- //
			reference operator*() const
			{
				return (*_ptr);
			}

			pointer operator->() const
			{
				return (_ptr);
			}

			reference operator[](difference_type n) const
			{
				return (_ptr[n]);
			}

			// --- Increment --- //
			vector_iterator &operator++() // ++it
			{
				++_ptr;
				return (*this);
			}

			vector_iterator operator++(int) // it++
			{
				vector_iterator tmp(*this);
				++_ptr;
				return (tmp);
			}

			// --- Decrement --- //
			vector_iterator &operator--() // --it
			{
				--_ptr;
				return (*this);
			}

			vector_iterator operator--(int) // it--
			{
				vector_iterator tmp(*this);
				--_ptr;
				return (tmp);
			}

			// --- Addition --- //
			vector_iterator operator+(difference_type n) const // it + n
			{
				vector_iterator tmp(*this);
				tmp._ptr += n;
				return (tmp);
			}

			vector_iterator &operator+=(difference_type n) // it += n
			{
				_ptr += n;
				return (*this);
			}

			// --- Subtraction --- //
			vector_iterator operator-(difference_type n) const // it - n
			{
				vector_iterator tmp(*this);
				tmp._ptr -= n;
				return (tmp);
			}

			vector_iterator &operator-=(difference_type n) // it -= n
			{
				_ptr -= n;
				return (*this);
			}

			// --- Difference --- //
			difference_type operator-(const vector_iterator &other) const // it - other
			{
				return (_ptr - other._ptr);
			}

			// --- Comparison --- //
			bool operator==(const vector_iterator &other) const // it == other
			{
				return (_ptr == other._ptr);
			}

			bool operator!=(const vector_iterator &other) const // it != other
			{
				return (_ptr != other._ptr);
			}

			bool operator<(const vector_iterator &other) const // it < other
			{
				return (_ptr < other._ptr);
			}

			bool operator<=(const vector_iterator &other) const // it <= other
			{
				return (_ptr <= other._ptr);
			}

			bool operator>(const vector_iterator &other) const // it > other
			{
				return (_ptr > other._ptr);
			}

			bool operator>=(const vector_iterator &other) const // it >= other
			{
				return (_ptr >= other._ptr);
			}

			friend std::ostream &operator<<(std::ostream &out, const vector_iterator &it)
			{
				out << it._ptr;
				return (out);
			}

			// -------------------------------------------------------------- //
			//  Friends                                                       //
			// -------------------------------------------------------------- //

			// --- Addition --- //
			template <typename U>
			friend vector_iterator<U> operator+(typename vector_iterator<U>::difference_type n, const vector_iterator<U> &it);

			// --- Difference --- //
			template <typename IteratorLeft, typename IteratorRight>
			friend typename IteratorRight::difference_type operator-(const IteratorLeft &left, const IteratorRight &right);

			// --- Comparison --- //
			template <class IteratorLeft, class IteratorRight>
			friend bool operator==(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

			template <class IteratorLeft, class IteratorRight>
			friend bool operator!=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

			template <class IteratorLeft, class IteratorRight>
			friend bool operator<(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

			template <class IteratorLeft, class IteratorRight>
			friend bool operator<=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

			template <class IteratorLeft, class IteratorRight>
			friend bool operator>(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

			template <class IteratorLeft, class IteratorRight>
			friend bool operator>=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right);

	};

	template <typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &it)
	{
		return (it + n);
	}

	// Using IteratorRight::difference_type instead of IteratorLeft::difference_type
	// to make sure that IteratorLeft and IteratorRight are of the same type
	template <class IteratorLeft, class IteratorRight>
	typename IteratorRight::difference_type operator-(const IteratorLeft &left, const IteratorRight &right)
	{
		return (left._ptr - right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator==(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr == right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator!=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr != right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator<(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr < right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator<=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr <= right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator>(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr > right._ptr);
	}

	template <class IteratorLeft, class IteratorRight>
	bool operator>=(const vector_iterator<IteratorLeft> &left, const vector_iterator<IteratorRight> &right)
	{
		return (left._ptr >= right._ptr);
	}


}
