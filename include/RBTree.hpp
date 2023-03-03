#pragma once

#include <ostream>
#include <iomanip>
#include <functional>
#include <memory>
#include <queue>

namespace ft
{

	/**
	 * Red-Black Tree properties:
	 * 1. Every node is colored either red or black.
	 * 2. The root is black.
	 * 3. Every leaf (nullptr) is black.
	 * 4. If a node is red, then both its children are black.
	 * 5. All paths to a leaf contain the same number of black nodes.
	 */
	template <
		typename T,
		typename Compare = std::less<T>,
		typename Allocator = std::allocator<T> >
	class RBTree
	{
		public:
			// -------------------------------------------------------------- //
			//  Member types                                                  //
			// -------------------------------------------------------------- //
			typedef T			value_type;
			typedef Compare		key_compare;
			typedef Allocator	allocator_type;

			typedef T&			reference;
			typedef const T&	const_reference;
			typedef T*			pointer;
			typedef const T*	const_pointer;

			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t		size_type;

			struct Node
			{
				enum Color
				{
					RED,
					BLACK
				};

				value_type	data;
				Color		color;
				Node		*parent;
				Node		*left;
				Node		*right;

				Node(const_reference data):
					data(data),
					color(RED),
					parent(nullptr),
					left(nullptr),
					right(nullptr)
				{}
			};

			// --- Node types --- //
			typedef Node*		node_pointer;
			typedef const Node*	const_node_pointer;

			typedef Node&		node_reference;
			typedef const Node&	const_node_reference;

			// -------------------------------------------------------------- //
			//  Iterators                                                     //
			// -------------------------------------------------------------- //
			typedef RBTree_iterator<RBTree<T, Compare, Allocator> >			iterator;
			typedef RBTree_iterator<const RBTree<T, Compare, Allocator> >	const_iterator;

			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		private:
			node_pointer	newNode(const_reference data)
			{
				node_pointer	node = _nodeAllocator.allocate(1);

				_nodeAllocator.construct(node, data);
				return node;
			}

			void	deleteNode(node_pointer *node)
			{
				if (node == nullptr || *node == nullptr)
					return ;

				replaceChildParent((*node)->parent, *node, nullptr);
				_nodeAllocator.destroy(*node);
				_nodeAllocator.deallocate(*node, 1);
				*node = nullptr;
			}

			void	deleteTree(node_pointer node)
			{
				if (node == nullptr)
					return ;

				deleteTree(node->left);
				deleteTree(node->right);
				deleteNode(&node);
			}

			bool	isBlack(node_pointer node)
			{
				return (node == nullptr || node->color == Node::BLACK);
			}

			void replaceChildParent(node_pointer parent, node_pointer oldChild, node_pointer newChild)
			{
				if (parent == nullptr)
					_root = newChild;

				else if (parent->left == oldChild)
					parent->left = newChild;

				else if (parent->right == oldChild)
					parent->right = newChild;

				if (newChild != nullptr)
					newChild->parent = parent;
			}

			node_pointer	deleteWithZeroOrOneChild(node_pointer node, node_pointer *movedParentNode)
			{
				node_pointer	moved = nullptr;

				if (node == nullptr)
					return nullptr;

				if (node->left != nullptr)
				{
					*movedParentNode = node->parent;
					replaceChildParent(node->parent, node, node->left);
					moved = node->left;
				}
				else if (node->right != nullptr)
				{
					*movedParentNode = node->parent;
					replaceChildParent(node->parent, node, node->right);
					moved = node->right;
				}
				else
				{
					*movedParentNode = node->parent;
					replaceChildParent(node->parent, node, nullptr);
					moved = nullptr;
				}

				deleteNode(&node);
				return moved;
			}

			/**
			 * Rotation exemple:
			 *       │               │
			 *       R               L
			 *     ┌─┴─┐           ┌─┴─┐
			 *     L   0    <=>    2   R
			 *   ┌─┴─┐               ┌─┴─┐
			 *   2   1               1   0
			 *
			 */
			void rightRotation(node_pointer node)
			{
				node_pointer	parent = node->parent;
				node_pointer	leftChild = node->left;

				if (leftChild == nullptr)
					return ;

				node->left = leftChild->right;
				if (node->left != nullptr)
					node->left->parent = node;

				leftChild->right = node;
				node->parent = leftChild;

				replaceChildParent(parent, node, leftChild);
			}

