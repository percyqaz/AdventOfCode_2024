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

static const char* _do(const char* c)
{
	if (*c == 'd' && *(c + 1) == 'o' && *(c + 2) == '(' && *(c + 3) == ')')
		return c + 4;
	return NULL;
}

static const char* dont(const char* c)
{
	if (*c == 'd' && *(c + 1) == 'o' && *(c + 2) == 'n' && *(c + 3) == '\'' && *(c + 4) == 't' && *(c + 5) == '(' && *(c + 6) == ')')
		return c + 7;
	return NULL;
}

constexpr int MUL_ENABLED{ 1 };
constexpr int MUL_DISABLED{ 0 };

__int64 solution_03_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	__int64 total{ 0 };
	int state{ MUL_ENABLED };
	while (std::getline(file, line))
	{
		const char* c{ line.c_str() };
		while (*c != 0)
		{
			if (state)
			{
				const char* parse_result{ parse_mul(c, total) };
				if (parse_result)
				{
					c = parse_result;
					continue;
				}
				else
				{
					const char* parse_dont{ dont(c) };
					if (parse_dont)
					{
						c = parse_dont;
						state = MUL_DISABLED;
						continue;
					}
				}
			}
			else
			{
				const char* parse_do{ _do(c) };
				if (parse_do)
				{
					c = parse_do;
					state = MUL_ENABLED;
					continue;
				}
			}
			c++;
		}
	}
	return total;
}