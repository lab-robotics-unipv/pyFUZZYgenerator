#ifndef RULES_roll_H
#define RULES_roll_H

#include "definitions_roll.h"

#ifndef MAX_L_NAME_roll
#error "MAX_L_NAME_roll not defined: check definitions_roll.h"
#endif

#ifndef N_INPUT_roll
#error "N_INPUT_roll not defined: check definitions_roll.h"
#endif

#ifndef N_OUTPUT_roll
#error "N_OUTPUT_roll not defined: check definitions_roll.h"
#endif

//! IF AND THEN STATEMENTS
typedef struct {
	char name[MAX_L_NAME_roll];		//!< Name of the variable
	char mf[MAX_L_NAME_roll];		//!< Member function of the variable
} ruleStatement_roll;

//! RULE
typedef struct {
	ruleStatement_roll ifRules[N_INPUT_roll];		//!< Vector of "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	ruleStatement_roll thenRules[N_OUTPUT_roll];	//!< Vector of "then statements"
	int nThenRules;						//!< Number of "then statements"
} rule_roll;

//! RULE AFTER FINDING THE INDICES OF THE INPUTS AND MEMBERSHIP FUNCTIONS OF THE FUZZY LOGIC
typedef struct {
	int ifRulesIndex[N_INPUT_roll];			//!< Vector of the indices of "if statements"
	int ifRulesMFIndex[N_INPUT_roll];		//!< Vector of the indices of the mf of the "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	int thenRulesIndex[N_OUTPUT_roll];		//!< Vector of the indices of the "then statements"
	int thenRulesMFIndex[N_OUTPUT_roll];		//!< Vector of the indices of the mf of the "then statements"
	int nThenRules;						//!< Number of "then statements"
} builtRule_roll;

#endif