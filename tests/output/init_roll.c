#include <string.h>

#include "definitions_roll.h"
#include "fuzzyLogic_roll.h"

int newState_roll(fuzzyLogic_roll * fl) {

	/*
	 * INPUT VARIABLES
	 */

	int flag;
	fuzzyInput_roll fi[N_INPUT_roll];

	// Input variable: roll_diff
	// Difference between the actual and desired roll value
	memFunction_roll MF_roll_diff[3];

	double poi_roll_diff_neg[] = { -5.0, -5.0, 0.0 };
	createMemFunction_roll(&(MF_roll_diff[0]), "neg", TRI_MF, poi_roll_diff_neg);
	double poi_roll_diff_zero[] = { -5.0, 0.0, 5.0 };
	createMemFunction_roll(&(MF_roll_diff[1]), "zero", TRI_MF, poi_roll_diff_zero);
	double poi_roll_diff_pos[] = { 0.0, 5.0, 5.0 };
	createMemFunction_roll(&(MF_roll_diff[2]), "pos", TRI_MF, poi_roll_diff_pos);

	flag = createInput_roll(&(fi[0]), "roll_diff", MF_roll_diff, 3, -5.0, 5.0);
	if (flag < 0) {
		return 1;
	}

	// Input variable: roll_diffVel
	// Difference between the actual and desired roll velocity
	memFunction_roll MF_roll_diffVel[3];

	double poi_roll_diffVel_neg[] = { -1.0, -1.0, 0.0 };
	createMemFunction_roll(&(MF_roll_diffVel[0]), "neg", TRI_MF, poi_roll_diffVel_neg);
	double poi_roll_diffVel_zero[] = { -1.0, 0.0, 1.0 };
	createMemFunction_roll(&(MF_roll_diffVel[1]), "zero", TRI_MF, poi_roll_diffVel_zero);
	double poi_roll_diffVel_pos[] = { 0.0, 1.0, 1.0 };
	createMemFunction_roll(&(MF_roll_diffVel[2]), "pos", TRI_MF, poi_roll_diffVel_pos);

	flag = createInput_roll(&(fi[1]), "roll_diffVel", MF_roll_diffVel, 3, -1.0, 1.0);
	if (flag < 0) {
		return 1;
	}


	/*
	 * OUTPUT VARIABLES
	 */

	fuzzyOutput_roll fo[N_OUTPUT_roll];

	// Output variable: left_prop_diff
	// Derivative of the voltage on the left propeller
	memFunction_roll MF_left_prop_diff[3];

	double poi_left_prop_diff_neg[] = { -0.5 };
	createMemFunction_roll(&(MF_left_prop_diff[0]), "neg", SPIKE_MF, poi_left_prop_diff_neg);
	double poi_left_prop_diff_zero[] = { 0.0 };
	createMemFunction_roll(&(MF_left_prop_diff[1]), "zero", SPIKE_MF, poi_left_prop_diff_zero);
	double poi_left_prop_diff_pos[] = { 0.5 };
	createMemFunction_roll(&(MF_left_prop_diff[2]), "pos", SPIKE_MF, poi_left_prop_diff_pos);

	flag = createOutput_roll(&(fo[0]), "left_prop_diff", MF_left_prop_diff, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: right_prop_diff
	// Derivative of the voltage on the right propeller
	memFunction_roll MF_right_prop_diff[3];

	double poi_right_prop_diff_neg[] = { -0.5 };
	createMemFunction_roll(&(MF_right_prop_diff[0]), "neg", SPIKE_MF, poi_right_prop_diff_neg);
	double poi_right_prop_diff_zero[] = { 0.0 };
	createMemFunction_roll(&(MF_right_prop_diff[1]), "zero", SPIKE_MF, poi_right_prop_diff_zero);
	double poi_right_prop_diff_pos[] = { 0.5 };
	createMemFunction_roll(&(MF_right_prop_diff[2]), "pos", SPIKE_MF, poi_right_prop_diff_pos);

	flag = createOutput_roll(&(fo[1]), "right_prop_diff", MF_right_prop_diff, 3);
	if (flag < 0) {
		return 1;
	}


	/*
	 * RULES
	 */

	rule_roll rules[N_RULES_roll];

	rules[0].nIfRules = 2;

	strcpy(rules[0].ifRules[0].name, "roll_diff");
	strcpy(rules[0].ifRules[0].mf, "neg");
	strcpy(rules[0].ifRules[1].name, "roll_diffVel");
	strcpy(rules[0].ifRules[1].mf, "neg");

	rules[0].thenValue = 1;
	
	rules[0].nThenRules = 2;

	strcpy(rules[0].thenRules[0].name, "left_prop_diff");
	strcpy(rules[0].thenRules[0].mf, "neg");
	strcpy(rules[0].thenRules[1].name, "right_prop_diff");
	strcpy(rules[0].thenRules[1].mf, "pos");

	rules[1].nIfRules = 2;

	strcpy(rules[1].ifRules[0].name, "roll_diff");
	strcpy(rules[1].ifRules[0].mf, "neg");
	strcpy(rules[1].ifRules[1].name, "roll_diffVel");
	strcpy(rules[1].ifRules[1].mf, "zero");

	rules[1].thenValue = 1;
	
	rules[1].nThenRules = 2;

	strcpy(rules[1].thenRules[0].name, "left_prop_diff");
	strcpy(rules[1].thenRules[0].mf, "neg");
	strcpy(rules[1].thenRules[1].name, "right_prop_diff");
	strcpy(rules[1].thenRules[1].mf, "pos");

	rules[2].nIfRules = 2;

	strcpy(rules[2].ifRules[0].name, "roll_diff");
	strcpy(rules[2].ifRules[0].mf, "neg");
	strcpy(rules[2].ifRules[1].name, "roll_diffVel");
	strcpy(rules[2].ifRules[1].mf, "pos");

	rules[2].thenValue = 1;
	
	rules[2].nThenRules = 2;

	strcpy(rules[2].thenRules[0].name, "left_prop_diff");
	strcpy(rules[2].thenRules[0].mf, "zero");
	strcpy(rules[2].thenRules[1].name, "right_prop_diff");
	strcpy(rules[2].thenRules[1].mf, "zero");

	rules[3].nIfRules = 2;

	strcpy(rules[3].ifRules[0].name, "roll_diff");
	strcpy(rules[3].ifRules[0].mf, "zero");
	strcpy(rules[3].ifRules[1].name, "roll_diffVel");
	strcpy(rules[3].ifRules[1].mf, "neg");

	rules[3].thenValue = 1;
	
	rules[3].nThenRules = 2;

	strcpy(rules[3].thenRules[0].name, "left_prop_diff");
	strcpy(rules[3].thenRules[0].mf, "neg");
	strcpy(rules[3].thenRules[1].name, "right_prop_diff");
	strcpy(rules[3].thenRules[1].mf, "pos");

	rules[4].nIfRules = 2;

	strcpy(rules[4].ifRules[0].name, "roll_diff");
	strcpy(rules[4].ifRules[0].mf, "zero");
	strcpy(rules[4].ifRules[1].name, "roll_diffVel");
	strcpy(rules[4].ifRules[1].mf, "zero");

	rules[4].thenValue = 1;
	
	rules[4].nThenRules = 2;

	strcpy(rules[4].thenRules[0].name, "left_prop_diff");
	strcpy(rules[4].thenRules[0].mf, "zero");
	strcpy(rules[4].thenRules[1].name, "right_prop_diff");
	strcpy(rules[4].thenRules[1].mf, "zero");

	rules[5].nIfRules = 2;

	strcpy(rules[5].ifRules[0].name, "roll_diff");
	strcpy(rules[5].ifRules[0].mf, "zero");
	strcpy(rules[5].ifRules[1].name, "roll_diffVel");
	strcpy(rules[5].ifRules[1].mf, "pos");

	rules[5].thenValue = 1;
	
	rules[5].nThenRules = 2;

	strcpy(rules[5].thenRules[0].name, "left_prop_diff");
	strcpy(rules[5].thenRules[0].mf, "pos");
	strcpy(rules[5].thenRules[1].name, "right_prop_diff");
	strcpy(rules[5].thenRules[1].mf, "neg");

	rules[6].nIfRules = 2;

	strcpy(rules[6].ifRules[0].name, "roll_diff");
	strcpy(rules[6].ifRules[0].mf, "pos");
	strcpy(rules[6].ifRules[1].name, "roll_diffVel");
	strcpy(rules[6].ifRules[1].mf, "neg");

	rules[6].thenValue = 1;
	
	rules[6].nThenRules = 2;

	strcpy(rules[6].thenRules[0].name, "left_prop_diff");
	strcpy(rules[6].thenRules[0].mf, "zero");
	strcpy(rules[6].thenRules[1].name, "right_prop_diff");
	strcpy(rules[6].thenRules[1].mf, "zero");

	rules[7].nIfRules = 2;

	strcpy(rules[7].ifRules[0].name, "roll_diff");
	strcpy(rules[7].ifRules[0].mf, "pos");
	strcpy(rules[7].ifRules[1].name, "roll_diffVel");
	strcpy(rules[7].ifRules[1].mf, "zero");

	rules[7].thenValue = 1;
	
	rules[7].nThenRules = 2;

	strcpy(rules[7].thenRules[0].name, "left_prop_diff");
	strcpy(rules[7].thenRules[0].mf, "pos");
	strcpy(rules[7].thenRules[1].name, "right_prop_diff");
	strcpy(rules[7].thenRules[1].mf, "neg");

	rules[8].nIfRules = 2;

	strcpy(rules[8].ifRules[0].name, "roll_diff");
	strcpy(rules[8].ifRules[0].mf, "pos");
	strcpy(rules[8].ifRules[1].name, "roll_diffVel");
	strcpy(rules[8].ifRules[1].mf, "pos");

	rules[8].thenValue = 1;
	
	rules[8].nThenRules = 2;

	strcpy(rules[8].thenRules[0].name, "left_prop_diff");
	strcpy(rules[8].thenRules[0].mf, "pos");
	strcpy(rules[8].thenRules[1].name, "right_prop_diff");
	strcpy(rules[8].thenRules[1].mf, "neg");


	/*
	 * LOGIC
	 */

	flag = createLogic_roll(fl, fi, fo, rules);
	if ( flag < 0 ) {
		return 3;
	}

	return 0;
}