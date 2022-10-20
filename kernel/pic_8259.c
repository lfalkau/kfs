// SPDX-FileCopyrightText: CGL-KFS
// SPDX-License-Identifier: BSD-3-Clause

/* kernel/pic_8259.c
 *
 * Manage Programmable Interrupt Controler.
 *
 * created: 2022/10/19 - mrxx0 <chcoutur@student.42.fr>
 * updated: 2022/10/20 - mrxx0 <chcoutur@student.42.fr>
 */

#include <kernel/pic_8259.h>
#include <kernel/port.h>

/* Set the mask of an IRQ to ignore its request and continue normal operation.
 *
 * */
static void irq_set_mask(uint8_t irq_id) {
    uint16_t port;
    uint8_t value;
 
    if(irq_id < 8) {
        port = PIC1 + 1;
    } else {
        port = PIC2 + 1;
        irq_id -= 8;
    }
    value = port_read(port) | (1 << irq_id);
    port_write(port, value);        
}

/* Clear the mask of an IRQ to be able to handle the interrupt multiple time 
 * (like a key press)
 * */
static void irq_clear_mask(uint8_t irq_id) {
    uint16_t port;
    uint8_t value;
 
    if(irq_id < 8) {
        port = PIC1 + 1;
    } else {
        port = PIC2 + 1;
        irq_id -= 8;
    }
    value = port_read(port) & ~(1 << irq_id);
    port_write(port, value);        
} 

/* Init 8259 PIC by remapping the IRQ id to avoid conflict with CPU interrupts 
 * in protected mode.
 *
 * @arg(pic1, pic2) : 	offset for the PIC1 and PIC2
 * */
void pic_8259_init(int pic1, int pic2)
{
	/* send ICW1 */
	port_write(PIC1_CMD, ICW1);
	port_write(PIC2_CMD, ICW1);
	/* send ICW2 */
	port_write(PIC1_DATA, pic1);
	port_write(PIC2_DATA, pic2);
	/* send ICW3 */
	port_write(PIC1_DATA, 4);
	port_write(PIC2_DATA, 2);
	/* send ICW4 */
	port_write(PIC1_DATA, ICW4);
	port_write(PIC2_DATA, ICW4);
	/* disable IRQs */
	port_write(PIC1_DATA, 0xFF);
	port_write(PIC2_DATA, 0xFF);
	irq_clear_mask(1);
}

/* Indicate the completion of the interrupt processing.
 *
 * @arg(irq_id) : the interrupt we want to indicate the end of processing
 * */
void pic_8259_eoi(uint8_t irq_id)
{
	if (irq_id > 8)
		port_write(PIC2, PIC1);
	port_write(PIC1, PIC1);
}