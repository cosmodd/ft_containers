#pragma once

#include <iostream>

namespace ft
{

	template <class Tree>
	class RBTree_iterator: public std::iterator<std::bidirectional_iterator_tag, typename Tree::value_type>
	{
		private:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //
			typedef typename std::iterator<std::bidirectional_iterator_tag, typename Tree::value_type>	iterator_type;

			typedef typename Tree::node_pointer					node_pointer;
			typedef typename Tree::const_node_pointer			const_node_pointer;

		public:
			typedef typename iterator_type::difference_type		difference_type;
			typedef typename iterator_type::value_type			value_type;
			typedef typename iterator_type::pointer				pointer;
			typedef typename iterator_type::reference			reference;
			typedef typename iterator_type::iterator_category	iterator_category;

		private:
			node_pointer	_ptr;

		public:
			// -------------------------------------------------------------- //
			//  Constructors/Destructors + assignment                         //
			// -------------------------------------------------------------- //
			RBTree_iterator(): _ptr(nullptr) {}

			RBTree_iterator(node_pointer node): _ptr(node) {}

			RBTree_iterator(const_node_pointer node): _ptr(const_cast<node_pointer>(node)) {}

			RBTree_iterator(const RBTree_iterator &other): _ptr(other._ptr) {}

			~RBTree_iterator() {}

			RBTree_iterator	&operator=(const RBTree_iterator &other)
			{
				_ptr = other._ptr;
				return *this;
			}

			// -------------------------------------------------------------- //
			//  Operators                                                     //
			// -------------------------------------------------------------- //
			// --- Accessors --- //
			// *it
			reference	operator*()
			{
				return _ptr->data;
			}

			const reference	operator*() const
			{
				return _ptr->data;
			}

			// it->member
			pointer		operator->()
			{
				return &(_ptr->data);
			}

			const pointer	operator->() const
			{
				return &(_ptr->data);
			}

			// --- Arithmetic --- //
			// ++it
			RBTree_iterator	&operator++()
			{
				if (_ptr == nullptr)
					return *this;
				if (_ptr->right != nullptr)
				{
					_ptr = _ptr->right;
					while (_ptr->left != nullptr)
						_ptr = _ptr->left;
				}
				else
				{
					node_pointer	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr != nullptr && tmp == _ptr->right)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
					}
				}
				return *this;
			}

			// it++
			RBTree_iterator	operator++(int)
			{
				RBTree_iterator tmp(*this);
				operator++();
				return tmp;
			}

			// --it
			RBTree_iterator	operator--()
			{
				if (_ptr == nullptr)
					return *this;
				if (_ptr->left != nullptr)
				{
					_ptr = _ptr->left;
					while (_ptr->right != nullptr)
						_ptr = _ptr->right;
				}
				else
				{
					node_pointer	tmp = _ptr;
					_ptr = _ptr->parent;
					while (_ptr != nullptr && tmp == _ptr->left)
					{
						tmp = _ptr;
						_ptr = _ptr->parent;
					}
				}
				return *this;
			}

			// it--
			RBTree_iterator	operator--(int)
			{
				RBTree_iterator tmp(*this);
				operator--();
				return tmp;
			}

			// --- Comparison --- //
			bool operator==(const RBTree_iterator &other) const // it == other
			{
				return (_ptr == other._ptr);
			}

			bool operator!=(const RBTree_iterator &other) const // it != other
			{
				return (_ptr != other._ptr);
			}

			template <class LeftTree, class RightTree>
			friend bool operator==(const RBTree_iterator<LeftTree> &left, const RBTree_iterator<RightTree> &right);

			template <class LeftTree, class RightTree>
			friend bool operator!=(const RBTree_iterator<LeftTree> &left, const RBTree_iterator<RightTree> &right);
	};

	template <class LeftTree, class RightTree>
	bool operator==(const RBTree_iterator<LeftTree> &left, const RBTree_iterator<RightTree> &right)
	{
		return (left._ptr == right._ptr);
	}

	template <class LeftTree, class RightTree>
	bool operator!=(const RBTree_iterator<LeftTree> &left, const RBTree_iterator<RightTree> &right)
	{
		return (left._ptr != right._ptr);
	}

}
