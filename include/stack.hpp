#pragma once

#include "vector.hpp"

namespace ft
{

	template< class T, class Container = ft::vector<T> >
	class stack
	{
		private:

		protected:
			Container	c;

		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::size_type		size_type;

			friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c == rhs.c; }

			friend bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c != rhs.c; }

			friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c < rhs.c; }

			friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c <= rhs.c; }

			friend bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c > rhs.c; }

			friend bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{ return lhs.c >= rhs.c; }

			stack(const Container& cont = Container()):
				c(cont)
			{}

			stack(const stack& other):					// Copy constructor
				c(other.c)
			{}

			stack&	operator=(const stack& other)		// Copy assignment operator
			{ c = other.c; }

			bool			empty(void) const
			{ return c.empty(); }

			size_type		size(void) const
			{ return c.size(); }

			reference		top(void)
			{ return c.back(); }

			const_reference	top(void) const
			{ return c.back(); }

			void			push(const value_type& value)
			{ c.push_back(value); }

			void			pop(void)
			{ c.pop_back(); }

	};

}
