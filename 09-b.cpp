#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>

__int64 solution_09_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	std::getline(file, line);
	auto files = std::vector<std::pair<char, size_t>>();
	auto gaps = std::vector<std::pair<char, size_t>>();
	size_t pos{ 0 };
	char d{};
	const char* c{ line.c_str() };
	bool represents_free{ false };
	while (*c)
	{
		d = *c - '0';
		if (represents_free)
			gaps.push_back({ d, pos });
		else
			files.push_back({ d, pos });
		pos += d;
		represents_free = !represents_free;
		c++;
	}

	for (int f = files.size() - 1; f >= 0; f--)
	{
		std::pair<char, size_t>& file{ files[f] };
		for (int g = 0; g < gaps.size() && gaps[g].second < file.second; g++)
		{
			if (gaps[g].first >= file.first) {
				std::pair<char, size_t>& gap{ gaps[g] };
				gap.first -= file.first;
				file.second = gap.second;
				gap.second += file.first;
				goto next_file;
			}
		}
	next_file:;
	}

	__int64 checksum{ 0 };
	for (int f = 0; f < files.size(); f++)
	{
		std::pair<char, size_t>& file{ files[f] };
		while (file.first)
		{
			checksum += file.second * f;
			file.second++;
			file.first--;
		}
	}
	return checksum;
}