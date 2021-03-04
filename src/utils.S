.globl delay
delay:
    subs x0, x0, #1
    bne delay
    ret

.globl put32
put32:
    str w1, [x0]
    ret

.globl get32
get32:
    ldr w0, [x0]
    ret

.globl get_el
get_el:
    /* mrs => Move to ARM register from system coprocessor register */
    mrs x0, CurrentEL
    /* Left shift by two to get actual value */
    lsr x0, x0, #2
    /* return exception level */
    ret
