#include <iostream>
#include "solutions.h"
#include "helpers.h"

int main()
{
	time_it(solution_01_a, "input/01-example.txt", 11);
	time_it(solution_01_a, "input/01-input.txt", 2196996);
	time_it(solution_01_b, "input/01-example.txt", 31);
	time_it(solution_01_b, "input/01-input.txt", 23655822);

	time_it(solution_02_a, "input/02-example.txt", 2);
	time_it(solution_02_a, "input/02-input.txt", 334);
	time_it(solution_02_b, "input/02-example.txt", 4);
	time_it(solution_02_b, "input/02-input.txt", 400);
}