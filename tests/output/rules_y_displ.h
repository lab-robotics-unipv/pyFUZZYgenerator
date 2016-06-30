#ifndef RULES_y_displ_H
#define RULES_y_displ_H

#include "definitions_y_displ.h"

#ifndef MAX_L_NAME_y_displ
#error "MAX_L_NAME_y_displ not defined: check definitions_y_displ.h"
#endif

#ifndef N_INPUT_y_displ
#error "N_INPUT_y_displ not defined: check definitions_y_displ.h"
#endif

#ifndef N_OUTPUT_y_displ
#error "N_OUTPUT_y_displ not defined: check definitions_y_displ.h"
#endif

//! IF AND THEN STATEMENTS
typedef struct {
	char name[MAX_L_NAME_y_displ];		//!< Name of the variable
	char mf[MAX_L_NAME_y_displ];		//!< Member function of the variable
} ruleStatement_y_displ;

//! RULE
typedef struct {
	ruleStatement_y_displ ifRules[N_INPUT_y_displ];		//!< Vector of "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	ruleStatement_y_displ thenRules[N_OUTPUT_y_displ];	//!< Vector of "then statements"
	int nThenRules;						//!< Number of "then statements"
} rule_y_displ;

//! RULE AFTER FINDING THE INDICES OF THE INPUTS AND MEMBERSHIP FUNCTIONS OF THE FUZZY LOGIC
typedef struct {
	int ifRulesIndex[N_INPUT_y_displ];			//!< Vector of the indices of "if statements"
	int ifRulesMFIndex[N_INPUT_y_displ];		//!< Vector of the indices of the mf of the "if statements"
	int nIfRules;						//!< Number of "if statements"

	double thenValue;					//!< Value of correctness of the rule

	int thenRulesIndex[N_OUTPUT_y_displ];		//!< Vector of the indices of the "then statements"
	int thenRulesMFIndex[N_OUTPUT_y_displ];		//!< Vector of the indices of the mf of the "then statements"
	int nThenRules;						//!< Number of "then statements"
} builtRule_y_displ;

#endif