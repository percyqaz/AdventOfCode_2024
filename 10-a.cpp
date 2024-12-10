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

	bool operator==(const Trail& other) const {
		return head_x == other.head_x &&
			head_y == other.head_y &&
			origin_x == other.origin_x &&
			origin_y == other.origin_y;
	}
};

struct TrailHash {
	size_t operator()(const Trail& trail) const {
		size_t h1 = std::hash<size_t>{}(trail.head_x);
		size_t h2 = std::hash<size_t>{}(trail.head_y);
		size_t h3 = std::hash<size_t>{}(trail.origin_x);
		size_t h4 = std::hash<size_t>{}(trail.origin_y);

		size_t hash_value = h1;
		hash_value ^= h2 + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
		hash_value ^= h3 + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
		hash_value ^= h4 + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);

		return hash_value;
	}
};

__int64 solution_10_a(const char* input)
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
	auto terminals = std::unordered_set<Trail, TrailHash>();
	do {
		for (size_t i = heads.size(); i; i--)
		{
			const Trail& t{ heads.front() };
			heads.pop();

			if (lines[t.head_y][t.head_x] == '9')
			{
				terminals.insert(t);
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
	return terminals.size();
}