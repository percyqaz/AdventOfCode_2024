#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

__int64 solution_04_b(const char* input)
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
			if (x < 1 || y < 1 || y + 1 == height || x + 1 == height)
				continue;
			if (lines[y][x] != 'A')
				continue;

			char lt{ lines[y - 1][x - 1] };
			char rt{ lines[y - 1][x + 1] };
			char rb{ lines[y + 1][x + 1] };
			char lb{ lines[y + 1][x - 1] };

			if (lt == 'M' && rt == 'M' && rb == 'S' && lb == 'S')
				++total;
			else if (lt == 'S' && rt == 'M' && rb == 'M' && lb == 'S')
				++total;
			else if (lt == 'S' && rt == 'S' && rb == 'M' && lb == 'M')
				++total;
			else if (lt == 'M' && rt == 'S' && rb == 'S' && lb == 'M')
				++total;
		}
	}
	return total;
}