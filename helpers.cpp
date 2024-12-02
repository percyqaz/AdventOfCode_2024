#include "helpers.h"
#include <iostream>
#include <chrono>

void time_it(__int64(*func)(const char*), const char* input, __int64 expected_result)
{
	auto before{ std::chrono::high_resolution_clock::now() };
	__int64 result{ func(input) };
	auto after{ std::chrono::high_resolution_clock::now() };
	std::chrono::duration<double, std::milli> ms = after - before;
	if (result == expected_result)
	{
		std::cout << ms.count() << "ms to find correct solution (" << result << ") for " << input << "\n";
	}
	else
	{
		std::cout << ms.count() << "ms to find wrong answer (" << result << ", expected " << expected_result << ") for " << input << "\n";
	}
}