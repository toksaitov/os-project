#!/bin/sh

# Start the kernel in QEMU from the ISO image, call `make iso` to generate the ISO image
qemu-system-i386 -cdrom bin/boot.iso
