#include "peripherals/timer.h"
#include "peripherals/irq.h"
#include "peripherals/auxilary.h"
#include "printf.h"

const u32 interval = CLOCK_HZ; // Every 1 sec
u32 current_val_0 = 0;
u32 current_val_3 = 0;

void timer_init()
{
    // Set timer 0 for every 1 sec
    current_val_0 = REGS_TIMER->counter_lo;
    current_val_0 += interval;
    REGS_TIMER->compare[1] = current_val_0;

    // Set timer 3 for every 3 sec
    current_val_3 = REGS_TIMER->counter_lo;
    current_val_3 += interval * 3;
    REGS_TIMER->compare[3] = current_val_3;
}

void handle_timer_1()
{
    // Set timer for every 1 sec
    current_val_0 += interval;
    REGS_TIMER->compare[1] = current_val_0;
    REGS_TIMER->control_status |= TIMER_IRQ_1;

    printf("Timer 1 received\n");
}

void handle_timer_3()
{
    // Set timer for every 3 sec
    current_val_3 += interval * 3;
    REGS_TIMER->compare[3] = current_val_3;
    REGS_TIMER->control_status |= TIMER_IRQ_3;

    printf("Timer 3 received\n");
}


