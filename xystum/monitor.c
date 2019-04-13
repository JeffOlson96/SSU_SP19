/* monitor.c
 * LD_PRELOAD code courtesy of https://gist.github.com/apsun/1e144bf7639b22ff0097171fa0f8c6b1
 * setitimer code courtesy of https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/apis/setitime.htm
 * 
 * Authored by Barry Rountree.
 */
#define _GNU_SOURCE		// Required for non-portable GNU dlsym extensions.
				// According to lore, this must be defined before any #includes.
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE  	// Required for sigaction.
#endif 

#include <stdio.h>		// printf() and friends
#include <stdint.h>		// For uint64_t and friends.
#include <inttypes.h>		// PRIx32 for printing hexidecimal uint32_t, and friends.
#include <cpuid.h>		// Friendlier interface for the cpuid instruction.
				//  This may be gcc-specific.  For implementation
				//  notes, see https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/cpuid.h
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
#include "../Sonoma-midterm-support/hwloc-2.0.3-install/include/hwloc.h"		// Counting sockets, core and hardware threads.
#include <sys/ioctl.h>		// For the ioctl interface to the msr-safe batch system.
#include "hwloc.h"
#include "dfdm.h"
#include "msr_safe.h"		// kernel interface for msr batch operations
#include "msr_derived.h"
#include "dumpbatch.h"
#include "dumpsamples.h"

#define typeof __typeof__	// Not sure while this is needed on rhetoric but not feyerabend.
#define TO_BE_READ 1 		// Dummy placeholder to make the code look nicer.
#define TO_BE_WRITTEN 0
static int total_sockets;	// From the hwloc library.
static int total_cores;		// "			"
static int total_threads;	// "			"
static int batch_fd;		// /dev/cpu/msr_batch

typedef enum{
	B_SCRATCHPAD,		// Use this to determine batch sizes.
	B_READ_ALL_CPU_ZERO,	// Grab a snapshot of all the MSRs we care about.
	B_SAMPLING,
	B_INITIALIZE_TO_ZERO,
	NUM_B_TYPES		// This is an enum idiom that allows us to declare arrays easily.
} batch_type_t;


static struct msr_batch_array batch[NUM_B_TYPES];		// Array of pointers to structs of type msr_batch_array
#define MAX_SAMPLES (100000)
static struct msr_batch_array samples[MAX_SAMPLES];

// See Volume 2A of the Intel SDM under the "cpuid" instruction.
#define MAX_WHITELIST_ENTRY_LENGTH (128)
#define MAX_WHITELIST_BUFFERSIZE   ((128 * 1024) + 1)
// Rather than rely on getting an existing whitelist, we're going to create our own.
static void populate_whitelist(){
	int msr_index=0, buf_index=0, rc=0;
	char* whitelist;
	int whitelist_fd = 0;

	// Count how many MSRs are listed in msr[].
	for(msr_index=0; msr[msr_index].address > 0; msr_index++);

	// Allocate zero-initialized memory to hold the whitelist.
	whitelist = calloc( msr_index, MAX_WHITELIST_ENTRY_LENGTH );
	assert(whitelist);

	// Open the whitelist file.
       	whitelist_fd = open("/dev/cpu/msr_whitelist", O_WRONLY | O_TRUNC ); 
	if(whitelist_fd == -1){
		fprintf(stderr, "ERROR at roughly %s:%d.\n", __FILE__, __LINE__);
		fprintf(stderr, "Oh, bother:  I'm not able to update the whitelist.\n");
		fprintf(stderr, "1.  Did you remember to load the msr-safe kernel module?\n");
		fprintf(stderr, "2.  Did you give read and write permissions to the whitelist file?\n");
		fprintf(stderr, "Here's what the operating system says.\n");
		perror(NULL);
		exit(-1); // Die loudly.  If we can't access the whitelist, we're done.
	}

	// The msr-safe kernel module wants a single write to update the whitelist.
	// So rather than writing each entry individually, we'll write them all into
	// the buffer and then write the buffer in toto.
	for( msr_index=0; msr[msr_index].address > 0; msr_index++){
		buf_index += 
			snprintf( 
				&(whitelist[buf_index]), 
				MAX_WHITELIST_ENTRY_LENGTH, 
				"0x%08"PRIx32" 0x%016"PRIx64"\n", 
				msr[msr_index].address, 
				msr[msr_index].writemask 
			);
	}

	// Let's write the buffer.
	rc = write(whitelist_fd, (const void *)(whitelist), buf_index);
	if( rc == -1 ){
		fprintf(stderr, "ERROR at roughly %s:%d.\n", __FILE__, __LINE__);
		fprintf(stderr, "I was able to open the whitelist but not write to it.");
		fprintf(stderr, "Try running dmesg and matching any errors at the end to the msr_safe source code.");
		fprintf(stderr, "Here's what the operating system says.\n");
		perror(NULL);
		exit(-1); // Die loudly.  If we can't access the whitelist, we're done.
	}
	close(whitelist_fd);
	free(whitelist);
}	
		
