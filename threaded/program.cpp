#include "program.h"

Program::Program(std::initializer_list<fn> functions)
    : m_functions{std::begin(functions), std::end(functions)} {}

void Program::execute() {
	fn* ptr = &m_functions[0];

	// r15 == address of first function and call it
	asm volatile(
	    "movq %0, %%r15\n"
	    "callq *(%%r15)\n"
	    :
	    : "r"(ptr)
	    : "r15");
}
