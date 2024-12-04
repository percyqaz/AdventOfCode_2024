#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

__int64 solution_04_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
		lines.push_back(line);
	size_t width{ lines[0].size() };
	size_t height{ lines.size() };
	__int64 total{ 0 };
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (lines[y][x] != 'X')
				continue;
			if (x >= 3 && lines[y][x - 1] == 'M' && lines[y][x - 2] == 'A' && lines[y][x - 3] == 'S')
				++total;
			if (x + 3 < width && lines[y][x + 1] == 'M' && lines[y][x + 2] == 'A' && lines[y][x + 3] == 'S')
				++total;
			if (y >= 3 && lines[y - 1][x] == 'M' && lines[y - 2][x] == 'A' && lines[y - 3][x] == 'S')
				++total;
			if (y + 3 < height && lines[y + 1][x] == 'M' && lines[y + 2][x] == 'A' && lines[y + 3][x] == 'S')
				++total;
			if (x >= 3 && y >= 3 && lines[y - 1][x - 1] == 'M' && lines[y - 2][x - 2] == 'A' && lines[y - 3][x - 3] == 'S')
				++total;
			if (x >= 3 && y + 3 < height && lines[y + 1][x - 1] == 'M' && lines[y + 2][x - 2] == 'A' && lines[y + 3][x - 3] == 'S')
				++total;
			if (x + 3 < width && y >= 3 && lines[y - 1][x + 1] == 'M' && lines[y - 2][x + 2] == 'A' && lines[y - 3][x + 3] == 'S')
				++total;
			if (x + 3 < width && y + 3 < height && lines[y + 1][x + 1] == 'M' && lines[y + 2][x + 2] == 'A' && lines[y + 3][x + 3] == 'S')
				++total;
		}
	}
	return total;
}