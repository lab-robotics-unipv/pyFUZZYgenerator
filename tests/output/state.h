#ifndef __STATE_H

#define __STATE_H

#include "fuzzyLogic_x_displ.h"
#include "fuzzyLogic_y_displ.h"
#include "fuzzyLogic_z_displ.h"
#include "fuzzyLogic_roll.h"
#include "fuzzyLogic_pitch.h"
#include "fuzzyLogic_yaw.h"

#include "init_x_displ.h"
#include "init_y_displ.h"
#include "init_z_displ.h"
#include "init_roll.h"
#include "init_pitch.h"
#include "init_yaw.h"

//! STATE OF THE SYSTEM
typedef struct state {
	fuzzyLogic_x_displ fl_x;
	fuzzyLogic_y_displ fl_y;
	fuzzyLogic_z_displ fl_z;
	fuzzyLogic_roll fl_roll;
	fuzzyLogic_pitch fl_pitch;
	fuzzyLogic_yaw fl_yaw;
} STATE;

/*! CONSTRUCTOR OF A SYSTEM STATE
 *		output			state			Pointer to system state
 */
void *newState();

/*! DESTRUCTOR OF THE SYSTEM STATE
 *		input/output	obj				Pointer to system state
 */
void killState(void *obj);

void control(void* state, double* x, double* theta, double* v, double* w, double* p, double* a, double* b);

#endif /* __STATE_H */
