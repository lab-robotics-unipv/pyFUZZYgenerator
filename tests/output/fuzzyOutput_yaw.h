#ifndef FUZZY_OUTPUT_yaw_H
#define FUZZY_OUTPUT_yaw_H

#include "definitions_yaw.h"
#include "memFunc_yaw.h"

#ifndef MAX_L_NAME_yaw
#error "MAX_L_NAME_yaw not defined: check definitions_yaw.h"
#endif

#ifndef MAX_N_MF_OUTPUT_yaw
#error "MAX_N_MF_yaw not defined: check definitions_yaw.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_yaw];		//!< Name of the output
	memFunction_yaw mf[MAX_N_MF_OUTPUT_yaw];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_yaw;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_yaw(fuzzyOutput_yaw * fo, char* name, memFunction_yaw * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_yaw(fuzzyOutput_yaw * fuzzy_output, char * name);

#endif