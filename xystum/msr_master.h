/* msr_master.h 
 *
 * Intel arranges MSRs into tables (see volume 4 of the SDM).  Each architecture
 * can refer to multiple tables.  Each table can be used in multiple architectures.
 * MSRs are not necessarily defined only in one table; where this happens, the 
 * last (highest-numbered) table is correct.
 *
 * To avoid massive code duplication, we duplicate this organization here.
 * Each of the MSR table files referenced below contains a set of _MSR macros
 * describing the MSRs in that table.  The _MSR macros have #ifndef guards
 * so that if a particular MSR is defined in multiple tables, only the 
 * first one is used.  Thus, when adding a new architecture, be sure to 
 * put the #includes in decreasing order by table number.
 *
 * The _MSR macros are used in several places in msr_derived.h, and so
 * the msr_undefs.h file in included at the end to reset all of the guard
 * conditions.  Both the table files and msr_undefs.h are generated 
 * automatically by generate-headers.py.
 *
 * Note that table numbering can change as Intel updates volume 4.  This
 * set of files refers to the January 2019 edition.  (Most of the problem
 * comes from new Intel Atom architectures being added in the middle.)
 *
 * Intel does not provide an architecture-to-tables mapping.  What follows
 * in this file is my interpretation of the table descriptions from volume
 * four.  While I have exercised due care, volume 4 itself is canonical.
 *
 * The fact that a particular MSR is given in a table does not guarantee
 * that MSR is available on the processor you purchased.  Firmware can 
 * disable arbitrary MSRs, there may be errors in Intel's documentation.
 * Per-architecture errors should be corrected here, per-table errors
 * should be corrected in generate-headers.py.  For example, Table 39
 * describes several MSRs that should be present on an 06_55h, but are
 * not on our local system.  By #defining those MSRs here we prevent
 * the corresponding _MSR macros from being picked up.
 *
 * The architectures are listed in the order they are introduced in 
 * volume four.  This may not be optimal.
 */


#ifdef 	ARCH_06_0F			// Intel Core microarchitecture
#include "msr_table_03.h"	

#elif defined	ARCH_06_17		// Enhanced Intel Core micorarchitecture
#include "msr_table_03.h"	

#elif defined	ARCH_06_1C		// 45 nm and 32 nm Atom processors	
#include "msr_table_04.h"	

#elif defined	ARCH_06_26		// 45 nm and 32 nm Atom processors	
#include "msr_table_04.h"	

#elif defined	ARCH_06_27		// 45 nm and 32 nm Atom processors	
#include "msr_table_05.h"	
#include "msr_table_04.h"	

#elif defined	ARCH_06_35		// 45 nm and 32 nm Atom processors	
#include "msr_table_04.h"	

#elif defined	ARCH_06_36		// 45 nm and 32 nm Atom processors	
#include "msr_table_04.h"	

#elif defined	ARCH_06_37		// Silvermont
#include "msr_table_09.h"	
#include "msr_table_08.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_4A		// Silvermont
#include "msr_table_08.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_4D		// Silvermont
#include "msr_table_10.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_5A		// Silvermont
#include "msr_table_08.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_5D		// Silvermont
#include "msr_table_08.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_4C		// Airmont
#include "msr_table_11.h"	
#include "msr_table_08.h"	
#include "msr_table_07.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_5C		// Goldmont
#include "msr_table_12.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_7A		// Goldmont Plus
#include "msr_table_13.h"	
#include "msr_table_12.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_86		// Tremont
#include "msr_table_14.h"	
#include "msr_table_13.h"	
#include "msr_table_12.h"	
#include "msr_table_06.h"	

#elif defined	ARCH_06_1A		// Nehalem
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_1E		// Nehalem
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_1F		// Nehalem
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_1F		// Nehalem (no msr 0x1AD)
#include "msr_table_17.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_25		// Westmere
#include "msr_table_18.h"	
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_2C		// Westmere
#include "msr_table_18.h"	
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_2F		// Westmere (no msr 0x1AD)
#include "msr_table_19.h"	
#include "msr_table_16.h"	
#include "msr_table_15.h"	

#elif defined	ARCH_06_2A		// Sandy Bridge
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_2D		// Sandy Bridge
#include "msr_table_24.h"	
#include "msr_table_23.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_3A		// Ivy Bridge
#include "msr_table_25.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_3E		// Ivy Bridge-E
#include "msr_table_28.h"	
#include "msr_table_27.h"	
#include "msr_table_26.h"	
#include "msr_table_24.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_3C		// Haswell
#include "msr_table_30.h"	
#include "msr_table_29.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_45		// Haswell
#include "msr_table_31.h"	
#include "msr_table_30.h"	
#include "msr_table_29.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_46		// Haswell
#include "msr_table_30.h"	
#include "msr_table_29.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_3F		// Haswell-E
#include "msr_table_33.h"	
#include "msr_table_32.h"	
#include "msr_table_29.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_3D		// Broadwell
#include "msr_table_35.h"	
#include "msr_table_34.h"	
#include "msr_table_30.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_47		// Broadwell
#include "msr_table_35.h"	
#include "msr_table_34.h"	
#include "msr_table_30.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_22.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_56		// Broadwell
#include "msr_table_37.h"	
#include "msr_table_36.h"	
#include "msr_table_34.h"	
#include "msr_table_29.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_4F		// Broadwell
#include "msr_table_38.h"	
#include "msr_table_36.h"	
#include "msr_table_34.h"	
#include "msr_table_29.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_4E		// Skylake
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_5E		// Skylake
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_55		// Skylake
// The following MSRs are not present based on Rhetoric at LLNL
// The #undefs are handled by generate-headers.h.
// rountree@llnl.gov
#define __HWP_CAPABILITIES
#define __HWP_INTERRUPT
#define __HWP_REQUEST
#define __HWP_REQUEST_PKG
#define __HWP_STATUS
#define __CORE_HDC_RESIDENCY
#define __PKG_HDC_CONFIG
#define __PKG_HDC_CTL
#define __PKG_HDC_DEEP_RESIDENCY
#define __PKG_HDC_SHALLOW_RESIDENCY
#define __PLATFORM_ENERGY_COUNTER
#define __PLATFORM_POWER_LIMIT
#define __PM_CTL1
#define __PP0_POLICY
#define __PP1_ENERGY_STATUS
#define __PP1_POLICY
#define __PP1_POWER_LIMIT
#define __THREAD_STALL
#define __WEIGHTED_CORE_C0
#define __PERFEVTSEL4
#define __PERFEVTSEL5
#define __PERFEVTSEL6
#define __PERFEVTSEL7
#define __PMC4
#define __PMC5
#define __PMC6
#define __PMC7
#include "msr_table_45.h"	
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_8E		// Coffee/Kaby Lake
#include "msr_table_41.h"	
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_9E		// Coffee/Kaby Lake
#include "msr_table_41.h"	
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_66		// Cannon Lake
#include "msr_table_43.h"	
#include "msr_table_42.h"	
#include "msr_table_40.h"	
#include "msr_table_39.h"	
#include "msr_table_35.h"	
#include "msr_table_29.h"	
#include "msr_table_25.h"	
#include "msr_table_21.h"	
#include "msr_table_20.h"	

#elif defined	ARCH_06_57		// Knights Landing
#include "msr_table_46.h"	

#elif defined	ARCH_06_85		// Knights Mill
#include "msr_table_47.h"	
#include "msr_table_46.h"	
#endif

#include "msr_undefs.h"
