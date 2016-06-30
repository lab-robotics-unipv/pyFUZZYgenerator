#ifndef FUZZY_INPUT__yawH
#define FUZZY_INPUT__yawH

#include "definitions_yaw.h"
#include "memFunc_yaw.h"

#ifndef MAX_L_NAME_yaw
#error "MAX_L_NAME_yaw not defined: check definitions_yaw.h"
#endif

#ifndef MAX_N_MF_INPUT_yaw
#error "MAX_N_MF_INPUT_yaw not defined: check definitions_yaw.h"
#endif

//! FUZZY INPUT STRUCTURE
typedef struct {
	char name[MAX_L_NAME_yaw];		//!< Name of the input
	memFunction_yaw mf[MAX_N_MF_INPUT_yaw];	//!< List of Member Functions
	int nMF;					//!< Number of MF
	double minValue;			//!< Minimum value of the Fuzzy Input
	double maxValue;			//!< Maximum value of the Fuzzy Input
} fuzzyInput_yaw;

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
int createInput_yaw(fuzzyInput_yaw * fi, char* name, memFunction_yaw * MFs, int nMF, double min, double max);

/*! FIND MF GIVEN NAME
 *		input		fuzzy_input		Pointer to the Fuzzy Input struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getInputMFFromName_yaw(fuzzyInput_yaw * fuzzy_input, char * name);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY INPUT
 *			input		fuzzy_input		A Fuzzy Input
 *			input 		inputValue		Value of the input
 * 
 * 			output		output			The % of membership to a Fuzzy Input given an input value		
 */
void getPercentageFromInput_yaw(fuzzyInput_yaw * fuzzy_input, double inputValue, double * output);

#endif