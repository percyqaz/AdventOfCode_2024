#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

struct Path
{
	int score;
	int x;
	int y;
	char direction;
};

__int64 solution_16_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	auto map = std::vector<std::string>();
	auto paths = std::queue<Path>();
	auto forks = std::unordered_map<int, int>();
	while (std::getline(file, line))
	{
		map.push_back(line);
	}
	size_t map_size{ map.size() };
	Path initial_path{ 0, 1, map_size - 2, 'R' };
	paths.push(initial_path);
	int best_path{ INT32_MAX };
	do {
		for (size_t i = paths.size(); i; i--)
		{
			const Path p{ paths.front() };
			paths.pop();

			if (p.y == 1 && p.x == map_size - 2)
			{
				if (p.score < best_path)
					best_path = p.score;
				continue;
			}

			if (p.score > best_path)
			{
				continue;
			}

			int up{ map[p.y - 1][p.x] != '#' };
			int down{ map[p.y + 1][p.x] != '#' };
			int left{ map[p.y][p.x - 1] != '#' };
			int right{ map[p.y][p.x + 1] != '#' };

			if (up + down + left + right > 2)
			{
				auto id = p.x * map_size + p.y;
				if (!forks[id])
				{
					forks[id] = p.score;
				}
				else if (p.score <= forks[id])
				{
					forks[id] = p.score;
				}
				else
				{
					continue;
				}
			}

			if (up && p.direction == 'U')
				paths.push({ p.score + 1, p.x, p.y - 1, 'U' });
			else if (up && p.direction != 'D')
				paths.push({ p.score + 1001, p.x, p.y - 1, 'U' });

			if (down && p.direction == 'D')
				paths.push({ p.score + 1, p.x, p.y + 1, 'D' });
			else if (down && p.direction != 'U')
				paths.push({ p.score + 1001, p.x, p.y + 1, 'D' });

			if (left && p.direction == 'L')
				paths.push({ p.score + 1, p.x - 1, p.y, 'L' });
			else if (left && p.direction != 'R')
				paths.push({ p.score + 1001, p.x - 1, p.y, 'L' });

			if (right && p.direction == 'R')
				paths.push({ p.score + 1, p.x + 1, p.y, 'R' });
			else if (right && p.direction != 'L')
				paths.push({ p.score + 1001, p.x + 1, p.y, 'R' });
		}
	} while (paths.size());
	return best_path;
}