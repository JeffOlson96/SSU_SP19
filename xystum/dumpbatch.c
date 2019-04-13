/* dumpbatch.c
 * 
 * Authored by Barry Rountree.
 */

#include <stdio.h>		// printf() and friends
#include <stdint.h>		// For uint64_t and friends.
#include <inttypes.h>		// PRIx32 for printing hexidecimal uint32_t, and friends.
#include <assert.h>		// assert macros.
#include "dumpbatch.h"		// Our external interface

// Set up translation from msr address to msr index
#define _MSR(tag,name,address,table,scope,writemask) case name: rc=name##_e; break;
static msr_e addr2idx(msr_a address){
        msr_e rc=LAST_MSR_INDEX;        // dummy value.
        switch (address) {
#include "msr_master.h"
                default: assert(0); break;
        }   
        return rc; 
}
#undef _MSR


void dump_batch(struct msr_batch_array *batch){
	int i;
	uint64_t msrdata;
	fprintf(stdout, "Total batch ops = %d\n", batch->numops);
	for(i=0; i<batch->numops; i++){
		msrdata = batch->ops[i].msrdata;
		fprintf(stdout, "cpu=%03d %s (0x%0x) raw=0x%llx\n", 
				batch->ops[i].cpu, 
				msr[ addr2idx( batch->ops[i].msr ) ].name,
				batch->ops[i].msr,
				batch->ops[i].msrdata);
		switch( batch->ops[i].msr ){
			case APERF:
				fprintf(stdout, "\t63: 0\t0x%lx\tActual cycles\n", 			MASK_VAL_64(msrdata,63, 0) );
				break;

			case CLOCK_MODULATION:
				fprintf(stdout, "\t 4: 0\t0x%lx\tEnable bit\n",				MASK_VAL_64(msrdata, 4, 0) );
				fprintf(stdout, "\t 3: 1\t0x%lx\tDuty Cycle\n",				MASK_VAL_64(msrdata, 3, 1) );
				break;

			case CORE_PERF_LIMIT_REASONS:
				fprintf(stdout, "\t30:63\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,30) );
				fprintf(stdout, "\t29:29\t0x%lx\tTurbo transition attenuation log\n",	MASK_VAL_64(msrdata,29,29) );
				fprintf(stdout, "\t28:28\t0x%lx\tMax turbo limit log\n",		MASK_VAL_64(msrdata,28,28) );
				fprintf(stdout, "\t27:27\t0x%lx\tPkg/Platform PL2 limiting log\n",	MASK_VAL_64(msrdata,27,27) );
				fprintf(stdout, "\t26:26\t0x%lx\tPkg/Platform PL1 limiting log\n",	MASK_VAL_64(msrdata,26,26) );
				fprintf(stdout, "\t25:25\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,25,25) );
				fprintf(stdout, "\t24:24\t0x%lx\tOther log\n",				MASK_VAL_64(msrdata,24,24) );
				fprintf(stdout, "\t23:23\t0x%lx\tVR thermal design current log\n",	MASK_VAL_64(msrdata,23,23) );
				fprintf(stdout, "\t22:22\t0x%lx\tVR thermal alert log\n",		MASK_VAL_64(msrdata,22,22) );
				fprintf(stdout, "\t21:21\t0x%lx\tRunning average thermal limit log\n",	MASK_VAL_64(msrdata,21,21) );
				fprintf(stdout, "\t20:20\t0x%lx\tResidency state regulation log\n",	MASK_VAL_64(msrdata,20,20) );
				fprintf(stdout, "\t19:18\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,19,18) );
				fprintf(stdout, "\t17:17\t0x%lx\tThermal log\n",			MASK_VAL_64(msrdata,17,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tPROCHOT log\n",			MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:14\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,15,14) );
				fprintf(stdout, "\t13:13\t0x%lx\tTurbo transition attenuation status\n",MASK_VAL_64(msrdata,13,13) );
				fprintf(stdout, "\t12:12\t0x%lx\tMax turbo limit status\n",		MASK_VAL_64(msrdata,12,12) );
				fprintf(stdout, "\t11:11\t0x%lx\tPkg/Platform PL2 limiting status\n",	MASK_VAL_64(msrdata,11,11) );
				fprintf(stdout, "\t10:10\t0x%lx\tPkg/Platform PL1 limiting status\n",	MASK_VAL_64(msrdata,10,10) );
				fprintf(stdout, "\t 9: 9\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 9, 9) );
				fprintf(stdout, "\t 8: 8\t0x%lx\tOther status\n",			MASK_VAL_64(msrdata, 8, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tVR thermal design current status\n",	MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tVR thermal alert status\n",		MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tRunning average thermal limit stat.\n",MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tResidency state regulation status\n",	MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 2\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 3, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tThermal status\n",			MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tPROCHOT status\n",			MASK_VAL_64(msrdata, 0, 0) );
				break;

			case DRAM_ENERGY_STATUS:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31: 0\t0x%lx\tScaled DRAM joules\n",			MASK_VAL_64(msrdata,31, 0) );
				break;

			case DRAM_PERF_STATUS:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31: 0\t0x%lx\tScaled DRAM throttled time\n",		MASK_VAL_64(msrdata,31, 0) );
				break;
					
			case DRAM_POWER_INFO:
				fprintf(stdout, "\t63:54\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,54) );
				fprintf(stdout, "\t53:48\t0x%lx\tDRAM Max time window\n",		MASK_VAL_64(msrdata,53,48) );
				fprintf(stdout, "\t47:47\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,47,47) );
				fprintf(stdout, "\t46:32\t0x%lx\tDRAM Max power\n",			MASK_VAL_64(msrdata,46,32) );
				fprintf(stdout, "\t31:31\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31,31) );
				fprintf(stdout, "\t30:16\t0x%lx\tDRAM Min power\n",			MASK_VAL_64(msrdata,30,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 0\t0x%lx\tDRAM Min power\n",			MASK_VAL_64(msrdata,14, 0) );
				break;

			case DRAM_POWER_LIMIT:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31   \t0x%lx\tLock bit\n",				MASK_VAL_64(msrdata,31,31) );
				fprintf(stdout, "\t30:24\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,30,24) );
				fprintf(stdout, "\t23:17\t0x%lx\tTime Window\n",			MASK_VAL_64(msrdata,23,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tClamping\n",				MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tEnable\n",				MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 0\t0x%lx\tPower Limit\n",			MASK_VAL_64(msrdata,14, 0) );
				break;

			case ENERGY_PERF_BIAS:
				fprintf(stdout, "\t63:04\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63, 4) );
				fprintf(stdout, "\t 3: 0\t0x%lx\tEnergy policy preference hint\n",	MASK_VAL_64(msrdata, 3, 0) );
				break;

			case FIXED_CTR0:
				fprintf(stdout, "\t63: 0\t0x%lx\tAccumulator 0\n",			MASK_VAL_64(msrdata,63, 0) );
				break;

			case FIXED_CTR1:
				fprintf(stdout, "\t63: 0\t0x%lx\tAccumulator 1\n",			MASK_VAL_64(msrdata,63, 0) );
				break;

			case FIXED_CTR2:
				fprintf(stdout, "\t63: 0\t0x%lx\tAccumulator 2\n",			MASK_VAL_64(msrdata,63, 0) );
				break;
			
			case FIXED_CTR_CTRL:
				fprintf(stdout, "\t63:12\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,12) );
				fprintf(stdout, "\t11:11\t0x%lx\tPMI on overflow enabled (CTR2)\n",	MASK_VAL_64(msrdata,11,11) );
				fprintf(stdout, "\t10:10\t0x%lx\tAny thread enabled (CTR2)\n",		MASK_VAL_64(msrdata,10,10) );
				fprintf(stdout, "\t 9: 8\t0x%lx\tEnable OS[1], USR[2], both[3] (CTR2)\n",MASK_VAL_64(msrdata, 9, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tPMI on overflow enabled (CTR1)\n",	MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tAny thread enabled (CTR1)\n",		MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 4\t0x%lx\tEnable OS[1], USR[2], both[3] (CTR1)\n",MASK_VAL_64(msrdata, 5, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tPMI on overflow enabled (CTR0)\n",	MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tAny thread enabled (CTR0)\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 0\t0x%lx\tEnable OS[1], USR[2], both[3] (CTR0)\n",MASK_VAL_64(msrdata, 1, 0) );
				break;
#if 0
			case HWP_CAPABILITIES:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31:24\t0x%lx\tLowest performance\n",			MASK_VAL_64(msrdata,31,24) );
				fprintf(stdout, "\t31:24\t0x%lx\tMost efficient performance\n",		MASK_VAL_64(msrdata,23,16) );
				fprintf(stdout, "\t31:24\t0x%lx\tGuaranteed performance\n",		MASK_VAL_64(msrdata,15, 8) );
				fprintf(stdout, "\t31:24\t0x%lx\tHighest performance\n",		MASK_VAL_64(msrdata, 7, 0) );
				break;

			case HWP_INTERRUPT:
				fprintf(stdout, "\t63: 4\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tEnable PECI override\n",		MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tEnable highest change\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tEnable excursion minimum\n",		MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tEnable guaranteed performance change\n",MASK_VAL_64(msrdata, 0, 0) );
				break;

			case HWP_REQUEST:
				fprintf(stdout, "\t63:63\t0x%lx\tMinimum valid\n",			MASK_VAL_64(msrdata,63,63) );
				fprintf(stdout, "\t62:62\t0x%lx\tMaximum valid\n",			MASK_VAL_64(msrdata,62,62) );
				fprintf(stdout, "\t61:61\t0x%lx\tDesired valid\n",			MASK_VAL_64(msrdata,61,61) );
				fprintf(stdout, "\t60:60\t0x%lx\tEPP valid\n",				MASK_VAL_64(msrdata,60,60) );
				fprintf(stdout, "\t59:59\t0x%lx\tActivity window valid\n",		MASK_VAL_64(msrdata,59,59) );
				fprintf(stdout, "\t58:43\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,58,43) );
				fprintf(stdout, "\t42:42\t0x%lx\tPackage control\n",			MASK_VAL_64(msrdata,42,42) );
				fprintf(stdout, "\t41:32\t0x%lx\tActivity window\n",			MASK_VAL_64(msrdata,41,32) );
				fprintf(stdout, "\t31:24\t0x%lx\tEnergy perfomance preference\n",	MASK_VAL_64(msrdata,31,24) );
				fprintf(stdout, "\t23:16\t0x%lx\tDesired performance\n",		MASK_VAL_64(msrdata,23,16) );
				fprintf(stdout, "\t15: 8\t0x%lx\tMaximum performance\n",		MASK_VAL_64(msrdata,15, 8) );
				fprintf(stdout, "\t 7: 0\t0x%lx\tMinimum performance\n",		MASK_VAL_64(msrdata, 7, 0) );
				break;

			case HWP_REQUEST_PKG:
				fprintf(stdout, "\t63:42\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,42) );
				fprintf(stdout, "\t41:32\t0x%lx\tActivity window\n",			MASK_VAL_64(msrdata,41,32) );
				fprintf(stdout, "\t31:24\t0x%lx\tEnergy perfomance preference\n",	MASK_VAL_64(msrdata,31,24) );
				fprintf(stdout, "\t23:16\t0x%lx\tDesired performance\n",		MASK_VAL_64(msrdata,23,16) );
				fprintf(stdout, "\t15: 8\t0x%lx\tMaximum performance\n",		MASK_VAL_64(msrdata,15, 8) );
				fprintf(stdout, "\t 7: 0\t0x%lx\tMinimum performance\n",		MASK_VAL_64(msrdata, 7, 0) );
				break;

			case HWP_STATUS:
				fprintf(stdout, "\t63: 6\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tPECI override exit\n",			MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tPECI override entry\n",		MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tHighest change\n",			MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tExcursion to minimum\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tGuaranteed performance chnage\n",	MASK_VAL_64(msrdata, 0, 0) );
				break;	
#endif 
			case MPERF:
				fprintf(stdout, "\t63: 0\t0x%lx\tReference cycles\n", 			MASK_VAL_64(msrdata,63, 0) );
				break;

			case PACKAGE_THERM_INTERRUPT:
				fprintf(stdout, "\t63:25\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,25) );
				fprintf(stdout, "\t24:24\t0x%lx\tPower limit notification enable\n",	MASK_VAL_64(msrdata,24,24) );
				fprintf(stdout, "\t23:23\t0x%lx\tThreshold #2 interrupt enable\n",	MASK_VAL_64(msrdata,23,23) );
				fprintf(stdout, "\t22:16\t0x%lx\tThreshold #2 value\n",			MASK_VAL_64(msrdata,22,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tThreshold #1 interupt enable\n",	MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 8\t0x%lx\tThreshold #1 value\n",			MASK_VAL_64(msrdata,14, 8) );
				fprintf(stdout, "\t 7: 5\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 7, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tOverheat interrupt enable\n",		MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tPROCHOT# interrupt enable\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tLow temperature interrupt enable\n",	MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tHigh temperature interrupt enable\n",	MASK_VAL_64(msrdata, 0, 0) );
				break;

			case PERF_CTL:
				fprintf(stdout, "\t63:33\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,25) );
				fprintf(stdout, "\t32:32\t0x%lx\tTurbo DISENGAGE\n",			MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31:16\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31,16) );
				fprintf(stdout, "\t15: 0\t0x%lx\tTransition target\n",			MASK_VAL_64(msrdata,15, 0) );
				break;
				
			case PERF_GLOBAL_CTRL:
				fprintf(stdout, "\t63:35\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,35) );
				fprintf(stdout, "\t34:34\t0x%lx\tFixed CTR2 enable\n",			MASK_VAL_64(msrdata,34,34) );
				fprintf(stdout, "\t33:33\t0x%lx\tFixed CTR1 enable\n",			MASK_VAL_64(msrdata,33,33) );
				fprintf(stdout, "\t32:32\t0x%lx\tFixed CTR0 enable\n",			MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31: 8\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tPMC 7 enable\n",			MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tPMC 6 enable\n",			MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tPMC 5 enable\n",			MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tPMC 4 enable\n",			MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tPMC 3 enable\n",			MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tPMC 2 enable\n",			MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tPMC 1 enable\n",			MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tPMC 0 enable\n",			MASK_VAL_64(msrdata, 0, 0) );
				break;

			case PERF_GLOBAL_STATUS_RESET:
				fprintf(stdout, "\t63:63\t0x%lx\tClear the condition changed bit\n",	MASK_VAL_64(msrdata,63,63) );
				fprintf(stdout, "\t62:62\t0x%lx\tClear the overflow DS buffer bit\n",	MASK_VAL_64(msrdata,62,62) );
				fprintf(stdout, "\t61:61\t0x%lx\tClear the uncore overflow bit\n",	MASK_VAL_64(msrdata,61,61) );
				fprintf(stdout, "\t60:35\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,60,35) );
				fprintf(stdout, "\t34:34\t0x%lx\tClear the fixed CTR2 overflow bit\n",	MASK_VAL_64(msrdata,34,34) );
				fprintf(stdout, "\t33:33\t0x%lx\tClear the fixed CTR1 overflow bit\n",	MASK_VAL_64(msrdata,33,33) );
				fprintf(stdout, "\t32:32\t0x%lx\tClear the fixed CTR0 overflow bit\n",	MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31: 8\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tClear the fixed PMC7 overflow bit\n",	MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tClear the fixed PMC6 overflow bit\n",	MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tClear the fixed PMC5 overflow bit\n",	MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tClear the fixed PMC4 overflow bit\n",	MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tClear the fixed PMC3 overflow bit\n",	MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tClear the fixed PMC2 overflow bit\n",	MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tClear the fixed PMC1 overflow bit\n",	MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tClear the fixed PMC0 overflow bit\n",	MASK_VAL_64(msrdata, 0, 0) );
				break;
			
			case PERF_GLOBAL_STATUS:
				fprintf(stdout, "\t63:63\t0x%lx\tCondition changed\n",			MASK_VAL_64(msrdata,63,63) );
				fprintf(stdout, "\t62:62\t0x%lx\toverflow DS buffer\n",			MASK_VAL_64(msrdata,62,62) );
				fprintf(stdout, "\t61:61\t0x%lx\tuncore overflow\n",			MASK_VAL_64(msrdata,61,61) );
				fprintf(stdout, "\t60:35\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,60,35) );
				fprintf(stdout, "\t34:34\t0x%lx\tfixed CTR2 overflow\n",		MASK_VAL_64(msrdata,34,34) );
				fprintf(stdout, "\t33:33\t0x%lx\tfixed CTR1 overflow\n",		MASK_VAL_64(msrdata,33,33) );
				fprintf(stdout, "\t32:32\t0x%lx\tfixed CTR0 overflow\n",		MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31: 8\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tfixed PMC7 overflow\n",		MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tfixed PMC6 overflow\n",		MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tfixed PMC5 overflow\n",		MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tfixed PMC4 overflow\n",		MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tfixed PMC3 overflow\n",		MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tfixed PMC2 overflow\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tfixed PMC1 overflow\n",		MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tfixed PMC0 overflow\n",		MASK_VAL_64(msrdata, 0, 0) );
				break;

			case PERF_GLOBAL_STATUS_SET:
				fprintf(stdout, "\t63:63\t0x%lx\tCondition changed\n",			MASK_VAL_64(msrdata,63,63) );
				fprintf(stdout, "\t62:62\t0x%lx\toverflow DS buffer\n",			MASK_VAL_64(msrdata,62,62) );
				fprintf(stdout, "\t61:61\t0x%lx\tuncore overflow\n",			MASK_VAL_64(msrdata,61,61) );
				fprintf(stdout, "\t60:35\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,60,35) );
				fprintf(stdout, "\t34:34\t0x%lx\tfixed CTR2 overflow\n",		MASK_VAL_64(msrdata,34,34) );
				fprintf(stdout, "\t33:33\t0x%lx\tfixed CTR1 overflow\n",		MASK_VAL_64(msrdata,33,33) );
				fprintf(stdout, "\t32:32\t0x%lx\tfixed CTR0 overflow\n",		MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31: 8\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tfixed PMC7 overflow\n",		MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tfixed PMC6 overflow\n",		MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tfixed PMC5 overflow\n",		MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tfixed PMC4 overflow\n",		MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tfixed PMC3 overflow\n",		MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tfixed PMC2 overflow\n",		MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tfixed PMC1 overflow\n",		MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tfixed PMC0 overflow\n",		MASK_VAL_64(msrdata, 0, 0) );
				break;


			case PERF_GLOBAL_INUSE:
				fprintf(stdout, "\t63:63\t0x%lx\tPMI\n",				MASK_VAL_64(msrdata,63,35) );
				fprintf(stdout, "\t62:35\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,35) );
				fprintf(stdout, "\t34:34\t0x%lx\tFixed CTR2 \n",			MASK_VAL_64(msrdata,34,34) );
				fprintf(stdout, "\t33:33\t0x%lx\tFixed CTR1 \n",			MASK_VAL_64(msrdata,33,33) );
				fprintf(stdout, "\t32:32\t0x%lx\tFixed CTR0 \n",			MASK_VAL_64(msrdata,32,32) );
				fprintf(stdout, "\t31: 8\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,31, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tPMC 7\n",				MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tPMC 6\n",				MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tPMC 5\n",				MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 4\t0x%lx\tPMC 4\n",				MASK_VAL_64(msrdata, 4, 4) );
				fprintf(stdout, "\t 3: 3\t0x%lx\tPMC 3\n",				MASK_VAL_64(msrdata, 3, 3) );
				fprintf(stdout, "\t 2: 2\t0x%lx\tPMC 2\n",				MASK_VAL_64(msrdata, 2, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tPMC 1\n",				MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tPMC 0\n",				MASK_VAL_64(msrdata, 0, 0) );
				break;

			case PERF_STATUS:
				fprintf(stdout, "\t63:48\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,48) );
				fprintf(stdout, "\t47:32\t0x%lx\tCore voltage\n",			MASK_VAL_64(msrdata,47,32) );
				fprintf(stdout, "\t31:16\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,31,16) );
				fprintf(stdout, "\t31: 0\t0x%lx\tCurrent performance state value\n",	MASK_VAL_64(msrdata,15, 0) );
				break;

			case PERFEVTSEL0: // Fallthrough....
			case PERFEVTSEL1:
			case PERFEVTSEL2:
			case PERFEVTSEL3:
#if 0 
			case PERFEVTSEL4:
			case PERFEVTSEL5:
			case PERFEVTSEL6:
			case PERFEVTSEL7:
#endif
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31:24\t0x%lx\tCounter mask (CMASK)\n",		MASK_VAL_64(msrdata,31,24) );
				fprintf(stdout, "\t23:23\t0x%lx\tInvert\n",				MASK_VAL_64(msrdata,23,23) );
				fprintf(stdout, "\t22:22\t0x%lx\tEnable\n",				MASK_VAL_64(msrdata,22,22) );
				fprintf(stdout, "\t21:21\t0x%lx\tAny thread\n",				MASK_VAL_64(msrdata,21,21) );
				fprintf(stdout, "\t20:20\t0x%lx\tAPIC interrupt enabled\n",		MASK_VAL_64(msrdata,20,20) );
				fprintf(stdout, "\t19:19\t0x%lx\tPin control\n",			MASK_VAL_64(msrdata,19,19) );
				fprintf(stdout, "\t18:18\t0x%lx\tEdge detect\n",			MASK_VAL_64(msrdata,18,18) );
				fprintf(stdout, "\t17:17\t0x%lx\tOperating system mode\n",		MASK_VAL_64(msrdata,17,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tUser mode\n",				MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15: 8\t0x%lx\tUnit mask (UMASK)\n",			MASK_VAL_64(msrdata,15, 8) );
				fprintf(stdout, "\t 7: 0\t0x%lx\tEvent select\n",			MASK_VAL_64(msrdata, 7, 0) );
				break;

			case PKG_CST_CONFIG_CONTROL:
				fprintf(stdout, "\t63:31\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,31) );
				fprintf(stdout, "\t30:30\t0x%lx\tPackage C state unDemotion enable\n", 	MASK_VAL_64(msrdata,30,30) );
				fprintf(stdout, "\t29:29\t0x%lx\tPackage C state demotion enable\n", 	MASK_VAL_64(msrdata,29,29) );
				fprintf(stdout, "\t28:28\t0x%lx\tEnable C1 undemotion\n", 		MASK_VAL_64(msrdata,28,28) );
				fprintf(stdout, "\t27:27\t0x%lx\tEnable C3 undemotion\n", 		MASK_VAL_64(msrdata,27,27) );
				fprintf(stdout, "\t26:26\t0x%lx\tC1 state auto demotion enable\n",	MASK_VAL_64(msrdata,26,26) );
				fprintf(stdout, "\t25:25\t0x%lx\tC3 state auto demotion enable\n",	MASK_VAL_64(msrdata,25,25) );
				fprintf(stdout, "\t24:17\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,24,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tAutomatic C state conversion enable\n",MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tCFG lock\n",				MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14:11\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,14,11) );
				fprintf(stdout, "\t10:10\t0x%lx\tI/O MWAIT redirection enable\n",	MASK_VAL_64(msrdata,10,10) );
				fprintf(stdout, "\t 9: 3\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 9, 3) );
				fprintf(stdout, "\t 2: 0\t0x%lx\tPackage C state limit\n",		MASK_VAL_64(msrdata, 2, 0) );
				break;

			case PKG_ENERGY_STATUS:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31: 0\t0x%lx\tTotal energy consumed\n", 		MASK_VAL_64(msrdata,31, 0) );
				break;
#if 0
			case PKG_HDC_CONFIG:
				fprintf(stdout, "\t63: 3\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63, 3) );
				fprintf(stdout, "\t 2: 0\t0x%lx\tHDC Cx monitor\n", 			MASK_VAL_64(msrdata, 2, 0) );
				break;

			case PKG_HDC_CTL:
				fprintf(stdout, "\t63: 1\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tHDC Pkg enable\n", 			MASK_VAL_64(msrdata, 0, 0) );
				break;

#endif 	
			case PKG_PERF_STATUS:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31: 0\t0x%lx\tAccumulated package throttle time\n",	MASK_VAL_64(msrdata,31, 0) );
				break;

			case PKG_POWER_INFO:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t53:48\t0x%lx\tMaximum time window\n",		MASK_VAL_64(msrdata,53,48) );
				fprintf(stdout, "\t47:47\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,47,47) );
				fprintf(stdout, "\t46:32\t0x%lx\tMaximum power\n",			MASK_VAL_64(msrdata,46,32) );
				fprintf(stdout, "\t31:31\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,31,31) );
				fprintf(stdout, "\t30:16\t0x%lx\tMinimum power\n",			MASK_VAL_64(msrdata,30,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 0\t0x%lx\tThermal spec power\n",			MASK_VAL_64(msrdata,14, 0) );
				break;

			case PKG_POWER_LIMIT:
				fprintf(stdout, "\t63:63\t0x%lx\tLock bit\n", 				MASK_VAL_64(msrdata,63,63) );
				fprintf(stdout, "\t55:49\t0x%lx\tTime Window 2\n", 			MASK_VAL_64(msrdata,55,49) );
				fprintf(stdout, "\t48:48\t0x%lx\tPkg Clamping Limit 2\n", 		MASK_VAL_64(msrdata,48,48) );
				fprintf(stdout, "\t47:47\t0x%lx\tEnable Limit 2\n", 			MASK_VAL_64(msrdata,47,47) );
				fprintf(stdout, "\t46:32\t0x%lx\tPower Limit 2\n", 			MASK_VAL_64(msrdata,46,32) );
				fprintf(stdout, "\t23:17\t0x%lx\tTime Window 1\n", 			MASK_VAL_64(msrdata,23,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tPkg Clamping Limit 1\n", 		MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tEnable Limit 1\n", 			MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 0\t0x%lx\tPower Limit 1\n", 			MASK_VAL_64(msrdata,14, 0) );
				break;

			case PLATFORM_INFO:
				fprintf(stdout, "\t63:48\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63,48) );
				fprintf(stdout, "\t47:40\t0x%lx\tMaximum efficiency ratio\n",		MASK_VAL_64(msrdata,47,40) );
				fprintf(stdout, "\t39:31\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,39,31) );
				fprintf(stdout, "\t30:30\t0x%lx\tProgrammable TJ offset\n", 		MASK_VAL_64(msrdata,30,30) );
				fprintf(stdout, "\t29:29\t0x%lx\tProg. TDP limit for turbo mode\n", 	MASK_VAL_64(msrdata,29,29) );
				fprintf(stdout, "\t28:28\t0x%lx\tProg. ratio limit for turbo mode\n", 	MASK_VAL_64(msrdata,28,28) );
				fprintf(stdout, "\t27:24\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,27,24) );
				fprintf(stdout, "\t23:23\t0x%lx\tPPIN_CAP\n", 				MASK_VAL_64(msrdata,23,23) );
				fprintf(stdout, "\t22:16\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,22,16) );
				fprintf(stdout, "\t15: 8\t0x%lx\tMaximum non-turbo ratio\n",		MASK_VAL_64(msrdata,15, 8) );
				fprintf(stdout, "\t 7: 0\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata, 7, 0) );
				break;

			case PM_ENABLE:
				fprintf(stdout, "\t63: 1\t0x%lx\tReserved\n", 				MASK_VAL_64(msrdata,63, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tHWP Enable\n", 			MASK_VAL_64(msrdata, 0, 0) );
				break;

			case PMC0:
			case PMC1:
			case PMC2:
			case PMC3:
#if 0 
			case PMC4:
			case PMC5:
			case PMC6:
			case PMC7:
#endif
				fprintf(stdout, "\t63: 0\t0x%lx\tAccumulator\n", 			MASK_VAL_64(msrdata,63, 0) );
				break;

			case POWER_CTL:
				fprintf(stdout, "\t63:21\t0x%lx\tReserved\n", 					MASK_VAL_64(msrdata,63,21) );
				fprintf(stdout, "\t20:20\t0x%lx\tDisable energy efficiency optimization\n",	MASK_VAL_64(msrdata,20,20) );
				fprintf(stdout, "\t19:19\t0x%lx\tDisable race to halt optimization\n",		MASK_VAL_64(msrdata,19,19) );
				fprintf(stdout, "\t18: 2\t0x%lx\tReserved\n", 					MASK_VAL_64(msrdata,18, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tC1E Enable\n", 				MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tReserved\n", 					MASK_VAL_64(msrdata, 0, 0) );
				break;	

			case PPERF:
				fprintf(stdout, "\t63: 0\t0x%lx\tProductive performance count\n",		MASK_VAL_64(msrdata,63,21) );
				break;

			case PP0_ENERGY_STATUS:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31: 0\t0x%lx\tScaled PP0 joules\n",			MASK_VAL_64(msrdata,31, 0) );
				break;

			case PP0_POWER_LIMIT:
				fprintf(stdout, "\t63:32\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,32) );
				fprintf(stdout, "\t31   \t0x%lx\tLock bit\n",				MASK_VAL_64(msrdata,31,31) );
				fprintf(stdout, "\t30:24\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,30,24) );
				fprintf(stdout, "\t23:17\t0x%lx\tTime Window\n",			MASK_VAL_64(msrdata,23,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tClamping\n",				MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:15\t0x%lx\tEnable\n",				MASK_VAL_64(msrdata,15,15) );
				fprintf(stdout, "\t14: 0\t0x%lx\tPower Limit\n",			MASK_VAL_64(msrdata,14, 0) );
				break;

			case RAPL_POWER_UNIT:
				fprintf(stdout, "\t63:20\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,20) );
				fprintf(stdout, "\t19:16\t0x%lx\tTime units\n",				MASK_VAL_64(msrdata,19,16) );
				fprintf(stdout, "\t15:13\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,15,13) );
				fprintf(stdout, "\t12: 8\t0x%lx\tEnergy status units\n",		MASK_VAL_64(msrdata,12, 8) );
				fprintf(stdout, "\t 7: 4\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 7, 4) );
				fprintf(stdout, "\t 3: 0\t0x%lx\tPower units\n",			MASK_VAL_64(msrdata, 3, 0) );
				break;

			case PPIN_CTL:
				fprintf(stdout, "\t63: 2\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tEnable PPIN\n",			MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tLockout\n",				MASK_VAL_64(msrdata, 0, 0) );
				break;
				
			case PPIN:
				fprintf(stdout, "\t63: 0\t0x%lx\tProtected processor inventory number\n",MASK_VAL_64(msrdata,63, 0) );
				break;

			case RING_PERF_LIMIT_REASONS:
				fprintf(stdout, "\t63:28\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,63,28) );
				fprintf(stdout, "\t27:27\t0x%lx\tPL2 power limiting log\n",		MASK_VAL_64(msrdata,27,27) );
				fprintf(stdout, "\t26:26\t0x%lx\tPL1 power limiting log\n",		MASK_VAL_64(msrdata,26,26) );
				fprintf(stdout, "\t25:25\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,25,25) );
				fprintf(stdout, "\t24:24\t0x%lx\tOther log\n",				MASK_VAL_64(msrdata,24,24) );
				fprintf(stdout, "\t23:23\t0x%lx\tVR thermal design current log\n",	MASK_VAL_64(msrdata,23,23) );
				fprintf(stdout, "\t22:22\t0x%lx\tVR therm alert log\n",			MASK_VAL_64(msrdata,22,22) );
				fprintf(stdout, "\t21:21\t0x%lx\tRunning average thermal limit log\n",	MASK_VAL_64(msrdata,21,21) );
				fprintf(stdout, "\t20:18\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,20,18) );
				fprintf(stdout, "\t17:17\t0x%lx\tThermal log\n",			MASK_VAL_64(msrdata,17,17) );
				fprintf(stdout, "\t16:16\t0x%lx\tPROCHOT log\n",			MASK_VAL_64(msrdata,16,16) );
				fprintf(stdout, "\t15:12\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata,15,12) );
				fprintf(stdout, "\t11:11\t0x%lx\tPL2 power limiting status\n",		MASK_VAL_64(msrdata,11,11) );
				fprintf(stdout, "\t10:10\t0x%lx\tPL1 power limiting status\n",		MASK_VAL_64(msrdata,10,10) );
				fprintf(stdout, "\t 9: 9\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 9, 9) );
				fprintf(stdout, "\t 8: 8\t0x%lx\tOther status\n",			MASK_VAL_64(msrdata, 8, 8) );
				fprintf(stdout, "\t 7: 7\t0x%lx\tVR thermal design current status\n",	MASK_VAL_64(msrdata, 7, 7) );
				fprintf(stdout, "\t 6: 6\t0x%lx\tVR therm alert status\n",		MASK_VAL_64(msrdata, 6, 6) );
				fprintf(stdout, "\t 5: 5\t0x%lx\tRunning average thermal limit status\n",MASK_VAL_64(msrdata, 5, 5) );
				fprintf(stdout, "\t 4: 2\t0x%lx\tReserved\n",				MASK_VAL_64(msrdata, 4, 2) );
				fprintf(stdout, "\t 1: 1\t0x%lx\tThermal status\n",			MASK_VAL_64(msrdata, 1, 1) );
				fprintf(stdout, "\t 0: 0\t0x%lx\tPROCHOT status\n",			MASK_VAL_64(msrdata, 0, 0) );
				break;

			case THERM_INTERRUPT:
				break;
				
			case THERM_STATUS:
				break;

			case TEMPERATURE_TARGET:
				break;

			case TIME_STAMP_COUNTER:
				break;

			case TURBO_ACTIVATION_RATIO:
				break;

			case TURBO_RATIO_LIMIT:
				break;

			case TURBO_RATIO_LIMIT_CORES:
				break;

			case UNCORE_RATIO_LIMIT:
				break;

			case CONFIG_TDP_CONTROL:
				break;

			case CONFIG_TDP_NOMINAL:
				break;

			case CONFIG_TDP_LEVEL1:
				break;

			case CONFIG_TDP_LEVEL2:
				break;	

			default:
				fprintf(stdout, "cpu=%02d (unknown msr) (0x%0x) raw=0x%016lx\n", 
						batch->ops[i].cpu, 
						batch->ops[i].msr,
						msrdata);
				break;
		}
	}
}

