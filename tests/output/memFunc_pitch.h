#ifndef MEMBERSHIP_FUNCTION_pitch_H
#define MEMBERSHIP_FUNCTION_pitch_H

#include "definitions_pitch.h"
#include "MFShapes.h"

#ifndef MAX_L_NAME_pitch
#error "MAX_L_NAME_pitch not defined: check definitions_pitch.h"
#endif

#ifndef MAX_N_POI_pitch
#error "MAX_N_POI_pitch not defined: check definitions_pitch.h"
#endif

//! MEMBER FUNCTIONS
typedef struct {
	char name[MAX_L_NAME_pitch];		//!< Name of the Fuzzy Set
	memFuncShape ms;			//!< Shape of the Fuzzy Set
	double poi[MAX_N_POI_pitch];		//!< Points of interest of the Fuzzy Set
	int lPoi;					//!< Numbers of POI
} memFunction_pitch;

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createMemFunction_pitch(memFunction_pitch * mf, char* name, memFuncShape ms, double* poi);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		double			Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
double getPercentage_pitch(memFunction_pitch * mf , double inputValue);

#endif