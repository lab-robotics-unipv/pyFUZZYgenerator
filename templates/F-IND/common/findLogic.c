#include <stdint.h>
#include <string.h>

#include "findLogic.h"

squareduint_t two_to_n(uint_t ninput) {
    return ((squareduint_t) 1)<<ninput;
}

void createFindLogic(findLogic *fl, findInput *inputs, findOutput *outputs, uint_t ninput) {
    fl->fInput = inputs;
    fl->fOutput = outputs;
	fl->ninput = ninput;
    fl->two_to_ndim = two_to_n(ninput);
}


/*! CALCULATE THE INDEX, GIVEN AN INPUT TO THE FIND SYSTEM.
 * 	THIS FUNCTIONS WORKS ***ONLY*** FOR F-IND SYSTEMS.
 * 	IN ORDER TO SEE HOW F-IND WORKS LOOK AT THE DOCUMENTATION
 *		input			fl				FIND logic
 *
 *		return							Index 
 */
dataType calculateFindIndex(findLogic *fl, dataType *inputs){

    squareduint_t mask=0, mask_ones = 0;
    uint_t skipped = 0, i, j;
    //mask: a mask of bit used to navigate all possible combinations
    //mask_ones: has ones where values are exactly 1.0f

    dataType fuzzified[fl->ninput];
    uint_t fuzzified_index[fl->ninput];

    dataType var[fl->fOutput->nMF];
    memset(var, 0, fl->fOutput->nMF*sizeof(dataType));

    for ( i = 0; i < fl->ninput; i++) {
        fuzzified_index[i] = getPercentageFromFindInput(&(fl->fInput[i]), inputs[i], &fuzzified[i]);
    }

    // This creates a "cache" to map the path that must be skipped.
    for(i=0; i < fl->ninput; i++)
        if(fuzzified[i]==1.0f)
            mask_ones = ( mask_ones ) | (((squareduint_t )1) << (fl->ninput - i -1));

    // The mask should create all possible combinations between 0 and TWO_TO_NDIM
    for(mask=0x00; mask < fl->two_to_ndim; mask++){

        // Optimization: we check if we will need to skip the current loop before actually doing any multiplication
        // (A loop is skipped when we should multiply with a 0 inside it and is mapped by mask_ones.
        // The idea here is that we have a 1 in mask_ones where there is a 1 (i-th position), and if mask is 1 in the i-th position
        // as well the multiplication is zero in the end.
        if((mask & mask_ones) != 0){
            skipped++;
            continue;
        }

        // Actual "costly" computation: the product of all variables in the current path
        float result_j = 1;
        float sum_j = 0;
        for (i = 0; i < fl->ninput; i++) {
            if (((mask >> (fl->ninput - i - 1)) & 1) == 0) {
                result_j *= fuzzified[i];
                sum_j += fl->fInput[i].mf[fuzzified_index[i]].normalizedWeight;
            }
            else
            {
                result_j *= 1 - fuzzified[i];
                sum_j += fl->fInput[i].mf[fuzzified_index[i] + 1].normalizedWeight;
            }
        }

        for (j = 0; j < fl->fOutput->nMF; j++) {
		    memFunction eMF = fl->fOutput->mf[j];
            dataType tmp = getPercentage(&eMF, sum_j);
            if(tmp != 0) {
                var[j] += tmp * result_j;
                if (j < (fl->fOutput->nMF - 1)) {
                    var[j + 1] += (1 - tmp) * result_j;
                }
                break;
            }
        }
    }

		dataType div = 1.0 / (fl->fOutput->nMF - 1.0);
		dataType indexValue = 0.0;

		for (i = 0; i < fl->fOutput->nMF; i++)
			indexValue += div * i * var[i];

		indexValue = 100 * indexValue;


		return (indexValue);
	}
