#pragma once

#ifndef FT_VECTOR
# define FT_VECTOR
#endif

#include <memory>
#include <cmath>

#include "iterators.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

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
			Allocator		_alloc;				// Allocator object
			size_type		_size;				// end - start
			size_type		_capacity;			// end_of_storage - start

			// --- Pointers of the storage --- //
			pointer			_start;				// Pointer to the first element
			pointer			_end;				// Pointer to the last element + 1
			pointer			_end_of_storage;	// Pointer to the end of the storage + 1

			// -------------------------------------------------------------- //
			//  Private member functions                                      //
			// -------------------------------------------------------------- //

		public:
			// -------------------------------------------------------------- //
			//  Constructors/Destructors + copying                            //
			// -------------------------------------------------------------- //
			// --- Default constructor --- //
			vector(void):
				_alloc(Allocator()),
				_size(0),
				_capacity(0),
				_start(nullptr),
				_end(nullptr),
				_end_of_storage(nullptr)
			{}

			// --- Constructor with allocator --- //
			explicit vector(const allocator_type &alloc):
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_start(nullptr),
				_end(nullptr),
				_end_of_storage(nullptr)
			{}

			// --- Constructor with count and value --- //
			explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = Allocator() ):
				_alloc(alloc),
				_size(count),
				_capacity(count * 2),
				_start(_alloc.allocate(count * 2)),
				_end(_start + count),
				_end_of_storage(_start + _capacity)
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
				_start(nullptr),
				_end(nullptr),
				_end_of_storage(nullptr)
			{
				assign(first, last);
			}

			// --- Copy constructor and assignment operator --- //
			vector(const vector &other):
				_alloc(other._alloc),
				_size(other._size),
				_capacity(other._capacity),
				_start(_alloc.allocate(other._capacity)),
				_end(_start + other._size),
				_end_of_storage(_start + other._capacity)
			{
				for (size_type i = 0; i < other._size; ++i)
					_alloc.construct(_start + i, other._start[i]);
			}

			// --- Destructor --- //
			~vector(void)
			{
				clear();
				_alloc.deallocate(_start, _capacity);
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //
			vector	&operator=(const vector& lhs)
			{
				(void) lhs;
				return (*this);
			}

			void	assign( size_type count, const value_type& value )
			{
				reserve(count * 2);
				_size = count;
				_end = _start + _size;
				for (int i = 0; i < count; i++)
					_alloc.construct(_start + i, value);
			}

			template < class InputIt >
			void	assign( InputIt first, InputIt last )
			{
				reserve((last - first) * 2);
				_size = last - first;
				_end = _start + _size;
				for (int i = 0; first != last; ++first, ++i)
					_alloc.construct(_start + i, *first);
			}

			// --- Element access --- //
			reference	operator[](size_type pos)
			{
				return (_start[pos]);
			}

			const_reference	operator[](size_type pos) const
			{
				return (_start[pos]);
			}

			// --- Iterators --- //
			iterator	begin(void)
			{
				return (iterator(_start));
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(_start));
			}

			iterator	end(void)
			{
				return (iterator(_end));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(_end));
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(_end));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(_end));
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(_start));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(_start));
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

				pointer	new_start = _alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(new_start + i, _start[i]);
					_alloc.destroy(_start + i);
				}
				_alloc.deallocate(_start, _capacity);
				_start = new_start;
				_capacity = new_cap;
				_end_of_storage = _start + _capacity;
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
					_alloc.destroy(_start + i);
				_size = 0;
				_end = _start;
			}
	};

}
