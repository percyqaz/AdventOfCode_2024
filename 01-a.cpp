#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using int_list = std::vector<int>;

static void bubble_sort(int_list& v)
{
	int n = v.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (v[j] > v[j + 1])
				std::swap(v[j], v[j + 1]);
		}
	}
}

void solution_01_a(const char* input)
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
	bubble_sort(left_numbers);
	bubble_sort(right_numbers);

	int dist{ 0 };
	int n = left_numbers.size();
	for (int i = 0; i < n; i++)
	{
		dist += std::abs(right_numbers[i] - left_numbers[i]);
	}
	std::cout << "Total distance: " << dist;
}