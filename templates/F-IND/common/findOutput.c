#include <stdint.h>
#include "memFunc.h"
#include "findOutput.h"

/*! INIT OF A FIND OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 */
void createFindOutput(findOutput *fo, memFunction *MFs, uint_t nMF) {


	fo->nMF = nMF;

	fo->mf = MFs;

}
