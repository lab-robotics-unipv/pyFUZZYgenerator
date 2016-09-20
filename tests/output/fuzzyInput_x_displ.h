#ifndef FUZZY_INPUT__x_displH
#define FUZZY_INPUT__x_displH

#include "definitions_x_displ.h"
#include "memFunc_x_displ.h"

#ifndef MAX_L_NAME_x_displ
#error "MAX_L_NAME_x_displ not defined: check definitions_x_displ.h"
#endif

#ifndef MAX_N_MF_INPUT_x_displ
#error "MAX_N_MF_INPUT_x_displ not defined: check definitions_x_displ.h"
#endif

//! FUZZY INPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_x_displ];		//!< Name of the input
	memFunction_x_displ mf[MAX_N_MF_INPUT_x_displ];	//!< List of Member Functions
	int nMF;					//!< Number of MF
	double minValue;			//!< Minimum value of the Fuzzy Input
	double maxValue;			//!< Maximum value of the Fuzzy Input
} fuzzyInput_x_displ;

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
int createInput_x_displ(fuzzyInput_x_displ * fi, char* name, memFunction_x_displ * MFs, int nMF, double min, double max);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_input		Pointer to the Fuzzy Input struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getInputMFFromName_x_displ(fuzzyInput_x_displ * fuzzy_input, char * name);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
void getPercentageFromInput_x_displ(fuzzyInput_x_displ * fuzzy_input, double inputValue, double * output);

#endif