/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrattez <mrattez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:17:45 by mrattez           #+#    #+#             */
/*   Updated: 2023/01/10 16:27:54 by mrattez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

namespace ft
{

	template< class T, class Container = std::vector<T> >
	class Stack
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

			Stack(const Container& cont = Container()):
				c(cont)
			{}

			Stack(const Stack& other):					// Copy constructor
				c(other.c)
			{}

			Stack&	operator=(const Stack& other)		// Copy assignment operator
			{
				c = other.c;
			}

			bool			empty(void) const
			{
				return c.empty();
			}

			size_type		size(void) const
			{
				return c.size();
			}

			reference		top(void)
			{
				return c.back();
			}

			const_reference	top(void) const
			{
				return c.back();
			}

			void			push(const value_type& value)
			{
				c.push_back(value);
			}

			void			pop(void)
			{
				c.pop_back();
			}

			

	};

	template<class T, class Container>
	bool	operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs.c == rhs.c;
	}
	template<class T, class Container>
	bool	operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);

	template<class T, class Container>
	bool	operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
	template<class T, class Container>
	bool	operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);

	template<class T, class Container>
	bool	operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
	template<class T, class Container>
	bool	operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);

}
