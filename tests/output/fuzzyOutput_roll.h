#ifndef FUZZY_OUTPUT_roll_H
#define FUZZY_OUTPUT_roll_H

#include "definitions_roll.h"
#include "memFunc_roll.h"

#ifndef MAX_L_NAME_roll
#error "MAX_L_NAME_roll not defined: check definitions_roll.h"
#endif

#ifndef MAX_N_MF_OUTPUT_roll
#error "MAX_N_MF_roll not defined: check definitions_roll.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_roll];		//!< Name of the output
	memFunction_roll mf[MAX_N_MF_OUTPUT_roll];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_roll;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_roll(fuzzyOutput_roll * fo, char* name, memFunction_roll * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_roll(fuzzyOutput_roll * fuzzy_output, char * name);

#endif