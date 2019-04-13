/* msr_table_45.h
 *
 * Model-specific registers selected from table 45 of 
 * Volume 4 of Intel's January 2019 Software Developers' Manual
 * (see https://software.intel.com/en-us/articles/intel-sdm).
 *
 * This file has been generated by generate-headers.py.
 * Probably best to make edits there.
 *
 * Columns are:  tag, name, address, table, scope and bitmask.
 */

#ifndef __DRAM_ENERGY_STATUS
#define __DRAM_ENERGY_STATUS
_MSR(MSR,DRAM_ENERGY_STATUS,0x619,45,package,MASK_RANGE_64(31,0))
#endif  //__DRAM_ENERGY_STATUS

#ifndef __DRAM_PERF_STATUS
#define __DRAM_PERF_STATUS
_MSR(MSR,DRAM_PERF_STATUS,0x61B,45,package,0x0)
#endif  //__DRAM_PERF_STATUS

#ifndef __DRAM_POWER_INFO
#define __DRAM_POWER_INFO
_MSR(MSR,DRAM_POWER_INFO,0x61C,45,package,0x0)
#endif  //__DRAM_POWER_INFO

#ifndef __DRAM_POWER_LIMIT
#define __DRAM_POWER_LIMIT
_MSR(MSR,DRAM_POWER_LIMIT,0x618,45,package,0x0)
#endif  //__DRAM_POWER_LIMIT

#ifndef __PKG_CST_CONFIG_CONTROL
#define __PKG_CST_CONFIG_CONTROL
_MSR(MSR,PKG_CST_CONFIG_CONTROL,0x0E2,45,core,0x0)
#endif  //__PKG_CST_CONFIG_CONTROL

#ifndef __PLATFORM_INFO
#define __PLATFORM_INFO
_MSR(MSR,PLATFORM_INFO,0x0CE,45,package,0x0)
#endif  //__PLATFORM_INFO

#ifndef __PP0_ENERGY_STATUS
#define __PP0_ENERGY_STATUS
_MSR(MSR,PP0_ENERGY_STATUS,0x639,45,package,0x0)
#endif  //__PP0_ENERGY_STATUS

#ifndef __RAPL_POWER_UNIT
#define __RAPL_POWER_UNIT
_MSR(MSR,RAPL_POWER_UNIT,0x606,45,package,0x0)
#endif  //__RAPL_POWER_UNIT

#ifndef __PPIN_CTL
#define __PPIN_CTL
_MSR(MSR,PPIN_CTL,0x04E,45,package,0x0)
#endif  //__PPIN_CTL

#ifndef __PPIN
#define __PPIN
_MSR(MSR,PPIN,0x04F,45,package,0x0)
#endif  //__PPIN

#ifndef __THERM_STATUS
#define __THERM_STATUS
_MSR(IA32,THERM_STATUS,0x19C,45,core,0x0)
#endif  //__THERM_STATUS

#ifndef __TEMPERATURE_TARGET
#define __TEMPERATURE_TARGET
_MSR(MSR,TEMPERATURE_TARGET,0x1A2,45,package,0x0)
#endif  //__TEMPERATURE_TARGET

#ifndef __TURBO_RATIO_LIMIT
#define __TURBO_RATIO_LIMIT
_MSR(MSR,TURBO_RATIO_LIMIT,0x1AD,45,package,0x0)
#endif  //__TURBO_RATIO_LIMIT

#ifndef __TURBO_RATIO_LIMIT_CORES
#define __TURBO_RATIO_LIMIT_CORES
_MSR(MSR,TURBO_RATIO_LIMIT_CORES,0x1AE,45,package,0x0)
#endif  //__TURBO_RATIO_LIMIT_CORES

#ifndef __UNCORE_RATIO_LIMIT
#define __UNCORE_RATIO_LIMIT
_MSR(MSR,UNCORE_RATIO_LIMIT,0x620,45,package,0x0)
#endif  //__UNCORE_RATIO_LIMIT
