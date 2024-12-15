#include <iostream>
#include <fstream>
#include <sstream>

static void pdigit(const char* c, __int64& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_13_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	__int64 total{};
	do
	{
		std::getline(file, line);
		c = line.c_str();

		for (; *(c++) != '+';);
		__int64 ma{ 0 };
		while (*c != ',')
		{
			pdigit(c, ma);
			c++;
		}
		c += 4;
		__int64 mc{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, mc);
			c++;
		}

		std::getline(file, line);
		c = line.c_str();

		for (; *(c++) != '+';);
		__int64 mb{ 0 };
		while (*c != ',')
		{
			pdigit(c, mb);
			c++;
		}
		c += 4;
		__int64 md{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, md);
			c++;
		}

		std::getline(file, line);
		c = line.c_str();

		for (; *(c++) != '=';);
		__int64 ta{ 0 };
		while (*c != ',')
		{
			pdigit(c, ta);
			c++;
		}
		ta += 10000000000000L;
		c += 4;
		__int64 tb{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, tb);
			c++;
		}
		tb += 10000000000000L;

		__int64 det = ma * md - mb * mc;
		if (!det)
		{
			// no solution
			continue;
		}

		__int64 solution_x_det = md * ta - mb * tb;
		__int64 solution_y_det = ma * tb - mc * ta;

		if (solution_x_det % det != 0)
		{
			// no integer solution
			continue;
		}

		if (solution_y_det % det != 0)
		{
			// no integer solution
			continue;
		}

		total += 3L * solution_x_det / det;
		total += solution_y_det / det;
	} while (std::getline(file, line));
	return total;
}