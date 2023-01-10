#include "Stack.hpp"
#include <iostream>
#include <list>

template <class T, class Container>
static void	printStackInformation(ft::Stack<T, Container> &stack)
{
	ft::Stack<T, Container>	copy = stack;
	int						index = 0;

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

static std::string	emojiBoolean(bool value, bool verbose = false)
{
	if (verbose)
		return (value ? "✅ Yes" : "❌ No");
	return (value ? "✅" : "❌");
}

int	main(void)
{
	ft::Stack<int>	stack;
	ft::Stack<int>	other;

	printStackInformation(stack);
	printStackInformation(other);
	for (int i = 0; i < 10; i++)
	{
		stack.push(i);
		other.push(i);
	}
	printStackInformation(stack);
	printStackInformation(other);

	std::cout << "(stack == other) = " << emojiBoolean(stack == other, true) << std::endl;

	return (EXIT_SUCCESS);
}
