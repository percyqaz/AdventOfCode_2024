#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

static void pdigit(const char* c, __int64& value)
{
	value *= 10;
	value += *c - '0';
}

static __int64 combo_value(char operand, __int64 reg_a, __int64 reg_b, __int64 reg_c)
{
	switch (operand)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return reg_a;
	case 5:
		return reg_b;
	case 6:
		return reg_c;
	default:
		return -1;
	}
}

enum Opcode
{
	ADV = 0,
	BXL = 1,
	BST = 2,
	JNZ = 3,
	BXC = 4,
	OUT = 5,
	BDV = 6,
	CDV = 7
};

std::string solution_17_a(const char* input)
{
	std::ifstream file(input);
	_ASSERT(file.is_open());
	std::string line;

	__int64 reg_a{ 0 };
	__int64 reg_b{ 0 };
	__int64 reg_c{ 0 };

	std::vector<char> program{};

	std::getline(file, line);
	for (const char* c = line.c_str() + 12; *c; pdigit(c, reg_a), c++);
	std::getline(file, line);
	for (const char* c = line.c_str() + 12; *c; pdigit(c, reg_b), c++);
	std::getline(file, line);
	for (const char* c = line.c_str() + 12; *c; pdigit(c, reg_c), c++);
	std::getline(file, line);
	std::getline(file, line);
	const char* c = line.c_str() + 7;
	do {
		c += 2;
		program.push_back(*c - '0');
	} while (*(c + 1));

	size_t instruction_pointer{ 0 };

	std::vector<char> output_buffer{};

	while (instruction_pointer < program.size())
	{
		char instruction = program[instruction_pointer];
		char operand = program[instruction_pointer + 1];
		switch (instruction)
		{
		case Opcode::ADV:
			reg_a >>= combo_value(operand, reg_a, reg_b, reg_c);
			break;
		case Opcode::BXL:
			reg_b ^= operand;
			break;
		case Opcode::BST:
			reg_b = combo_value(operand, reg_a, reg_b, reg_c) & 0x7;
			break;
		case Opcode::JNZ:
			if (reg_a)
				instruction_pointer = static_cast<__int64>(operand) - 2;
			break;
		case Opcode::BXC:
			reg_b = reg_b ^ reg_c;
			break;
		case Opcode::OUT:
			output_buffer.push_back('0' + (combo_value(operand, reg_a, reg_b, reg_c) & 0x7));
			output_buffer.push_back(',');
			break;
		case Opcode::BDV:
			reg_b = reg_a >> combo_value(operand, reg_a, reg_b, reg_c);
			break;
		case Opcode::CDV:
			reg_c = reg_a >> combo_value(operand, reg_a, reg_b, reg_c);
			break;
		}
		instruction_pointer += 2;
	}

	output_buffer[output_buffer.size() - 1] = NULL;
	return std::string{ &output_buffer[0] };
}