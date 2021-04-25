#include "gpio.h"
#include "utils.h"
#include "peripherals/auxilary.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init()
{
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    REGS_AUX->aux_enables = 1;
    REGS_AUX->aux_mu_cntl_reg = 0;
    REGS_AUX->aux_mu_ier_reg = 0xD;
    REGS_AUX->aux_mu_lcr_reg = 3;
    REGS_AUX->aux_mu_mcr_reg = 0;

#if RPI_VERSION == 3
    // BCM2835 ARM Peripherals, Page 11

    REGS_AUX->aux_mu_baud_reg = 270; // = 115200 @ 250 MHz
#endif

#if RPI_VERSION == 4
    // BCM2835 ARM Peripherals, Page 11

    REGS_AUX->aux_mu_baud_reg = 541; // = 115200 @ 500 MHz
#endif

    REGS_AUX->aux_mu_cntl_reg = 3;
    uart_send('\r');
    uart_send('\n');
    uart_send('\n');
}

void uart_send(char c){
    // BCM2835 ARM Peripherals, Page 15
    // If AUX_MU_LSR_REG Bit 5 is set, transmit FIFO can accept at least one byte
    // Wait until it is available

    // & 0x20 gives 5th bit
    while (!(REGS_AUX->aux_mu_lsr_reg & 0x20));

    REGS_AUX->aux_mu_io_reg = c;   
}

char uart_recv(){
    // BCM2835 ARM Peripherals, Page 15
    // Check AUX_MU_LSR_REG bit 0 is set (data ready)
    while (!(REGS_AUX->aux_mu_lsr_reg & 1));

    return REGS_AUX->aux_mu_io_reg & 0xFF;
}

void uart_send_string(char *str){
    while(*str){
        if (*str == '\n'){
            uart_send('\r');
        }

        uart_send(*str);
        str++;
    }
}
