#ifndef FUZZY_OUTPUT_y_displ_H
#define FUZZY_OUTPUT_y_displ_H

#include "definitions_y_displ.h"
#include "memFunc_y_displ.h"

#ifndef MAX_L_NAME_y_displ
#error "MAX_L_NAME_y_displ not defined: check definitions_y_displ.h"
#endif

#ifndef MAX_N_MF_OUTPUT_y_displ
#error "MAX_N_MF_y_displ not defined: check definitions_y_displ.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_y_displ];		//!< Name of the output
	memFunction_y_displ mf[MAX_N_MF_OUTPUT_y_displ];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_y_displ;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_y_displ(fuzzyOutput_y_displ * fo, char* name, memFunction_y_displ * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_y_displ(fuzzyOutput_y_displ * fuzzy_output, char * name);

#endif