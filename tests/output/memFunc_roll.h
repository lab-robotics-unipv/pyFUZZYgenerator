#ifndef MEMBERSHIP_FUNCTION_roll_H
#define MEMBERSHIP_FUNCTION_roll_H

#include "definitions_roll.h"
#include "MFShapes.h"

#ifndef MAX_L_NAME_roll
#error "MAX_L_NAME_roll not defined: check definitions_roll.h"
#endif

#ifndef MAX_N_POI_roll
#error "MAX_N_POI_roll not defined: check definitions_roll.h"
#endif

//! MEMBER FUNCTIONS
typedef struct {
	char name[MAX_L_NAME_roll];		//!< Name of the Fuzzy Set
	memFuncShape ms;			//!< Shape of the Fuzzy Set
	double poi[MAX_N_POI_roll];		//!< Points of interest of the Fuzzy Set
	int lPoi;					//!< Numbers of POI
} memFunction_roll;

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createMemFunction_roll(memFunction_roll * mf, char* name, memFuncShape ms, double* poi);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		double			Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
double getPercentage_roll(memFunction_roll * mf , double inputValue);

#endif