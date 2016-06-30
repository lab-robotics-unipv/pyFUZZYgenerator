#ifndef FUZZY_OUTPUT_pitch_H
#define FUZZY_OUTPUT_pitch_H

#include "definitions_pitch.h"
#include "memFunc_pitch.h"

#ifndef MAX_L_NAME_pitch
#error "MAX_L_NAME_pitch not defined: check definitions_pitch.h"
#endif

#ifndef MAX_N_MF_OUTPUT_pitch
#error "MAX_N_MF_pitch not defined: check definitions_pitch.h"
#endif

//! FUZZY OUTPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_pitch];		//!< Name of the output
	memFunction_pitch mf[MAX_N_MF_OUTPUT_pitch];	//!< List of the Member Functions
	int nMF;					//!< Number of MF
} fuzzyOutput_pitch;

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_pitch(fuzzyOutput_pitch * fo, char* name, memFunction_pitch * MFs, int nMF);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_pitch(fuzzyOutput_pitch * fuzzy_output, char * name);

#endif