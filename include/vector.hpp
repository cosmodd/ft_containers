#pragma once

#ifndef FT_VECTOR
# define FT_VECTOR
#endif

#include <memory>
#include <cmath>

#include "iterators.hpp"
#include "vector_iterator.hpp"

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
			typedef vector_iterator<T>						iterator;
			typedef vector_iterator<const T>				const_iterator;
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
			void	_reallocate(size_type new_capacity)
			{
				pointer	prev_start = _start;

				_start = _alloc.allocate(new_capacity);
				if (prev_start != nullptr)
				{
					for (int i = 0; i < new_capacity && i < _size; i++)
						_start[i] = prev_start[i];
					_alloc.deallocate(prev_start, _capacity);
				}

				_capacity = new_capacity;
				_size = std::min(_size, _capacity);
			}

			void	_update_pointers(void)
			{
				_end = _start + _size;
				_end_of_storage = _start + _capacity;
			}

		public:
			// -------------------------------------------------------------- //
			//  Constructors/Destructors + copying                            //
			// -------------------------------------------------------------- //
			vector(void):
				_alloc(Allocator()),
				_size(0),
				_capacity(0),
				_start(nullptr),
				_end(nullptr),
				_end_of_storage(nullptr)
			{}

			explicit vector(const allocator_type &alloc):
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_start(nullptr),
				_end(nullptr),
				_end_of_storage(nullptr)
			{}

			explicit vector( size_type count, const value_type& value = T(), const allocator_type& alloc = Allocator() ):
				_alloc(alloc),
				_size(count),
				_capacity(count),
				_start(_alloc.allocate(count)),
				_end(_start + count),
				_end_of_storage(_start + count)
			{
				assign(count, value);
			}

			template < class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = Allocator()):
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
				// TODO: implement
				return (*this);
			}

			void	assign( size_type count, const T& value )
			{
				_reallocate(count * 2);
				_size = count;
				_update_pointers();
				for (int i = 0; i < count; i++)
					_start[i] = value;
			}

			template < class InputIt >
			void	assign( InputIt first, InputIt last )
			{
				_reallocate((last - first) * 2);
				_size = last - first;
				_update_pointers();
				for (int i = 0; i < _size; i++)
					_start[i] = first[i];
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
				// TODO: implement
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
				_update_pointers();
			}
	};

}
