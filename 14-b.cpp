#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Robot
{
	int x;
	int y;
	int vx;
	int vy;

	std::pair<int, int> position_at_time(int time, int width, int height) const
	{
		return { ((x + time * vx) % width + width) % width, ((y + time * vy) % height + height) % height };
	}
};

static void pdigit(const char* c, int& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_14_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	int width{ input[9] == 'e' ? 11 : 101 };
	int height{ input[9] == 'e' ? 7 : 103 };
	std::vector<Robot> robots{ std::vector<Robot>() };
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

		robots.push_back({ px, py, vx, vy });
	}

	// magic numbers are optional; you can run this at 0 incrementing by 1, but this is 101x faster
	int i{ 46 }; // magic number for my input data, solution could be improved by detecting these magic numbers
	while (true)
	{
		std::vector<std::string> buffer = std::vector<std::string>();
		for (int y = 0; y < height; y++)
		{
			std::string line(width, '0');
			buffer.push_back(line);
		}
		for (Robot& r : robots)
		{
			auto pos = r.position_at_time(i, width, height);
			buffer[pos.second][pos.first]++;
		}
		for (int y = 0; y < height; y++)
		{
			if (buffer[y].contains("111111111111111111111111"))
				return i;
		}
		i += 101; // magic number for my input data, solution could be improved by detecting this magic numbers
	}
	return -1;
}