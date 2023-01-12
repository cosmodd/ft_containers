#pragma once

#ifndef FT_VECTOR
# define FT_VECTOR
#endif

#include <memory>

namespace ft
{

	template <class T, class Allocator = std::allocator<T>()>
	class vector
	{

		private:

		protected:

		public:
			typedef T				value_type;
			typedef Allocator		allocator_type;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t	size_type;

			vector(void);
			vector(const Allocator &alloc);
			vector(const vector &other);
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
			template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator());

	};

}
