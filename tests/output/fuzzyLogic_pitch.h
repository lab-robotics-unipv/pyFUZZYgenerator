#ifndef FUZZY_LOGIC_pitch_H
#define FUZZY_LOGIC_pitch_H

#include "definitions_pitch.h"

#include "rules_pitch.h"
#include "fuzzyInput_pitch.h"
#include "fuzzyOutput_pitch.h"

//! FUZZY LOGIC STRUCTURE
typedef struct {
	fuzzyInput_pitch fInput[N_INPUT_pitch];
	fuzzyOutput_pitch fOutput[N_OUTPUT_pitch];
	builtRule_pitch rules[N_RULES_pitch];
	double fuzzified[N_INPUT_pitch * MAX_N_MF_INPUT_pitch];
	double evaluated[N_OUTPUT_pitch * MAX_N_MF_OUTPUT_pitch];
} fuzzyLogic_pitch;

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_pitch(fuzzyLogic_pitch * fl, fuzzyInput_pitch * inputs, fuzzyOutput_pitch * outputs, rule_pitch * r);

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
void fuzzify_pitch(fuzzyLogic_pitch * fl, double * inputs);

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_pitch(fuzzyLogic_pitch * fl);

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_pitch(fuzzyLogic_pitch * fl, double * outputs);

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input or -1 if not found
 */
int getInputFromName_pitch(fuzzyLogic_pitch * fl, char * name);

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output or -1 if not found
 */
int getOutputFromName_pitch(fuzzyLogic_pitch * fl, char * name);

#endif