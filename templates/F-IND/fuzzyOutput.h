#ifndef FUZZY_OUTPUT_H
#define FUZZY_OUTPUT_H

#include <stdint.h>

#include "memFunc.h"

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	memFunction *mf;	//!< List of the Member Functions
	uint_t nMF;					//!< Number of MF
} fuzzyOutput;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
void createOutput(fuzzyOutput *fo, memFunction *MFs, uint_t nMF);

#endif