/* twiddling.h
 *
 * For bit twiddling.  Obvs.
 *
 * Authored by Barry Rountree.
 */


#include <stdint.h>	// For uint64_t and friends.

#ifndef __TWIDDLING_H
#define __TWIDDLING_H

// Create a 64-bit mask from bit m to n (63 >= m >= n >= 0).
#define MASK_RANGE_64(m,n) ( (m==63 && n==0) ? (~((uint64_t)(0))) : ((((uint64_t)1<<((m)-(n)+1))-1)<<(n)) )

// Create a 32-bit mask from bit m to n (31 >= m >= n >= 0).
#define MASK_RANGE_32(m,n) ( (m==32 && n==0) ? (~((uint32_t)(0))) : ((((uint32_t)1<<((m)-(n)+1))-1)<<(n)) )

// Return the value of x after applying bitmask (m,n) (63 >= m >= n >= 0).
#define MASK_VAL_64(x,m,n) (((uint64_t)(x)&MASK_RANGE_64((m),(n)))>>(n))

// Return the value of x after applying bitmask (m,n) (31 >= m >= n >= 0).
#define MASK_VAL_32(x,m,n) (((uint32_t)(x)&MASK_RANGE_32((m),(n)))>>(n))

#endif

