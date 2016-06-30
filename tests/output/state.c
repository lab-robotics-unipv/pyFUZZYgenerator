#include "state.h"
#include <stdlib.h>

/*! CONSTRUCTOR OF A SYSTEM STATE
 *		output			state			Pointer to system state
 */
void *newState() {
	STATE * state = malloc(sizeof(STATE));

	newState_x_displ(&(state->fl_x));
	newState_y_displ(&(state->fl_y));
	newState_z_displ(&(state->fl_z));
	newState_roll(&(state->fl_roll));
	newState_pitch(&(state->fl_pitch));
	newState_yaw(&(state->fl_yaw));

	return state;
}

/*! DESTRUCTOR OF THE SYSTEM STATE
 *		input/output	obj				Pointer to system state
 */
void killState(void *obj) {
	struct state *s = (struct state *) obj;
	if (s == NULL)
		return;
	free(s);
}

void control(void* state, double* x, double* theta, double* v, double* w, double* p, double* a, double* b) {
	STATE* s = (STATE*) state;

	double out_x[N_INPUT_x_displ];
	fuzzify_x_displ(&(s->fl_x), &(x[0]));
	evaluateRules_x_displ(&(s->fl_x));
	defuzzify_x_displ(&(s->fl_x), out_x);

	double out_y[N_INPUT_y_displ];
	fuzzify_y_displ(&(s->fl_y), &(x[1]));
	evaluateRules_y_displ(&(s->fl_y));
	defuzzify_y_displ(&(s->fl_y), out_y);

	double out_z[N_INPUT_z_displ];
	fuzzify_z_displ(&(s->fl_z), &(x[2]));
	evaluateRules_z_displ(&(s->fl_z));
	defuzzify_z_displ(&(s->fl_z), out_z);

	double out_roll[N_INPUT_roll];
	fuzzify_roll(&(s->fl_roll), &(theta[0]));
	evaluateRules_roll(&(s->fl_roll));
	defuzzify_roll(&(s->fl_roll), out_roll);

	double out_pitch[N_INPUT_pitch];
	fuzzify_pitch(&(s->fl_pitch), &(theta[1]));
	evaluateRules_pitch(&(s->fl_pitch));
	defuzzify_pitch(&(s->fl_pitch), out_pitch);

	double out_yaw[N_INPUT_yaw];
	fuzzify_yaw(&(s->fl_yaw), &(theta[2]));
	evaluateRules_yaw(&(s->fl_yaw));
	defuzzify_yaw(&(s->fl_yaw), out_yaw);

	p[0] = (out_z[0] + out_pitch[0])/2;	// z[0], pitch[0]
	p[1] = (out_z[1] + out_roll[0])/2;	// z[1], roll[0]
	p[2] = (out_z[2] + out_pitch[1])/2;	// z[2], pitch[1]
	p[3] = (out_z[3] + out_roll[1])/2;	// z[3], roll[1]

	a[0] = (out_y[2] + out_yaw[0])/2;	// y[2], yaw[0]
	a[1] = (out_x[2] + out_yaw[1])/2;	// x[2], yaw[1]
	a[2] = (out_y[3] + out_yaw[2])/2;	// y[3], yaw[2]
	a[3] = (out_x[3] + out_yaw[3])/2;	// x[3], yaw[3]

	b[0] = out_x[0];	// x[0]
	b[1] = out_y[1];	// y[0]
	b[2] = out_x[0];	// x[1]
	b[3] = out_y[1];	// y[1]

}
