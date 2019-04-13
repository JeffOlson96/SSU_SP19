/* msr_derived.h
 *
 * Authored by Barry Rountree.
 */
#include "twiddling.h"
#ifndef __MSR_DERIVED_H
#define __MSR_DERIVED_H

typedef enum msr_scope{
	SCOPE_platform,
	SCOPE_package,
	SCOPE_core,
	SCOPE_thread,
	SCOPE_unknown,
	NUM_SCOPES
} msr_scope;

// Set up the msr address enumeration. For example, APERF is set its register offset (i.e. 0x0E8).
#define _MSR(tag,name,address,table,scope,writemask) name=address,
typedef enum msr_address{
#include "msr_master.h"
	LAST_MSR_ADDRESS=-1
} msr_a;
#undef _MSR

// Set up the msr index enumeration.  APERF becomes APERF_e and is set to its row in the msr table.
// This allows idioms like msr[APERF_e].writemask.
#define _MSR(tag,name,address,table,scope,writemask) name##_e,
typedef enum msr_index{
#include "msr_master.h"
	LAST_MSR_INDEX=-1
} msr_e;
#undef _MSR

// Our msr table will be populated with these structs.
struct msr{
	msr_a address;		// MSR address 
	uint32_t table;		// Table to consult in v4 of the Jan 2019 Intel SDM
	msr_scope scope;	// thread, core, package, platform, unknown
	uint64_t writemask;	// Only allow writing to these bits; all bits are readable.
	char *name;		// charater string of the MSR name
};

// Set up the msr table.
#define _MSR(tag,name,address,table,scope,writemask) { address, table, SCOPE_##scope, writemask, #name },
static struct msr msr[] = {
#include "msr_master.h"
	_MSR(dummy, dummy, -1, 0, core, 0x0)
};
#undef _MSR

#if 0
// Set up translation from msr address to msr index
#define _MSR(tag,name,address,table,scope,writemask) case name: rc=name##_e; break;
static msr_e addr2idx(msr_a address){
	msr_e rc=LAST_MSR_INDEX;	// dummy value.
	switch (address) {
#include "msr_master.h"
		default: assert(0); break;
	}
	return rc;
}
#undef _MSR
#endif 

#endif //__MSR_DERIVED_H
