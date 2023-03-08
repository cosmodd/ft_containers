#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "utility.hpp"

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

template <class Iterator>
void	printIterator(std::string name, Iterator it, Iterator ite)
{
	std::cout << name << " ";
	for (Iterator iter = it; iter != ite; iter++)
	{
		if (iter != it)
			std::cout << ", ";
		std::cout << *iter;
	}
	std::cout << std::endl;
}

template <class T>
std::list<T>	generateList(T min, T max)
{
	std::list<T>	list;

	for (T i = min; i < max; i++)
		list.push_back(i);

	return (list);
}

int main(void)
{
	typedef ft::map<std::string, int>	map_type;

	// --- Containers --- //
	map_type		map;

	// --- Insertion --- //
	map.insert(ft::make_pair("Hello", 42));
	map.insert(ft::make_pair("World", 21));
	map.insert(ft::make_pair("!", 0));

	// --- Iterators --- //
	std::cout << "\e[100;37m Iterators \e[0m" << std::endl;
	for (map_type::iterator it = map.begin(); it != map.end(); it++)
		std::cout << it->first << " -> " << it->second << std::endl;
	std::cout << std::endl;

	// --- Accessors --- //
	std::cout << "\e[100;37m Accessors \e[0m" << std::endl;
	std::cout << "map[\"Hello\"] = " << map["Hello"] << std::endl;
	std::cout << "map[\"World\"] = " << map["World"] << std::endl;
	std::cout << "map[\"!\"] = " << map["!"] << std::endl;
	std::cout << std::endl;
	std::cout << "map.at(\"Hello\") = " << map.at("Hello") << std::endl;
	std::cout << "map.at(\"World\") = " << map.at("World") << std::endl;
	std::cout << "map.at(\"!\") = " << map.at("!") << std::endl;
	std::cout << std::endl;

	// --- Constness test --- //
	std::cout << "\e[100;37m Constness test \e[0m" << std::endl;
	const map_type constMap(map);

	std::cout << "constMap[\"Hello\"] = " << constMap["Hello"] << std::endl;
	std::cout << "constMap[\"World\"] = " << constMap["World"] << std::endl;
	std::cout << "constMap[\"!\"] = " << constMap["!"] << std::endl;
	std::cout << std::endl;
	std::cout << "constMap.at(\"Hello\") = " << constMap.at("Hello") << std::endl;
	std::cout << "constMap.at(\"World\") = " << constMap.at("World") << std::endl;
	std::cout << "constMap.at(\"!\") = " << constMap.at("!") << std::endl;
	std::cout << std::endl;

	// --- Capacity --- //
	std::cout << "\e[100;37m Capacity \e[0m" << std::endl;
	std::cout << "Size: " << map.size() << std::endl;
	std::cout << "Empty: " << emojiBoolean(map.empty(), true) << std::endl;

	return (EXIT_SUCCESS);
}
