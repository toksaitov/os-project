#ifndef _PIT_H_
#define _PIT_H_

#include "isr.h"

#include "lib/kint.h"
#include "kio.h"

/*
 * Initializes the Programmable Interval Timer (PIT) with a specific
 * update frequency.
 */
void init_pit(uint32_t frequency);

#endif
