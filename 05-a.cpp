#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

static void pdigit(const char* c, int& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_05_a(const char* input)
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

		for (int i = 0; i < pages.size() - 1; ++i)
		{
			for (int j = i + 1; j < pages.size(); j++)
			{
				if (rules.contains({ pages[j], pages[i] }))
				{
					goto incorrect;
				}
			}
		}

		total += pages[pages.size() / 2];
	incorrect:;
	}
	return total;
}