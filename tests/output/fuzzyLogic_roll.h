#ifndef FUZZY_LOGIC_roll_H
#define FUZZY_LOGIC_roll_H

#include "definitions_roll.h"

#include "rules_roll.h"
#include "fuzzyInput_roll.h"
#include "fuzzyOutput_roll.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	fuzzyInput_roll fInput[N_INPUT_roll];
	fuzzyOutput_roll fOutput[N_OUTPUT_roll];
	builtRule_roll rules[N_RULES_roll];
	double fuzzified[N_INPUT_roll * MAX_N_MF_INPUT_roll];
	double evaluated[N_OUTPUT_roll * MAX_N_MF_OUTPUT_roll];
} fuzzyLogic_roll;

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_roll(fuzzyLogic_roll * fl, fuzzyInput_roll * inputs, fuzzyOutput_roll * outputs, rule_roll * r);

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
void fuzzify_roll(fuzzyLogic_roll * fl, double * inputs);

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_roll(fuzzyLogic_roll * fl);

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_roll(fuzzyLogic_roll * fl, double * outputs);

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input or -1 if not found
 */
int getInputFromName_roll(fuzzyLogic_roll * fl, char * name);

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output or -1 if not found
 */
int getOutputFromName_roll(fuzzyLogic_roll * fl, char * name);

#endif