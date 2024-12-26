#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

static __int64 possibilities(const char* current, std::vector<const char*>& patterns, std::map<const char*, __int64>& memoisation)
{
	if (!*current)
		return 1;

	if (memoisation.contains(current))
		return memoisation[current];

	__int64 ps{ 0 };

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
		if (!*t)
			ps += possibilities(c, patterns, memoisation);
	}

	memoisation[current] = ps;
	return ps;
}

__int64 solution_19_b(const char* input)
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
	std::map<const char*, __int64> memoisation{};
	while (std::getline(file, line))
	{
		const char* c = line.c_str();
		possibles += possibilities(c, patterns, memoisation);
		memoisation.clear();
	}
	return possibles;
}