#ifndef FUZZY_OUTPUT_x_displ_H
#define FUZZY_OUTPUT_x_displ_H

#include "definitions_x_displ.h"
#include "memFunc_x_displ.h"

#ifndef MAX_L_NAME_x_displ
#error "MAX_L_NAME_x_displ not defined: check definitions_x_displ.h"
#endif

#ifndef MAX_N_MF_OUTPUT_x_displ
#error "MAX_N_MF_x_displ not defined: check definitions_x_displ.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_x_displ];		//!< Name of the output
	memFunction_x_displ mf[MAX_N_MF_OUTPUT_x_displ];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_x_displ;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_x_displ(fuzzyOutput_x_displ * fo, char* name, memFunction_x_displ * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_x_displ(fuzzyOutput_x_displ * fuzzy_output, char * name);

#endif