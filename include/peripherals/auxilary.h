#ifndef AUXILARY_H
#define AUXILARY_H

#include "common.h"
#include "peripherals/base.h"

//BCM2835 ARM Peripherals, Page 8
struct AuxRegs {
    reg32 aux_irq;          // Auxilary Interrupt Status
    reg32 aux_enables;      // Auxilary enables
    reg32 reserved[14];     // 
    reg32 aux_mu_io_reg;    // Mini Uart I/o Data
    reg32 aux_mu_ier_reg;   // Mini Uart Interrupt Enable
    reg32 aux_mu_iir_reg;   // Mini Uart Interrupt Identify
    reg32 aux_mu_lcr_reg;   // Mini Uart Line Control
    reg32 aux_mu_mcr_reg;   // Mini Uart Modem Control
    reg32 aux_mu_lsr_reg;   // Mini Uart Line Status
    reg32 aux_mu_msr_reg;   // Mini Uart Modem Status
    reg32 aux_mu_scratch;   // Mini Uart Scratch
    reg32 aux_mu_cntl_reg;  // Mini Uart Extra Control
    reg32 aux_mu_stat_reg;  // Mini Uart Extra Status
    reg32 aux_mu_baud_reg;  // Mini Uart Baudrate
};

#define REGS_AUX ((struct AuxRegs*)(PBASE + 0x00215000))

#endif //AUXILARY_H
