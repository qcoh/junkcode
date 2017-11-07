#pragma once

#include <initializer_list>
#include <vector>

#include "types.h"

class Program {
public:
	Program(std::initializer_list<fn>);
	void execute();

private:
	std::vector<fn> m_functions;
};
