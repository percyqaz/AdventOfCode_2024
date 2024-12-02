#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

__int64 solution_01_a(const char* input)
{
	auto lefts = std::multiset<int>();
	auto rights = std::multiset<int>();

	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int left, right;
		if (!(iss >> left >> right)) { break; }

		lefts.emplace(left);
		rights.emplace(right);
	}

	int dist{ 0 };

	auto left_iter{ lefts.begin() };
	auto right_iter{ rights.begin() };
	while (left_iter != lefts.end())
	{
		dist += std::abs(*left_iter - *right_iter);
		left_iter++;
		right_iter++;
	}

	return dist;
}