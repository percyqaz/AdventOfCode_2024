#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

static void pdigit(const char* c, __int64& value)
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

static const bool possible_rec(const __int64 target, const std::vector<__int64>& numbers, const __int64 index, const __int64 accumulator)
{
	int next = numbers[index];
	if (index + 1 == numbers.size())
	{
		return (next * accumulator == target || next + accumulator == target);
	}

	if (target >= next * accumulator && possible_rec(target, numbers, index + 1, next * accumulator))
	{
		return true;
	}

	if (target >= next + accumulator && possible_rec(target, numbers, index + 1, next + accumulator))
	{
		return true;
	}

	return false;
}

static const bool possible(const __int64 target, const std::vector<__int64>& numbers)
{
	return possible_rec(target, numbers, 1, numbers[0]);
}

__int64 solution_07_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	__int64 target{};
	__int64 num{};
	std::vector<__int64> numbers = std::vector<__int64>();
	__int64 total{ 0 };
	while (std::getline(file, line))
	{
		numbers.clear();
		target = 0;
		const char* c = line.c_str();
		for (; *c != ':'; pdigit(c, target), ++c);
		c += 2;

	parse_num:
		num = 0;
		for (; *c != ' ' && *c != NULL; pdigit(c, num), ++c);
		numbers.push_back(num);
		if (*c == ' ')
		{
			++c;
			goto parse_num;
		}

		total += possible(target, numbers) ? target : 0;
	}
	return total;
}