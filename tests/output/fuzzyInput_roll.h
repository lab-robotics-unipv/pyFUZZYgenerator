#ifndef FUZZY_INPUT__rollH
#define FUZZY_INPUT__rollH

#include "definitions_roll.h"
#include "memFunc_roll.h"

#ifndef MAX_L_NAME_roll
#error "MAX_L_NAME_roll not defined: check definitions_roll.h"
#endif

#ifndef MAX_N_MF_INPUT_roll
#error "MAX_N_MF_INPUT_roll not defined: check definitions_roll.h"
#endif

//! FUZZY INPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_roll];		//!< Name of the input
	memFunction_roll mf[MAX_N_MF_INPUT_roll];	//!< List of Member Functions
	int nMF;					//!< Number of MF
	double minValue;			//!< Minimum value of the Fuzzy Input
	double maxValue;			//!< Maximum value of the Fuzzy Input
} fuzzyInput_roll;

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
int createInput_roll(fuzzyInput_roll * fi, char* name, memFunction_roll * MFs, int nMF, double min, double max);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_input		Pointer to the Fuzzy Input struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getInputMFFromName_roll(fuzzyInput_roll * fuzzy_input, char * name);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
void getPercentageFromInput_roll(fuzzyInput_roll * fuzzy_input, double inputValue, double * output);

#endif