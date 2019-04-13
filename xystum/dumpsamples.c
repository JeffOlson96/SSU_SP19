/* dump_samples.c
 * 
 * Authored by Barry Rountree.
 */
				// According to lore, this must be defined before any #includes.

#include <stdio.h>		// printf() and friends
#include <stdint.h>		// For uint64_t and friends.
#include <inttypes.h>		// PRIx32 for printing hexidecimal uint32_t, and friends.
#include <sys/types.h>		// man -S2 open
#include <sys/stat.h>		//  "
#include <fcntl.h>		//  "
#include <errno.h>		// perror()
#include <stdlib.h>		// exit()
#include <unistd.h>		// write()
#include <string.h>		// memset(), memcpy()
#include <sys/time.h>		// get/setitimer().
#include <signal.h>		// sigemptyset(), sigaction().
#include <dlfcn.h>		// dlsym().
#include <assert.h>		// assert macros.
#include "msr_derived.h"
#include "dumpsamples.h"

void dump_samples(struct msr_batch_array* samples){
	uint32_t i,j;
	FILE *f;
	uint16_t cpu;
	uint64_t msrdata;
	f=fopen("./samples.R", "w");
	
	// First, print out the column headings
	for( i=0; i<samples[0].numops; i++ ){
		cpu = samples[0].ops[i].cpu;
		switch( samples[0].ops[i].msr ){
			case APERF:
				fprintf(f, "APERF_%02d ", cpu);
				break;
			case MPERF:
				fprintf(f, "MPERF_%02d ", cpu);
				break;
			case CORE_PERF_LIMIT_REASONS:
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Turbo_transition_attenuation_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Max_turbo_limit_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Pkg/Platform_PL2_limiting_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Pkg/Platform_PL1_limiting_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Other_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__VR_thermal_design_current_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__VR_thermal_alert_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Running_average_thermal_limit_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Residency_state_regulation_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Thermal_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__PROCHOT_log_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Turbo_transition_attenuation_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Max_turbo_limit_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Pkg/Platform_PL2_limiting_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Pkg/Platform_PL1_limiting_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Other_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__VR_thermal_design_current_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__VR_thermal_alert_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Running_average_thermal_limit_stat._%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Residency_state_regulation_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__Thermal_status_%02d ", cpu);
				fprintf(f,"CORE_PERF_LIMIT_REASONS__PROCHOT_status_%02d ", cpu);
				break;
			case DRAM_ENERGY_STATUS:
				fprintf(f,"DRAM_ENERGY_STATUS_%02d ", cpu);
				break;
			case PKG_ENERGY_STATUS:
				fprintf(f,"PKG_ENERGY_STATUS_%02d ", cpu);
				break;
			case PERF_CTL:
				fprintf(f,"PERF_CTL__Raw_%02d ", cpu);
				fprintf(f,"PERF_CTL__Turbo_DISengage_%02d ", cpu);
				fprintf(f,"PERF_CTL__Transition_target_%02d ", cpu);
				break;
			case PERF_STATUS:
				fprintf(f,"PERF_STATUS__Raw_%02d ", cpu);
				fprintf(f,"PERF_STATUS__Core_voltage_%02d ", cpu);
				fprintf(f,"PERF_STATUS__Current_performance_state_value_%02d ", cpu);
				break;
			default:
				fprintf(f,"UNKNOWN_%02d ", cpu);
		}
	}
	fprintf(f,"\n");
	
	// Now print the data itself.
	for( i=0; i<MAX_SAMPLES && samples[i].ops[0].msrdata > 0; i++ ){
		for( j=0; j<samples[i].numops; j++ ){
			msrdata	= samples[i].ops[j].msrdata;
			switch( samples[i].ops[j].msr ){
				case APERF:
				case MPERF:	
					fprintf(f, "%lld ", samples[i].ops[j].msrdata);
					break;
				case DRAM_ENERGY_STATUS:
				case PKG_ENERGY_STATUS:
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,31, 0) );
					break;
				case PERF_STATUS:
					fprintf(f, "0x%lx ", msrdata);
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,47,32) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,15, 8) );
					break;
				case PERF_CTL:
					fprintf(f, "0x%lx ", msrdata);
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,32,32) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,15, 8) );
					break;
				case CORE_PERF_LIMIT_REASONS:
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,29,29) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,28,28) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,27,27) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,26,26) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,24,24) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,23,23) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,22,22) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,21,21) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,20,20) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,17,17) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,16,16) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,13,13) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,12,12) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,11,11) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata,10,10) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 8, 8) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 7, 7) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 6, 6) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 5, 5) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 4, 4) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 1, 1) );
					fprintf(f, "%ld ", MASK_VAL_64(msrdata, 0, 0) );
					break;
				default:
					fprintf(f, "na ");
					break;
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

