#pragma once

#include <functional>

#include "RBTree.hpp"
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
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			// --- Value compare --- //
			struct value_compare
			{
				// Needed for accessing private members of map
				friend class map;

				protected:
					Compare	_comp;

				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					value_compare(Compare c): _comp(c) {}
					value_compare(const value_compare& x): _comp(x._comp) {}

					bool operator()(const value_type& x, const value_type& y) const
					{
						return _comp(x.first, y.first);
					}
			};

		private:
			typedef ft::RBTree<value_type, value_compare, allocator_type>	tree_type;

		public:
			// --- Iterator types --- //
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		private:
			// -------------------------------------------------------------- //
			//  Data members                                                  //
			// -------------------------------------------------------------- //
			tree_type		_tree;
			allocator_type	_alloc;
			key_compare		_comp;

			// -------------------------------------------------------------- //
			//  Private member functions                                      //
			// -------------------------------------------------------------- //
			value_type*	_findPair(const key_type& key)
			{
				typename tree_type::node_pointer	node = _tree.getRoot();

				while (node)
				{
					if (key == node->data.first)
						return &node->data;
					else if (_comp(key, node->data.first))
						node = node->left;
					else
						node = node->right;
				}
				return nullptr;
			}

			const value_type*	_findPair(const key_type& key) const
			{
				typename tree_type::const_node_pointer	node = _tree.getRoot();

				while (node)
				{
					if (key == node->data.first)
						return &node->data;
					else if (_comp(key, node->data.first))
						node = node->left;
					else
						node = node->right;
				}
				return nullptr;
			}

		public:
			// -------------------------------------------------------------- //
			//  Constructors                                                  //
			// -------------------------------------------------------------- //
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc),
				_alloc(alloc),
				_comp(comp)
			{}

			template <class InputIterator>
			map(
				InputIterator first,
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
			):
				_tree(comp, alloc),
				_alloc(alloc),
				_comp(comp)
			{
				_tree.insert(first, last);
			}

			map(const map& x):
				_tree(x._tree),
				_alloc(x._alloc),
				_comp(x._comp)
			{}

			map& operator=(const map& x)
			{
				_tree = x._tree;
				_alloc = x._alloc;
				_comp = x._comp;
				return *this;
			}

			// --- Destructor --- //
			~map()
			{}

			allocator_type	get_allocator() const
			{
				return _alloc;
			}

			// -------------------------------------------------------------- //
			//  Iterators                                                     //
			// -------------------------------------------------------------- //
			iterator begin()
			{
				return _tree.begin();
			}

			const_iterator begin() const
			{
				return _tree.begin();
			}

			iterator end()
			{
				return _tree.end();
			}

			const_iterator end() const
			{
				return _tree.end();
			}

			reverse_iterator rbegin()
			{
				return _tree.rbegin();
			}

			const_reverse_iterator rbegin() const
			{
				return _tree.rbegin();
			}

			reverse_iterator rend()
			{
				return _tree.rend();
			}

			const_reverse_iterator rend() const
			{
				return _tree.rend();
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //
			// --- Accessors --- //
			mapped_type& operator[](const key_type& key)
			{
				value_type*	pair = _findPair(key);

				if (pair == nullptr)
					pair = &(*_tree.insert(ft::make_pair(key, mapped_type())).first);
				return pair->second;
			}

			const mapped_type& operator[](const key_type& key) const
			{
				value_type*	pair = _findPair(key);

				if (pair == nullptr)
					pair = &(*_tree.insert(ft::make_pair(key, mapped_type())).first);
				return pair->second;
			}

			mapped_type&	at(const key_type& key)
			{
				value_type*	pair = _findPair(key);

				if (pair == nullptr)
					throw std::out_of_range("map::at");
				return pair->second;
			}

			const mapped_type&	at(const key_type& key) const
			{
				value_type*	pair = _findPair(key);

				if (pair == nullptr)
					throw std::out_of_range("map::at");
				return pair->second;
			}

			// --- Capacity --- //
			bool empty() const
			{
				return _tree.getRoot() == nullptr;
			}

			size_type size() const
			{
				return _tree.size();
			}

			size_type max_size() const
			{
				return _alloc.max_size();
			}

			// --- Modifiers --- //
			void	clear(void)
			{
				_tree.clear();
			}

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				return _tree.insert(val);
			}

	};

}
