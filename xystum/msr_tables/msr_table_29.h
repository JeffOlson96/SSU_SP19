/* msr_table_29.h
 *
 * Model-specific registers selected from table 29 of 
 * Volume 4 of Intel's January 2019 Software Developers' Manual
 * (see https://software.intel.com/en-us/articles/intel-sdm).
 *
 * This file has been generated by generate-headers.py.
 * Probably best to make edits there.
 *
 * Columns are:  tag, name, address, table, scope and bitmask.
 */

#ifndef __PERFEVTSEL0
#define __PERFEVTSEL0
_MSR(IA32,PERFEVTSEL0,0x186,29,thread,0x0)
#endif  //__PERFEVTSEL0

#ifndef __PERFEVTSEL1
#define __PERFEVTSEL1
_MSR(IA32,PERFEVTSEL1,0x187,29,thread,0x0)
#endif  //__PERFEVTSEL1

#ifndef __PERFEVTSEL2
#define __PERFEVTSEL2
_MSR(IA32,PERFEVTSEL2,0x188,29,thread,0x0)
#endif  //__PERFEVTSEL2

#ifndef __PERFEVTSEL3
#define __PERFEVTSEL3
_MSR(IA32,PERFEVTSEL3,0x189,29,thread,0x0)
#endif  //__PERFEVTSEL3

#ifndef __PKG_PERF_STATUS
#define __PKG_PERF_STATUS
_MSR(MSR,PKG_PERF_STATUS,0x613,29,package,0x0)
#endif  //__PKG_PERF_STATUS

#ifndef __TURBO_ACTIVATION_RATIO
#define __TURBO_ACTIVATION_RATIO
_MSR(MSR,TURBO_ACTIVATION_RATIO,0x64C,29,package,0x0)
#endif  //__TURBO_ACTIVATION_RATIO

#ifndef __CONFIG_TDP_CONTROL
#define __CONFIG_TDP_CONTROL
_MSR(MSR,CONFIG_TDP_CONTROL,0x64B,29,package,0x0)
#endif  //__CONFIG_TDP_CONTROL

#ifndef __CONFIG_TDP_NOMINAL
#define __CONFIG_TDP_NOMINAL
_MSR(MSR,CONFIG_TDP_NOMINAL,0x648,29,package,0x0)
#endif  //__CONFIG_TDP_NOMINAL

#ifndef __CONFIG_TDP_LEVEL1
#define __CONFIG_TDP_LEVEL1
_MSR(MSR,CONFIG_TDP_LEVEL1,0x649,29,package,0x0)
#endif  //__CONFIG_TDP_LEVEL1

#ifndef __CONFIG_TDP_LEVEL2
#define __CONFIG_TDP_LEVEL2
_MSR(MSR,CONFIG_TDP_LEVEL2,0x64A,29,package,0x0)
#endif  //__CONFIG_TDP_LEVEL2

