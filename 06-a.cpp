#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

__int64 solution_06_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::vector<std::string> lines;
	std::string line;
	size_t x{ 0 };
	size_t y{};
	char direction = 'U';
	while (std::getline(file, line))
	{
		if (!x) {
			x = line.find('^');
			y = lines.size();
			if (x == std::string::npos)
				x = 0;
		}
		lines.push_back(line);
	}
	size_t width{ lines[0].size() };
	size_t height{ lines.size() };
	auto seen = std::set<std::pair<int, int>>();
	while (x >= 0 && x < width && y >= 0 && y < height)
	{
		seen.insert({ x, y });
		switch (direction)
		{
		case 'U':
			--y;
			if (y == -1) goto done;
			if (lines[y][x] == '#')
			{
				++y;
				direction = 'R';
			}
			break;
		case 'D':
			++y;
			if (y == height) goto done;
			if (lines[y][x] == '#')
			{
				--y;
				direction = 'L';
			}
			break;
		case 'L':
			--x;
			if (x == -1) goto done;
			if (lines[y][x] == '#')
			{
				++x;
				direction = 'U';
			}
			break;
		case 'R':
			++x;
			if (x == width) goto done;
			if (lines[y][x] == '#')
			{
				--x;
				direction = 'D';
			}
			break;
		}
	}
done:
	return seen.size();
}