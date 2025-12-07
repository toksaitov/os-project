#!/bin/sh

# Start the kernel in QEMU, call `make` to generate the kernel
qemu-system-i386 -kernel kernel
