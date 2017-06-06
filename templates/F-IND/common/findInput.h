#ifndef FIND_INPUT_H
#define FIND_INPUT_H

#include "defCommon.h"
#include "memFunc.h"

//! FIND INPUT STRUCTURE
typedef struct {
	memFunction *mf;	//!< List of Member Functions
	uint_t nMF;					//!< Number of MF
	dataType minValue;			//!< Minimum value of the FIND Input
	dataType maxValue;			//!< Maximum value of the FIND Input
} findInput;

/*! INIT OF A FIND INPUT
 *		output		fi			Fuzzy input to init
 *		input		name		Label of the FIND input
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 * 		input		min			Minimum value of the FIND Input
 * 		input 		max			Maximum value of the FIND Input
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
void createFindInput(findInput *fi, memFunction *MFs, uint_t nMF, dataType min, dataType max);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FIND INPUT
 *			input		fuzzy_input		A FIND Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
uint_t getPercentageFromFindInput(findInput *fuzzy_input, dataType inputValue, dataType *output);

#endif