static void execute_batch(struct msr_batch_array *p){
	int rc; 
	rc = ioctl( batch_fd, X86_IOC_MSR_BATCH, p );
	if (rc != 0){
		fprintf(stderr, "ERROR:  ioctl returned %d\n", rc);
		perror(NULL);
		exit(0);
	}
}

static void mytimerhandler( int sig ) {
	static uint32_t sample_idx=0;
	if( sample_idx<MAX_SAMPLES ){
		execute_batch( &samples[sample_idx++] );
	}
}

static void set_up_itimer(time_t sec, suseconds_t usec){
	// Note that there are three timers and their associated signals.
	// 	ITIMER_REAL    -> SIGALRM 	wall-clock time
	//	ITIMER_VIRTUAL -> SIGVTALRM	process time
	//	ITIMER_PROF    -> SIGPROF	profiling time
	//					(includes syscalls made on behalf of the process)
	struct itimerval itv;
	struct sigaction sact;
	int rc;
	sigemptyset( &sact.sa_mask );		// macro to initialize sact.
	sact.sa_flags = 0;			// see man page for sigaction.
	sact.sa_handler = mytimerhandler;	// execute this function when the timer expires.
	sigaction( SIGPROF, &sact, NULL );	// set up our signal handler.

	itv.it_interval.tv_sec  =  sec; 	// Timer interval in seconds        
	itv.it_interval.tv_usec = usec;  	//   and microseconds.
	itv.it_value.tv_sec     =  sec;      	// Time to first signal,
	itv.it_value.tv_usec    = usec;     	//   same units.

	rc = setitimer( ITIMER_PROF, &itv, NULL );
	if(rc){
		fprintf(stderr, "QQQ %s:%d ERROR setitimer returned (%d) (%s).\n", 
			__FILE__, __LINE__, rc, strerror(errno) );
		exit(-1);	// No need to continue.  Bail out now.
	}
}

static void get_topology(){
	hwloc_topology_t topology;

        hwloc_topology_init(&topology);  // initialization
        hwloc_topology_load(topology);   // actual detection

	// Set a few static global variables.
        total_sockets = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_SOCKET);
        total_cores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
        total_threads = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PU);

        hwloc_topology_destroy(topology);

	fprintf(stdout, "hwloc reports %i sockets, %i total cores and %i total threads.\n", 
		total_sockets, total_cores, total_threads );
}


static void make_batch_from_scratchpad( struct msr_batch_array *p ){
		p->numops = batch[B_SCRATCHPAD].numops;
		p->ops = calloc( (size_t)(p->numops+1), sizeof(struct msr_batch_op) );	
		assert(p->ops);
		memcpy( p->ops, batch[B_SCRATCHPAD].ops, (size_t)(p->numops+1) * sizeof(struct msr_batch_op) );
}


