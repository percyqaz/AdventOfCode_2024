#include <iostream>
#include <fstream>
#include <regex>

__int64 solution_03_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;
	std::regex r("mul\\((\\d{1,3}),(\\d{1,3})\\)");
	std::smatch sm;
	__int64 total{ 0 };
	while (std::getline(file, line))
	{
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), r);
		auto words_end = std::sregex_iterator();
		for (std::regex_iterator i = words_begin; i != words_end; i++)
		{
			sm = *i;
			total += std::stoi(sm[1]) * std::stoi(sm[2]);
		}
	}
	return total;
}