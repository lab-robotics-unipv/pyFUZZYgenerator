#ifndef RULES_pitch_H
#define RULES_pitch_H

#include "definitions_pitch.h"

#ifndef MAX_L_NAME_pitch
#error "MAX_L_NAME_pitch not defined: check definitions_pitch.h"
#endif

#ifndef N_INPUT_pitch
#error "N_INPUT_pitch not defined: check definitions_pitch.h"
#endif

#ifndef N_OUTPUT_pitch
#error "N_OUTPUT_pitch not defined: check definitions_pitch.h"
#endif

//! IF AND THEN STATEMENTS
typedef struct {
	char name[MAX_L_NAME_pitch];		//!< Name of the variable
	char mf[MAX_L_NAME_pitch];		//!< Member function of the variable
} ruleStatement_pitch;

//! RULE
typedef struct {
	ruleStatement_pitch ifRules[N_INPUT_pitch];		//!< Vector of "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	ruleStatement_pitch thenRules[N_OUTPUT_pitch];	//!< Vector of "then statements"
	int nThenRules;						//!< Number of "then statements"
} rule_pitch;

//! RULE AFTER FINDING THE INDICES OF THE INPUTS AND MEMBERSHIP FUNCTIONS OF THE FUZZY LOGIC
typedef struct {
	int ifRulesIndex[N_INPUT_pitch];			//!< Vector of the indices of "if statements"
	int ifRulesMFIndex[N_INPUT_pitch];		//!< Vector of the indices of the mf of the "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	int thenRulesIndex[N_OUTPUT_pitch];		//!< Vector of the indices of the "then statements"
	int thenRulesMFIndex[N_OUTPUT_pitch];		//!< Vector of the indices of the mf of the "then statements"
	int nThenRules;						//!< Number of "then statements"
} builtRule_pitch;

#endif