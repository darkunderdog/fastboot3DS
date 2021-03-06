#pragma once

/*
 * This code is part of ctrulib (https://github.com/smealum/ctrulib)
 */

#include "types.h"


#define HID_KEY_MASK_ALL          ((KEY_Y << 1) - 1)
#define HID_VERBOSE_MODE_BUTTONS  (KEY_SELECT | KEY_START)

enum
{
	KEY_A       = (1),
	KEY_B       = (1<<1),
	KEY_SELECT  = (1<<2),
	KEY_START   = (1<<3),
	KEY_DRIGHT  = (1<<4),
	KEY_DLEFT   = (1<<5),
	KEY_DUP     = (1<<6),
	KEY_DDOWN   = (1<<7),
	KEY_R       = (1<<8),
	KEY_L       = (1<<9),
	KEY_X       = (1<<10),
	KEY_Y       = (1<<11)
};



void hidScanInput(void);
u32 hidKeysHeld(void);
u32 hidKeysDown(void);
u32 hidKeysUp(void);
