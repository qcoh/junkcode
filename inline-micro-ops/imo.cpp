#include <iostream>

using u8 = unsigned char;

struct cpu {
	u8 a{0};
	u8 b{0};

	u8 scratch{0};

	u8 mmu[512]{0};
};

template <typename... Ops>
struct Instruction {
	static void invoke(cpu& c) noexcept {
		(Ops::invoke(c), ...);
	}
};

struct FetchLocA {
	inline static void invoke(cpu& c) noexcept {
		c.scratch = c.mmu[c.a];
	}
};

struct Inc {
	inline static void invoke(cpu& c) noexcept {
		c.scratch++;
	}
};

struct StoreLocA {
	inline static void invoke(cpu& c) noexcept {
		c.mmu[c.a] = c.scratch;
	}
};

using IncAtA = Instruction<FetchLocA, Inc, StoreLocA>;

int main(int argc, char *argv[]) {
	cpu c;
	c.mmu[0] = reinterpret_cast<u8*>(argv[0])[0];

	IncAtA::invoke(c);
	std::cout << +c.mmu[0] << '\n';
}
