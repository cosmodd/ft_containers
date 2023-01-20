// #include "stack.hpp"
// #include "vector.hpp"
#include "iterators.hpp"

#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <chrono>

// static std::string	emojiBoolean(bool value, bool verbose = false)
// {
// 	if (verbose)
// 		return (value ? "✅ Yes" : "❌ No");
// 	return (value ? "✅" : "❌");
// }

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
		if (index > 0)
			std::cout << ", ";
		std::cout << copy.top();
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

int main(void)
{
	std::vector<int>	list;
	std::vector<int>	list2;

	for (int i = 0; i < 5; i++)
	{
		list.push_back(i);
		list2.push_back(i);
	}

	printVector(list, " ft");
	printVector(list2, "std");

	ft::reverse_iterator<std::vector<int>::iterator>	begin(list.end());
	ft::reverse_iterator<std::vector<int>::iterator>	end(list.begin());

	std::reverse(begin, end);

	printVector(list, " ft");
	printVector(list2, "std");

	return (EXIT_SUCCESS);
}
