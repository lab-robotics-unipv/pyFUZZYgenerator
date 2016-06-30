#ifndef MEMBERSHIP_FUNCTION_yaw_H
#define MEMBERSHIP_FUNCTION_yaw_H

#include "definitions_yaw.h"
#include "MFShapes.h"

#ifndef MAX_L_NAME_yaw
#error "MAX_L_NAME_yaw not defined: check definitions_yaw.h"
#endif

#ifndef MAX_N_POI_yaw
#error "MAX_N_POI_yaw not defined: check definitions_yaw.h"
#endif

//! MEMBER FUNCTIONS
typedef struct {
	char name[MAX_L_NAME_yaw];		//!< Name of the Fuzzy Set
	memFuncShape ms;			//!< Shape of the Fuzzy Set
	double poi[MAX_N_POI_yaw];		//!< Points of interest of the Fuzzy Set
	int lPoi;					//!< Numbers of POI
} memFunction_yaw;

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createMemFunction_yaw(memFunction_yaw * mf, char* name, memFuncShape ms, double* poi);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		double			Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
double getPercentage_yaw(memFunction_yaw * mf , double inputValue);

#endif