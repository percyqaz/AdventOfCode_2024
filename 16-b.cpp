#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

struct PositionLinkedList
{
	size_t p;
	std::shared_ptr<PositionLinkedList> next;
};

struct PathB
{
	int score;
	size_t x;
	size_t y;
	char direction;
	std::shared_ptr<PositionLinkedList> positions;
};

__int64 solution_16_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	auto map = std::vector<std::string>();
	auto forks = std::unordered_map<int, int>();
	while (std::getline(file, line))
	{
		map.push_back(line);
	}
	size_t map_size{ map.size() };
	PathB initial_path{ 0, 1, map_size - 2, 'R', NULL };
	std::queue<PathB> paths{};
	paths.push(initial_path);
	int best_path{ INT32_MAX };
	std::vector<std::shared_ptr<PositionLinkedList>> best_paths{ std::vector<std::shared_ptr<PositionLinkedList>>() };
	do {
		for (size_t i = paths.size(); i; i--)
		{
			const PathB p = paths.front();
			paths.pop();

			size_t id = p.x * map_size + p.y;
			std::shared_ptr<PositionLinkedList> positions{ new PositionLinkedList{ id, p.positions } };

			if (p.y == 1 && p.x == map_size - 2)
			{
				if (p.score < best_path)
				{
					best_path = p.score;
					best_paths.clear();
					best_paths.push_back(positions);
				}
				else if (p.score == best_path)
				{
					best_paths.push_back(positions);
				}
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
				if (!forks[id])
				{
					forks[id] = p.score;
				}
				else if (p.score <= forks[id] + 1001)
				{
					forks[id] = p.score;
				}
				else
				{
					continue;
				}
			}

			if (up && p.direction == 'U')
				paths.push({ p.score + 1, p.x, p.y - 1, 'U', positions });
			else if (up && p.direction != 'D')
				paths.push({ p.score + 1001, p.x, p.y - 1, 'U', positions });

			if (down && p.direction == 'D')
				paths.push({ p.score + 1, p.x, p.y + 1, 'D', positions });
			else if (down && p.direction != 'U')
				paths.push({ p.score + 1001, p.x, p.y + 1, 'D', positions });

			if (left && p.direction == 'L')
				paths.push({ p.score + 1, p.x - 1, p.y, 'L', positions });
			else if (left && p.direction != 'R')
				paths.push({ p.score + 1001, p.x - 1, p.y, 'L', positions });

			if (right && p.direction == 'R')
				paths.push({ p.score + 1, p.x + 1, p.y, 'R', positions });
			else if (right && p.direction != 'L')
				paths.push({ p.score + 1001, p.x + 1, p.y, 'R', positions });
		}
	} while (paths.size());
	std::set<int> tiles_in_best_path{};
	tiles_in_best_path.insert(map_size * 2 - 2);
	for (std::shared_ptr<PositionLinkedList> p : best_paths)
	{
		while (p->next)
		{
			tiles_in_best_path.insert(p->p);
			p = p->next;
		}
	}
	return tiles_in_best_path.size();
}