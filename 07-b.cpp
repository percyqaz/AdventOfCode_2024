#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

static void pdigit(const char* c, __int64& value)
{
	value *= 10;
	value += *c - '0';
}

const __int64 concat(__int64 left, __int64 right)
{
	if (right >= 100)
	{
		left *= 10;
		left += right / 100;
		right %= 100;
		left *= 10;
		left += right / 10;
		right %= 10;
		left *= 10;
		left += right;
		return left;
	}

	if (right >= 10)
	{
		left *= 10;
		left += right / 10;
		right %= 10;
		left *= 10;
		left += right;
		return left;
	}

	left *= 10;
	left += right;
	return left;
}

static const bool possible_rec(const __int64 target, const std::vector<__int64>& numbers, const size_t index, const __int64 accumulator)
{
	const __int64 next = numbers[index];
	const __int64 cat = concat(accumulator, next);
	if (index + 1 == numbers.size())
	{
		return
			cat == target ||
			next * accumulator == target ||
			next + accumulator == target;
	}

	if (target >= cat && possible_rec(target, numbers, index + 1, cat))
	{
		return true;
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

__int64 solution_07_b(const char* input)
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