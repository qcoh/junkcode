#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>

struct Asm {
	template <typename T>
	Asm& operator|(const T& op) {
		op.emit();
		return *this;
	}
};

template <uint8_t... Bytes>
class Op {
private:
	using array_type = std::array<uint8_t, sizeof...(Bytes)>;

public:
	static void emit() {
		array_type arr{{Bytes...}};

		std::cout << '\t' << std::hex << std::setw(2);
		std::copy(std::cbegin(arr), std::cend(arr),
			  std::ostream_iterator<int>(std::cout));
		std::cout << '\n';
	}

	template <uint8_t... WithArgBytes>
	class WithArg {
	private:
		using with_arg_array_type =
		    std::array<uint8_t, sizeof...(WithArgBytes)>;

	public:
		static void emit() {
			array_type arr{{Bytes...}};
			with_arg_array_type with_arg_arr{{WithArgBytes...}};

			std::cout << '\t' << std::hex << std::setw(2);
			std::copy(std::cbegin(arr), std::cend(arr),
				  std::ostream_iterator<int>(std::cout));
			std::copy(std::cbegin(with_arg_arr),
				  std::cend(with_arg_arr),
				  std::ostream_iterator<int>(std::cout));
			std::cout << '\n';
		}
	};
};

using nop = Op<0x90U>;

using inc = Op<0xffU>;

int main() {
	Asm assembler;
	assembler
	| nop{}
	| nop{}
	| inc::WithArg<0xc0U>{};
}
