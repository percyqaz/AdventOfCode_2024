#include <iostream>
#include <fstream>
#include <sstream>

// is entire remainder of this stream safe
bool is_safe_part_1(std::istringstream& iss)
{
	int a, b{};
	iss >> std::ws >> a >> b;
	if (a == b || std::abs(a - b) > 3)
	{
		return false;
	}
	int next{};
	while (iss >> next)
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			return false;
		}
		b = next;
	}
	return true;
}

// is this stream safe except second number
bool is_safe_bug_fix(std::istringstream& iss)
{
	int a, b{};
	int discard_second;
	iss >> std::ws >> a >> discard_second >> b;
	if (a == b || std::abs(a - b) > 3)
	{
		return false;
	}
	int next{};
	while (iss >> next)
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			return false;
		}
		b = next;
	}
	return true;
}

// is this report safe with a skip allowed
bool is_safe_part_2(std::istringstream& iss)
{
	int a, b{};
	iss >> a >> b;
	bool used_skip{ false };
	if (a == b || std::abs(a - b) > 3)
	{
		used_skip = true;
		iss >> b;
		if (a == b || std::abs(a - b) > 3)
		{
			return false;
		}
	}
	int next{};
	while (iss >> next)
	{
		if (
			(b > a && (next - b < 1 || next - b > 3))
			|| (b < a && (b - next < 1 || b - next > 3))
			)
		{
			if (!used_skip)
			{
				used_skip = true;
				continue;
			}
			return false;
		}
		b = next;
	}
	return true;
}

__int64 solution_02_b(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	int safe{ 0 };
	int discard_first;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::istringstream iss2(line);
		std::istringstream with_first_removed(line);
		with_first_removed >> discard_first;
		if (is_safe_part_2(iss) || is_safe_part_1(with_first_removed) || is_safe_bug_fix(iss2))
		{
			safe++;
		}
	}
	return safe;
}