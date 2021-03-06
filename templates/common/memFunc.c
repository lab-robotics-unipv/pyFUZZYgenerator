#include "memFunc.h"

/*! ALLOCATION AND CREATION OF A MEMBER FUNCTION (A FUZZY SET):
 *		output		mf			Fuzzy Set to init
 *		input		name		Label of the Fuzzy set
 *		input		ms			Member Function shape
 *		input		poi			Array containing the points of interest of the shape
 */
void createMemFunction(memFunction *mf, memFuncShape ms, const dataType *poi) {

	mf->ms = ms;

	mf->lPoi = getMFPoiNum(ms);

	mf->normalizedWeight = 0.0;

	mf->poi = poi;

}

/*! CALCULATION OF THE MEMBERSHIP TO A GIVEN FUZZY SET
 *			input		mf				Pointer to a Member Function
 *			input 		inputValue		Value of the input
 *
 *			return		dataType		Return the % of membership to a Fuzzy set (mf) given as input inputValue
 */
dataType getPercentage(memFunction *mf, dataType inputValue)
{
	dataType slope;
	dataType slope1;

	switch (mf->ms) {
		case TRI_MF:
			//We first consider the special case of Rectangle Triangle
			if (mf->poi[0] == mf->poi[1] && inputValue <= mf->poi[0]) {
				return 1;
			} else if (mf->poi[1] == mf->poi[2] && inputValue >= mf->poi[2]) {
				return 1;
			}

			//Normal Triangle
			if (inputValue <= mf->poi[0] || inputValue >= mf->poi[2])
				return 0;
			else {
				if (inputValue < mf->poi[1]) {
					slope = 1/(mf->poi[1]-mf->poi[0]);
					return slope*(inputValue - mf->poi[0]);
				} else if (inputValue > mf->poi[1]) {
					slope = 1/(mf->poi[1]-mf->poi[2]);
					return slope*(inputValue - mf->poi[2]);
				} else {
					return 1;
				}
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
				
		/* TODO : Insert an upper and lower bound to these functions in orther to get only 1 or 0 after a certain threshold */
		case SIGMOID_MF:
			//First point is the slope, the second one is the center of the Sigmoid
			//If slope > 0 the function is increasing 
			slope = exp( -mf->poi[0] * ( inputValue - mf->poi[1]));
			return 1 / ( 1 + slope );
		
		case GAUSSIAN_MF:
			//First point is sigma, the second one is the center of the Gaussian
			slope = pow(( inputValue - mf->poi[1] ), 2) ;
			return exp ( -slope / ( 2 * pow( mf->poi[0], 2 )) ); 
			
		case DIF_SIGMOID_MF:
			//First point is the slope, the second one is the center of the first Sigmoid
			//Third point is the slope, the fourth one is the center of the second Sigmoid
			slope = exp( -mf->poi[0] * ( inputValue - mf->poi[1]));
			slope1 = exp( -mf->poi[2] * ( inputValue - mf->poi[3]));
			return fabs( (1 / (1 + slope)) - ( 1 / ( 1 + slope1)));
	}
	//Warning: it should never reach this point
	return 0;
}

/*!	SET THE WEIGHT ASSOCIATED TO THE MEMBER FUNCTION
 * 			input		mf				Member Function
 * 			input		nWeight			The normalized weight to be associated to the Member Function
 * 
 * 			return		void
 */
void setNormalizedWeight(memFunction *mf, dataType nWeight){
	
	mf->normalizedWeight = nWeight;
}
