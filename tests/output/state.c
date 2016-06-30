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

	// double out_y[N_INPUT_y_displ];
	// fuzzify_(&(s->fl_));
	// evaluateRules_(&(s->fl_));
	// defuzzify_(&(s->fl_));

	// double out_z[N_INPUT_z_displ];
	// fuzzify_(&(s->fl_));
	// evaluateRules_(&(s->fl_));
	// defuzzify_(&(s->fl_));

	// double out_roll[N_INPUT_roll];
	// fuzzify_(&(s->fl_));
	// evaluateRules_(&(s->fl_));
	// defuzzify_(&(s->fl_));

	// double out_pitch[N_INPUT_pitch];
	// fuzzify_(&(s->fl_));
	// evaluateRules_(&(s->fl_));
	// defuzzify_(&(s->fl_));

	// double out_yaw[N_INPUT_yaw];
	// fuzzify_(&(s->fl_));
	// evaluateRules_(&(s->fl_));
	// defuzzify_(&(s->fl_));

	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;

	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;

	b[0] = 0;
	b[1] = 0;
	b[2] = 0;
	b[3] = 0;

}
