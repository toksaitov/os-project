#ifndef _KBD_H_
#define _KBD_H_

#include "isr.h"
#include "kio.h"

#include "lib/kint.h"
#include "lib/kdef.h"

extern uint8_t EN_us[128];

void init_keyboard(void);

#endif
