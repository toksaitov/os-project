#ifndef _PIC_H_
#define _PIC_H_

#include "kio.h"

/*
 * Initializes the Programmable Interrupt Controller (PIC).
 */
void init_pic(void);

/*
 * Sends an EOI (End Of Interrupt) signal to the master PIC.
 */
void reset_master_pic(void);

/*
 * Sends an EOI (End Of Interrupt) signal to the slave PIC.
 */
void reset_slave_pic(void);

#endif
