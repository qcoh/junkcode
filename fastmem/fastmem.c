// Babby's first fastmem
//
// References:
// 	man pages
// 	https://gist.github.com/fairlight1337/55978671ace2c75020eddbfbdd670221
// 	https://stackoverflow.com/questions/6768426/in-a-signal-handler-how-to-know-where-the-program-is-interrupted

#define _GNU_SOURCE 1

#include <stdio.h>
#include <signal.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <stdint.h>
#include <stdbool.h>

enum {
	PAGE_SIZE = 4096,
};

static uint8_t *ptr = NULL;

extern uint8_t rread();
extern void wwrite();

void sigsegv_handler(int signum, siginfo_t *si, void *mcontext) {
	ucontext_t *context = (ucontext_t*)mcontext;
	const bool isWrite = context->uc_mcontext.gregs[REG_ERR] & 0x2;

	if (isWrite) {
		printf("write occured: %lld\n", context->uc_mcontext.gregs[REG_R9]);
	} else {
		printf("read occured\n");
	}

	context->uc_mcontext.gregs[REG_R9] = 99;
	context->uc_mcontext.gregs[REG_RIP] += 3; // mov r9, [rdi] and mov [rdi], r9 are 3 bytes each
}

int main() {
	struct sigaction action = {0};
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = sigsegv_handler;
	sigaction(SIGSEGV, &action, NULL);

	ptr = mmap(NULL,
		   PAGE_SIZE,
		   PROT_NONE, 
		   MAP_PRIVATE | MAP_ANONYMOUS,
		   -1,
		   0);

	if (ptr == MAP_FAILED) {
		perror("mmap");
		goto finish;
	}

	if (mprotect(ptr, PAGE_SIZE, PROT_NONE) == -1) {
		perror("mprotect");
		goto cleanup;
	}

	uint8_t *addr = ptr + 12;

	printf("%d\n", rread(addr));

	wwrite(addr, 77);

cleanup:
	if (munmap(ptr, PAGE_SIZE) == -1) {
		perror("munmap");
	}

finish:
	printf("goodbye\n");
	return 0;
}
