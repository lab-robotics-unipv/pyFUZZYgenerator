#include <string.h>
#include "memFunc_yaw.h"

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createMemFunction_yaw(memFunction_yaw * mf, char* name, memFuncShape ms, double* poi) {
	if (mf == NULL) {
		return -1;
	}

	strcpy(mf->name, name);

	mf->ms = ms;

	mf->lPoi = getMFPoiNum(ms);
	if (mf->lPoi == -1) {
		return -1;
	}
	memcpy(mf->poi, poi, mf->lPoi*sizeof(double));

	return 0;
}

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		double			Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
double getPercentage_yaw(memFunction_yaw * mf , double inputValue)
{
	double slope;

	switch (mf->ms) {
		case TRI_MF:
			if (inputValue == mf->poi[1])
				return 1;
			else if (inputValue > mf->poi[0] && inputValue < mf->poi[1]) {
					slope = 1/(mf->poi[1]-mf->poi[0]);
					return slope*(inputValue - mf->poi[0]);
				} else if (inputValue > mf->poi[1] && inputValue < mf->poi[2]) {
					slope = 1/(mf->poi[1]-mf->poi[2]);
					return slope*(inputValue - mf->poi[2]);
				} else{
					return 0;
				}

		case TRAP_MF:
			if (inputValue >= mf->poi[1] && inputValue <= mf->poi[2])
				return 1;
		
			if (inputValue <= mf->poi[0] || inputValue >= mf->poi[3])
				return 0;

			else if (inputValue < mf->poi[1]) {
						slope = 1/(mf->poi[1]-mf->poi[0]);
						return slope*(inputValue - mf->poi[0]);
					} else if (inputValue > mf->poi[2]) {
						slope = 1/(mf->poi[2]-mf->poi[3]);
						return slope*(inputValue - mf->poi[3]);
						}

		case SPIKE_MF:
			if(inputValue==mf->poi[0])
				return 1;
			else
				return 0;
	}
}