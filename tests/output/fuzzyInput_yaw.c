#include <string.h>
#include "fuzzyInput_yaw.h"

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
int createInput_yaw(fuzzyInput_yaw * fi, char* name, memFunction_yaw * MFs, int nMF, double min, double max) {
	if (fi == NULL) {
		return -1;
	}
	strcpy(fi->name, name);
	
	fi->minValue = min;
	fi->maxValue = max;

	fi->nMF = nMF;
	if (nMF > MAX_N_MF_INPUT_yaw) {
		return -1;
	}

	if (MFs == NULL) {
		return -1;
	}
	memcpy(fi->mf, MFs, nMF*sizeof(memFunction_yaw));

	return 0;
}

/*! FIND MF GIVEN NAME
 *		input		fuzzy_input		Pointer to the Fuzzy Input struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getInputMFFromName_yaw(fuzzyInput_yaw * fuzzy_input, char * name) {
	int i;
	for (i = 0; i < fuzzy_input->nMF; i++) {
		if ( strcmp(name, fuzzy_input->mf[i].name) == 0 ) {
			return i;
		}
	}
	return -1;
}

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
void getPercentageFromInput_yaw(fuzzyInput_yaw * fuzzy_input, double inputValue, double * output) {
	if (inputValue < fuzzy_input->minValue) {
		inputValue = fuzzy_input->minValue;
	} else if (inputValue > fuzzy_input->maxValue) {
		inputValue = fuzzy_input->maxValue;
	}
	
	int i;	
	for ( i = 0; i < fuzzy_input->nMF; i++) {
		output[i] = getPercentage_yaw(&(fuzzy_input->mf[i]), inputValue);		
	}		
}