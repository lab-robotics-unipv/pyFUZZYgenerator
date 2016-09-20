#ifndef FUZZY_LOGIC_y_displ_H
#define FUZZY_LOGIC_y_displ_H

#include "definitions_y_displ.h"

#include "rules_y_displ.h"
#include "fuzzyInput_y_displ.h"
#include "fuzzyOutput_y_displ.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	fuzzyInput_y_displ fInput[N_INPUT_y_displ];
	fuzzyOutput_y_displ fOutput[N_OUTPUT_y_displ];
	builtRule_y_displ rules[N_RULES_y_displ];
	double fuzzified[N_INPUT_y_displ * MAX_N_MF_INPUT_y_displ];
	double evaluated[N_OUTPUT_y_displ * MAX_N_MF_OUTPUT_y_displ];
} fuzzyLogic_y_displ;

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_y_displ(fuzzyLogic_y_displ * fl, fuzzyInput_y_displ * inputs, fuzzyOutput_y_displ * outputs, rule_y_displ * r);

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
void fuzzify_y_displ(fuzzyLogic_y_displ * fl, double * inputs);

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_y_displ(fuzzyLogic_y_displ * fl);

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_y_displ(fuzzyLogic_y_displ * fl, double * outputs);

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input or -1 if not found
 */
int getInputFromName_y_displ(fuzzyLogic_y_displ * fl, char * name);

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output or -1 if not found
 */
int getOutputFromName_y_displ(fuzzyLogic_y_displ * fl, char * name);

#endif