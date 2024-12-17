#pragma once

#include <iostream>

void time_it(__int64(*func)(const char*), const char* input, __int64 expected_result);
void time_it(std::string(*func)(const char*), const char* input, const std::string expected_result);