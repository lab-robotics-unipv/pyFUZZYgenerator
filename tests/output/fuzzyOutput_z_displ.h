#ifndef FUZZY_OUTPUT_z_displ_H
#define FUZZY_OUTPUT_z_displ_H

#include "definitions_z_displ.h"
#include "memFunc_z_displ.h"

#ifndef MAX_L_NAME_z_displ
#error "MAX_L_NAME_z_displ not defined: check definitions_z_displ.h"
#endif

#ifndef MAX_N_MF_OUTPUT_z_displ
#error "MAX_N_MF_z_displ not defined: check definitions_z_displ.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_z_displ];		//!< Name of the output
	memFunction_z_displ mf[MAX_N_MF_OUTPUT_z_displ];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_z_displ;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_z_displ(fuzzyOutput_z_displ * fo, char* name, memFunction_z_displ * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_z_displ(fuzzyOutput_z_displ * fuzzy_output, char * name);

#endif