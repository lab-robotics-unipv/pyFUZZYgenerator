#include <stdlib.h>
#include <string.h>
#include "fuzzyLogic_yaw.h"

/*! CONSTRUCTOR OF THE FUZZY LOGIC
 *		output			fl			Fuzzy logic to init
 *		input			inputs		Vector of inputs of the logic
 *		input			outputs		Vector of outputs of the logic
 *		input			rules		Vector of rules to add to the logic
 *
 *		return						Flag: -1 if error, 0 otherwise
 */
int createLogic_yaw(fuzzyLogic_yaw * fl, fuzzyInput_yaw * inputs, fuzzyOutput_yaw * outputs, rule_yaw * r) {
	if (fl == NULL || inputs == NULL || outputs == NULL || r == NULL) {
		return -1;
	}
	memcpy(fl->fInput, inputs, N_INPUT_yaw*sizeof(fuzzyInput_yaw));
	memcpy(fl->fOutput, outputs, N_OUTPUT_yaw*sizeof(fuzzyOutput_yaw));

	int i, j, k;
	int index, index2;
	for (i = 0; i < N_RULES_yaw; i++) {
		fl->rules[i].nIfRules = r[i].nIfRules;
		fl->rules[i].thenValue = r[i].thenValue;
		fl->rules[i].nThenRules = r[i].nThenRules;

		for (j = 0; j < r[i].nIfRules; j++) {
			index = getInputFromName_yaw(fl, r[i].ifRules[j].name);
			if (index<0) {
				return -1;
			} else {
				fl->rules[i].ifRulesIndex[j] = index;
			}
			index2 = getInputMFFromName_yaw(&(fl->fInput[index]), r[i].ifRules[j].mf);
			if (index2 < 0) {
				return -1;
			} else {
				fl->rules[i].ifRulesMFIndex[j] = index2;
			}
		}

		for (j = 0; j < r[i].nThenRules; j++) {
			index = getOutputFromName_yaw(fl, r[i].thenRules[j].name);
			if (index<0) {
				return -1;
			} else {
				fl->rules[i].thenRulesIndex[j] = index;
			}
			index2 = getOutputMFFromName_yaw(&(fl->fOutput[index]), r[i].thenRules[j].mf);
			if (index2 < 0) {
				return -1;
			} else {
				fl->rules[i].thenRulesMFIndex[j] = index2;
			}
		}
	}
	return 0;
}

/*! FUZZIFY THE INPUTS
 *		input/output	fl					Fuzzy logic
 *		input			inputs				Inputs of the fuzzy logic			
 */
//The output type of fuzzifiedValues should be changed to pointer( no more pointer to pointer)
void fuzzify_yaw(fuzzyLogic_yaw * fl, double * inputs) {
	int i;
	for ( i = 0; i < N_INPUT_yaw; i++) {
			getPercentageFromInput_yaw( &(fl->fInput[i]), inputs[i], &(fl->fuzzified[i * MAX_N_MF_INPUT_yaw]));
	}
}

/*! EVALUATE THE RULES GIVEN THE FUZZIFIED INPUTS
 *		input/output		fl			Fuzzy logic
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int evaluateRules_yaw(fuzzyLogic_yaw * fl) {
	int i, j;

	// Set evaluations to zeros
	for ( i = 0; i < N_OUTPUT_yaw; i++) {
		for ( j = 0; j < fl->fOutput[i].nMF; j++) {
			fl->evaluated[i * MAX_N_MF_OUTPUT_yaw + j] = 0;
		}
	}

	double minValue;
	for ( i = 0; i < N_RULES_yaw; i++) {
		minValue = 2;	//!< The values are always less than 1
		builtRule_yaw * r = &(fl->rules[i]);
		for ( j = 0; j < r->nIfRules; j++) {
			// TODO: possibility to choose the function
			minValue = MIN(minValue, fl->fuzzified[(r->ifRulesIndex[j]) * MAX_N_MF_INPUT_yaw + r->ifRulesMFIndex[j]]);
		}

		minValue = MIN(minValue, r->thenValue);
		
		double * e;
		for ( j = 0; j < r->nThenRules; j++) {
			e = &(fl->evaluated[(r->thenRulesIndex[j]) * MAX_N_MF_OUTPUT_yaw + r->thenRulesMFIndex[j]]);
			*e = *e == 0 ? minValue : MIN(minValue, *e);
		}
	}
	return 0;
}

/*! DEFUZZIFY THE EVALUATED RULES
 *		input			fl				Fuzzy logic
 *		output			outputs			Vector of the outputs of the fuzzy control
 *
 *		return							-1 if smtg went wrong, 0 otherwise
 */
int defuzzify_yaw(fuzzyLogic_yaw * fl, double * outputs) {
	int i, j;
	double sum = 0;
	double aux = 0;
	
	for ( i = 0; i < N_OUTPUT_yaw; i++) {
		for ( j = 0; j < fl->fOutput[i].nMF; j++) {
			sum = sum + fl->evaluated[i * MAX_N_MF_OUTPUT_yaw + j];
			aux = aux + (fl->fOutput[i].mf[j].poi[0]) * (fl->evaluated[i * MAX_N_MF_OUTPUT_yaw + j]);
		}
		outputs[i] = aux/sum;
		aux = 0;
		sum = 0;
	}
	
}

/*! FIND INPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the input
 *
 *		return							Index of the input
 */
int getInputFromName_yaw(fuzzyLogic_yaw * fl, char * name) {
	int i;
	for ( i = 0 ; i < N_INPUT_yaw; i++) {
		if (strcmp(fl->fInput[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

/*! FIND OUTPUT INDEX GIVEN NAME
 *		input			fl				Fuzzy logic
 *		input			name			Name of the output
 *
 *		return							Index of the output
 */
int getOutputFromName_yaw(fuzzyLogic_yaw * fl, char * name) {
	int i;
	for ( i = 0 ; i < N_INPUT_yaw; i++) {
		if (strcmp(fl->fOutput[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

