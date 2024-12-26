#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <map>

static void pdigit(const char* c, int& value)
{
	value *= 10;
	value += *c - '0';
}

__int64 solution_18_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	const char* c;
	int size{ input[9] == 'e' ? 7 : 71 };
	int target{ input[9] == 'e' ? 12 : 1024 };
	std::unordered_set<int> blocked{};
	for (int i = 0; i < target && std::getline(file, line); i++)
	{
		int x{ 0 };
		c = line.c_str();
		while (*c != ',')
		{
			pdigit(c, x);
			c++;
		}
		c++;
		int y{ 0 };
		while (*c)
		{
			pdigit(c, y);
			c++;
		}
		blocked.insert(x * size + y);
	}
	std::queue<std::pair<int, int>> queue{};
	queue.push({ 0, 0 });
	blocked.insert(0);
	int pass = 0;
	while (true)
	{
		int i = queue.size();
		for (; i > 0; i--)
		{
			std::pair<int, int>& p = queue.front();
			int x = p.first;
			int y = p.second;
			queue.pop();

			if (x == size - 1 && y == size - 1)
				return pass;

			if (x > 0 && !blocked.contains((x - 1) * size + y))
			{
				blocked.insert((x - 1) * size + y);
				queue.push({ x - 1, y });
			}
			if (x + 1 < size && !blocked.contains((x + 1) * size + y))
			{
				blocked.insert((x + 1) * size + y);
				queue.push({ x + 1, y });
			}
			if (y > 0 && !blocked.contains(x * size + y - 1))
			{
				blocked.insert(x * size + y - 1);
				queue.push({ x, y - 1 });
			}
			if (y + 1 < size && !blocked.contains(x * size + y + 1))
			{
				blocked.insert(x * size + y + 1);
				queue.push({ x, y + 1 });
			}

		}
		pass++;
	}
}