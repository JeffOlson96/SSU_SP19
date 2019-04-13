/* dfdm.c
 * 
 * A cheap interface for getting the "display family" and 
 * "display model" out of Intel processors.
 *
 * Might want to eventually return those values instead of printing them, 
 * but let's put that off until we actually need that functionality.
 *
 * Authored by Barry Rountree.
 */

#include <stdio.h>		
#include <stdint.h>		
#include <inttypes.h>		
#include <cpuid.h>		//  See https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/cpuid.h
#include "dfdm.h"				
#include "twiddling.h"



// See Volume 2A of the Intel SDM under the "cpuid" instruction.
void dump_displayfamily_displaymodel(){

	uint32_t	leaf = 1; 
	uint32_t	eax;
	uint32_t	ebx;
	uint32_t	ecx;
	uint32_t	edx;

	// Macro that expands to inline assembly that calls the cpuid instruction.
	__get_cpuid( leaf, &eax, &ebx, &ecx, &edx );
	
	// Bitfields for EAX register after call to cpuid using leaf=1.
	//
	// 31:28 Reserved
	// 27:20 Extended Family
	// 19:16 Extended Model
	// 15:14 Reserved
	// 13:12 Processor Type
	// 11:08 Family Code
	// 07:04 Model Number
	// 03:00 Stepping
	
	//fprintf(stdout, "0x%1"PRIx32"%1"PRIx32"\n", eax,eax);
	fprintf(stdout, "DisplayFamily:DisplayModel of this processor is 0x%1"PRIx32"%1"PRIx32":0x%1"PRIx32"%1"PRIx32".\n", 
		MASK_VAL_32(eax, 27, 20), 
		MASK_VAL_32(eax, 11,  8), 
		MASK_VAL_32(eax, 19, 16), 
		MASK_VAL_32(eax,  7,  4) 
	);
}
