#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "utils.h"

void putc(void *p, char c) {
    if (c == '\n') {
        uart_send('\r');
    }

    uart_send(c);
}

void kernel_main() {
    uart_init();
    init_printf(0, putc);
    printf("yaezOS initializing...\n");

#if RPI_VERSION == 3
    printf("\t Board: Raspberry PI 3\n");
#endif

#if RPI_VERSION == 4
    printf("\t Board: Raspberry PI 4\n");
#endif

    printf("\nException level: %d\n", get_el());
    while (1){
        uart_send(uart_recv());
    }
}