import logging
import numpy as np
import pytoml as toml

from core.Variable import VariableFIND
from core.Membership import computeWeights


class Model:
    def __init__(self, name=None, data=None):
        if name is not None:
            self.name = name
        if data is not None and 'fuzzify' in data['model']:
            self.variables = data['model']['fuzzify']
        else:
            self.variables = []

        if data is not None and 'defuzzify' in data['model']:
            self.defuzzify = data['model']['defuzzify']
        else:
            self.defuzzify = []

    def getNumRules(self):
        """
        Computes the total number of rules required by the current model, considering all the possible
        combinations of membership functions and variables.
        :return: Total number of rules.
        """
        n_rules = 1.0
        for v in self.variables:
            n_rules *= len(v.membership_functions)
        return n_rules

    def getMaxNumberOfMF(self):
        """
        Computes the maximum number of membership functions among all the variables.
        :return: Maximum number of membership functions.
        """
        return max([len(v.membership_functions) for v in self.variables])

    def setInputValuesList(self, values):
        """
        Assign the input value to each input variable taking values from a list.

        :param values: the list of input values
        :return: None
        """
        for i, var in enumerate(self.variables):
            var.input = values[i]


class ModelFIND(Model):
    def load(self, infile):
        with open(infile, 'rb') as f:
            data = toml.load(f)
        if 'model' not in data:
            raise ValueError("Missing 'model' section")
        if 'fuzzify' not in data['model']:
            raise ValueError("Missing 'fuzzify' section in model section")
        if 'defuzzify' not in data['model']:
            raise ValueError("Missing 'defuzzify' section in model section")
        if len(data['model']['fuzzify']) < 1:
            raise ValueError("At least 1 input variable required")

        for var_name in data['model']['fuzzify']:
            var = VariableFIND(name=var_name, data=data[var_name])
            self.variables.append(var)
            logging.debug(str(var))
        output_function_name = data['model']['defuzzify']
        self.defuzzify = VariableFIND(name=output_function_name, data=data[output_function_name])
        return data

    def calcIndex(self):
        """
        First the program does the AND of all the rules and then the SUM of all
        the ANDs. The exit function is evaluated according to sum of the
        normalized weights of all the functions. Finally the value of the
        functions composing the exit function are evaluated dividing the
        range of the index [0; 100] into a number of parts equal to the number of
        functions in the exit variable. The final value is obtained through a
        composition of the intermediate indexes. The number of executions of this
        procedure is equal to the combination of all functions of all variables.

        :return: The value of the index.
        """

        nv = len(self.variables)
        # // product of the number of functions
        # long n_rules;
        # double[] membership = new double[nv];
        # double[] var = new double[ef.getFuncNumber()];
        # double weight_sum, sum_membership_prod, membership_prod, div;
        # // counter for the index of each variable
        # int[] count = new int[nv];

        if (nv <= 0):
            raise ValueError("The number of variables {} (<= 0): can not compute the index".format(nv))

        # gets the maximum number of membership functions among all variables
        maxMF = self.getMaxNumberOfMF()

        # # indexes of the active MFs in each variable
        # # an active MF is one MF having output != 0 for the given input value
        # int activeMF[][] = new int[nv][maxMF]
        #
        # # number of active functions for each variable
        # int[] naf = new int[nv]
        #
        # # resets the content of arrays
        # for (i = 0; i < nv; i++):
        #     naf[i] = 0
        #     count[i] = 0
        #     for (j = 0; j < maxMF; j++):
        #         activeMF[i][j] = -1

        # number of active functions for each variable
        naf = np.zeros(nv)
        # counter for the index of each variable
        count = np.zeros(nv)
        # indexes of the active MFs in each variable
        # an active MF is one MF having output != 0 for the given input value
        activeMF = -1 * np.ones(nv * maxMF).reshape(nv, maxMF)

        membership = np.zeros(nv)

        # initialize the arrays
        # for (i = 0; i < nv; i++):
        for i, var in enumerate(self.variables):
            # Variable currVar = v.get(i);
            # for (j = 0; j < currVar.getFuncNumber(); j++):
            for j, mf in enumerate(var.membership_functions):
                if mf.outputIsNull(var.input):
                # if mf.outputIsNull(var.getInput()):
                # if (mf.f(var.getInput()) != 0.0):   # TODO: a isNull() method may help here
                    activeMF[i][naf[i]] = j
                    naf[i] += 1

        # calculate the total number of rules
        n_rules = 1
        # for (i = 0; i < nv; i++):
        for val in naf:
            n_rules *= val

        n_exit_functions = len(self.defuzzify.membership_functions)

        fuzzyOut = np.zeros(n_exit_functions)
        var = np.zeros(n_exit_functions)

        # for (i = 0; i < ef.getFuncNumber(); i++):
        #     fuzzyOut[i] = 0.0
        #     var[i] = 0.

        # one loop for each rule
        sum_membership_prod = 0.0
        # for (i = 0; i < n_rules; i++):
        # for i in xrange(n_rules):
        for i in np.arange(n_rules):
            weight_sum = 0.0
            membership_prod = 1.0

            # one loop for each value of the rule
            # for (j = 0; j < nv; j++):
            for j, var in enumerate(self.variables):
                # Variable currVar = v.get(j)

                # mf = var.getMF(activeMF[j][count[j]])
                mf = var.membership_functions[int(activeMF[j][count[j]])]

                # sum the contribution of the j-th variable
                # weight_sum += mf.getNormalizedWeight()
                weight_sum += mf.normalized_weight

                # calculate the membership grade of j-th variable
                membership[j] = mf.f(var.getInput())

                # calculate the AND operator among membership grades
                membership_prod *= membership[j]

            # sum the column of ANDs
            sum_membership_prod += membership_prod

            # for (j = 0; j < ef.getFuncNumber(); j++):
            for j in np.arange(n_exit_functions):
                var[j] += self.ef.getMF(j).f(weight_sum) * membership_prod

            # update the counters to evaluate the next rule
            count[0] += 1
            # for (j = 0; j < nv - 1; j++):
            for j in np.arange(nv - 1):
                count[j + 1] += count[j] / naf[j]
                count[j] %= naf[j]

        # double es_n_func = ef.getFuncNumber()
        es_n_func = n_exit_functions
        div = 1.0 / (es_n_func - 1.0)
        indexValue = 0.0
        # for (i = 0; i < ef.getFuncNumber(); i++):
        for i in np.arange(es_n_func):
            fuzzyOut[i] = var[i] / sum_membership_prod
            indexValue += div * i * fuzzyOut[i]

        indexValue = 100 * indexValue

        return indexValue


    def computeNormalizedWeights(self):
        """
	    Compute and assign the normalized weights of the functions. First add the
	    weights of all the best functions of all the variables, then divide the
	    weight of all the functions of all the variables by this sum.
	    """
        # int nv, nf;
		# int i, j;
		# double sum, w;

		# get the sum of all the weights of the best cases
        sum = 0.0
        for var in self.variables:
            sum += var.weight * var.getBestMF().weight

        for var in self.variables:
            nf = var.getFuncNumber()

            # compute and assign the normalized weights
            # for (j = 0; j < nf; j++):
            #     w = var.getMF(j).getWeight()
            #     var.getMF(j).setNormalizedWeight(var.getWeight() * w / sum)


            for mf in var.membership_functions:
                w = mf.weight
                mf.normalized_weight = var.weight * w / sum

    def computeVariables(self, step):
        """
        First computes the weights for each variable; afterwards calculates the normalized weights
        of all the functions for all the variables in the model

        :param step: the number of integration steps used to calculate the distances between membership functions.
	    """

        # nv = getVarNumber()
        # for (i = 0; i < nv; i++) {
        #     v.get(i).computeWeights(step)
        # computeNormalizedWeights()

        computeWeights(self, step)
        self.computeNormalizedWeights(self)
