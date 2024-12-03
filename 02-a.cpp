#include <iostream>
#include <fstream>
#include <sstream>

static bool is_safe_asc(int* n)
{
	for (; *(n + 1); n++) {
		if (*(n + 1) - *n < 1 || *(n + 1) - *n > 3)
		{
			return false;
		}
	}
	return true;
}

static bool is_safe_desc(int* n)
{
	for (; *(n + 1); n++) {
		if (*n - *(n + 1) < 1 || *n - *(n + 1) > 3)
		{
			return false;
		}
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

__int64 solution_02_a(const char* input)
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
		for (; number(c, &buffer[i]); i++)
		{
			if (*c == ' ') c++;
			else break;
		}
		buffer[i + 1] = 0;
		if (is_safe_asc(buffer) || is_safe_desc(buffer)) safe++;
	}
	return safe;
}