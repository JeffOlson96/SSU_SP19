#!/usr/bin/python3

m = (
("IA32",	"APERF",	                "0x0E8",	"20",	"thread",	"MASK_RANGE_64(63,0)"),
("MSR",	        "CORE_PERF_LIMIT_REASONS",	"0x64F",	"39",	"package",	"MASK_RANGE_64(29,26) | MASK_RANGE_64(24,20) | MASK_RANGE_64(17,10) | MASK_RANGE_64(8,4) | MASK_RANGE_64(1, 0)"),
("IA32",	"CLOCK_MODULATION",	        "0x19A",	"20",	"thread",	"0x0"),
("MSR",	        "DRAM_ENERGY_STATUS",	        "0x619",	"45",	"package",	"MASK_RANGE_64(31,0)"),
("MSR",	        "DRAM_PERF_STATUS",	        "0x61B",	"45",	"package",	"0x0"),
("MSR",	        "DRAM_POWER_INFO",	        "0x61C",	"45",	"package",	"0x0"),
("MSR",	        "DRAM_POWER_LIMIT",	        "0x618",	"45",	"package",	"0x0"),
("IA32",	"ENERGY_PERF_BIAS",	        "0x1B0",	"20",	"package",	"0x0"),
("IA32",	"FIXED_CTR0",                   "0x309",	"20",	"thread",	"0x0"),
("IA32",	"FIXED_CTR1",                   "0x30A",	"20",	"thread",	"0x0"),
("IA32",	"FIXED_CTR2",                   "0x30B",	"20",	"thread",	"0x0"),
("IA32",	"FIXED_CTR_CTRL",	        "0x38D",	"20",	"thread",	"0x0"),
("IA32",	"MPERF",	                "0x0E7",	"20",	"thread",	"MASK_RANGE_64(63,0)"),
("IA32",	"PACKAGE_THERM_INTERRUPT",	"0x1B2",	"20",	"package",	"0x0"),
("IA32",	"PERF_CTL",	                "0x199",	"20",	"thread",	"MASK_RANGE_64(32,32) | MASK_RANGE_64(15,0)"),
("IA32",	"PERF_GLOBAL_CTRL",             "0x38F",	"20",	"thread",	"0x0"),
("IA32",	"PERF_GLOBAL_STATUS"    ,       "0x38E",	"39",	"thread",	"0x0"),
("IA32",	"PERF_GLOBAL_STATUS_RESET",	"0x390",	"39",	"thread",	"0x0"),
("IA32",	"PERF_GLOBAL_STATUS_SET",	"0x391",	"39",	"thread",	"0x0"),
("IA32",	"PERF_GLOBAL_INUSE",	        "0x392",	"39",	"thread",	"0x0"),
("MSR",	        "PERF_STATUS",                  "0x198",	"20",	"package",	"0x0"),
("IA32",	"PERFEVTSEL0",                  "0x186",	"29",	"thread",	"0x0"),
("IA32",	"PERFEVTSEL1",                  "0x187",	"29",	"thread",	"0x0"),
("IA32",	"PERFEVTSEL2",                  "0x188",	"29",	"thread",	"0x0"),
("IA32",	"PERFEVTSEL3",                  "0x189",	"29",	"thread",	"0x0"),
("MSR",	        "PKG_CST_CONFIG_CONTROL",	"0x0E2",	"45",	"core",	        "0x0"),
("MSR",	        "PKG_ENERGY_STATUS",            "0x611",	"20",	"package",	"MASK_RANGE_64(31,0)"),
("MSR",	        "PKG_PERF_STATUS",              "0x613",	"29",	"package",	"0x0"),
("MSR",	        "PKG_POWER_INFO",               "0x614",	"20",	"package",	"0x0"),
("MSR",	        "PKG_POWER_LIMIT",              "0x610",	"20",	"package",	"0x0"),
("MSR",	        "PLATFORM_INFO",                "0x0CE",	"45",	"package",	"0x0"),
("IA32",	"PM_ENABLE",	                "0x770",	"39",	"package",	"0x0"),
("IA32",	"PMC0",                         "0x0C1",	"20",	"thread",	"0x0"),
("IA32",	"PMC1",                         "0x0C2",	"20",	"thread",	"0x0"),
("IA32",	"PMC2",                         "0x0C3",	"20",	"thread",	"0x0"),
("IA32",	"PMC3",                         "0x0C4",	"20",	"thread",	"0x0"),
("MSR",	        "POWER_CTL",                    "0x1FC",	"39",	"package",	"0x0"),
("MSR",	        "PPERF",                        "0x64E",	"39",	"thread",	"0x0"),
("MSR",	        "PP0_ENERGY_STATUS",            "0x639",	"45",	"package",	"0x0"),
("MSR",	        "PP0_POWER_LIMIT",              "0x638",	"20",	"package",	"0x0"),
("MSR",	        "RAPL_POWER_UNIT",              "0x606",	"45",	"package",	"0x0"),
("MSR",	        "PPIN_CTL",                     "0x04E",	"45",	"package",	"0x0"),
("MSR",	        "PPIN",	                        "0x04F",	"45",	"package",	"0x0"),
("MSR",	        "RING_PERF_LIMIT_REASONS",	"0x6B1",	"39",	"package",	"0x0"),
("IA32",	"THERM_INTERRUPT",	        "0x19B",	"20",	"core",	        "0x0"),
("IA32",	"THERM_STATUS",	                "0x19C",	"45",	"core",	        "0x0"),
("MSR",	        "TEMPERATURE_TARGET",	        "0x1A2",	"45",	"package",	"0x0"),
("IA32",	"TIME_STAMP_COUNTER",	        "0x010",	"20",	"thread",	"0x0"),
("MSR",	        "TURBO_ACTIVATION_RATIO",	"0x64C",	"29",	"package",	"0x0"),
("MSR",	        "TURBO_RATIO_LIMIT",	        "0x1AD",	"45",	"package",	"0x0"),
("MSR",	        "TURBO_RATIO_LIMIT_CORES",	"0x1AE",	"45",	"package",	"0x0"),
("MSR",	        "UNCORE_RATIO_LIMIT",	        "0x620",	"45",	"package",	"0x0"),
("MSR",	        "CONFIG_TDP_CONTROL",	        "0x64B",	"29",	"package",	"0x0"),
("MSR",	        "CONFIG_TDP_NOMINAL",	        "0x648",	"29",	"package",	"0x0"),
("MSR",	        "CONFIG_TDP_LEVEL1",	        "0x649",	"29",	"package",	"0x0"),
("MSR",	        "CONFIG_TDP_LEVEL2",	        "0x64A",	"29",	"package",	"0x0"),
# These are listed in tables for 06_55h but are not present on Rhetoric.
( "IA32",		"HWP_CAPABILITIES",               "0x771",		"39",     "thread",         "0x0"),    
( "IA32",		"HWP_INTERRUPT",                  "0x773",		"39",     "thread",         "0x0"),    
( "IA32",		"HWP_REQUEST",                    "0x774",		"39",     "thread",         "0x0"),    
( "IA32",		"HWP_REQUEST_PKG",                "0x772",		"39",     "package",        "0x0"),    
( "IA32",		"HWP_STATUS",                     "0x777",		"39",     "thread",         "0x0"),    
( "MSR",		"CORE_HDC_RESIDENCY",             "0x653",		"39",     "core",           "0x0"),    
( "MSR",		"PKG_HDC_CONFIG",                 "0x652",		"39",     "package",        "0x0"),    
( "IA32",		"PKG_HDC_CTL",                    "0xDB0",		"39",     "package",        "0x0"),    
( "MSR",		"PKG_HDC_DEEP_RESIDENCY",         "0x656",		"39",     "package",        "0x0"),    
( "MSR",		"PKG_HDC_SHALLOW_RESIDENCY",      "0x655",		"39",     "package",        "0x0"),    
( "MSR",		"PLATFORM_ENERGY_COUNTER",        "0x64D",		"39",     "platform",       "0x0"),    
( "MSR",		"PLATFORM_POWER_LIMIT",           "0x65C",		"39",     "platform",       "0x0"),    
( "IA32",		"PM_CTL1",                        "0xDB1",		"39",     "thread",         "0x0"),    
( "MSR",		"PP0_POLICY",                     "0x63A",		"21",     "package",        "0x0"),    
( "MSR",		"PP1_ENERGY_STATUS",              "0x641",		"21",     "package",        "0x0"),    
( "MSR",		"PP1_POLICY",                     "0x642",		"21",     "package",        "0x0"),    
( "MSR",		"PP1_POWER_LIMIT",                "0x640",		"21",     "package",        "0x0"),    
( "IA32",		"THREAD_STALL",                   "0xDB2",		"39",     "thread",         "0x0"),    
( "MSR",		"WEIGHTED_CORE_C0",               "0x658",		"39",     "package",        "0x0"),   
( "IA32",		"PERFEVTSEL4",                    "0x18A",		"20",     "thread",         "0x0"),    
( "IA32",		"PERFEVTSEL5",                    "0x18B",		"20",     "thread",         "0x0"),    
( "IA32",		"PERFEVTSEL6",                    "0x18C",		"20",     "thread",         "0x0"),    
( "IA32",		"PERFEVTSEL7",                    "0x18D",		"20",     "thread",         "0x0"),    
( "IA32",		"PMC4",                           "0x0C5",		"20",     "thread",         "0x0"),    
( "IA32",		"PMC5",                           "0x0C6",		"20",     "thread",         "0x0"),    
( "IA32",		"PMC6",                           "0x0C7",		"20",     "thread",         "0x0"),    
( "IA32",		"PMC7",                           "0x0C8",		"20",     "thread",         "0x0"),  
)

