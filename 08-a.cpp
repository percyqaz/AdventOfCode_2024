#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>

__int64 solution_08_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	size_t y{ 0 };
	std::string line;
	auto antennae = std::unordered_map<char, std::vector<std::pair<size_t, size_t>>>();
	while (std::getline(file, line))
	{
		const char* initial_c{ line.c_str() };
		const char* c{ initial_c };
		while (*c)
		{
			if (*c != '.')
			{
				antennae[*c].push_back({ c - initial_c, y });
			}
			++c;
		}
		++y;
	}
	auto antinodes = std::set<std::pair<size_t, size_t>>();
	size_t ax{};
	size_t ay{};
	for (auto& it : antennae)
	{
		std::vector<std::pair<size_t, size_t>>& group{ it.second };
		for (int i = 0; i < group.size(); ++i)
		{
			for (int j = 0; j < group.size(); ++j)
			{
				if (i == j) continue;
				std::pair<size_t, size_t>& a{ group[i] };
				std::pair<size_t, size_t>& b{ group[j] };

				ax = b.first + b.first - a.first;
				if (ax < 0 || ax >= y) continue;
				ay = b.second + b.second - a.second;
				if (ay < 0 || ay >= y) continue;
				antinodes.insert({ ax, ay });

				ax = a.first + a.first - b.first;
				if (ax < 0 || ax >= y) continue;
				ay = a.second + a.second - b.second;
				if (ay < 0 || ay >= y) continue;
				antinodes.insert({ ax, ay });
			}
		}
	}
	return antinodes.size();
}