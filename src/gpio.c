#include "gpio.h"
#include "utils.h"

void gpio_pin_set_func(u8 pinNumber, GpioFunc func){
    u8 bitStart = (pinNumber * 3) % 30;
    u8 reg = pinNumber / 10;
    u32 selector = REGS_GPIO->func_select[reg];
    selector &= ~(7 << bitStart);
    selector |= (func << bitStart);

    REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pinNumber){
    //BCM2835 ARM Peripherals, Page 101

    /* Write to GPPUD to set the required control signal (i.e. Pull-up or Pull-Down or neither
     * to remove the current Pull-up/down) */
    REGS_GPIO->pupd_enable = 0;

    /* Wait 150 cycles – this provides the required set-up time for the control signal */
    delay(150);

    /* Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you wish to
     * modify – NOTE only the pads which receive a clock will be modified, all others will
     * retain their previous state. */
    REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 1 << (pinNumber % 32);

    /* Wait 150 cycles – this provides the required hold time for the control signal */
    delay(150);

    /* Write to GPPUD to remove the control signal */
    REGS_GPIO->pupd_enable = 0;

    /* Write to GPPUDCLK0/1 to remove the clock */
    REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 0;
}