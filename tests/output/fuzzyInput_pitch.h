#ifndef FUZZY_INPUT__pitchH
#define FUZZY_INPUT__pitchH

#include "definitions_pitch.h"
#include "memFunc_pitch.h"

#ifndef MAX_L_NAME_pitch
#error "MAX_L_NAME_pitch not defined: check definitions_pitch.h"
#endif

#ifndef MAX_N_MF_INPUT_pitch
#error "MAX_N_MF_INPUT_pitch not defined: check definitions_pitch.h"
#endif

//! FUZZY INPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_pitch];		//!< Name of the input
	memFunction_pitch mf[MAX_N_MF_INPUT_pitch];	//!< List of Member Functions
	int nMF;					//!< Number of MF
	double minValue;			//!< Minimum value of the Fuzzy Input
	double maxValue;			//!< Maximum value of the Fuzzy Input
} fuzzyInput_pitch;

/*! INIT OF A FUZZY INPUT
 *		output		fi			Fuzzy input to init
 *		input		name		Label of the Fuzzy input
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 * 		input		min			Minimum value of the Fuzzy Input
 * 		input 		max			Maximum value of the Fuzzy Input
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createInput_pitch(fuzzyInput_pitch * fi, char* name, memFunction_pitch * MFs, int nMF, double min, double max);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_input		Pointer to the Fuzzy Input struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getInputMFFromName_pitch(fuzzyInput_pitch * fuzzy_input, char * name);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
void getPercentageFromInput_pitch(fuzzyInput_pitch * fuzzy_input, double inputValue, double * output);

#endif