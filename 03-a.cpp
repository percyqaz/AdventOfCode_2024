#include <iostream>
#include <fstream>
#include <sstream>

static const char* mul_paren(const char* c)
{
	if (*c == 'm' && *(c + 1) == 'u' && *(c + 2) == 'l' && *(c + 3) == '(')
		return c + 4;
	return NULL;
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

static const char* number(const char* c, int& value)
{
	if (digit(c, value))
	{
		if (digit(c + 1, value))
		{
			if (digit(c + 2, value))
			{
				return c + 3;
			}
			return c + 2;
		}
		return c + 1;
	}
	return NULL;
}

static const char* comma(const char* c)
{
	if (*c == ',')
		return c + 1;
	return NULL;
}

static const char* close_paren(const char* c)
{
	if (*c == ')')
		return c + 1;
	return NULL;
}

static const char* parse_mul(const char* c, __int64& total)
{
	c = mul_paren(c);
	if (!c)
		return NULL;
	int num1{ 0 };
	c = number(c, num1);
	if (!c)
		return NULL;
	c = comma(c);
	if (!c)
		return NULL;
	int num2{ 0 };
	c = number(c, num2);
	if (!c)
		return NULL;
	c = close_paren(c);
	if (!c)
		return NULL;
	total += num1 * num2;
	return c;
}

__int64 solution_03_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	__int64 total{ 0 };
	while (std::getline(file, line))
	{
		const char* c{ line.c_str() };
		while (*c != 0)
		{
			const char* parse_result{ parse_mul(c, total) };
			if (parse_result)
				c = parse_result;
			else
				c++;
		}
	}
	return total;
}