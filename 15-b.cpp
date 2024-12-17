#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

// debugging tools
static void debug_print(size_t x, size_t y, std::vector<std::vector<char>>& map)
{
	int y2{ 0 };
	for (std::vector<char> line : map)
	{
		if (y2 == y) line[x] = '@';
		std::cout << &line[0] << "\n";
		if (y2 == y) line[x] = '.';
		y2++;
	}
}

static int box_count(std::vector<std::vector<char>>& map)
{
	int boxes{ 0 };
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			if (map[y][x] == '[')
			{
				boxes++;
			}
		}
	}
	return boxes;
}

static bool push_upwards(size_t y, std::set<size_t> current_row, std::vector<std::vector<char>>& map)
{
	std::vector<std::set<size_t>> all_rows{ current_row };
	size_t y2{ y - 2 };
	std::set<size_t> next_row{ std::set<size_t>() };
another_row:
	for (auto x : current_row)
	{
		if (map[y2][x] == ']')
			next_row.insert(x - 1);
		else if (map[y2][x] == '[')
			next_row.insert(x);
		else if (map[y2][x] == '#')
			return false;
		if (map[y2][x + 1] == '[')
			next_row.insert(x + 1);
		else if (map[y2][x + 1] == '#')
			return false;
	}
	if (next_row.size())
	{
		all_rows.push_back(next_row);
		current_row = next_row;
		next_row = std::set<size_t>();
		y2--;
		goto another_row;
	}
	for (; y2 < y - 1; y2++)
	{
		auto& row = all_rows[y - y2 - 2];
		for (auto x : row)
		{
			map[y2][x] = map[y2 + 1][x];
			map[y2][x + 1] = map[y2 + 1][x + 1];
			map[y2 + 1][x] = '.';
			map[y2 + 1][x + 1] = '.';
		}
	}
	return true;
}

static bool push_downwards(size_t y, std::set<size_t> current_row, std::vector<std::vector<char>>& map)
{
	std::vector<std::set<size_t>> all_rows{ current_row };
	size_t y2{ y + 2 };
	std::set<size_t> next_row{ std::set<size_t>() };
another_row:
	for (auto x : current_row)
	{
		if (map[y2][x] == ']')
			next_row.insert(x - 1);
		else if (map[y2][x] == '[')
			next_row.insert(x);
		else if (map[y2][x] == '#')
			return false;
		if (map[y2][x + 1] == '[')
			next_row.insert(x + 1);
		else if (map[y2][x + 1] == '#')
			return false;
	}
	if (next_row.size())
	{
		all_rows.push_back(next_row);
		current_row = next_row;
		next_row = std::set<size_t>();
		y2++;
		goto another_row;
	}
	for (; y2 > y + 1; y2--)
	{
		auto& row = all_rows[y2 - y - 2];
		for (auto x : row)
		{
			map[y2][x] = map[y2 - 1][x];
			map[y2][x + 1] = map[y2 - 1][x + 1];
			map[y2 - 1][x] = '.';
			map[y2 - 1][x + 1] = '.';
		}
	}
	return true;
}

__int64 solution_15_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	size_t x{ 0 };
	size_t y{};
	std::vector<std::vector<char>> map{ std::vector<std::vector<char>>() };
	while (std::getline(file, line))
	{
		if (line.length() == 0) break;
		if (!x) {
			x = line.find('@');
			y = map.size();
			if (x == std::string::npos)
				x = 0;
			else x *= 2;
		}
		auto double_line{ std::vector<char>() };
		for (char c : line)
		{
			switch (c)
			{
			case '#':
				double_line.push_back('#');
				double_line.push_back('#');
				break;
			case 'O':
				double_line.push_back('[');
				double_line.push_back(']');
				break;
			case '.':
			case '@':
				double_line.push_back('.');
				double_line.push_back('.');
				break;
			default:
				break;
			}
		}
		double_line.push_back(NULL);
		map.push_back(double_line);
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
				if (map[y - 1][x] == '[' && !push_upwards(y, { x }, map)) break;
				if (map[y - 1][x] == ']' && !push_upwards(y, { x - 1 }, map)) break;
				y--;
				break;
			case 'v':
				if (map[y + 1][x] == '#') break;
				if (map[y + 1][x] == '[' && !push_downwards(y, { x }, map)) break;
				if (map[y + 1][x] == ']' && !push_downwards(y, { x - 1 }, map)) break;
				y++;
				break;
			case '<':
				if (map[y][x - 1] == '#') break;
				if (map[y][x - 1] == ']')
				{
					size_t x2{ x - 3 };
					while (map[y][x2] == ']' || map[y][x2] == '[') x2--;
					if (map[y][x2] == '#') break;
					while (x2 < x)
					{
						map[y][x2] = map[y][x2 + 1];
						x2++;
					}
					map[y][x - 1] = '.';
				}
				x--;
				break;
			case '>':
				if (map[y][x + 1] == '#') break;
				if (map[y][x + 1] == '[')
				{
					size_t x2{ x + 3 };
					while (map[y][x2] == '[' || map[y][x2] == ']') x2++;
					if (map[y][x2] == '#') break;
					while (x2 > x)
					{
						map[y][x2] = map[y][x2 - 1];
						x2--;
					}
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
			if (map[y][x] == '[')
			{
				total += 100 * y + x;
			}
		}
	}
	return total;
}