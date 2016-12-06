#include "types.h"
#include "util.h"
#include "arm11/loader_init.h"
#include "arm11/i2c.h"
#include "gfx.h"
#include "pxi.h"



void turn_off(void)
{
	i2cmcu_lcd_poweroff();
	i2cmcu_lcd_backlight_poweroff();
	for(;;)
	{
		i2c_writeregdata(3, 0x20, 0xff);
		wait(0x200000);
	}
}

int main(void)
{
	bool poweroff_allowed = false;

	hardwareInit();

	gfx_clear_framebufs();

	for(;;)
	{
		bool successFlag;
		u32 cmdCode = PXI_tryRecvWord(&successFlag);

		// process cmd
		if(successFlag)
		{

			switch(cmdCode)
			{
				case PXI_CMD_ENABLE_LCDS:
					gfx_init();
					PXI_sendWord(PXI_RPL_OK);
					break;
				case PXI_CMD_ALLOW_POWER_OFF:
					poweroff_allowed = true;
					break;
				case PXI_CMD_FORBID_POWER_OFF:
					poweroff_allowed = false;
					break;
				case PXI_CMD_POWER_OFF:
					turn_off();
					break;
				case PXI_CMD_FIRM_LAUNCH:
					goto start_firmlaunch;
				default:
					break;
			}
		}

		/* Update state, check for changes */
		u8 hidstate = i2cmcu_readreg_hid();

		if(hidstate & MCU_HID_POWER_BUTTON_PRESSED)
		{
			if(poweroff_allowed)	// direct power off allowed?
				turn_off();
			PXI_trySendWord(PXI_RPL_POWER_PRESSED);
		}

		if(hidstate & MCU_HID_HOME_BUTTON_PRESSED)
			PXI_trySendWord(PXI_RPL_HOME_PRESSED);

		// handle shell state
		if(hidstate & MCU_HID_SHELL_GOT_CLOSED)
			i2cmcu_lcd_poweroff();
		else if(hidstate & MCU_HID_SHELL_GOT_OPENED)
		{
			i2cmcu_lcd_poweron();
			i2cmcu_lcd_backlight_poweron();
		}

		// wait a bit, don't spam the i2c bus
		wait(0x8000);
	}

start_firmlaunch:

/*
	// Turn off LCDs and backlight before FIRM launch.
	i2cmcu_lcd_poweroff();
	i2cmcu_lcd_backlight_poweroff();
*/

	return 0;
}
