/* dfdm.h
 * 
 * A cheap interface for getting the "display family" and 
 * "display model" out of Intel processors.
 *
 * Might want to eventually return those values instead of printing them, 
 * but let's put that off until we actually need that functionality.
 *
 * Authored by Barry Rountree.
 */

#ifndef __DFDM_H
#define __DFDM_H

void dump_displayfamily_displaymodel();

#endif
