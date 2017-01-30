#include <stdio.h>
#include "init_Prova.h"

int main(){
	
	
	/*
	 * This is a simple test for the FIND system.
	 * 
	 * There are 2 Inputs variables, each defined by 3 Membership functions ( A,B,C) defined as follows:
	 * 
	 * A -> Triangle defined in X : ( 0.0 , 20.0 ) Rectangle in 0.0
	 * B -> Triangle defined in X : ( 0.0, 40.0 ) With maximum in 20.0
	 * C -> Triangle defined in X : ( 20.0, 40.0 ) Rectangle in 40.0
	 * 
	 * For both inputs the BEST function is A
	 * For both inputs the WORST function is C
	 */
	 
	fuzzyLogic_Prova fl;
	int flag = newState_Prova(&fl);
	if ( flag < 0 )
		printf("Some error occured");
	
	/*
	 * In order to change the INPUTS variable you have to change the following array
	 */
	 
	double input[N_INPUT_Prova] = { 10.0, 0.0};
	double output;
	int i,j;
	
	fuzzify_Prova(&fl, &(input[0]));
	
	for ( i = 0; i < N_INPUT_Prova; i++) 
		for ( j = 0; j < fl.fInput[i].nMF; j++) 
		printf("%s\t%s\tEvaluated :\t%f\n", fl.fInput[i].name , fl.fInput[i].mf[j].name, fl.fuzzified[i * MAX_N_MF_INPUT_Prova + j]);	
			

	output = calculateIndex_Prova(&fl);	
	printf("\nIndex calculated by FIND system is : %f\n", output);
	
	return 0;
}
