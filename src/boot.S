#include "mm.h"
#include "sysregs.h"

/*
 * mrs => move to arm register from system coprocessor register
 * cbz => compare and branch on zero
 * b   => branch
 *  bl  => branch with link: copies the address of the next instruction into r14 (lr, the link register) and causes a branch to "label"
 * wfe => wait for event
 */

.section ".text.boot"

.globl _start
_start:
    mrs x0, mpidr_el1 /*  move to arm register from system coprocessor register */
    and x0, x0, #0xFF /*  get the cpuid */
    cbz x0, master /*compare and branch on zero: if x0 is zero then jump to master branch */ 
    b proc_hang /* if x0 is not zero, then branch to proc_hand (jump) */ 

master:
    /* Memory management unit disabled EL1 */
    ldr x0, =SCTLR_MMU_DISABLED
    msr sctlr_el1, x0

    /* Hypervisor configuration register, 31. bit is set to enable execution state for EL1 is AArch64 */
    ldr x0, =HCR_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0

    adr x0, el1_entry
    msr elr_el3, x0

    eret

el1_entry:
    adr x0, bss_begin /* get bss_begin address */ 
    adr x1, bss_end /* get bss_end address */ 
    sub x1, x1, x0 /* get the size of this section */ 
    bl memzero /* run memzero on that section (fill bss section with zeros) */

    mov sp, #LOW_MEMORY    /* move stack pointer into low_memory variable */
    bl kernel_main
    b proc_hang

proc_hang:
    wfe /* wait for event */
    b proc_hang
    