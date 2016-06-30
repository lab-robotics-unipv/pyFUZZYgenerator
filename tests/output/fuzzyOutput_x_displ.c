#include <string.h>
#include "fuzzyOutput_x_displ.h"

/*! INIT OF A FUZZY OUTPUT
 *		output		fo			Fuzzy output to init
 *		input		name		Label of the Fuzzy output
 *		input		MFs			Array of membership functions
 *		input 		nMF			Number of membership functions to be included
 *
 *		return					Flag: -1 if error, 0 otherwise
 */
int createOutput_x_displ(fuzzyOutput_x_displ * fo, char* name, memFunction_x_displ * MFs, int nMF) {
	if (fo == NULL) {
		return -1;
	}
	strcpy(fo->name, name);

	fo->nMF = nMF;
	if (nMF > MAX_N_MF_OUTPUT_x_displ) {
		return -1;
	}

	if (MFs == NULL) {
		return -1;
	}
	memcpy(fo->mf, MFs, nMF*sizeof(memFunction_x_displ));

	return 0;
}

/*! FIND MF GIVEN NAME
 *		input		fuzzy_output	Pointer to the Fuzzy Output struct
 *		input		name			Name of the MF
 *
 *		return						Index of the MF or -1 if not found
 */
int getOutputMFFromName_x_displ(fuzzyOutput_x_displ * fuzzy_output, char * name) {
	int i;
	for (i = 0; i < fuzzy_output->nMF; i++) {
		if ( strcmp(name, fuzzy_output->mf[i].name) == 0 ) {
			return i;
		}
	}
	return -1;
}