#ifndef MEMBERSHIP_FUNCTION_H
#define MEMBERSHIP_FUNCTION_H

#include <stdint.h>
#include <math.h>

#include "defCommon.h"
#include "MFShapes.h"

//! MEMBER FUNCTIONS
typedef struct {
	memFuncShape ms;			//!< Shape of the Fuzzy Set
	const dataType *poi;		//!< Points of interest of the Fuzzy Set
	int lPoi;					//!< Numbers of POI
	dataType normalizedWeight;	//!< Normalized weight associated to the Fuzzy Set
} memFunction;

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
void createMemFunction(memFunction *mf, memFuncShape ms, const dataType *poi);

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		double			Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
dataType getPercentage(memFunction *mf, dataType inputValue);

/*!	SET THE WEIGHT ASSOCIATED TO THE MEMBER FUNCTION
 * 			input		mf				Member Function
 * 			input		nWeight			The normalized weight to be associated to the Member Function
 * 
 * 			return		void
 */
void setNormalizedWeight(memFunction *mf, dataType nWeight);
#endif
