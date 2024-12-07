#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

__int64 solution_06_b(const char* input)
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
	auto seen = std::set<std::pair<size_t, size_t>>();
	size_t original_x{ x };
	size_t original_y{ y };
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
	int paradoxes{ 0 };
	int l{ 0 };
	for (auto s : seen)
	{
		auto seen2 = std::set<std::tuple<char, size_t, size_t>>();
		size_t sx{ std::get<0>(s) };
		size_t sy{ std::get<1>(s) };
		direction = 'U';
		x = original_x;
		y = original_y;
		while (x >= 0 && x < width && y >= 0 && y < height)
		{
			seen2.insert({ direction, x, y });
			switch (direction)
			{
			case 'U':
				--y;
				if (seen2.contains({ direction, x, y }))
				{
					++paradoxes;
					goto next_seen;
				}
				if (y == -1) goto next_seen;
				if (lines[y][x] == '#' || (y == sy && x == sx))
				{
					++y;
					direction = 'R';
				}
				break;
			case 'D':
				++y;
				if (seen2.contains({ direction, x, y }))
				{
					++paradoxes;
					goto next_seen;
				}
				if (y == height) goto next_seen;
				if (lines[y][x] == '#' || (y == sy && x == sx))
				{
					--y;
					direction = 'L';
				}
				break;
			case 'L':
				--x;
				if (seen2.contains({ direction, x, y }))
				{
					++paradoxes;
					goto next_seen;
				}
				if (x == -1) goto next_seen;
				if (lines[y][x] == '#' || (y == sy && x == sx))
				{
					++x;
					direction = 'U';
				}
				break;
			case 'R':
				++x;
				if (seen2.contains({ direction, x, y }))
				{
					++paradoxes;
					goto next_seen;
				}
				if (x == width) goto next_seen;
				if (lines[y][x] == '#' || (y == sy && x == sx))
				{
					--x;
					direction = 'D';
				}
				break;
			}
			l++;
		}
	next_seen:;
	}
	return paradoxes;
}