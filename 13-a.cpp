#include <iostream>
#include <fstream>
#include <sstream>

static void pdigit(const char* c, int& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_13_a(const char* input)
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
		int ma{ 0 };
		while (*c != ',')
		{
			pdigit(c, ma);
			c++;
		}
		c += 4;
		int mc{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, mc);
			c++;
		}

		std::getline(file, line);
		c = line.c_str();

		for (; *(c++) != '+';);
		int mb{ 0 };
		while (*c != ',')
		{
			pdigit(c, mb);
			c++;
		}
		c += 4;
		int md{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, md);
			c++;
		}

		std::getline(file, line);
		c = line.c_str();

		for (; *(c++) != '=';);
		int ta{ 0 };
		while (*c != ',')
		{
			pdigit(c, ta);
			c++;
		}
		c += 4;
		int tb{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, tb);
			c++;
		}

		int det = ma * md - mb * mc;
		if (!det)
		{
			// no solution
			continue;
		}

		int solution_x_det = md * ta - mb * tb;
		int solution_y_det = ma * tb - mc * ta;

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

		total += 3 * solution_x_det / det;
		total += solution_y_det / det;
	} while (std::getline(file, line));
	return total;
}