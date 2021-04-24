#ifndef IRQ_H
#define IRQ_H

void irq_init_vectors();
void irq_enable();
void irq_disable();

void enable_interrupt_controller();

#endif //IRQ_H
