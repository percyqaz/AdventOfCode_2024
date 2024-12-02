#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

__int64 solution_01_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	auto lefts = std::unordered_map<int, int>();
	auto rights = std::unordered_map<int, int>();
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int left, right;
		if (!(iss >> left >> right)) { break; }

		lefts[left]++;
		rights[right]++;
	}
	int similarity{ 0 };
	for (auto iter = lefts.begin(); iter != lefts.end(); iter++)
	{
		std::pair kvp{ *iter };
		similarity += kvp.first * kvp.second * rights[kvp.first];
	}
	return similarity;
}