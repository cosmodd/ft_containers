#include "stack.hpp"
#include "vector.hpp"
#include "utility.hpp"
#include "RBTree.hpp"
#include "RBTree_iterator.hpp"

#include <iostream>
#include <iomanip>
#include <list>
#include <stack>
#include <vector>
#include <chrono>
#include <string>
#include <typeinfo>

// -------------------------------------------------------------------------- //
//  Structs                                                                   //
// -------------------------------------------------------------------------- //
template <class T>
struct test_integral
{
	typedef typename std::is_integral<T>::type stdi;
	typedef typename ft::is_integral<T>::type fti;

	static const bool value = stdi::value == fti::value;
	operator bool() const { return value; }
};

// -------------------------------------------------------------------------- //
//  Functions                                                                 //
// -------------------------------------------------------------------------- //

static std::string emojiBoolean(bool b, bool verbose = false)
{
	if (verbose)
		return b ? "✅ Yes" : "❌ No";
	return b ? "✅" : "❌";
}

template <class Vector>
static void printVector(Vector const &vec, std::string name = "", bool print_content = true)
{
	std::cout << std::endl;
	if (!name.empty())
		std::cout << "🏷  " << name << std::endl;
	std::cout << "📏 Size: " << vec.size() << std::endl;
	std::cout << "🛢  Capacity: " << vec.capacity() << std::endl;

	if (print_content)
	{
		std::cout << "📦 Content: ";

		typename Vector::const_iterator it = vec.begin();
		typename Vector::const_iterator ite = vec.end();

		for (; it != ite; ++it)
		{
			if (it != vec.begin())
				std::cout << ", ";
			std::cout << *it;
		}

		std::cout << std::endl;
	}
}

template <class Iterator>
static void printRange(Iterator first, Iterator last, std::string name)
{
	if (!name.empty())
		std::cout << name << "[" << last - first << "]: ";
	while (first != last)
	{
		std::cout << *first;
		if (++first != last)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

template <class T>
static void testComparisons(std::string name, T a, T b)
{
	std::cout << name << ": " << std::endl;
	std::cout << "a == b: " << emojiBoolean(a == b) << std::endl;
	std::cout << "a != b: " << emojiBoolean(a != b) << std::endl;
	std::cout << "a < b: " << emojiBoolean(a < b) << std::endl;
	std::cout << "a <= b: " << emojiBoolean(a <= b) << std::endl;
	std::cout << "a > b: " << emojiBoolean(a > b) << std::endl;
	std::cout << "a >= b: " << emojiBoolean(a >= b) << std::endl;
}

template <class T>
static void printIntegral(const std::string name)
{
	std::cout << " " << std::left
			  << std::setw(30) << name << " ⎮ "
			  << std::setw(28) << emojiBoolean(std::is_integral<T>::value, true) << " ⎮ "
			  << std::setw(28) << emojiBoolean(ft::is_integral<T>::value, true) << std::endl;
}

// Displays a boolean as a green checkmark or a red cross
// deopending on the value of the boolean of
// std::is_integral<T>::value and ft::is_integral<T>::value
static void testIntegrals()
{
	std::cout << "\e[47m " << std::left
			  << std::setw(30) << "TYPE"
			  << " ⎮ "
			  << std::setw(18) << "std::is_integral"
			  << " ⎮ "
			  << std::setw(18) << "ft::is_integral"
			  << " \e[0m" << std::endl;

	printIntegral<bool>("bool");
	printIntegral<char>("char");
	printIntegral<signed char>("signed char");
	printIntegral<unsigned char>("unsigned char");
	printIntegral<wchar_t>("wchar_t");
	printIntegral<short>("short");
	printIntegral<unsigned short>("unsigned short");
	printIntegral<int>("int");
	printIntegral<unsigned int>("unsigned int");
	printIntegral<long>("long");
	printIntegral<unsigned long>("unsigned long");
	printIntegral<long long>("long long");
	printIntegral<unsigned long long>("unsigned long long");
	printIntegral<float>("float");
	printIntegral<double>("double");
	printIntegral<long double>("long double");
	printIntegral<std::string>("std::string");
	printIntegral<std::vector<int> >("std::vector<int>");
}

static uint64_t timer(void)
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static void printExecutionTime(uint64_t start, uint64_t end)
{
	std::cout << "Execution time: " << end - start << " ms" << std::endl;
}

static void printDiff(std::vector<int> const &v1, std::vector<int> const &v2)
{
	// Prints the two vectors side by side and highlights the differences
	std::string s1 = "ft::vector = {";
	std::string s2 = "std::vector = {";

	for (size_t i = 0; i < v1.size(); ++i)
	{
		if (v1[i] != v2[i])
		{
			s1 += "\e[41m";
			s2 += "\e[41m";
		}
		s1 += std::to_string(v1[i]);
		s2 += std::to_string(v2[i]);
		if (v1[i] != v2[i])
		{
			s1 += "\e[0m";
			s2 += "\e[0m";
		}
		if (i != v1.size() - 1)
		{
			s1 += ", ";
			s2 += ", ";
		}
	}

	s1 += "}";
	s2 += "}";

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
}

int main(void)
{
	typedef ft::RBTree<int>	Container;

	// --- Containers --- //
	Container								tree;

	// --- Nodes --- //
	Container::node_pointer					leftMost;
	Container::node_pointer					rightMost;

	// --- Iterators --- //
	ft::RBTree_iterator<Container>			it;
	const ft::RBTree_iterator<Container>	ite; // Iterator pointing to NULL

	ft::reverse_iterator<ft::RBTree_iterator<Container> > rit;
	ft::reverse_iterator<ft::RBTree_iterator<Container> > rite;

	// --- Tests --- //
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	leftMost = tree.getRoot();
	while (leftMost->left)
		leftMost = leftMost->left;

	rightMost = tree.getRoot();
	while (rightMost->right)
		rightMost = rightMost->right;

	// --- In-order traversal --- //
	std::cout << "\e[100;37m In-order traversal \e[0m" << std::endl;
	it = leftMost;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	// --- Reverse in-order traversal --- //
	std::cout << "\e[100;37m Reverse in-order traversal \e[0m" << std::endl;
	it = rightMost;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		--it;
	}

	// --- Reverse iterator --- //
	std::cout << "\e[100;37m Reverse iterator \e[0m" << std::endl;
	rit = ft::reverse_iterator<ft::RBTree_iterator<Container> >(rightMost);
	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		++rit;
	}

	return (EXIT_SUCCESS);
}
