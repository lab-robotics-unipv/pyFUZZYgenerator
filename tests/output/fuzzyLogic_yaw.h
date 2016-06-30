#ifndef FUZZY_LOGIC_yaw_H
#define FUZZY_LOGIC_yaw_H

#include "definitions_yaw.h"

#include "rules_yaw.h"
#include "fuzzyInput_yaw.h"
#include "fuzzyOutput_yaw.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	fuzzyInput_yaw fInput[N_INPUT_yaw];
	fuzzyOutput_yaw fOutput[N_OUTPUT_yaw];
	builtRule_yaw rules[N_RULES_yaw];
	double fuzzified[N_INPUT_yaw * MAX_N_MF_INPUT_yaw];
	double evaluated[N_OUTPUT_yaw * MAX_N_MF_OUTPUT_yaw];
} fuzzyLogic_yaw;

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_yaw(fuzzyLogic_yaw * fl, fuzzyInput_yaw * inputs, fuzzyOutput_yaw * outputs, rule_yaw * r);

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
void fuzzify_yaw(fuzzyLogic_yaw * fl, double * inputs);

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_yaw(fuzzyLogic_yaw * fl);

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_yaw(fuzzyLogic_yaw * fl, double * outputs);

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input or -1 if not found
 */
int getInputFromName_yaw(fuzzyLogic_yaw * fl, char * name);

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output or -1 if not found
 */
int getOutputFromName_yaw(fuzzyLogic_yaw * fl, char * name);

#endif