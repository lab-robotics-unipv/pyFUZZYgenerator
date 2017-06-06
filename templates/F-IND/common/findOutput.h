#ifndef FIND_OUTPUT_H
#define FIND_OUTPUT_H

#include <stdint.h>

#include "memFunc.h"

//! FIND OUTPUT STRUCTURE
typedef struct {
	memFunction *mf;	//!< List of the Member Functions
	uint_t nMF;					//!< Number of MF
} findOutput;

/*! INIT OF A FIND OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 */
void createFindOutput(findOutput *fo, memFunction *MFs, uint_t nMF);

#endif