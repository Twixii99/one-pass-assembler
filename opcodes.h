#ifndef OPCODES_H
#define OPCODES_H

#include <string>
class Opcodes {
	private:
		static Opcodes* unique;
		Opcodes();
		void fill_optable();
	public:
		std::string getopcode(std::string);
		static Opcodes* getInstance();
};

#endif