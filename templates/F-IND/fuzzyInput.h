#ifndef FUZZY_INPUT_H
#define FUZZY_INPUT_H

#include "defCommon.h"
#include "memFunc.h"

//! FUZZY INPUT STRUCTURE
typedef struct {
	memFunction *mf;	//!< List of Member Functions
	uint_t nMF;					//!< Number of MF
	dataType minValue;			//!< Minimum value of the Fuzzy Input
	dataType maxValue;			//!< Maximum value of the Fuzzy Input
} fuzzyInput;

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
void createInput(fuzzyInput *fi, memFunction *MFs, uint_t nMF, dataType min, dataType max);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
uint_t getPercentageFromInput(fuzzyInput *fuzzy_input, dataType inputValue, dataType *output);

#endif
