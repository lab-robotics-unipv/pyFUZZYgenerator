#ifndef FUZZY_LOGIC_H
#define FUZZY_LOGIC_H

#include "fuzzyInput.h"
#include "fuzzyOutput.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	uint_t ninput;
	squareduint_t two_to_ndim;
	fuzzyInput *fInput;
	fuzzyOutput *fOutput;
} fuzzyLogic;

/*! CONSTRUCTOR OF THE FUZZY LOGIC FOR FIND SYSTEM
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
void createFindLogic(fuzzyLogic *fl, fuzzyInput *inputs, fuzzyOutput *outputs, uint_t ninput);

/*! CALCULATE THE INDEX, GIVEN AN INPUT TO THE FUZZY SYSTEM.
 * 	THIS FUNCTIONS WORKS ***ONLY*** FOR F-IND SYSTEMS.
 * 	IN ORDER TO SEE HOW F-IND WORKS LOOK AT THE DOCUMENTATION
 *		input			fl				Fuzzy logic
 *
 *		return							Index 
 */
dataType calculateIndex(fuzzyLogic *fl, dataType *index);

#endif
