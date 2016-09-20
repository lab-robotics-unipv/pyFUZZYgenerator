#include <string.h>

#include "definitions_z_displ.h"
#include "fuzzyLogic_z_displ.h"

int newState_z_displ(fuzzyLogic_z_displ * fl) {

	/*
	 * INPUT VARIABLES
	 */

	int flag;
	fuzzyInput_z_displ fi[N_INPUT_z_displ];

	// Input variable: z_diff
	// Difference between the actual and desired z
	memFunction_z_displ MF_z_diff[3];

	double poi_z_diff_neg[] = { -5.0, -5.0, 0.0 };
	createMemFunction_z_displ(&(MF_z_diff[0]), "neg", TRI_MF, poi_z_diff_neg);
	double poi_z_diff_zero[] = { -5.0, 0.0, 5.0 };
	createMemFunction_z_displ(&(MF_z_diff[1]), "zero", TRI_MF, poi_z_diff_zero);
	double poi_z_diff_pos[] = { 0.0, 5.0, 5.0 };
	createMemFunction_z_displ(&(MF_z_diff[2]), "pos", TRI_MF, poi_z_diff_pos);

	flag = createInput_z_displ(&(fi[0]), "z_diff", MF_z_diff, 3, -5.0, 5.0);
	if (flag < 0) {
		return 1;
	}

	// Input variable: z_diffVel
	// Difference between the actual and desired z velocity
	memFunction_z_displ MF_z_diffVel[3];

	double poi_z_diffVel_neg[] = { -1.0, -1.0, 0.0 };
	createMemFunction_z_displ(&(MF_z_diffVel[0]), "neg", TRI_MF, poi_z_diffVel_neg);
	double poi_z_diffVel_zero[] = { -1.0, 0.0, 1.0 };
	createMemFunction_z_displ(&(MF_z_diffVel[1]), "zero", TRI_MF, poi_z_diffVel_zero);
	double poi_z_diffVel_pos[] = { 0.0, 1.0, 1.0 };
	createMemFunction_z_displ(&(MF_z_diffVel[2]), "pos", TRI_MF, poi_z_diffVel_pos);

	flag = createInput_z_displ(&(fi[1]), "z_diffVel", MF_z_diffVel, 3, -1.0, 1.0);
	if (flag < 0) {
		return 1;
	}


	/*
	 * OUTPUT VARIABLES
	 */

	fuzzyOutput_z_displ fo[N_OUTPUT_z_displ];

	// Output variable: front_prop
	// Derivative of the alpha angle on the front propeller
	memFunction_z_displ MF_front_prop[3];

	double poi_front_prop_neg[] = { -0.5 };
	createMemFunction_z_displ(&(MF_front_prop[0]), "neg", SPIKE_MF, poi_front_prop_neg);
	double poi_front_prop_zero[] = { 0.0 };
	createMemFunction_z_displ(&(MF_front_prop[1]), "zero", SPIKE_MF, poi_front_prop_zero);
	double poi_front_prop_pos[] = { 0.5 };
	createMemFunction_z_displ(&(MF_front_prop[2]), "pos", SPIKE_MF, poi_front_prop_pos);

	flag = createOutput_z_displ(&(fo[0]), "front_prop", MF_front_prop, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: left_prop
	// Derivative of the alpha angle on the left propeller
	memFunction_z_displ MF_left_prop[3];

	double poi_left_prop_neg[] = { -0.5 };
	createMemFunction_z_displ(&(MF_left_prop[0]), "neg", SPIKE_MF, poi_left_prop_neg);
	double poi_left_prop_zero[] = { 0.0 };
	createMemFunction_z_displ(&(MF_left_prop[1]), "zero", SPIKE_MF, poi_left_prop_zero);
	double poi_left_prop_pos[] = { 0.5 };
	createMemFunction_z_displ(&(MF_left_prop[2]), "pos", SPIKE_MF, poi_left_prop_pos);

	flag = createOutput_z_displ(&(fo[1]), "left_prop", MF_left_prop, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: rear_prop
	// Derivative of the alpha angle on the rear propeller
	memFunction_z_displ MF_rear_prop[3];

	double poi_rear_prop_neg[] = { -0.5 };
	createMemFunction_z_displ(&(MF_rear_prop[0]), "neg", SPIKE_MF, poi_rear_prop_neg);
	double poi_rear_prop_zero[] = { 0.0 };
	createMemFunction_z_displ(&(MF_rear_prop[1]), "zero", SPIKE_MF, poi_rear_prop_zero);
	double poi_rear_prop_pos[] = { 0.5 };
	createMemFunction_z_displ(&(MF_rear_prop[2]), "pos", SPIKE_MF, poi_rear_prop_pos);

	flag = createOutput_z_displ(&(fo[2]), "rear_prop", MF_rear_prop, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: right_prop
	// Derivative of the alpha angle on the right propeller
	memFunction_z_displ MF_right_prop[3];

	double poi_right_prop_neg[] = { -0.5 };
	createMemFunction_z_displ(&(MF_right_prop[0]), "neg", SPIKE_MF, poi_right_prop_neg);
	double poi_right_prop_zero[] = { 0.0 };
	createMemFunction_z_displ(&(MF_right_prop[1]), "zero", SPIKE_MF, poi_right_prop_zero);
	double poi_right_prop_pos[] = { 0.5 };
	createMemFunction_z_displ(&(MF_right_prop[2]), "pos", SPIKE_MF, poi_right_prop_pos);

	flag = createOutput_z_displ(&(fo[3]), "right_prop", MF_right_prop, 3);
	if (flag < 0) {
		return 1;
	}


	/*
	 * RULES
	 */

	rule_z_displ rules[N_RULES_z_displ];

	rules[0].nIfRules = 2;

	strcpy(rules[0].ifRules[0].name, "z_diff");
	strcpy(rules[0].ifRules[0].mf, "neg");
	strcpy(rules[0].ifRules[1].name, "z_diffVel");
	strcpy(rules[0].ifRules[1].mf, "neg");

	rules[0].thenValue = 1;
	
	rules[0].nThenRules = 4;

	strcpy(rules[0].thenRules[0].name, "front_prop");
	strcpy(rules[0].thenRules[0].mf, "neg");
	strcpy(rules[0].thenRules[1].name, "left_prop");
	strcpy(rules[0].thenRules[1].mf, "neg");
	strcpy(rules[0].thenRules[2].name, "rear_prop");
	strcpy(rules[0].thenRules[2].mf, "neg");
	strcpy(rules[0].thenRules[3].name, "right_prop");
	strcpy(rules[0].thenRules[3].mf, "neg");

	rules[1].nIfRules = 2;

	strcpy(rules[1].ifRules[0].name, "z_diff");
	strcpy(rules[1].ifRules[0].mf, "neg");
	strcpy(rules[1].ifRules[1].name, "z_diffVel");
	strcpy(rules[1].ifRules[1].mf, "zero");

	rules[1].thenValue = 1;
	
	rules[1].nThenRules = 4;

	strcpy(rules[1].thenRules[0].name, "front_prop");
	strcpy(rules[1].thenRules[0].mf, "neg");
	strcpy(rules[1].thenRules[1].name, "left_prop");
	strcpy(rules[1].thenRules[1].mf, "neg");
	strcpy(rules[1].thenRules[2].name, "rear_prop");
	strcpy(rules[1].thenRules[2].mf, "neg");
	strcpy(rules[1].thenRules[3].name, "right_prop");
	strcpy(rules[1].thenRules[3].mf, "neg");

	rules[2].nIfRules = 2;

	strcpy(rules[2].ifRules[0].name, "z_diff");
	strcpy(rules[2].ifRules[0].mf, "neg");
	strcpy(rules[2].ifRules[1].name, "z_diffVel");
	strcpy(rules[2].ifRules[1].mf, "pos");

	rules[2].thenValue = 1;
	
	rules[2].nThenRules = 4;

	strcpy(rules[2].thenRules[0].name, "front_prop");
	strcpy(rules[2].thenRules[0].mf, "zero");
	strcpy(rules[2].thenRules[1].name, "left_prop");
	strcpy(rules[2].thenRules[1].mf, "zero");
	strcpy(rules[2].thenRules[2].name, "rear_prop");
	strcpy(rules[2].thenRules[2].mf, "zero");
	strcpy(rules[2].thenRules[3].name, "right_prop");
	strcpy(rules[2].thenRules[3].mf, "zero");

	rules[3].nIfRules = 2;

	strcpy(rules[3].ifRules[0].name, "z_diff");
	strcpy(rules[3].ifRules[0].mf, "zero");
	strcpy(rules[3].ifRules[1].name, "z_diffVel");
	strcpy(rules[3].ifRules[1].mf, "neg");

	rules[3].thenValue = 1;
	
	rules[3].nThenRules = 4;

	strcpy(rules[3].thenRules[0].name, "front_prop");
	strcpy(rules[3].thenRules[0].mf, "neg");
	strcpy(rules[3].thenRules[1].name, "left_prop");
	strcpy(rules[3].thenRules[1].mf, "neg");
	strcpy(rules[3].thenRules[2].name, "rear_prop");
	strcpy(rules[3].thenRules[2].mf, "neg");
	strcpy(rules[3].thenRules[3].name, "right_prop");
	strcpy(rules[3].thenRules[3].mf, "neg");

	rules[4].nIfRules = 2;

	strcpy(rules[4].ifRules[0].name, "z_diff");
	strcpy(rules[4].ifRules[0].mf, "zero");
	strcpy(rules[4].ifRules[1].name, "z_diffVel");
	strcpy(rules[4].ifRules[1].mf, "zero");

	rules[4].thenValue = 1;
	
	rules[4].nThenRules = 4;

	strcpy(rules[4].thenRules[0].name, "front_prop");
	strcpy(rules[4].thenRules[0].mf, "zero");
	strcpy(rules[4].thenRules[1].name, "left_prop");
	strcpy(rules[4].thenRules[1].mf, "zero");
	strcpy(rules[4].thenRules[2].name, "rear_prop");
	strcpy(rules[4].thenRules[2].mf, "zero");
	strcpy(rules[4].thenRules[3].name, "right_prop");
	strcpy(rules[4].thenRules[3].mf, "zero");

	rules[5].nIfRules = 2;

	strcpy(rules[5].ifRules[0].name, "z_diff");
	strcpy(rules[5].ifRules[0].mf, "zero");
	strcpy(rules[5].ifRules[1].name, "z_diffVel");
	strcpy(rules[5].ifRules[1].mf, "pos");

	rules[5].thenValue = 1;
	
	rules[5].nThenRules = 4;

	strcpy(rules[5].thenRules[0].name, "front_prop");
	strcpy(rules[5].thenRules[0].mf, "pos");
	strcpy(rules[5].thenRules[1].name, "left_prop");
	strcpy(rules[5].thenRules[1].mf, "pos");
	strcpy(rules[5].thenRules[2].name, "rear_prop");
	strcpy(rules[5].thenRules[2].mf, "pos");
	strcpy(rules[5].thenRules[3].name, "right_prop");
	strcpy(rules[5].thenRules[3].mf, "pos");

	rules[6].nIfRules = 2;

	strcpy(rules[6].ifRules[0].name, "z_diff");
	strcpy(rules[6].ifRules[0].mf, "pos");
	strcpy(rules[6].ifRules[1].name, "z_diffVel");
	strcpy(rules[6].ifRules[1].mf, "neg");

	rules[6].thenValue = 1;
	
	rules[6].nThenRules = 4;

	strcpy(rules[6].thenRules[0].name, "front_prop");
	strcpy(rules[6].thenRules[0].mf, "zero");
	strcpy(rules[6].thenRules[1].name, "left_prop");
	strcpy(rules[6].thenRules[1].mf, "zero");
	strcpy(rules[6].thenRules[2].name, "rear_prop");
	strcpy(rules[6].thenRules[2].mf, "zero");
	strcpy(rules[6].thenRules[3].name, "right_prop");
	strcpy(rules[6].thenRules[3].mf, "zero");

	rules[7].nIfRules = 2;

	strcpy(rules[7].ifRules[0].name, "z_diff");
	strcpy(rules[7].ifRules[0].mf, "pos");
	strcpy(rules[7].ifRules[1].name, "z_diffVel");
	strcpy(rules[7].ifRules[1].mf, "zero");

	rules[7].thenValue = 1;
	
	rules[7].nThenRules = 4;

	strcpy(rules[7].thenRules[0].name, "front_prop");
	strcpy(rules[7].thenRules[0].mf, "pos");
	strcpy(rules[7].thenRules[1].name, "left_prop");
	strcpy(rules[7].thenRules[1].mf, "pos");
	strcpy(rules[7].thenRules[2].name, "rear_prop");
	strcpy(rules[7].thenRules[2].mf, "pos");
	strcpy(rules[7].thenRules[3].name, "right_prop");
	strcpy(rules[7].thenRules[3].mf, "pos");

	rules[8].nIfRules = 2;

	strcpy(rules[8].ifRules[0].name, "z_diff");
	strcpy(rules[8].ifRules[0].mf, "pos");
	strcpy(rules[8].ifRules[1].name, "z_diffVel");
	strcpy(rules[8].ifRules[1].mf, "pos");

	rules[8].thenValue = 1;
	
	rules[8].nThenRules = 4;

	strcpy(rules[8].thenRules[0].name, "front_prop");
	strcpy(rules[8].thenRules[0].mf, "pos");
	strcpy(rules[8].thenRules[1].name, "left_prop");
	strcpy(rules[8].thenRules[1].mf, "pos");
	strcpy(rules[8].thenRules[2].name, "rear_prop");
	strcpy(rules[8].thenRules[2].mf, "pos");
	strcpy(rules[8].thenRules[3].name, "right_prop");
	strcpy(rules[8].thenRules[3].mf, "pos");


	/*
	 * LOGIC
	 */

	flag = createLogic_z_displ(fl, fi, fo, rules);
	if ( flag < 0 ) {
		return 3;
	}

	return 0;
}