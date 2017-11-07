all:
	nasm -f elf64 -F dwarf -g ops.s
	clang++-5.0 -Wall -std=c++1z -g -c program.cpp -o program.o
	clang++-5.0 -Wall -std=c++1z -g -c main.cpp -o main.o
	clang++-5.0 main.o program.o ops.o
	                           