			/**
			 * Rotation exemple:
			 *       │               │
			 *       R               L
			 *     ┌─┴─┐           ┌─┴─┐
			 *     L   0    <=>    2   R
			 *   ┌─┴─┐               ┌─┴─┐
			 *   2   1               1   0
			 *
			 */
			void leftRotation(node_pointer node)
			{
				node_pointer	parent = node->parent;
				node_pointer	rightChild = node->right;

				if (rightChild == nullptr)
					return ;

				node->right = rightChild->left;
				if (node->right != nullptr)
					node->right->parent = node;

				rightChild->left = node;
				node->parent = rightChild;

				replaceChildParent(parent, node, rightChild);
			}

			void	fixTreeInsertion(node_pointer node)
			{
				node_pointer	parent = node->parent;
				node_pointer	uncle = nullptr;
				node_pointer	grandParent = nullptr;

				// If node is the root
				if (parent == nullptr)
				{
					node->color = Node::BLACK;
					return ;
				}

				// If node's parent is black
				if (parent->color == Node::BLACK)
					return ;

				// Node's parent is red for sure

				grandParent = parent->parent;
				uncle = (grandParent->left == parent) ? grandParent->right : grandParent->left;

				// If node's uncle is red
				if (!isBlack(uncle))
				{
					parent->color = Node::BLACK;
					uncle->color = Node::BLACK;
					grandParent->color = Node::RED;
					fixTreeInsertion(grandParent);
					return ;
				}

				// If node's uncle is black
				if (grandParent->left == parent)
				{
					if (parent->right == node)
					{
						leftRotation(parent);
						node = parent;
						parent = node->parent;
					}
					rightRotation(grandParent);
				}
				else
				{
					if (parent->left == node)
					{
						rightRotation(parent);
						node = parent;
						parent = node->parent;
					}
					leftRotation(grandParent);
				}

				parent->color = Node::BLACK;
				grandParent->color = Node::RED;
			}

			void	fixTreeDeletion(node_pointer moveNode, node_pointer parent)
			{
				node_pointer	sibling = nullptr;

				// If node is the root
				if (parent == nullptr)
				{
					if (moveNode != nullptr)
						moveNode->color = Node::BLACK;
					return ;
				}

				sibling = (parent->left == moveNode) ? parent->right : parent->left;

				// If node's sibling is red
				if (sibling->color == Node::RED)
				{
					// Recoloring
					sibling->color = Node::BLACK;
					parent->color = Node::RED;

					// Rotation
					if (parent->left == moveNode)
						leftRotation(parent);
					else
						rightRotation(parent);

					// Update sibling
					sibling = (parent->left == moveNode) ? parent->right : parent->left;
				}

				// If node's sibling is black
				if (isBlack(sibling->left) && isBlack(sibling->right))
				{
					// Recoloring
					sibling->color = Node::RED;

					// If parent is red
					if (parent->color == Node::RED)
					{
						parent->color = Node::BLACK;
						return ;
					}

					// If parent is black
					fixTreeDeletion(parent, parent->parent);
					return ;
				}

				bool	isLeft = (parent->left == moveNode);

				// If node's sibling is black and has a red child
				if (isLeft && isBlack(sibling->right))
				{
					// Recoloring
					sibling->color = Node::RED;
					sibling->left->color = Node::BLACK;

					// Rotation
					rightRotation(sibling);

					// Update sibling
					sibling = parent->right;
				}
				else if (!isLeft && isBlack(sibling->left))
				{
					// Recoloring
					sibling->color = Node::RED;
					sibling->right->color = Node::BLACK;

					// Rotation
					leftRotation(sibling);

					// Update sibling
					sibling = parent->left;
				}

				// Recoloring
				sibling->color = parent->color;
				parent->color = Node::BLACK;

				// Rotation
				if (isLeft)
				{
					sibling->right->color = Node::BLACK;
					leftRotation(parent);
				}
				else
				{
					sibling->left->color = Node::BLACK;
					rightRotation(parent);
				}
			}

