#include <iostream>
#include <fstream>
#include <sstream>

static void pdigit(const char* c, int& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_14_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	int width{ input[9] == 'e' ? 11 : 101 };
	int height{ input[9] == 'e' ? 7 : 103 };
	int quad1{ 0 };
	int quad2{ 0 };
	int quad3{ 0 };
	int quad4{ 0 };
	bool minus;
	while (std::getline(file, line))
	{
		c = line.c_str() + 2;
		int px{ 0 };
		while (*c != ',')
		{
			pdigit(c, px);
			c++;
		}
		c++;
		int py{ 0 };
		while (*c != ' ')
		{
			pdigit(c, py);
			c++;
		}
		c += 3;
		if (*c == '-')
		{
			minus = true;
			c++;
		}
		else
		{
			minus = false;
		}
		int vx{ 0 };
		while (*c != ',')
		{
			pdigit(c, vx);
			c++;
		}
		vx *= minus ? -1 : 1;
		c++;
		if (*c == '-')
		{
			minus = true;
			c++;
		}
		else
		{
			minus = false;
		}
		int vy{ 0 };
		while (*c && *c != ' ')
		{
			pdigit(c, vy);
			c++;
		}
		vy *= minus ? -1 : 1;

		px = ((px + 100 * vx) % width + width) % width;
		py = ((py + 100 * vy) % height + height) % height;

		if (px == width / 2) continue;
		if (py == height / 2) continue;

		if (px < width / 2)
		{
			if (py < height / 2)
			{
				quad1++;
			}
			else
			{
				quad2++;
			}
		}
		else
		{
			if (py < height / 2)
			{
				quad3++;
			}
			else
			{
				quad4++;
			}
		}
	}
	return quad1 * quad2 * quad3 * quad4;
}