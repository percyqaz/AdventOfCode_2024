#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

static void pdigit(const char* c, int& value)
{
	switch (*c)
	{
	case '0':
		value *= 10;
		return;
	case '1':
		value *= 10;
		value += 1;
		return;
	case '2':
		value *= 10;
		value += 2;
		return;
	case '3':
		value *= 10;
		value += 3;
		return;
	case '4':
		value *= 10;
		value += 4;
		return;
	case '5':
		value *= 10;
		value += 5;
		return;
	case '6':
		value *= 10;
		value += 6;
		return;
	case '7':
		value *= 10;
		value += 7;
		return;
	case '8':
		value *= 10;
		value += 8;
		return;
	case '9':
		value *= 10;
		value += 9;
		return;
	default:
		throw std::logic_error("Expected digit");
	}
}

__int64 solution_05_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	auto rules = std::set<std::pair<int, int>>();
	while (std::getline(file, line) && line[0])
	{
		const char* c = line.c_str();
		int a{ 0 };
		int b{ 0 };
		pdigit(c, a);
		++c;
		pdigit(c, a);
		++c;
		_ASSERT(*c == '|');
		++c;
		pdigit(c, b);
		++c;
		pdigit(c, b);
		_ASSERT(*(++c) == NULL);
		rules.insert({ a, b });
	}
	__int64 total{ 0 };
	while (std::getline(file, line))
	{
		const char* c = line.c_str();
		auto pages{ std::vector<int>() };
		int a;
		do
		{
			a = 0;
			pdigit(c, a);
			++c;
			pdigit(c, a);
			++c;
			pages.push_back(a);
		} while (*(c++));

		bool swaps_made{ false };
	after_swap:
		for (int i = 0; i < pages.size() - 1; ++i)
		{
			for (int j = i + 1; j < pages.size(); j++)
			{
				if (rules.contains({ pages[j], pages[i] }))
				{
					swaps_made = true;
					std::swap(pages[j], pages[i]);
					goto after_swap;
				}
			}
		}

		if (swaps_made)
			total += pages[pages.size() / 2];
	}
	return total;
}