		private:
			node_pointer					_root;
			key_compare				_comparator;
			allocator_type			_allocator;
			std::allocator<Node>	_nodeAllocator;

		public:
			// -------------------------------------------------------------- //
			//  Constructors                                                  //
			// -------------------------------------------------------------- //

			RBTree() : _root(nullptr) {}

			RBTree(const RBTree &other)
			{
				(void)(other);
				// TODO: implement copy constructor
			}

			RBTree &operator=(const RBTree &other)
			{
				(void)(other);
				// TODO: implement copy assignment operator
				return *this;
			}

			~RBTree()
			{
				deleteTree(_root);
			}

			// -------------------------------------------------------------- //
			//  Member functions                                              //
			// -------------------------------------------------------------- //)
			node_pointer search(const_reference data) const
			{
				node_pointer current = _root;

				while (current != nullptr)
				{
					if (data == current->data)
						return current;
					else if (_comparator(data, current->data))
						current = current->left;
					else
						current = current->right;
				}

				return nullptr;
			}

			void	insert(const_reference data)
			{
				node_pointer	current = _root;
				node_pointer	parent = nullptr;
				node_pointer	node = newNode(data);

				// If the tree is empty, the new node is the root
				if (current == nullptr)
				{
					_root = node;
					node->color = Node::BLACK;
					return ;
				}

				// Find the right place to insert the new node
				while (current != nullptr)
				{
					parent = current;
					if (_comparator(data, current->data))
						current = current->left;
					else
						current = current->right;
				}

				// Insert the new node
				if (_comparator(data, parent->data))
					parent->left = node;
				else
					parent->right = node;

				node->parent = parent;

				// Fix the tree
				fixTreeInsertion(node);
			}

			void	remove(const_reference data)
			{
				node_pointer			node = search(data);
				node_pointer			movedNode = nullptr;
				node_pointer			movedParentNode = nullptr;
				typename Node::Color	deletedColor = Node::RED;
				// bool					hadNoChild = false;

				if (node == nullptr)
					return ;

				// If node has no or one children
				if (node->left == nullptr || node->right == nullptr)
				{
					// hadNoChild = (node->left == nullptr && node->right == nullptr);
					deletedColor = node->color;
					movedNode = deleteWithZeroOrOneChild(node, &movedParentNode);
				}
				else
				{
					node_pointer	successor = node->right;

					// Find the successor
					while (successor->left != nullptr)
						successor = successor->left;

					// Swap the data
					node->data = successor->data;

					// hadNoChild = (successor->left == nullptr && successor->right == nullptr);

					// Delete the successor
					deletedColor = successor->color;
					movedNode = deleteWithZeroOrOneChild(successor, &movedParentNode);
				}

				// If the deleted node was black, fix the tree
				if (deletedColor == Node::BLACK)
					fixTreeDeletion(movedNode, movedParentNode);
			}

			node_pointer getRoot() const
			{
				return _root;
			}

			// -------------------------------------------------------------- //
			//  Iterators                                                     //
			// -------------------------------------------------------------- //
			iterator	begin()
			{
				node_pointer	current = _root;

				if (current == nullptr)
					return iterator(nullptr);

				while (current->left != nullptr)
					current = current->left;

				return iterator(current);
			}

			iterator	end()
			{
				/* FIXME: Need to implement a way to keep track of the
				 * nullptr node after the last node. This is needed for the
				 * reverse iterator to work properly.
				 * For now, we return an iterator pointing to nullptr (leaf node)
				 */
				return iterator(nullptr);
			}

	};

	template< class Node >
	void	printNode(std::ostream &os, const Node *node)
	{
		if (node == nullptr)
			return;

		if (node->color == Node::RED)
			os << "\e[41m";
		else
			os << "\e[40m";
		os << " " << node->data << " \e[0m";
	}

	template< class Node >
	void	printRBTree(std::ostream &os, const Node *node, bool isRight, std::string indent)
	{
		if (node != nullptr)
		{
			os << indent;
			os << (isRight && node->parent->left != nullptr ? "├──" : "└──" );
			printNode(os, node);
			os << std::endl;

			indent += (isRight ? "│   " : "    ");

			printRBTree(os, node->right, true, indent);
			printRBTree(os, node->left, false, indent);
		}
	}

}
