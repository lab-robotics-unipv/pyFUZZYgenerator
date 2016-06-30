#ifndef FUZZY_LOGIC_x_displ_H
#define FUZZY_LOGIC_x_displ_H

#include "definitions_x_displ.h"

#include "rules_x_displ.h"
#include "fuzzyInput_x_displ.h"
#include "fuzzyOutput_x_displ.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	fuzzyInput_x_displ fInput[N_INPUT_x_displ];
	fuzzyOutput_x_displ fOutput[N_OUTPUT_x_displ];
	builtRule_x_displ rules[N_RULES_x_displ];
	double fuzzified[N_INPUT_x_displ * MAX_N_MF_INPUT_x_displ];
	double evaluated[N_OUTPUT_x_displ * MAX_N_MF_OUTPUT_x_displ];
} fuzzyLogic_x_displ;

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_x_displ(fuzzyLogic_x_displ * fl, fuzzyInput_x_displ * inputs, fuzzyOutput_x_displ * outputs, rule_x_displ * r);

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
void fuzzify_x_displ(fuzzyLogic_x_displ * fl, double * inputs);

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_x_displ(fuzzyLogic_x_displ * fl);

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_x_displ(fuzzyLogic_x_displ * fl, double * outputs);

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input or -1 if not found
 */
int getInputFromName_x_displ(fuzzyLogic_x_displ * fl, char * name);

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output or -1 if not found
 */
int getOutputFromName_x_displ(fuzzyLogic_x_displ * fl, char * name);

#endif