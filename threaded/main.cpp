#include <iostream>

#include "program.h"

extern "C" {
void HW();
void EXIT();
}

int main() {
	Program program{HW, HW, EXIT};
	program.execute();

	std::cout << "I would be pleasantly surprised if this works\n";
}
