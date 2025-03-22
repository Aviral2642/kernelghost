# 🔥 KernelGhost: Hypervisor & eBPF Rootkit Framework

[![License: GPLv3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://github.com/yourusername/kernelghost/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/kernelghost/actions)
[![CodeQL](https://github.com/yourusername/kernelghost/actions/workflows/codeql.yml/badge.svg)](https://github.com/yourusername/kernelghost/actions/workflows/codeql.yml)

**Next-generation offensive security framework combining eBPF stealth and hypervisor-level exploitation**  
*"When userland isn't enough and the kernel isn't safe"*

![KernelGhost Demo](docs/demo.gif)

---

## 📌 Features

### 🕵️‍♂️ Core Capabilities
- **eBPF-Based Rootkit**
  - Process/network hiding via syscall hooking
  - `/proc`/`/sys` filesystem manipulation
  - Anti-forensic BPF verifier bypasses

- **Hypervisor Escapes**
  - KVM/QEMU guest-to-host memory writes
  - Hyper-V VMBus ring buffer exploitation (CVE-2023-XXXX)
  - Nested virtualization attacks

- **Advanced Persistence**
  - UEFI firmware implants via SPI flash
  - Initramfs backdoor injection
  - Cross-VM migration survival

---

### 🛡️ Defense Evasion

| Technique                | Implementation                     | Bypasses            |
|-------------------------|--------------------------------------|---------------------|
| Kernel Symbol Obfuscation | `__ksymtab` modification           | Sysdig, ftrace      |
| Memory Cloaking          | Nested Page Table manipulation      | LiME, Volatility    |
| Cryptographic C2         | AES-256-GCM over DNS-over-HTTPS     | Network IDS         |

---

## 🚀 Quick Start

### 🔧 Prerequisites

```bash
# Ubuntu 22.04+ (Linux kernel ≥5.15)
sudo apt install linux-headers-$(uname -r) clang-15 bpftool qemu-kvm
```

### 🛠️ Installation

```bash
git clone https://github.com/yourusername/kernelghost
cd kernelghost
make all -j$(nproc)
sudo make deploy
```

---

## 🧪 Basic Usage

```python
from ghostctl import Ghost

# Hide process from detection
gh = Ghost()
gh.hide_pid(1337)

# Execute hypervisor escape
if gh.check_hypervisor() == "KVM":
    gh.escape_vm(payload="reverse_shell")
```

---

## 🧩 Examples

### 🔍 Process Ghosting

```bash
# Hide current shell process
./examples/process_ghosting $$

# Verify hiding (should show error)
ps -p $$
```

### 🧨 VM Escape PoC

```bash
# Launch attack on KVM host
./examples/vm_escape_poc --payload host_mem_dump.bin
```

### 🎯 Cobalt Strike Integration

```bash
python examples/cs_integration.py --listen 443 --aes-key $(openssl rand -hex 32)
```

---

## 📚 Documentation

| Document                  | Description                                 |
|--------------------------|---------------------------------------------|
| `TECHNICAL.md`           | Architecture, attack flows, internals       |
| `DEPLOYMENT.md`          | Deployment checklist, OPSEC practices       |
| `ATTACK-matrix.md`       | MITRE ATT&CK Tactics/Techniques Mapping     |

---

## 🛠️ Development

### 🔧 Build Options

```bash
# Build with debug symbols
make DEBUG=1

# Cross-compile for ARM64
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
```

### ✅ Testing

```bash
# Run kernel module tests
make -C tests kunit

# eBPF verifier bypass tests
./tests/verify_bypass.sh
```

---

## 🌟 Roadmap

- ✅ ARM64/M1 Silicon Support (Q4 2024)
- ⏳ Windows Hyper-V Rootkit Module (Q1 2025)
- 🚧 Quantum-Safe C2 Channels (PQ3/TLS1.3+)

---

## ⚠️ Disclaimer

This project is intended for:

- ✅ Authorized red team engagements
- ✅ Academic research on advanced persistence
- ✅ Defensive countermeasure development

> ❗ **Never use this tool for unauthorized access. Developers assume no liability for misuse.**
