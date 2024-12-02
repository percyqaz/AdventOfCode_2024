#include <iostream>
#include <fstream>
#include <sstream>

__int64 solution_02_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	int safe{ 0 };
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int a, b{};
		iss >> std::ws >> a >> b;
		if (a == b || std::abs(a - b) > 3)
		{
			continue;
		}
		safe++;
		int next{};
		while (iss >> next)
		{
			if (
				(b > a && (next - b < 1 || next - b > 3))
				|| (b < a && (b - next < 1 || b - next > 3))
				)
			{
				safe--;
				break;
			}
			b = next;
		}
	}
	return safe;
}