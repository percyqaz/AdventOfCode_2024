#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>

__int64 solution_09_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	std::getline(file, line);
	auto drive = std::vector<int>();
	const char* c{ line.c_str() };
	char d{};
	bool represents_free{ false };
	int file_id{ 1 };
	while (*c)
	{
		d = *c - '0';
		if (represents_free) {
			while (d)
			{
				drive.push_back(NULL);
				d--;
			}
		}
		else
		{
			while (d)
			{
				drive.push_back(file_id);
				d--;
			}
			file_id++;
		}
		represents_free = !represents_free;
		c++;
	}
	__int64 checksum{ 0 };
	size_t left{ 0 };
	size_t right{ drive.size() - 1 };

	while (left < right) {
		for (; drive[left]; checksum += left * (drive[left] - 1), left++);
		for (; !drive[right]; right--);
		std::swap(drive[left], drive[right]);
	}
	return checksum;
}