#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

static void pdigit(const char* c, __int64& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_11_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	size_t y{ 0 };
	size_t x{ 0 };
	auto stones = std::map<__int64, __int64>();
	auto stones2 = std::map<__int64, __int64>();
	std::getline(file, line);
	const char* c{ line.c_str() };
	__int64 num{ 0 };
	while (*c)
	{
	parse_num:
		num = 0;
		for (; *c != ' ' && *c != NULL; pdigit(c, num), ++c);
		stones[num]++;
		if (*c == ' ')
		{
			++c;
			goto parse_num;
		}
	}
	std::map<__int64, __int64>* current{ &stones };
	std::map<__int64, __int64>* next{ &stones2 };
	int digits{};
	__int64 d{};
	for (int i = 0; i < 25; i++)
	{
		for (std::pair<__int64, __int64> p : *current)
		{
			if (p.first == 0)
			{
				(*next)[1] += p.second;
				continue;
			}

			digits = 1;
			d = p.first;
			for (; d > 9; digits *= 10, d /= 100);
			if (!d)
			{
				(*next)[p.first / digits] += p.second;
				(*next)[p.first % digits] += p.second;
				continue;
			}

			(*next)[p.first * 2024] += p.second;
		}
		std::swap(next, current);
		next->clear();
	}
	__int64 total{ 0 };
	for (std::pair<__int64, __int64> p : *current)
		total += p.second;
	return total;
}