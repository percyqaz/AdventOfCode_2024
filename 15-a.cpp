#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

__int64 solution_15_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	size_t x{ 0 };
	size_t y{};
	std::vector<std::string> map{ std::vector<std::string>() };
	while (std::getline(file, line))
	{
		if (line.length() == 0) break;
		if (!x) {
			x = line.find('@');
			y = map.size();
			if (x == std::string::npos)
				x = 0;
		}
		map.push_back(line);
	}
	while (std::getline(file, line))
	{
		c = line.c_str();
		while (*c)
		{
			switch (*c)
			{
			case '^':
				if (map[y - 1][x] == '#') break;
				if (map[y - 1][x] == 'O')
				{
					size_t y2{ y - 2 };
					while (map[y2][x] == 'O') y2--;
					if (map[y2][x] == '#') break;
					map[y2][x] = 'O';
					map[y - 1][x] = '.';
				}
				y--;
				break;
			case 'v':
				if (map[y + 1][x] == '#') break;
				if (map[y + 1][x] == 'O')
				{
					size_t y2{ y + 2 };
					while (map[y2][x] == 'O') y2++;
					if (map[y2][x] == '#') break;
					map[y2][x] = 'O';
					map[y + 1][x] = '.';
				}
				y++;
				break;
			case '<':
				if (map[y][x - 1] == '#') break;
				if (map[y][x - 1] == 'O')
				{
					size_t x2{ x - 2 };
					while (map[y][x2] == 'O') x2--;
					if (map[y][x2] == '#') break;
					map[y][x2] = 'O';
					map[y][x - 1] = '.';
				}
				x--;
				break;
			case '>':
				if (map[y][x + 1] == '#') break;
				if (map[y][x + 1] == 'O')
				{
					size_t x2{ x + 2 };
					while (map[y][x2] == 'O') x2++;
					if (map[y][x2] == '#') break;
					map[y][x2] = 'O';
					map[y][x + 1] = '.';
				}
				x++;
				break;
			default:
				break;
			}
			c++;
		}
	}
	__int64 total{ 0 };
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			if (map[y][x] == 'O')
				total += 100 * y + x;
		}
	}
	return total;
}