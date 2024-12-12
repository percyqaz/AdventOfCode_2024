#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

static int generate_id()
{
	static int current{ 0 };
	return ++current;
}

__int64 solution_12_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	int grid_size{ 0 };
	auto lines = std::vector<std::string>();
	while (std::getline(file, line))
	{
		lines.push_back(line);
		grid_size++;
	}

	std::vector<int> group_id_store{ std::vector<int>() };
	group_id_store.reserve(10000);
	int** group_pointers{ new int* [grid_size * grid_size] };

	char previous{};
	int* previous_id = NULL;
	for (int y = 0; y < grid_size; y++)
	{
		previous = NULL;
		for (int x = 0; x < grid_size; x++)
		{
			if (lines[y][x] != previous)
			{
				group_id_store.push_back(generate_id());
				previous_id = &group_id_store[group_id_store.size() - 1];
				previous = lines[y][x];
			}
			group_pointers[x * grid_size + y] = previous_id;
		}
	}

	for (int x = 0; x < grid_size; x++)
	{
		previous = NULL;
		for (int y = 0; y < grid_size; y++)
		{
			if (lines[y][x] == previous)
			{
				int above{ *group_pointers[x * grid_size + y] };
				int below{ *group_pointers[x * grid_size + (y - 1)] };
				// I bet this can be optimised
				for (int i = 0; i < group_id_store.size(); i++)
				{
					if (group_id_store[i] == above) {
						group_id_store[i] = below;
					}
				}
			}
			previous = lines[y][x];
		}
	}

	std::unordered_map<int, int> area = std::unordered_map<int, int>();
	std::unordered_map<int, int> perimeter = std::unordered_map<int, int>();

	bool left, right, up, down{};

	for (int y = 0; y < grid_size; y++)
	{
		for (int x = 0; x < grid_size; x++)
		{
			int group_id = *group_pointers[x * grid_size + y];
			area[group_id]++;

			previous = lines[y][x];

			left = x > 0 && lines[y][x - 1] == previous;
			right = x + 1 < grid_size && lines[y][x + 1] == previous;
			up = y > 0 && lines[y - 1][x] == previous;
			down = y + 1 < grid_size && lines[y + 1][x] == previous;

			if (!left)
			{
				if (!up)
					perimeter[group_id]++;
				if (!down)
					perimeter[group_id]++;
			}
			if (!right)
			{
				if (!up)
					perimeter[group_id]++;
				if (!down)
					perimeter[group_id]++;
			}

			if (up && left && lines[y - 1][x - 1] != previous)
				perimeter[group_id]++;
			if (up && right && lines[y - 1][x + 1] != previous)
				perimeter[group_id]++;
			if (down && left && lines[y + 1][x - 1] != previous)
				perimeter[group_id]++;
			if (down && right && lines[y + 1][x + 1] != previous)
				perimeter[group_id]++;
		}
	}

	__int64 result{ 0 };
	for (std::pair<int, int> g : area)
	{
		result += g.second * (perimeter[g.first]);
	}
	return result;
}