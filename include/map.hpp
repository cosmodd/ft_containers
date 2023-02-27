#pragma once

#include <functional>
#include "utility.hpp"

namespace ft
{

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
		public:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef ft::pair<const Key, T>				value_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;

			// --- Iterator types --- //
			// typedef <ITERATOR>				iterator;
			// typedef <CONST_ITERATOR>			const_iterator;
			// typedef <REVERSE_ITERATOR>		reverse_iterator;
			// typedef <CONST_REVERSE_ITERATOR>	const_reverse_iterator;

		private:

		protected:

		public:
			// -------------------------------------------------------------- //
			//  Constructors                                                  //
			// -------------------------------------------------------------- //

	};

}