static void set_up_batches(){
	int i;
	// Open the batch interface file.
	batch_fd = open("/dev/cpu/msr_batch", O_RDWR);
	if(batch_fd == -1){
		fprintf(stderr, "ERROR at roughly %s:%d.\n", __FILE__, __LINE__);
		fprintf(stderr, "Oh, bother:  I'm not able to update the msr_batch file.\n");
		fprintf(stderr, "1.  Did you remember to load the msr-safe kernel module?\n");
		fprintf(stderr, "2.  Did you give read and write permissions to the batch file?\n");
		fprintf(stderr, "Here's what the operating system says.\n");
		perror(NULL);
		exit(-1); // Die loudly.  If we can't access the whitelist, we're done.
	}

	// Allocate memory for our scratchpad.  
	// To create a new batch, zero out .ops and use a MAKE_[RD/WR]_BATCH_ENTRY to add
	// as many MSRs on as many CPUs as you like.  Then call make_batch_from_scratchpad
	// to copy the data over to the new batch.
	batch[B_SCRATCHPAD].ops = calloc( (size_t)(MAX_BATCH_OPS+1), sizeof(struct msr_batch_op) );	
	assert( batch[B_SCRATCHPAD].ops );

	// READ_ALL_CPU_ZERO
	// Grab all of the MSRs off of thread 0 to exercise the translator.
	batch[B_SCRATCHPAD].numops = 0;
	for(i=0; msr[i].address != -1 && i<MAX_BATCH_OPS; i++){
		fprintf(stderr, "Added %s to batch, i=%d.\n", msr[i].name, i);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,0,msr[i].address,0x0);
	}	
	make_batch_from_scratchpad( &batch[B_READ_ALL_CPU_ZERO] );
	
	// INITIALIZE_TO_ZERO
	batch[B_SCRATCHPAD].numops = 0;
	for(i=0; i<total_threads; i++){
		MAKE_WR_BATCH_ENTRY(batch,B_SCRATCHPAD,i,APERF,0x0);
		MAKE_WR_BATCH_ENTRY(batch,B_SCRATCHPAD,i,MPERF,0x0);
		MAKE_WR_BATCH_ENTRY(batch,B_SCRATCHPAD,i,CORE_PERF_LIMIT_REASONS,0x0);
	}
	make_batch_from_scratchpad( &batch[B_INITIALIZE_TO_ZERO] );

	// INITIALIZE_FIXED_COUNTERS
	 

	// SAMPLING
	batch[B_SCRATCHPAD].numops = 0;
	// Per-thread?
	for(i=0; i<total_threads; i++){
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,MPERF,0x0);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,APERF,0x0);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,PERF_STATUS,0x0);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,PERF_CTL,0x0);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,CORE_PERF_LIMIT_REASONS,0x0);
		MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,i,MPERF,0x0);
	}
	// Per-package
	MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,0,DRAM_ENERGY_STATUS,0x0);
	MAKE_RD_BATCH_ENTRY(batch,B_SCRATCHPAD,0,PKG_ENERGY_STATUS,0x0);
	
	// Make lots of these batches of samples.
	for( i=0; i<MAX_SAMPLES; i++){
		make_batch_from_scratchpad( &samples[i] );
	}

	
}

static void teardown_batches(){
	// Close the batch interface file.
	close( batch_fd );
}


// Declare a pointer to hold the original value for main().
// Being static makes sure nothing outside this file can see it.
static int (*main_orig)(int, char **, char **);

int main_hook(int argc, char **argv, char **envp)
{
	struct timeval start, stop;
	int ret = 0 ;
	dump_displayfamily_displaymodel();	// Useful to know which family and model you're working with.
	populate_whitelist();			// Makes sure you can access the MSRs you want to.
	get_topology();				// How many sockets/cores/threads do we have?

	set_up_batches();			// Grab the initial values (we'll be restoring some of them).

	execute_batch(&batch[B_INITIALIZE_TO_ZERO]);
	fprintf(stderr, "<<< About to execute batch.\n");
	execute_batch(&batch[B_READ_ALL_CPU_ZERO]);	// Read/write the MSRs using the msr-safe batch interface.
	fprintf(stderr, "<<< Returned from batch execution.\n");
	dump_batch(&batch[B_READ_ALL_CPU_ZERO]);
	fflush(NULL);



	set_up_itimer(0,100LL);		
	
	gettimeofday(&start, NULL);
	ret = main_orig(argc, argv, envp);
	gettimeofday(&stop, NULL);
	fprintf(stdout, "Elapsed time in main_orig: %lf seconds.\n",
			(stop.tv_sec - start.tv_sec)
			+ (stop.tv_usec - start.tv_usec)/1000000.0 );

	sleep(3);				// Capture cooldown behavior (depending on timer used)
	set_up_itimer(0,0);			// Disables the timer.
	dump_samples(samples);
	teardown_batches();

	return ret;
}

// We can't trap _start(), but we can trap __libc_start_main().
// See the definition at http://refspecs.linuxbase.org/LSB_3.1.0/LSB-generic/LSB-generic/baselib---libc-start-main-.html
int __libc_start_main(
    int (*main)(int, char **, char **),		// function pointer for main()
    int argc,					// number of arguments in argv
    char **argv,				// list of the arguments passed to the program
    int (*init)(int, char **, char **),		// function pointer for init()
    void (*fini)(void),				// function pointer for fini()
    void (*rtld_fini)(void),			// function pointer for rtld_fini
    void *stack_end)				// Haven't been able to track this down in the standards.
{
    main_orig = main;

    // Find the real __libc_start_main() and call it.
    // Note that typeof is used instead of typedef.
    typeof(&__libc_start_main) orig__libc_start_main = dlsym(RTLD_NEXT, "__libc_start_main");
    return orig__libc_start_main(main_hook, argc, argv, init, fini, rtld_fini, stack_end);
}
