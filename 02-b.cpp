#include <iostream>
#include <fstream>
#include <sstream>

// is entire remainder of this stream safe
bool is_safe_part_1(int* report)
{
	int a{ *(report++) };
	int b{ *(report++) };
	if (a == b || std::abs(a - b) > 3)
	{
		return false;
	}
	int next{};
	while (next = *(report++))
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			return false;
		}
		b = next;
	}
	return true;
}

// is this stream safe except second number
bool is_safe_bug_fix(int* report)
{
	int a{ *(report++) };
	++report;
	int b{ *(report++) };
	if (a == b || std::abs(a - b) > 3)
	{
		return false;
	}
	int next{};
	while (next = *(report++))
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			return false;
		}
		b = next;
	}
	return true;
}

// is this report safe with a skip allowed
bool is_safe_part_2(int* report)
{
	int a{ *(report++) };
	int b{ *(report++) };
	bool used_skip{ false };
	if (a == b || std::abs(a - b) > 3)
	{
		used_skip = true;
		b = *(report++);
		if (a == b || std::abs(a - b) > 3)
		{
			return false;
		}
	}
	int next{};
	while (next = *(report++))
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			if (!used_skip)
			{
				used_skip = true;
				continue;
			}
			return false;
		}
		b = next;
	}
	return true;
}

static bool digit(const char* c, int& value)
{
	switch (*c)
	{
	case '0':
		value *= 10;
		return true;
	case '1':
		value *= 10;
		value += 1;
		return true;
	case '2':
		value *= 10;
		value += 2;
		return true;
	case '3':
		value *= 10;
		value += 3;
		return true;
	case '4':
		value *= 10;
		value += 4;
		return true;
	case '5':
		value *= 10;
		value += 5;
		return true;
	case '6':
		value *= 10;
		value += 6;
		return true;
	case '7':
		value *= 10;
		value += 7;
		return true;
	case '8':
		value *= 10;
		value += 8;
		return true;
	case '9':
		value *= 10;
		value += 9;
		return true;
	default:
		return false;
	}
}

static int number(char*& c, int* output)
{
	*output = 0;
	for (; digit(c, *output); c++);
	return *output;
}

constexpr int LARGEST_REPORT{ 8 };
constexpr int BUFFER_SIZE{ LARGEST_REPORT + 1 };

__int64 solution_02_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	int safe{ 0 };
	int buffer[BUFFER_SIZE];
	while (std::getline(file, line))
	{
		int i{ 0 };
		char* c{ line.data() };
		for (; number(c, &buffer[i]); ++i)
		{
			if (*c == ' ') ++c;
			else break;
		}
		buffer[i + 1] = 0;
		if (is_safe_part_2(buffer) || is_safe_bug_fix(buffer) || is_safe_part_1(buffer + 1))
			safe++;
	}
	return safe;
}