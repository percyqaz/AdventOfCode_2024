#include <iostream>
#include "solutions.h"
#include "helpers.h"

int main()
{
	time_it(solution_11_a, "input/11-example.txt", 55312);
	time_it(solution_11_a, "input/11-input.txt", 187738);

	time_it(solution_11_b, "input/11-input.txt", 223767210249237);
	std::cout << std::endl;

	time_it(solution_10_a, "input/10-example.txt", 36);
	time_it(solution_10_a, "input/10-input.txt", 776);
	time_it(solution_10_b, "input/10-example.txt", 81);
	time_it(solution_10_b, "input/10-input.txt", 1657);
	std::cout << std::endl;

	time_it(solution_09_a, "input/09-example.txt", 1928);
	time_it(solution_09_a, "input/09-input.txt", 6384282079460);
	time_it(solution_09_b, "input/09-example.txt", 2858);
	time_it(solution_09_b, "input/09-input.txt", 6408966547049);
	std::cout << std::endl;

	time_it(solution_08_a, "input/08-example.txt", 14);
	time_it(solution_08_a, "input/08-input.txt", 291);
	time_it(solution_08_b, "input/08-example.txt", 34);
	time_it(solution_08_b, "input/08-input.txt", 1015);
	std::cout << std::endl;

	time_it(solution_07_a, "input/07-example.txt", 3749);
	time_it(solution_07_a, "input/07-input.txt", 1708857123053);
	time_it(solution_07_b, "input/07-example.txt", 11387);
	time_it(solution_07_b, "input/07-input.txt", 189207836795655);
	std::cout << std::endl;

	time_it(solution_06_a, "input/06-example.txt", 41);
	time_it(solution_06_a, "input/06-input.txt", 5329);
	time_it(solution_06_b, "input/06-example.txt", 6);
	time_it(solution_06_b, "input/06-input.txt", 2162);
	std::cout << std::endl;

	time_it(solution_05_a, "input/05-example.txt", 143);
	time_it(solution_05_a, "input/05-input.txt", 5509);
	time_it(solution_05_b, "input/05-example.txt", 123);
	time_it(solution_05_b, "input/05-input.txt", 4407);
	std::cout << std::endl;

	time_it(solution_04_a, "input/04-example.txt", 18);
	time_it(solution_04_a, "input/04-input.txt", 2593);
	time_it(solution_04_b, "input/04-example.txt", 9);
	time_it(solution_04_b, "input/04-input.txt", 1950);
	std::cout << std::endl;

	time_it(solution_03_a, "input/03-example.txt", 161);
	time_it(solution_03_a, "input/03-input.txt", 189600467);
	time_it(solution_03_b, "input/03-example.txt", 48);
	time_it(solution_03_b, "input/03-input.txt", 107069718);
	std::cout << std::endl;

	time_it(solution_02_a, "input/02-example.txt", 2);
	time_it(solution_02_a, "input/02-input.txt", 334);
	time_it(solution_02_b, "input/02-example.txt", 4);
	time_it(solution_02_b, "input/02-input.txt", 400);
	std::cout << std::endl;

	time_it(solution_01_a, "input/01-example.txt", 11);
	time_it(solution_01_a, "input/01-input.txt", 2196996);
	time_it(solution_01_b, "input/01-example.txt", 31);
	time_it(solution_01_b, "input/01-input.txt", 23655822);
	std::cout << std::endl;
}