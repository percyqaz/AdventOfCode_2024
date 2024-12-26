#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

static bool possible(const char* current, std::vector<const char*>& patterns)
{
	if (!*current)
		return true;

	for (const char* p : patterns)
	{
		const char* c = current;
		const char* t = p;
		while (*c && *t)
		{
			if (*c != *t)
				break;
			c++;
			t++;
		}
		if (!*t && possible(c, patterns))
			return true;
	}
	return false;
}

__int64 solution_19_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string first_line;
	std::vector<const char*> patterns;
	std::getline(file, first_line);
	const char* delimiter = ", ";
	char* next_token{ NULL };
	char* t = strtok_s((char*)first_line.c_str(), delimiter, &next_token);
	while (t)
	{
		patterns.push_back(t);
		t = strtok_s(NULL, delimiter, &next_token);
	}
	for (int i = 0; i < patterns.size() - 1; i++)
	{
		if (strlen(patterns[i]) < strlen(patterns[i + 1]))
		{
			std::swap(patterns[i], patterns[i + 1]);
			i = -1;
		}
	}
	std::string line;
	std::getline(file, line);
	__int64 possibles{ 0 };
	while (std::getline(file, line))
	{
		const char* c = line.c_str();
		if (possible(c, patterns))
			possibles++;
	}
	return possibles;
}