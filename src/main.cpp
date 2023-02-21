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

std::vector<int>	g_range;

template <class Vector>
static std::vector<int> testVector(uint64_t &start, uint64_t &end, bool ft = false)
{
	std::vector<int>	results;
	Vector				vector;
	Vector				temp;

	start = timer();

	std::cout << "\n\e[47m " << (ft ? "ft::" : "std::") << "vector \e[0m\n"
			  << std::endl;

	temp.assign(26, 1);
	vector.assign(42, 1);
	vector.insert(vector.end() - 10, temp.begin(), temp.end());
	results.push_back(vector[3]);
	results.push_back(vector.size());
	results.push_back(vector.capacity());

	if (ft)
	{
		ft::vector<double>		ft_vector;
		ft::vector<int>			ft_vector2;

		ft_vector.assign(42, 1);
		try
		{
			ft_vector2.insert(ft_vector2.begin(), ft_vector.begin(), ft_vector.end());
		}
		catch (...) {
			results.push_back(ft_vector2.size());
			results.push_back(ft_vector2.capacity());
		}
	}

	end = timer();
	std::cout << std::endl;
	printExecutionTime(start, end);

	return (results);
}

int main(void)
{
	(void)testIntegrals;

	for (int i = 0; i < 100; ++i)
		g_range.push_back(i);

	uint64_t start;
	uint64_t end;

	std::vector<int> results[2];

	results[0] = testVector<ft::vector<int> >(start, end, true);
	results[1] = testVector<std::vector<int> >(start, end, false);

	std::cout << "\n\e[47m Other tests \e[0m\n"
			  << std::endl;

	std::cout << "ft_vec == std_vec: " << emojiBoolean(results[0] == results[1]) << std::endl;
	printDiff(results[0], results[1]);

	return (EXIT_SUCCESS);
}
