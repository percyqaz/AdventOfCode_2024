#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>

struct Trail
{
	size_t head_x;
	size_t head_y;
	size_t origin_x;
	size_t origin_y;
};

__int64 solution_10_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	size_t y{ 0 };
	size_t x{ 0 };
	auto lines = std::vector<std::string>();
	auto heads = std::queue<Trail>();
	while (std::getline(file, line))
	{
		x = line.find('0');
		while (x != std::string::npos)
		{
			heads.push({ x, y, x, y });
			x = line.find('0', x + 1);
		}
		lines.push_back(line);
		y++;
	}
	__int64 count{ 0 };
	do {
		for (size_t i = heads.size(); i; i--)
		{
			const Trail t{ heads.front() }; // note the lack of & in this solution!
			heads.pop();

			if (lines[t.head_y][t.head_x] == '9')
			{
				count++;
				continue;
			}

			if (t.head_x > 0 && lines[t.head_y][t.head_x - 1] - lines[t.head_y][t.head_x] == 1)
				heads.push({ t.head_x - 1, t.head_y, t.origin_x, t.origin_y });
			if (t.head_x + 1 < y && lines[t.head_y][t.head_x + 1] - lines[t.head_y][t.head_x] == 1)
				heads.push({ t.head_x + 1, t.head_y, t.origin_x, t.origin_y });
			if (t.head_y > 0 && lines[t.head_y - 1][t.head_x] - lines[t.head_y][t.head_x] == 1)
				heads.push({ t.head_x, t.head_y - 1, t.origin_x, t.origin_y });
			if (t.head_y + 1 < y && lines[t.head_y + 1][t.head_x] - lines[t.head_y][t.head_x] == 1)
				heads.push({ t.head_x, t.head_y + 1, t.origin_x, t.origin_y });
		}
	} while (heads.size());
	return count;
}