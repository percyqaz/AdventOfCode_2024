#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using int_list = std::vector<int>;

void solution_01_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	int_list left_numbers = std::vector<int>();
	int_list right_numbers = std::vector<int>();
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int left, right;
		if (!(iss >> left >> right)) { break; }

		left_numbers.push_back(left);
		right_numbers.push_back(right);
	}
	int similarity{ 0 };
	int n = left_numbers.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (left_numbers[i] == right_numbers[j])
			{
				similarity += left_numbers[i];
			}
		}
	}
	std::cout << "Total similarity: " << similarity;
}