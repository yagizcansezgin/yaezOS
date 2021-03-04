.globl _start
_start:
    /* load location of our kernel */
    ldr w0, kernel_entry32
    /* branch to here */
    br x0

.ltorg

/* .org directive specifies the start address to store the related program/data */
.org 0xf0
.globl stub_magic
stub_magic:
    .word 0x5afe570b

.org 0xf4
.globl stub_version
stub_version:
    .word 0

.org 0xfc
.globl kernel_entry32
kernel_entry32:
    .word 0x0
