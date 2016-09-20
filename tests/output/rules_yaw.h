#ifndef RULES_yaw_H
#define RULES_yaw_H

#include "definitions_yaw.h"

#ifndef MAX_L_NAME_yaw
#error "MAX_L_NAME_yaw not defined: check definitions_yaw.h"
#endif

#ifndef N_INPUT_yaw
#error "N_INPUT_yaw not defined: check definitions_yaw.h"
#endif

#ifndef N_OUTPUT_yaw
#error "N_OUTPUT_yaw not defined: check definitions_yaw.h"
#endif

//! IF AND THEN STATEMENTS
typedef struct {
	char name[MAX_L_NAME_yaw];		//!< Name of the variable
	char mf[MAX_L_NAME_yaw];		//!< Member function of the variable
} ruleStatement_yaw;

//! RULE
typedef struct {
	ruleStatement_yaw ifRules[N_INPUT_yaw];		//!< Vector of "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	ruleStatement_yaw thenRules[N_OUTPUT_yaw];	//!< Vector of "then statements"
	int nThenRules;						//!< Number of "then statements"
} rule_yaw;

//! RULE AFTER FINDING THE INDICES OF THE INPUTS AND MEMBERSHIP FUNCTIONS OF THE FUZZY LOGIC
typedef struct {
	int ifRulesIndex[N_INPUT_yaw];			//!< Vector of the indices of "if statements"
	int ifRulesMFIndex[N_INPUT_yaw];		//!< Vector of the indices of the mf of the "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	int thenRulesIndex[N_OUTPUT_yaw];		//!< Vector of the indices of the "then statements"
	int thenRulesMFIndex[N_OUTPUT_yaw];		//!< Vector of the indices of the mf of the "then statements"
	int nThenRules;						//!< Number of "then statements"
} builtRule_yaw;

#endif