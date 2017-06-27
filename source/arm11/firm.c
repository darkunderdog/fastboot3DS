#include <stdnoreturn.h>
#include <string.h>
#include "types.h"
#include "mem_map.h"
#include "arm11/start.h"
#include "pxi.h"



void NAKED firmLaunchStub(void)
{
	*((vu32*)A11_FALLBACK_ENTRY) = 0;

	// Answer ARM0
	REG_PXI_SYNC11 = 0; // Disable all IRQs
	while(REG_PXI_CNT11 & PXI_SEND_FIFO_FULL);
	REG_PXI_SEND11 = PXI_RPL_OK;

	// Wait for entry address
	while(REG_PXI_CNT11 & PXI_RECV_FIFO_EMPTY);
	u32 entry = REG_PXI_RECV11;

	// Tell ARM9 we got the entry
	while(REG_PXI_CNT11 & PXI_SEND_FIFO_FULL);
	REG_PXI_SEND11 = PXI_RPL_FIRM_LAUNCH_READY;
	REG_PXI_CNT11 = 0; // Disable PXI

	if(!entry)
	{
		while(!*((vu32*)A11_FALLBACK_ENTRY));
		entry = *((vu32*)A11_FALLBACK_ENTRY);
	}

	((void (*)(void))entry)();
}

noreturn void firm_launch(void)
{
	// Relocate ARM11 stub
	memcpy((void*)A11_STUB_ENTRY, (const void*)firmLaunchStub, A11_STUB_SIZE);

	deinitCpu();

	((void (*)(void))A11_STUB_ENTRY)();
	while(1);
}
