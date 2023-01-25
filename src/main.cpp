// #include "stack.hpp"
#include "vector.hpp"
#include "iterators.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"

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

#if defined(FT_STACK) || defined(FT_VECTOR)
static std::string	emojiBoolean(bool value, bool verbose = false)
{
	if (verbose)
		return (value ? "\e[42m ✅ Yes \e[0m" : "\e[41m ❌ No  \e[0m");
	return (value ? "✅" : "❌");
}
#endif

#ifdef FT_STACK

template <class T, class Container>
static void printStackInformation(ft::stack<T, Container> &stack)
{
	ft::stack<T, Container> copy = stack;
	int index = 0;

	std::cout << std::endl;
	std::cout << "Is empty: " << emojiBoolean(stack.empty()) << std::endl;
	std::cout << "Size: " << stack.size() << std::endl;
	std::cout << "Content: ";
	while (!copy.empty())
	{
		if (index > 0)
			std::cout << ", ";
		std::cout << copy.top();
		copy.pop();
		index++;
	}
	std::cout << std::endl;
}

template <class T, class Container>
static void printStackInformation(std::stack<T, Container> &stack)
{
	std::stack<T, Container> copy = stack;
	int index = 0;

	std::cout << std::endl;
	std::cout << "Is empty: " << emojiBoolean(stack.empty()) << std::endl;
	std::cout << "Size: " << stack.size() << std::endl;
	std::cout << "Content: ";
	while (!copy.empty())
	{
		if (index > 0)
			std::cout << ", ";
		std::cout << copy.top();
		copy.pop();
		index++;
	}
	std::cout << std::endl;
}

template <class S>
void test_stack(S &stack)
{
	S other;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
	std::chrono::duration<double, std::milli> time;

	printStackInformation(stack);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		stack.push(i);
		other.push(i);
	}
	end = std::chrono::high_resolution_clock::now();
	printStackInformation(stack);
	time = end - start;

	std::cout << "Time spent: " << time.count() << "ms" << std::endl;

	std::cout << std::endl;
	std::cout << "(stack == other) = " << emojiBoolean(stack == other, true) << std::endl;
	std::cout << "(stack != other) = " << emojiBoolean(stack != other, true) << std::endl;
	std::cout << "(stack < other) = " << emojiBoolean(stack < other, true) << std::endl;
	std::cout << "(stack <= other) = " << emojiBoolean(stack <= other, true) << std::endl;
	std::cout << "(stack > other) = " << emojiBoolean(stack > other, true) << std::endl;
	std::cout << "(stack >= other) = " << emojiBoolean(stack >= other, true) << std::endl;
}

void test_stacks()
{
	ft::stack<int> stack;
	std::stack<int> stdstack;

	std::cout << "\e[94m ft::Stack \e[0m" << std::endl;
	test_stack(stack);
	std::cout << "\e[94m std::stack \e[0m" << std::endl;
	test_stack(stdstack);
}

#endif

#ifdef FT_VECTOR

template <class Vector>
static void printVectorInformations(Vector &vec)
{
	std::cout << std::endl;
	std::cout << "Empty: " << emojiBoolean(vec.empty()) << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Content: ";
	for (int i = 0; i < vec.size(); i++)
	{
		if (i > 0)
			std::cout << ", ";
		std::cout << vec[i];
	}
	std::cout << std::endl;
}

void test_vectors()
{
	ft::vector<int> vector;
	std::vector<int> stdvector;

	std::cout << "\e[94m ft::Vector \e[0m" << std::endl;
	printVectorInformations(vector);
	std::cout << "\e[94m std::vector \e[0m" << std::endl;
	printVectorInformations(stdvector);
}

#endif

template <class T>
static void printVector(std::vector<T> vec, std::string name)
{
	if (!name.empty())
		std::cout << name << ": ";
	for (int i = 0; i < (int)vec.size(); i++)
	{
		if (i > 0)
			std::cout << ", ";
		std::cout << vec[i];
	}
	std::cout << std::endl;
}


/**
 * 🏷 ft::vector
 * 📏 Size: 0
 * 🛢 Capacity: 0
 * 📦 Content: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 */
template <class T>
static void printVector(ft::vector<T> vec, std::string name)
{
	if (!name.empty())
		std::cout << "🏷  " << name << std::endl;
	std::cout << "📏 Size: " << vec.size() << std::endl;
	std::cout << "🛢  Capacity: " << vec.capacity() << std::endl;
	std::cout << "📦 Content: ";
	for (int i = 0; i < (int)vec.size(); i++)
	{
		if (i > 0)
			std::cout << ", ";
		std::cout << vec[i];
	}
	std::cout << std::endl;
}

template < class Iterator >
static void	printRange(Iterator first, Iterator last, std::string name)
{
	if (!name.empty())
		std::cout << name << ": ";
	while (first != last)
	{
		std::cout << *first;
		if (++first != last)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

template <class T>
static void testBooleans(std::string name, T a, T b)
{
	std::cout << name << ": " << std::endl;
	std::cout << "a == b: " << emojiBoolean(a == b) << std::endl;
	std::cout << "a != b: " << emojiBoolean(a != b) << std::endl;
	std::cout << "a < b: " << emojiBoolean(a < b) << std::endl;
	std::cout << "a <= b: " << emojiBoolean(a <= b) << std::endl;
	std::cout << "a > b: " << emojiBoolean(a > b) << std::endl;
	std::cout << "a >= b: " << emojiBoolean(a >= b) << std::endl;
}

static void	testIntegrals()
{
	std::cout << std::setw(25) << "T<int> = " << emojiBoolean(ft::is_integral<int>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<char> = " << emojiBoolean(ft::is_integral<char>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<float> = " << emojiBoolean(ft::is_integral<float>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<double> = " << emojiBoolean(ft::is_integral<double>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<long> = " << emojiBoolean(ft::is_integral<long>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<long long> = " << emojiBoolean(ft::is_integral<long long>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<short> = " << emojiBoolean(ft::is_integral<short>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<unsigned int> = " << emojiBoolean(ft::is_integral<unsigned int>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<unsigned char> = " << emojiBoolean(ft::is_integral<unsigned char>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<unsigned long> = " << emojiBoolean(ft::is_integral<unsigned long>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<unsigned long long> = " << emojiBoolean(ft::is_integral<unsigned long long>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<unsigned short> = " << emojiBoolean(ft::is_integral<unsigned short>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<bool> = " << emojiBoolean(ft::is_integral<bool>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<std::string> = " << emojiBoolean(ft::is_integral<std::string>::value, true) << std::endl;
	std::cout << std::setw(25) << "T<std::vector<int>> = " << emojiBoolean(ft::is_integral<std::vector<int> >::value, true) << std::endl;
}

int main(void)
{
	static const int	size = 10;

	std::vector<int>	range;
	for (int i = 0; i < size; i++) range.push_back(i);

	ft::vector<int>			ft_vector(range.begin(), range.end());

	ft::vector<int>::const_iterator	begin = ft_vector.begin();
	ft::vector<int>::const_iterator	end = ft_vector.end();
	return (EXIT_SUCCESS);
}
