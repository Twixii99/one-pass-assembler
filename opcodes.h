#ifndef OPCODES_H
#define OPCODES_H

#include <string>
class Opcodes {
	void fill_optable();
	public:
		Opcodes();
		std::string getopcode(std::string);
};

#endif