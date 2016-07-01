#include <string.h>

#include "definitions_pitch.h"
#include "fuzzyLogic_pitch.h"

int newState_pitch(fuzzyLogic_pitch * fl) {

	/*
	 * INPUT VARIABLES
	 */

	int flag;
	fuzzyInput_pitch fi[N_INPUT_pitch];

	// Input variable: pitch_diff
	// Difference between the actual and desired pitch value
	memFunction_pitch MF_pitch_diff[3];

	double poi_pitch_diff_neg[] = { -5.0, -5.0, 0.0 };
	createMemFunction_pitch(&(MF_pitch_diff[0]), "neg", TRI_MF, poi_pitch_diff_neg);
	double poi_pitch_diff_zero[] = { -5.0, 0.0, 5.0 };
	createMemFunction_pitch(&(MF_pitch_diff[1]), "zero", TRI_MF, poi_pitch_diff_zero);
	double poi_pitch_diff_pos[] = { 0.0, 5.0, 5.0 };
	createMemFunction_pitch(&(MF_pitch_diff[2]), "pos", TRI_MF, poi_pitch_diff_pos);

	flag = createInput_pitch(&(fi[0]), "pitch_diff", MF_pitch_diff, 3, -5.0, 5.0);
	if (flag < 0) {
		return 1;
	}

	// Input variable: pitch_diffVel
	// Difference between the actual and desired pitch velocity
	memFunction_pitch MF_pitch_diffVel[3];

	double poi_pitch_diffVel_neg[] = { -1.0, -1.0, 0.0 };
	createMemFunction_pitch(&(MF_pitch_diffVel[0]), "neg", TRI_MF, poi_pitch_diffVel_neg);
	double poi_pitch_diffVel_zero[] = { -1.0, 0.0, 1.0 };
	createMemFunction_pitch(&(MF_pitch_diffVel[1]), "zero", TRI_MF, poi_pitch_diffVel_zero);
	double poi_pitch_diffVel_pos[] = { 0.0, 1.0, 1.0 };
	createMemFunction_pitch(&(MF_pitch_diffVel[2]), "pos", TRI_MF, poi_pitch_diffVel_pos);

	flag = createInput_pitch(&(fi[1]), "pitch_diffVel", MF_pitch_diffVel, 3, -1.0, 1.0);
	if (flag < 0) {
		return 1;
	}


	/*
	 * OUTPUT VARIABLES
	 */

	fuzzyOutput_pitch fo[N_OUTPUT_pitch];

	// Output variable: front_prop_diff
	// Derivative of the voltage on the front propeller
	memFunction_pitch MF_front_prop_diff[3];

	double poi_front_prop_diff_neg[] = { -0.5, -0.5, 0.0 };
	createMemFunction_pitch(&(MF_front_prop_diff[0]), "neg", TRI_MF, poi_front_prop_diff_neg);
	double poi_front_prop_diff_zero[] = { -0.5, 0.0, 0.5 };
	createMemFunction_pitch(&(MF_front_prop_diff[1]), "zero", TRI_MF, poi_front_prop_diff_zero);
	double poi_front_prop_diff_pos[] = { 0.0, 0.5, 0.5 };
	createMemFunction_pitch(&(MF_front_prop_diff[2]), "pos", TRI_MF, poi_front_prop_diff_pos);

	flag = createOutput_pitch(&(fo[0]), "front_prop_diff", MF_front_prop_diff, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: rear_prop_diff
	// Derivative of the voltage on the rear propeller
	memFunction_pitch MF_rear_prop_diff[3];

	double poi_rear_prop_diff_neg[] = { -0.5, -0.5, 0.0 };
	createMemFunction_pitch(&(MF_rear_prop_diff[0]), "neg", TRI_MF, poi_rear_prop_diff_neg);
	double poi_rear_prop_diff_zero[] = { -0.5, 0.0, 0.5 };
	createMemFunction_pitch(&(MF_rear_prop_diff[1]), "zero", TRI_MF, poi_rear_prop_diff_zero);
	double poi_rear_prop_diff_pos[] = { 0.0, 0.5, 0.5 };
	createMemFunction_pitch(&(MF_rear_prop_diff[2]), "pos", TRI_MF, poi_rear_prop_diff_pos);

	flag = createOutput_pitch(&(fo[1]), "rear_prop_diff", MF_rear_prop_diff, 3);
	if (flag < 0) {
		return 1;
	}


	/*
	 * RULES
	 */

	rule_pitch rules[N_RULES_pitch];

	rules[0].nIfRules = 2;

	strcpy(rules[0].ifRules[0].name, "pitch_diff");
	strcpy(rules[0].ifRules[0].mf, "neg");
	strcpy(rules[0].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[0].ifRules[1].mf, "neg");

	rules[0].thenValue = 1;
	
	rules[0].nThenRules = 2;

	strcpy(rules[0].thenRules[0].name, "front_prop_diff");
	strcpy(rules[0].thenRules[0].mf, "pos");
	strcpy(rules[0].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[0].thenRules[1].mf, "neg");

	rules[1].nIfRules = 2;

	strcpy(rules[1].ifRules[0].name, "pitch_diff");
	strcpy(rules[1].ifRules[0].mf, "neg");
	strcpy(rules[1].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[1].ifRules[1].mf, "zero");

	rules[1].thenValue = 1;
	
	rules[1].nThenRules = 2;

	strcpy(rules[1].thenRules[0].name, "front_prop_diff");
	strcpy(rules[1].thenRules[0].mf, "pos");
	strcpy(rules[1].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[1].thenRules[1].mf, "neg");

	rules[2].nIfRules = 2;

	strcpy(rules[2].ifRules[0].name, "pitch_diff");
	strcpy(rules[2].ifRules[0].mf, "neg");
	strcpy(rules[2].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[2].ifRules[1].mf, "pos");

	rules[2].thenValue = 1;
	
	rules[2].nThenRules = 2;

	strcpy(rules[2].thenRules[0].name, "front_prop_diff");
	strcpy(rules[2].thenRules[0].mf, "zero");
	strcpy(rules[2].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[2].thenRules[1].mf, "zero");

	rules[3].nIfRules = 2;

	strcpy(rules[3].ifRules[0].name, "pitch_diff");
	strcpy(rules[3].ifRules[0].mf, "zero");
	strcpy(rules[3].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[3].ifRules[1].mf, "neg");

	rules[3].thenValue = 1;
	
	rules[3].nThenRules = 2;

	strcpy(rules[3].thenRules[0].name, "front_prop_diff");
	strcpy(rules[3].thenRules[0].mf, "pos");
	strcpy(rules[3].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[3].thenRules[1].mf, "neg");

	rules[4].nIfRules = 2;

	strcpy(rules[4].ifRules[0].name, "pitch_diff");
	strcpy(rules[4].ifRules[0].mf, "zero");
	strcpy(rules[4].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[4].ifRules[1].mf, "zero");

	rules[4].thenValue = 1;
	
	rules[4].nThenRules = 2;

	strcpy(rules[4].thenRules[0].name, "front_prop_diff");
	strcpy(rules[4].thenRules[0].mf, "zero");
	strcpy(rules[4].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[4].thenRules[1].mf, "zero");

	rules[5].nIfRules = 2;

	strcpy(rules[5].ifRules[0].name, "pitch_diff");
	strcpy(rules[5].ifRules[0].mf, "zero");
	strcpy(rules[5].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[5].ifRules[1].mf, "pos");

	rules[5].thenValue = 1;
	
	rules[5].nThenRules = 2;

	strcpy(rules[5].thenRules[0].name, "front_prop_diff");
	strcpy(rules[5].thenRules[0].mf, "neg");
	strcpy(rules[5].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[5].thenRules[1].mf, "pos");

	rules[6].nIfRules = 2;

	strcpy(rules[6].ifRules[0].name, "pitch_diff");
	strcpy(rules[6].ifRules[0].mf, "pos");
	strcpy(rules[6].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[6].ifRules[1].mf, "neg");

	rules[6].thenValue = 1;
	
	rules[6].nThenRules = 2;

	strcpy(rules[6].thenRules[0].name, "front_prop_diff");
	strcpy(rules[6].thenRules[0].mf, "zero");
	strcpy(rules[6].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[6].thenRules[1].mf, "zero");

	rules[7].nIfRules = 2;

	strcpy(rules[7].ifRules[0].name, "pitch_diff");
	strcpy(rules[7].ifRules[0].mf, "pos");
	strcpy(rules[7].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[7].ifRules[1].mf, "zero");

	rules[7].thenValue = 1;
	
	rules[7].nThenRules = 2;

	strcpy(rules[7].thenRules[0].name, "front_prop_diff");
	strcpy(rules[7].thenRules[0].mf, "neg");
	strcpy(rules[7].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[7].thenRules[1].mf, "pos");

	rules[8].nIfRules = 2;

	strcpy(rules[8].ifRules[0].name, "pitch_diff");
	strcpy(rules[8].ifRules[0].mf, "pos");
	strcpy(rules[8].ifRules[1].name, "pitch_diffVel");
	strcpy(rules[8].ifRules[1].mf, "pos");

	rules[8].thenValue = 1;
	
	rules[8].nThenRules = 2;

	strcpy(rules[8].thenRules[0].name, "front_prop_diff");
	strcpy(rules[8].thenRules[0].mf, "neg");
	strcpy(rules[8].thenRules[1].name, "rear_prop_diff");
	strcpy(rules[8].thenRules[1].mf, "pos");


	/*
	 * LOGIC
	 */

	flag = createLogic_pitch(fl, fi, fo, rules);
	if ( flag < 0 ) {
		return 3;
	}

	return 0;
}