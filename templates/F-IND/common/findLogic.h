#ifndef FIND_LOGIC_H
#define FIND_LOGIC_H

#include "findInput.h"
#include "findOutput.h"

//! FIND LOGIC STRUCTURE
typedef struct {
	uint_t ninput;
	squareduint_t two_to_ndim;
	findInput *fInput;
	findOutput *fOutput;
} findLogic;

/*! CONSTRUCTOR OF THE FIND LOGIC FOR FIND SYSTEM
 *		output			fl			FIND logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 */
void createFindLogic(findLogic *fl, findInput *inputs, findOutput *outputs, uint_t ninput);

/*! CALCULATE THE INDEX, GIVEN AN INPUT TO THE FIND SYSTEM.
 * 	THIS FUNCTIONS WORKS ***ONLY*** FOR F-IND SYSTEMS.
 * 	IN ORDER TO SEE HOW F-IND WORKS LOOK AT THE DOCUMENTATION
 *		input			fl				FIND logic
 *
 *		return							Index 
 */
dataType calculateFindIndex(findLogic *fl, dataType *index);

#endif
