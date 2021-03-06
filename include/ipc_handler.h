#pragma once

/*
 *   This file is part of fastboot 3DS
 *   Copyright (C) 2017 derrek, profi200
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "types.h"


#define IPC_MAX_PARAMS              (15)
#define IPC_CMD_ID_MASK(cmd)        ((cmd)>>24)
#define IPC_CMD_IN_BUFS_MASK(cmd)   ((cmd)>>20 & 0xFu)
#define IPC_CMD_OUT_BUFS_MASK(cmd)  ((cmd)>>16 & 0xFu)
#define IPC_CMD_PARAMS_MASK(cmd)    ((cmd)>>12 & 0xFu)


#define CMD_ID(id)       ((id)<<24)
#define CMD_IN_BUFS(n)   ((n)<<20)
#define CMD_OUT_BUFS(n)  ((n)<<16)
#define CMD_PARAMS(n)    ((n)<<12)

typedef enum
{
	IPC_CMD9_FMOUNT              = CMD_ID(0)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FUNMOUNT            = CMD_ID(1)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FIS_DRIVE_MOUNTED   = CMD_ID(2)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FGETFREE            = CMD_ID(3)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(1)  | CMD_PARAMS(1),
	IPC_CMD9_FGET_DEV_SIZE       = CMD_ID(4)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FIS_DEV_ACTIVE      = CMD_ID(5)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FPREP_RAW_ACCESS    = CMD_ID(6)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FFINAL_RAW_ACCESS   = CMD_ID(7)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FCREATE_DEV_BUF     = CMD_ID(8)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FFREE_DEV_BUF       = CMD_ID(9)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FREAD_TO_DEV_BUF    = CMD_ID(10) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(4),
	IPC_CMD9_FWRITE_FROM_DEV_BUF = CMD_ID(11) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(4),
	IPC_CMD9_FOPEN               = CMD_ID(12) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FREAD               = CMD_ID(13) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(1)  | CMD_PARAMS(1),
	IPC_CMD9_FWRITE              = CMD_ID(14) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FSYNC               = CMD_ID(15) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FLSEEK              = CMD_ID(16) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(2),
	IPC_CMD9_FTELL               = CMD_ID(17) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FSIZE               = CMD_ID(18) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FCLOSE              = CMD_ID(19) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FEXPAND             = CMD_ID(20) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(2),
	IPC_CMD9_FSTAT               = CMD_ID(21) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(1)  | CMD_PARAMS(0),
	IPC_CMD9_FOPEN_DIR           = CMD_ID(22) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_FREAD_DIR           = CMD_ID(23) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(1)  | CMD_PARAMS(2),
	IPC_CMD9_FCLOSE_DIR          = CMD_ID(24) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FMKDIR              = CMD_ID(25) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_FRENAME             = CMD_ID(26) | CMD_IN_BUFS(2)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_FUNLINK             = CMD_ID(27) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_FVERIFY_NAND_IMG    = CMD_ID(28) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_FSET_NAND_PROT      = CMD_ID(29) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_WRITE_FIRM_PART     = CMD_ID(30) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_LOAD_VERIFY_FIRM    = CMD_ID(31) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(1),
	IPC_CMD9_FIRM_LAUNCH         = CMD_ID(32) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_LOAD_VERIFY_UPDATE  = CMD_ID(33) | CMD_IN_BUFS(1)  | CMD_OUT_BUFS(1)  | CMD_PARAMS(0),
	IPC_CMD9_GET_BOOT_ENV        = CMD_ID(34) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_PREPARE_POWER       = CMD_ID(35) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_PANIC               = CMD_ID(36) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD9_EXCEPTION           = CMD_ID(37) | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0)
} IpcCmd9;

typedef enum
{
	IPC_CMD11_PRINT_MSG        = CMD_ID(0)  | CMD_IN_BUFS(15) | CMD_OUT_BUFS(15) | CMD_PARAMS(15), // Invalid on purpose. Will be decided later.
	IPC_CMD11_PANIC            = CMD_ID(1)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0),
	IPC_CMD11_EXCEPTION        = CMD_ID(2)  | CMD_IN_BUFS(0)  | CMD_OUT_BUFS(0)  | CMD_PARAMS(0)
} IpcCmd11;

#undef CMD_ID
#undef CMD_IN_BUFS
#undef CMD_OUT_BUFS
#undef CMD_PARAMS


typedef struct
{
	void *ptr;
	u32 size;
} IpcBuffer;



u32 IPC_handleCmd(u8 cmdId, u32 inBufs, u32 outBufs, const u32 *const buf);
