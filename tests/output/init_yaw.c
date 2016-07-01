#include <string.h>

#include "definitions_yaw.h"
#include "fuzzyLogic_yaw.h"

int newState_yaw(fuzzyLogic_yaw * fl) {

	/*
	 * INPUT VARIABLES
	 */

	int flag;
	fuzzyInput_yaw fi[N_INPUT_yaw];

	// Input variable: yaw_diff
	// Difference between the actual and desired roll yaw
	memFunction_yaw MF_yaw_diff[3];

	double poi_yaw_diff_neg[] = { -5.0, -5.0, 0.0 };
	createMemFunction_yaw(&(MF_yaw_diff[0]), "neg", TRI_MF, poi_yaw_diff_neg);
	double poi_yaw_diff_zero[] = { -5.0, 0.0, 5.0 };
	createMemFunction_yaw(&(MF_yaw_diff[1]), "zero", TRI_MF, poi_yaw_diff_zero);
	double poi_yaw_diff_pos[] = { 0.0, 5.0, 5.0 };
	createMemFunction_yaw(&(MF_yaw_diff[2]), "pos", TRI_MF, poi_yaw_diff_pos);

	flag = createInput_yaw(&(fi[0]), "yaw_diff", MF_yaw_diff, 3, -5.0, 5.0);
	if (flag < 0) {
		return 1;
	}

	// Input variable: yaw_diffVel
	// Difference between the actual and desired roll velocity
	memFunction_yaw MF_yaw_diffVel[3];

	double poi_yaw_diffVel_neg[] = { -1.0, -1.0, 0.0 };
	createMemFunction_yaw(&(MF_yaw_diffVel[0]), "neg", TRI_MF, poi_yaw_diffVel_neg);
	double poi_yaw_diffVel_zero[] = { -1.0, 0.0, 1.0 };
	createMemFunction_yaw(&(MF_yaw_diffVel[1]), "zero", TRI_MF, poi_yaw_diffVel_zero);
	double poi_yaw_diffVel_pos[] = { 0.0, 1.0, 1.0 };
	createMemFunction_yaw(&(MF_yaw_diffVel[2]), "pos", TRI_MF, poi_yaw_diffVel_pos);

	flag = createInput_yaw(&(fi[1]), "yaw_diffVel", MF_yaw_diffVel, 3, -1.0, 1.0);
	if (flag < 0) {
		return 1;
	}


	/*
	 * OUTPUT VARIABLES
	 */

	fuzzyOutput_yaw fo[N_OUTPUT_yaw];

	// Output variable: front_alpha_angle
	// Derivative of the alpha angle on the front propeller
	memFunction_yaw MF_front_alpha_angle[3];

	double poi_front_alpha_angle_neg[] = { -1.0 };
	createMemFunction_yaw(&(MF_front_alpha_angle[0]), "neg", SPIKE_MF, poi_front_alpha_angle_neg);
	double poi_front_alpha_angle_zero[] = { 0.0 };
	createMemFunction_yaw(&(MF_front_alpha_angle[1]), "zero", SPIKE_MF, poi_front_alpha_angle_zero);
	double poi_front_alpha_angle_pos[] = { 1.0 };
	createMemFunction_yaw(&(MF_front_alpha_angle[2]), "pos", SPIKE_MF, poi_front_alpha_angle_pos);

	flag = createOutput_yaw(&(fo[0]), "front_alpha_angle", MF_front_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: left_alpha_angle
	// Derivative of the alpha angle on the left propeller
	memFunction_yaw MF_left_alpha_angle[3];

	double poi_left_alpha_angle_neg[] = { -1.0 };
	createMemFunction_yaw(&(MF_left_alpha_angle[0]), "neg", SPIKE_MF, poi_left_alpha_angle_neg);
	double poi_left_alpha_angle_zero[] = { 0.0 };
	createMemFunction_yaw(&(MF_left_alpha_angle[1]), "zero", SPIKE_MF, poi_left_alpha_angle_zero);
	double poi_left_alpha_angle_pos[] = { 1.0 };
	createMemFunction_yaw(&(MF_left_alpha_angle[2]), "pos", SPIKE_MF, poi_left_alpha_angle_pos);

	flag = createOutput_yaw(&(fo[1]), "left_alpha_angle", MF_left_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: rear_alpha_angle
	// Derivative of the alpha angle on the rear propeller
	memFunction_yaw MF_rear_alpha_angle[3];

	double poi_rear_alpha_angle_neg[] = { -1.0 };
	createMemFunction_yaw(&(MF_rear_alpha_angle[0]), "neg", SPIKE_MF, poi_rear_alpha_angle_neg);
	double poi_rear_alpha_angle_zero[] = { 0.0 };
	createMemFunction_yaw(&(MF_rear_alpha_angle[1]), "zero", SPIKE_MF, poi_rear_alpha_angle_zero);
	double poi_rear_alpha_angle_pos[] = { 1.0 };
	createMemFunction_yaw(&(MF_rear_alpha_angle[2]), "pos", SPIKE_MF, poi_rear_alpha_angle_pos);

	flag = createOutput_yaw(&(fo[2]), "rear_alpha_angle", MF_rear_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}

	// Output variable: right_alpha_angle
	// Derivative of the alpha angle on the right propeller
	memFunction_yaw MF_right_alpha_angle[3];

	double poi_right_alpha_angle_neg[] = { -1.0 };
	createMemFunction_yaw(&(MF_right_alpha_angle[0]), "neg", SPIKE_MF, poi_right_alpha_angle_neg);
	double poi_right_alpha_angle_zero[] = { 0.0 };
	createMemFunction_yaw(&(MF_right_alpha_angle[1]), "zero", SPIKE_MF, poi_right_alpha_angle_zero);
	double poi_right_alpha_angle_pos[] = { 1.0 };
	createMemFunction_yaw(&(MF_right_alpha_angle[2]), "pos", SPIKE_MF, poi_right_alpha_angle_pos);

	flag = createOutput_yaw(&(fo[3]), "right_alpha_angle", MF_right_alpha_angle, 3);
	if (flag < 0) {
		return 1;
	}


	/*
	 * RULES
	 */

	rule_yaw rules[N_RULES_yaw];

	rules[0].nIfRules = 2;

	strcpy(rules[0].ifRules[0].name, "yaw_diff");
	strcpy(rules[0].ifRules[0].mf, "neg");
	strcpy(rules[0].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[0].ifRules[1].mf, "neg");

	rules[0].thenValue = 1;
	
	rules[0].nThenRules = 4;

	strcpy(rules[0].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[0].thenRules[0].mf, "pos");
	strcpy(rules[0].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[0].thenRules[1].mf, "pos");
	strcpy(rules[0].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[0].thenRules[2].mf, "pos");
	strcpy(rules[0].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[0].thenRules[3].mf, "pos");

	rules[1].nIfRules = 2;

	strcpy(rules[1].ifRules[0].name, "yaw_diff");
	strcpy(rules[1].ifRules[0].mf, "neg");
	strcpy(rules[1].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[1].ifRules[1].mf, "zero");

	rules[1].thenValue = 1;
	
	rules[1].nThenRules = 4;

	strcpy(rules[1].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[1].thenRules[0].mf, "pos");
	strcpy(rules[1].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[1].thenRules[1].mf, "pos");
	strcpy(rules[1].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[1].thenRules[2].mf, "pos");
	strcpy(rules[1].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[1].thenRules[3].mf, "pos");

	rules[2].nIfRules = 2;

	strcpy(rules[2].ifRules[0].name, "yaw_diff");
	strcpy(rules[2].ifRules[0].mf, "neg");
	strcpy(rules[2].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[2].ifRules[1].mf, "pos");

	rules[2].thenValue = 1;
	
	rules[2].nThenRules = 4;

	strcpy(rules[2].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[2].thenRules[0].mf, "zero");
	strcpy(rules[2].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[2].thenRules[1].mf, "zero");
	strcpy(rules[2].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[2].thenRules[2].mf, "zero");
	strcpy(rules[2].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[2].thenRules[3].mf, "zero");

	rules[3].nIfRules = 2;

	strcpy(rules[3].ifRules[0].name, "yaw_diff");
	strcpy(rules[3].ifRules[0].mf, "zero");
	strcpy(rules[3].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[3].ifRules[1].mf, "neg");

	rules[3].thenValue = 1;
	
	rules[3].nThenRules = 4;

	strcpy(rules[3].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[3].thenRules[0].mf, "pos");
	strcpy(rules[3].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[3].thenRules[1].mf, "pos");
	strcpy(rules[3].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[3].thenRules[2].mf, "pos");
	strcpy(rules[3].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[3].thenRules[3].mf, "pos");

	rules[4].nIfRules = 2;

	strcpy(rules[4].ifRules[0].name, "yaw_diff");
	strcpy(rules[4].ifRules[0].mf, "zero");
	strcpy(rules[4].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[4].ifRules[1].mf, "zero");

	rules[4].thenValue = 1;
	
	rules[4].nThenRules = 4;

	strcpy(rules[4].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[4].thenRules[0].mf, "zero");
	strcpy(rules[4].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[4].thenRules[1].mf, "zero");
	strcpy(rules[4].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[4].thenRules[2].mf, "zero");
	strcpy(rules[4].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[4].thenRules[3].mf, "zero");

	rules[5].nIfRules = 2;

	strcpy(rules[5].ifRules[0].name, "yaw_diff");
	strcpy(rules[5].ifRules[0].mf, "zero");
	strcpy(rules[5].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[5].ifRules[1].mf, "pos");

	rules[5].thenValue = 1;
	
	rules[5].nThenRules = 4;

	strcpy(rules[5].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[5].thenRules[0].mf, "neg");
	strcpy(rules[5].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[5].thenRules[1].mf, "neg");
	strcpy(rules[5].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[5].thenRules[2].mf, "neg");
	strcpy(rules[5].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[5].thenRules[3].mf, "neg");

	rules[6].nIfRules = 2;

	strcpy(rules[6].ifRules[0].name, "yaw_diff");
	strcpy(rules[6].ifRules[0].mf, "pos");
	strcpy(rules[6].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[6].ifRules[1].mf, "neg");

	rules[6].thenValue = 1;
	
	rules[6].nThenRules = 4;

	strcpy(rules[6].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[6].thenRules[0].mf, "zero");
	strcpy(rules[6].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[6].thenRules[1].mf, "zero");
	strcpy(rules[6].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[6].thenRules[2].mf, "zero");
	strcpy(rules[6].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[6].thenRules[3].mf, "zero");

	rules[7].nIfRules = 2;

	strcpy(rules[7].ifRules[0].name, "yaw_diff");
	strcpy(rules[7].ifRules[0].mf, "pos");
	strcpy(rules[7].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[7].ifRules[1].mf, "zero");

	rules[7].thenValue = 1;
	
	rules[7].nThenRules = 4;

	strcpy(rules[7].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[7].thenRules[0].mf, "neg");
	strcpy(rules[7].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[7].thenRules[1].mf, "neg");
	strcpy(rules[7].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[7].thenRules[2].mf, "neg");
	strcpy(rules[7].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[7].thenRules[3].mf, "neg");

	rules[8].nIfRules = 2;

	strcpy(rules[8].ifRules[0].name, "yaw_diff");
	strcpy(rules[8].ifRules[0].mf, "pos");
	strcpy(rules[8].ifRules[1].name, "yaw_diffVel");
	strcpy(rules[8].ifRules[1].mf, "pos");

	rules[8].thenValue = 1;
	
	rules[8].nThenRules = 4;

	strcpy(rules[8].thenRules[0].name, "front_alpha_angle");
	strcpy(rules[8].thenRules[0].mf, "neg");
	strcpy(rules[8].thenRules[1].name, "left_alpha_angle");
	strcpy(rules[8].thenRules[1].mf, "neg");
	strcpy(rules[8].thenRules[2].name, "rear_alpha_angle");
	strcpy(rules[8].thenRules[2].mf, "neg");
	strcpy(rules[8].thenRules[3].name, "right_alpha_angle");
	strcpy(rules[8].thenRules[3].mf, "neg");


	/*
	 * LOGIC
	 */

	flag = createLogic_yaw(fl, fi, fo, rules);
	if ( flag < 0 ) {
		return 3;
	}

	return 0;
}