#include <string.h>

#include "definitions_x_displ.h"
#include "fuzzyLogic_x_displ.h"

int newState_x_displ(fuzzyLogic_x_displ * fl) {

	/*
	 * INPUT VARIABLES
	 */

	int flag;
	fuzzyInput_x_displ fi[N_INPUT_x_displ];

	// Input variable: x_diff
	// Difference between the actual and desired x value
	memFunction_x_displ MF_x_diff[3];

	double poi_x_diff_neg[] = { -0.5, -0.5, 0.0 };
	createMemFunction_x_displ(&(MF_x_diff[0]), "neg", TRI_MF, poi_x_diff_neg);
	double poi_x_diff_zero[] = { -0.5, 0.0, 0.5 };
	createMemFunction_x_displ(&(MF_x_diff[1]), "zero", TRI_MF, poi_x_diff_zero);
	double poi_x_diff_pos[] = { 0.0, 0.5, 0.5 };
	createMemFunction_x_displ(&(MF_x_diff[2]), "pos", TRI_MF, poi_x_diff_pos);

	flag = createInput_x_displ(&(fi[0]), "x_diff", MF_x_diff, 3, -0.5, 0.5);
	if (flag < 0) {
		return 1;
	}

	// Input variable: x_diffVel
	// Difference between the actual and desired x velocity
	memFunction_x_displ MF_x_diffVel[3];

	double poi_x_diffVel_neg[] = { -1.0, -1.0, 0.0 };
	createMemFunction_x_displ(&(MF_x_diffVel[0]), "neg", TRI_MF, poi_x_diffVel_neg);
	double poi_x_diffVel_zero[] = { -1.0, 0.0, 1.0 };
	createMemFunction_x_displ(&(MF_x_diffVel[1]), "zero", TRI_MF, poi_x_diffVel_zero);
	double poi_x_diffVel_pos[] = { 0.0, 1.0, 1.0 };
	createMemFunction_x_displ(&(MF_x_diffVel[2]), "pos", TRI_MF, poi_x_diffVel_pos);

	flag = createInput_x_displ(&(fi[1]), "x_diffVel", MF_x_diffVel, 3, -1.0, 1.0);
	if (flag < 0) {
		return 1;
	}


	/*
	 * OUTPUT VARIABLES
	 */

	fuzzyOutput_x_displ fo[N_OUTPUT_x_displ];

	// Output variable: front_beta_angle
	// Derivative of the beta angle on the front propeller
	memFunction_x_displ MF_front_beta_angle[3];

	double poi_front_beta_angle_neg[] = { -1.0 };
	createMemFunction_x_displ(&(MF_front_beta_angle[0]), "neg", SPIKE_MF, poi_front_beta_angle_neg);
	double poi_front_beta_angle_zero[] = { 0.0 };
	createMemFunction_x_displ(&(MF_front_beta_angle[1]), "zero", SPIKE_MF, poi_front_beta_angle_zero);
	double poi_front_beta_angle_pos[] = { 1.0 };
	createMemFunction_x_displ(&(MF_front_beta_angle[2]), "pos", SPIKE_MF, poi_front_beta_angle_pos);

	flag = createOutput_x_displ(&(fo[0]), "front_beta_angle", MF_front_beta_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: rear_beta_angle
	// Derivative of the beta angle on the rear propeller
	memFunction_x_displ MF_rear_beta_angle[3];

	double poi_rear_beta_angle_neg[] = { -1.0 };
	createMemFunction_x_displ(&(MF_rear_beta_angle[0]), "neg", SPIKE_MF, poi_rear_beta_angle_neg);
	double poi_rear_beta_angle_zero[] = { 0.0 };
	createMemFunction_x_displ(&(MF_rear_beta_angle[1]), "zero", SPIKE_MF, poi_rear_beta_angle_zero);
	double poi_rear_beta_angle_pos[] = { 1.0 };
	createMemFunction_x_displ(&(MF_rear_beta_angle[2]), "pos", SPIKE_MF, poi_rear_beta_angle_pos);

	flag = createOutput_x_displ(&(fo[1]), "rear_beta_angle", MF_rear_beta_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: left_alpha_angle
	// Derivative of the alpha angle on the left propeller
	memFunction_x_displ MF_left_alpha_angle[3];

	double poi_left_alpha_angle_neg[] = { -1.0 };
	createMemFunction_x_displ(&(MF_left_alpha_angle[0]), "neg", SPIKE_MF, poi_left_alpha_angle_neg);
	double poi_left_alpha_angle_zero[] = { 0.0 };
	createMemFunction_x_displ(&(MF_left_alpha_angle[1]), "zero", SPIKE_MF, poi_left_alpha_angle_zero);
	double poi_left_alpha_angle_pos[] = { 1.0 };
	createMemFunction_x_displ(&(MF_left_alpha_angle[2]), "pos", SPIKE_MF, poi_left_alpha_angle_pos);

	flag = createOutput_x_displ(&(fo[2]), "left_alpha_angle", MF_left_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: right_alpha_angle
	// Derivative of the angle angle on the right propeller
	memFunction_x_displ MF_right_alpha_angle[3];

	double poi_right_alpha_angle_neg[] = { -1.0 };
	createMemFunction_x_displ(&(MF_right_alpha_angle[0]), "neg", SPIKE_MF, poi_right_alpha_angle_neg);
	double poi_right_alpha_angle_zero[] = { 0.0 };
	createMemFunction_x_displ(&(MF_right_alpha_angle[1]), "zero", SPIKE_MF, poi_right_alpha_angle_zero);
	double poi_right_alpha_angle_pos[] = { 1.0 };
	createMemFunction_x_displ(&(MF_right_alpha_angle[2]), "pos", SPIKE_MF, poi_right_alpha_angle_pos);

	flag = createOutput_x_displ(&(fo[3]), "right_alpha_angle", MF_right_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}


	/*
	 * RULES
	 */

	rule_x_displ rules[N_RULES_x_displ];

	rules[0].nIfRules = 2;

	strcpy(rules[0].ifRules[0].name, "x_diff");
	strcpy(rules[0].ifRules[0].mf, "neg");
	strcpy(rules[0].ifRules[1].name, "x_diffVel");
	strcpy(rules[0].ifRules[1].mf, "neg");

	rules[0].thenValue = 1;
	
	rules[0].nThenRules = 4;

	strcpy(rules[0].thenRules[0].name, "front_beta_angle");
	strcpy(rules[0].thenRules[0].mf, "neg");
	strcpy(rules[0].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[0].thenRules[1].mf, "pos");
	strcpy(rules[0].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[0].thenRules[2].mf, "neg");
	strcpy(rules[0].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[0].thenRules[3].mf, "pos");

	rules[1].nIfRules = 2;

	strcpy(rules[1].ifRules[0].name, "x_diff");
	strcpy(rules[1].ifRules[0].mf, "neg");
	strcpy(rules[1].ifRules[1].name, "x_diffVel");
	strcpy(rules[1].ifRules[1].mf, "zero");

	rules[1].thenValue = 1;
	
	rules[1].nThenRules = 4;

	strcpy(rules[1].thenRules[0].name, "front_beta_angle");
	strcpy(rules[1].thenRules[0].mf, "neg");
	strcpy(rules[1].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[1].thenRules[1].mf, "pos");
	strcpy(rules[1].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[1].thenRules[2].mf, "neg");
	strcpy(rules[1].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[1].thenRules[3].mf, "pos");

	rules[2].nIfRules = 2;

	strcpy(rules[2].ifRules[0].name, "x_diff");
	strcpy(rules[2].ifRules[0].mf, "neg");
	strcpy(rules[2].ifRules[1].name, "x_diffVel");
	strcpy(rules[2].ifRules[1].mf, "pos");

	rules[2].thenValue = 1;
	
	rules[2].nThenRules = 4;

	strcpy(rules[2].thenRules[0].name, "front_beta_angle");
	strcpy(rules[2].thenRules[0].mf, "neg");
	strcpy(rules[2].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[2].thenRules[1].mf, "pos");
	strcpy(rules[2].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[2].thenRules[2].mf, "zero");
	strcpy(rules[2].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[2].thenRules[3].mf, "zero");

	rules[3].nIfRules = 2;

	strcpy(rules[3].ifRules[0].name, "x_diff");
	strcpy(rules[3].ifRules[0].mf, "zero");
	strcpy(rules[3].ifRules[1].name, "x_diffVel");
	strcpy(rules[3].ifRules[1].mf, "neg");

	rules[3].thenValue = 1;
	
	rules[3].nThenRules = 4;

	strcpy(rules[3].thenRules[0].name, "front_beta_angle");
	strcpy(rules[3].thenRules[0].mf, "neg");
	strcpy(rules[3].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[3].thenRules[1].mf, "pos");
	strcpy(rules[3].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[3].thenRules[2].mf, "zero");
	strcpy(rules[3].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[3].thenRules[3].mf, "zero");

	rules[4].nIfRules = 2;

	strcpy(rules[4].ifRules[0].name, "x_diff");
	strcpy(rules[4].ifRules[0].mf, "zero");
	strcpy(rules[4].ifRules[1].name, "x_diffVel");
	strcpy(rules[4].ifRules[1].mf, "zero");

	rules[4].thenValue = 1;
	
	rules[4].nThenRules = 4;

	strcpy(rules[4].thenRules[0].name, "front_beta_angle");
	strcpy(rules[4].thenRules[0].mf, "zero");
	strcpy(rules[4].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[4].thenRules[1].mf, "zero");
	strcpy(rules[4].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[4].thenRules[2].mf, "zero");
	strcpy(rules[4].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[4].thenRules[3].mf, "zero");

	rules[5].nIfRules = 2;

	strcpy(rules[5].ifRules[0].name, "x_diff");
	strcpy(rules[5].ifRules[0].mf, "zero");
	strcpy(rules[5].ifRules[1].name, "x_diffVel");
	strcpy(rules[5].ifRules[1].mf, "pos");

	rules[5].thenValue = 1;
	
	rules[5].nThenRules = 4;

	strcpy(rules[5].thenRules[0].name, "front_beta_angle");
	strcpy(rules[5].thenRules[0].mf, "pos");
	strcpy(rules[5].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[5].thenRules[1].mf, "neg");
	strcpy(rules[5].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[5].thenRules[2].mf, "zero");
	strcpy(rules[5].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[5].thenRules[3].mf, "zero");

	rules[6].nIfRules = 2;

	strcpy(rules[6].ifRules[0].name, "x_diff");
	strcpy(rules[6].ifRules[0].mf, "pos");
	strcpy(rules[6].ifRules[1].name, "x_diffVel");
	strcpy(rules[6].ifRules[1].mf, "neg");

	rules[6].thenValue = 1;
	
	rules[6].nThenRules = 4;

	strcpy(rules[6].thenRules[0].name, "front_beta_angle");
	strcpy(rules[6].thenRules[0].mf, "pos");
	strcpy(rules[6].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[6].thenRules[1].mf, "neg");
	strcpy(rules[6].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[6].thenRules[2].mf, "zero");
	strcpy(rules[6].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[6].thenRules[3].mf, "zero");

	rules[7].nIfRules = 2;

	strcpy(rules[7].ifRules[0].name, "x_diff");
	strcpy(rules[7].ifRules[0].mf, "pos");
	strcpy(rules[7].ifRules[1].name, "x_diffVel");
	strcpy(rules[7].ifRules[1].mf, "zero");

	rules[7].thenValue = 1;
	
	rules[7].nThenRules = 4;

	strcpy(rules[7].thenRules[0].name, "front_beta_angle");
	strcpy(rules[7].thenRules[0].mf, "pos");
	strcpy(rules[7].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[7].thenRules[1].mf, "neg");
	strcpy(rules[7].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[7].thenRules[2].mf, "pos");
	strcpy(rules[7].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[7].thenRules[3].mf, "neg");

	rules[8].nIfRules = 2;

	strcpy(rules[8].ifRules[0].name, "x_diff");
	strcpy(rules[8].ifRules[0].mf, "pos");
	strcpy(rules[8].ifRules[1].name, "x_diffVel");
	strcpy(rules[8].ifRules[1].mf, "pos");

	rules[8].thenValue = 1;
	
	rules[8].nThenRules = 4;

	strcpy(rules[8].thenRules[0].name, "front_beta_angle");
	strcpy(rules[8].thenRules[0].mf, "pos");
	strcpy(rules[8].thenRules[1].name, "rear_beta_angle");
	strcpy(rules[8].thenRules[1].mf, "neg");
	strcpy(rules[8].thenRules[2].name, "left_alpha_angle");
	strcpy(rules[8].thenRules[2].mf, "pos");
	strcpy(rules[8].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[8].thenRules[3].mf, "neg");


	/*
	 * LOGIC
	 */

	flag = createLogic_x_displ(fl, fi, fo, rules);
	if ( flag < 0 ) {
		return 3;
	}

	return 0;
}