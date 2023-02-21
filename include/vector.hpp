#pragma once

#include <memory>
#include <cmath>
#include <algorithm>

#include "iterators.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{

	// --- Vector class --- //
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef std::ptrdiff_t							difference_type;
			typedef std::size_t								size_type;

			// --- Iterator types --- //
			// This is a template class which defines a random access iterator. The
			// iterator is templated on the type T, which must be a class. The
			// iterator is a random access iterator, so it has operators for
			// addition, subtraction, and comparison.
			typedef vector_iterator<value_type>				iterator;
			typedef vector_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			// -------------------------------------------------------------- //
			//  Member variables                                              //
			// -------------------------------------------------------------- //
			allocator_type		_alloc;		// Allocator object
			size_type			_size;		// Number of elements
			size_type			_capacity;	// Capacity of the vector
			pointer				_ptr;		// Pointer to the first element

			// -------------------------------------------------------------- //
			//  Private member functions                                      //
			// -------------------------------------------------------------- //
			void	move_right(iterator pos, size_type n)
			{
				if (n == 0)
					return ;

				size_type index = pos - _ptr;

				if (_size + n > _capacity)
					reallocation(_size + n);

				// Move the elements to the right
				for (size_type i = _size; i > index && i > 0; i--)
					_ptr[i + n - 1] = _ptr[i - 1];

				// Update the size
				_size += n;
			}

			void	move_left(iterator pos, size_type n)
			{
				if (n == 0)
					return ;

				size_type index = pos - _ptr;

				// Move the elements to the left
				for (size_type i = index; i < _size; i++)
					_ptr[i] = _ptr[i + n];

				// Update the size
				_size -= n;
			}

			void	reallocation(size_type new_capacity)
			{
				new_capacity = std::max(new_capacity, _capacity * 2);
				reserve(new_capacity);
			}

		public:
			// -------------------------------------------------------------- //
			//  Constructors/Destructors + copying                            //
			// -------------------------------------------------------------- //
			// --- Default constructor --- //
			vector(void):
				_alloc(Allocator()),
				_size(0),
				_capacity(0),
				_ptr(nullptr)
			{}

			// --- Constructor with allocator --- //
			explicit vector(const allocator_type &alloc):
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_ptr(nullptr)
			{}

			// --- Constructor with count and value --- //
			explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = Allocator() ):
				_alloc(alloc),
				_size(count),
				_capacity(count),
				_ptr(_alloc.allocate(count))
			{
				assign(count, value);
			}

			// --- Constructor from iterators --- //
			// This constructor is only enabled if the type InputIt is not an
			// integral type. This is done to prevent the compiler from
			// confusing this constructor with the one above.
			template < class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0):
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_ptr(nullptr)
			{
				assign(first, last);
			}

			// --- Copy constructor --- //
			vector(const vector &other):
				_alloc(other._alloc),
				_size(other._size),
				_capacity(other._capacity),
				_ptr(_alloc.allocate(other._capacity))
			{
				for (size_type i = 0; i < other._size; ++i)
					_alloc.construct(_ptr + i, other._ptr[i]);
			}

			// --- Destructor --- //
			~vector(void)
			{
				clear();
				_alloc.deallocate(_ptr, _capacity);
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //
			vector	&operator=(const vector& lhs)
			{
				// Destroy the current vector
				clear();
				_alloc.deallocate(_ptr, _capacity);

				// Copy the new vector
				_alloc = lhs._alloc;
				_size = lhs._size;
				_capacity = lhs._capacity;

				// Copy the elements
				_ptr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(_ptr + i, lhs._ptr[i]);
				return (*this);
			}

			void	assign(size_type count, const value_type& value)
			{
				if (count > _capacity)
					reserve(count);
				_size = count;
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_ptr + i, value);
			}

			template < class InputIt >
			void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
			{
				typename std::iterator_traits<InputIt>::difference_type	n = std::distance(first, last);
				
				if (_size != (size_type)n)
					reserve(n);
				_size = n;
				for (size_type i = 0; first != last; ++first, ++i)
					_alloc.construct(_ptr + i, *first);
			}

			allocator_type	get_allocator(void) const
			{
				return (_alloc);
			}

			// --- Element access --- //
			reference at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector::at");
				return (_ptr[pos]);
			}

			const_reference at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector::at");
				return (_ptr[pos]);
			}

			reference	operator[](size_type pos)
			{
				return (_ptr[pos]);
			}

			const_reference	operator[](size_type pos) const
			{
				return (_ptr[pos]);
			}

			reference	front(void)
			{
				return (*_ptr);
			}

			const_reference	front(void) const
			{
				return (*_ptr);
			}

			reference	back(void)
			{
				return (*(_ptr + _size - 1));
			}

			const_reference	back(void) const
			{
				return (*(_ptr + _size - 1));
			}

			pointer	data(void)
			{
				return (_ptr);
			}

			const_pointer	data(void) const
			{
				return (_ptr);
			}

			// --- Iterators --- //
			iterator	begin(void)
			{
				return (iterator(_ptr));
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(_ptr));
			}

			iterator	end(void)
			{
				return (iterator(_ptr + _size));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(_ptr + _size));
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(_ptr + _size));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(_ptr + _size));
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(_ptr));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(_ptr));
			}

			// --- Capacity --- //
			size_type	size(void) const
			{
				return (_size);
			}

			size_type	max_size(void) const
			{
				return (_alloc.max_size());
			}

			void	reserve(size_type new_cap)
			{
				if (new_cap <= _capacity)
					return ;

				if (new_cap > max_size())
					throw std::length_error("vector::reserve");
					
				pointer	new_start = _alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(new_start + i, _ptr[i]);
					_alloc.destroy(_ptr + i);
				}
				_alloc.deallocate(_ptr, _capacity);
				_ptr = new_start;
				_capacity = new_cap;
			}

			size_type	capacity(void) const
			{
				return (_capacity);
			}

			bool	empty(void) const
			{
				return (_size == 0);
			}

			// --- Modifiers --- //
			void	clear(void)
			{
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr, _capacity);
				_size = 0;
				_ptr = nullptr;
				_capacity = 0;
			}

			void	push_back(const value_type& value)
			{
				if (_size >= _capacity)
					reallocation(_capacity + 1);
				_alloc.construct(_ptr + _size, value);
				++_size;
			}

			void	pop_back(void)
			{
				if (_size == 0)
					return ;
				_alloc.destroy(_ptr + _size - 1);
				--_size;
			}

			iterator	insert(iterator pos, const value_type& value)
			{
				difference_type	offset = pos - begin();

				move_right(pos, 1);
				_alloc.construct(_ptr + offset, value);
				return (begin() + offset);
			}

			iterator	insert(iterator pos, size_type count, const value_type& value)
			{
				difference_type	offset = pos - begin();

				move_right(pos, count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_ptr + offset + i, value);
				return (begin() + offset);
			}

			template < class InputIt >
			iterator	insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
			{
				difference_type	offset = pos - begin();
				size_type		count = std::distance(first, last);

				if (count == 0)
					return (pos);
				
				move_right(pos, count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_ptr + offset + i, *first++);
				return (begin() + offset);
			}

			iterator	erase(iterator pos)
			{
				move_left(pos, 1);
				return (pos);
			}

			iterator	erase(iterator first, iterator last)
			{
				move_left(first, last - first);
				return (first);
			}

			void	resize(size_type newSize, T value = T())
			{
				if (newSize > _size)
				{
					if (newSize > _capacity)
						reallocation(newSize);
					for (size_type i = _size; i < newSize; ++i)
						_alloc.construct(_ptr + i, value);
				}
				else
				{
					for (size_type i = newSize; i < _size; ++i)
						_alloc.destroy(_ptr + i);
				}
				_size = newSize;
			}

			void	swap(vector& other)
			{
				std::swap(_ptr, other._ptr);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
			}
	};

	template < class T, class Alloc >
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < class T, class Alloc >
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template < class T, class Alloc >
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < class T, class Alloc >
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template < class T, class Alloc >
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template < class T, class Alloc >
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template < class T, class Alloc >
	void	swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}
