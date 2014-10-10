/******************************************************************************\
* Project:  Module Subsystem Interface to SP Interpreter Core                  *
* Authors:  Iconoclast                                                         *
* Release:  2014.10.10                                                         *
* License:  CC0 Public Domain Dedication                                       *
*                                                                              *
* To the extent possible under law, the author(s) have dedicated all copyright *
* and related and neighboring rights to this software to the public domain     *
* worldwide. This software is distributed without any warranty.                *
*                                                                              *
* You should have received a copy of the CC0 Public Domain Dedication along    *
* with this software.                                                          *
* If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.             *
\******************************************************************************/

#ifndef _MODULE_H_
#define _MODULE_H_

#include "my_types.h"

#include "Rsp_#1.1.h"

#define CFG_FILE    "rsp_conf.cfg"

/*
 * Most of the point behind this config system is to let users use HLE video
 * or audio plug-ins.  The other task types are used less than 1% of the time
 * and only in a few games.  They require simulation from within the RSP
 * internally, which I have no intention to ever support.  Some good research
 * on a few of these special task types was done by Hacktarux in the MUPEN64
 * HLE RSP plug-in, so consider using that instead for complete HLE.
 */
#define CFG_HLE_GFX     (conf[0x00])
#define CFG_HLE_AUD     (conf[0x01])
#define CFG_HLE_VID     (conf[0x02]) /* reserved/unused */
#define CFG_HLE_JPG     (conf[0x03]) /* unused */

/*
 * Schedule binary dump exports to the DllConfig schedule delay queue.
 */
#define CFG_QUEUE_E_DRAM    (*(int *)(conf + 0x04))
#define CFG_QUEUE_E_DMEM    (*(int *)(conf + 0x08))
#define CFG_QUEUE_E_IMEM    (*(int *)(conf + 0x0C))
/*
 * Note:  This never actually made it into the configuration system.
 * Instead, DMEM and IMEM are always exported on every call to DllConfig().
 */

/*
 * Special switches.
 * (generally for correcting RSP clock behavior on Project64 2.x)
 * Also includes RSP register states debugger.
 */
#define CFG_WAIT_FOR_CPU_HOST       (*(int *)(conf + 0x10))
#define CFG_MEND_SEMAPHORE_LOCK     (*(int *)(conf + 0x14))
#define CFG_TRACE_RSP_REGISTERS     (*(int *)(conf + 0x18))

/*
 * Update RSP configuration memory from local file resource.
 */
#define CHARACTERS_PER_LINE     (80)
/* typical standard DOS text file limit per line */

NOINLINE extern void update_conf(const char* source);

NOINLINE extern void export_data_cache(void);
NOINLINE extern void export_instruction_cache(void);

NOINLINE extern void message(const char* body);

#ifdef SP_EXECUTE_LOG
static FILE *output_log;
extern void step_SP_commands(u32 inst);
#endif
extern void export_SP_memory(void);

#endif