FileDescriptors = {}
namelist = []
tag     = 0
name    = 1
address = 2
table   = 3
scope   = 4
bitmask = 5

# Open all of the table headers and add the preface.
for i in range(3,54):
    FileDescriptors[f"{i:02d}"] = open(file="msr_table_"+f"{i:02d}"+".h", mode="at")
    FileDescriptors[f"{i:02d}"].write(f"/* msr_table_{i:02d}.h\n")
    FileDescriptors[f"{i:02d}"].write(f" *\n")
    FileDescriptors[f"{i:02d}"].write(f" * Model-specific registers selected from table {i:02d} of \n")
    FileDescriptors[f"{i:02d}"].write(f" * Volume 4 of Intel's January 2019 Software Developers' Manual\n")
    FileDescriptors[f"{i:02d}"].write(f" * (see https://software.intel.com/en-us/articles/intel-sdm).\n")
    FileDescriptors[f"{i:02d}"].write(f" *\n")
    FileDescriptors[f"{i:02d}"].write(f" * This file has been generated by generate-headers.py.\n")
    FileDescriptors[f"{i:02d}"].write(f" * Probably best to make edits there.\n")
    FileDescriptors[f"{i:02d}"].write(f" *\n")
    FileDescriptors[f"{i:02d}"].write(f" * Columns are:  tag, name, address, table, scope and bitmask.\n")
    FileDescriptors[f"{i:02d}"].write(f" */\n")
    FileDescriptors[f"{i:02d}"].write(f"\n")
	

# Put each MSR in the right table header file.
for i in m:
    if i[name] not in namelist:
        namelist.append( i[name] )
    FileDescriptors[ i[table] ].write( f"#ifndef __{i[name]}\n" )
    FileDescriptors[ i[table] ].write( f"#define __{i[name]}\n" )
    FileDescriptors[ i[table] ].write( f"_MSR({i[tag]},{i[name]},{i[address]},{i[table]},{i[scope]},{i[bitmask]})\n" )
    FileDescriptors[ i[table] ].write( f"#endif  //__{i[name]}\n" )
    FileDescriptors[ i[table] ].write( f"\n" )

# Create #undefs for all of the unique MRSs we've seen.
fd = open(file="msr_undefs.h", mode="wt")
for n in namelist:
    fd.write( f"#undef __{n}\n" )
fd.close()

# Close all of the table header files.
for key in FileDescriptors:
    FileDescriptors[key].close()


