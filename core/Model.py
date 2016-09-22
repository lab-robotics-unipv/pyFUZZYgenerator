import re
# import logging
# import numpy as np

from core.Variable import VariableFis, VariableFind, VariableFeq
# from core.Membership import computeWeights


class Model:
	def __init__(self, data):
		self.name = data.get('name', None)
		self.description = data.get('description', None)
		self.version = data.get('version', None)
		self.type = data.get('type', 'fis')

		self.input_var = []
		self.output_var = []
		try:
			self._input_var = data['input_var']
			self._output_var = data['output_var']
		except:
			raise

		self._rules = data.get('rules', None)
		self.andFn = self._rules.get('and', 'min')
		self.thenFn = self._rules.get('then', 'max')

	def getCorrectNumRules(self):
		"""
		Computes the total number of rules required by the current model, considering all the possible
		combinations of membership functions and variables.
		:return: Total number of rules.
		"""
		n_rules = 1.0
		for iv in self.input_var:
			n_rules *= len(iv.membership_functions)
		return n_rules

	def __str__(self):
		s = self.name + '\n'
		s += 'Inputs\n'
		for vi in self.input_var:
			s += '\t' + str(vi) + '\n'

		s += 'Outputs\n'
		for vo in self.output_var:
			s += '\t' + str(vo) + '\n'

		return s

	def getMaxNumberOfMFInput(self):
		"""
		Computes the maximum number of membership functions among all input the variables.
		:return: Maximum number of membership functions.
		"""
		return max([len(vi.membership_functions) for vi in self.input_var])

	def getMaxNumberOfMFOutput(self):
		"""
		Computes the maximum number of membership functions among all the output variables.
		:return: Maximum number of membership functions.
		"""
		return max([len(vo.membership_functions) for vo in self.output_var])

class ModelFeq(Model):
	def __init__(self, data):
		super().__init__(data)

		for iv in self._input_var:
			self.input_var.append(VariableFeq(iv))

		for ov in self._output_var:
			self.output_var.append(VariableFeq(ov, False))

		try:
			self.checkRules()
		except:
			raise

		self.createRules()

	def createRules(self):
		self.rules = []
		numRules = self.getCorrectNumRules()
		ruleGen = self.iterate()
		while len(self.rules) != numRules:
			ifMFs = next(ruleGen)
			thMFs = [0] * len(self.output_var)

			ifRs = []
			weight_sum = 0
			for iv, mf in zip(self.input_var, ifMFs):
				ifRs.append((iv.name, iv.membership_functions[mf].name))
				for i, ov in enumerate(self.output_var):
					r = next((rule for rule in iv.rules if rule['output'] == ov.name), None)
					p = r['fact'] * r['weight'] * (mf - iv.equilibrium)
					weight_sum += r['weight']
					thMFs[i] += p

			thRs = []
			for i, ov in enumerate(self.output_var):
				thMFs[i] = round(thMFs[i]/weight_sum)
				thMFs[i] += ov.equilibrium
				# import pdb; pdb.set_trace()
				# thMFs[i] = thMFs[i]/weight_sum
				if thMFs[i] < 0:
					thMFs[i] = 0
				elif thMFs[i] >= len(ov.membership_functions) - 1:
					thMFs[i] = len(ov.membership_functions) - 1

				thRs.append((ov.name, ov.membership_functions[thMFs[i]].name))

			self.rules.append((list(ifRs), list(thRs), 1))

		for r in self.rules:
			print(r)
		print("")

		#round(sum(fatt))

	def iterate(self):
		num = [0]*len(self.input_var)
		stop = [len(i.membership_functions) for i in self.input_var]
		while num[0] < stop[0]:
			yield num
			num[-1] += 1
			for i in reversed(range(1, len(self.input_var))):
				if num[i] == stop[i]:
					num[i] = 0
					num[i-1] += 1

	def checkRules(self):
		for iv in self.input_var:
			if len(iv.rules) > len(self.output_var):
				raise ValueError("Too many rules for {}".format(iv.name))

			for ov in self.output_var:
				r = [n['output'] for n in iv.rules]
				if ov.name not in r:
					raise ValueError("{} not in rules for {}".format(ov.name, iv.name))

class ModelFis(Model):
	def __init__(self, data):
		super().__init__(data)

		for iv in self._input_var:
			self.input_var.append(VariableFis(iv))

		for ov in self._output_var:
			self.output_var.append(VariableFis(ov))

		self.rules = self.parseRules()
		if len(self.rules) != self.getCorrectNumRules():
			raise Exception("Correct number of rules for model {name} is {num}".format(name=self.name, num=self.getCorrectNumRules()))

	def parseRules(self):
		regexpGlobal = r'if (.*) then (.*) with (\d)'
		rules = []
		try:
			for r in self._rules['rules']:
				a = re.match(regexpGlobal, r)
				ifR = re.split('\sand\s', a.group(1))
				thR = re.split('\sand\s', a.group(2))

				ifRs = []
				for i in ifR:
					ifRs.append(tuple(re.split('\sis\s', i[1:-1])))

				thRs = []
				for i in thR:
					thRs.append(tuple(re.split('\sis\s', i[1:-1])))

				rules.append((ifRs, thRs, a.group(3)))
		except:
			raise

		return rules


	# def setInputValuesList(self, values):
	# 	"""
	# 	Assign the input value to each input variable taking values from a list.

	# 	:param values: the list of input values
	# 	:return: None
	# 	"""
	# 	for i, var in enumerate(self.variables):
	# 		var.input = values[i]


class ModelFIND(Model):
	def __init__(self, data):
		super().__init__(data)
		for iv in self._input_var:
			self.input_var.append(VariableFind(iv))

		for ov in self._output_var:
			self.output_var.append(VariableFind(ov))
#
# 	def calcIndex(self):
# 		"""
# 		First the program does the AND of all the rules and then the SUM of all
# 		the ANDs. The exit function is evaluated according to sum of the
# 		normalized weights of all the functions. Finally the value of the
# 		functions composing the exit function are evaluated dividing the
# 		range of the index [0; 100] into a number of parts equal to the number of
# 		functions in the exit variable. The final value is obtained through a
# 		composition of the intermediate indexes. The number of executions of this
# 		procedure is equal to the combination of all functions of all variables.
#
# 		:return: The value of the index.
# 		"""
#
# 		nv = len(self.variables)
# 		# // product of the number of functions
# 		# long n_rules;
# 		# double[] membership = new double[nv];
# 		# double[] var = new double[ef.getFuncNumber()];
# 		# double weight_sum, sum_membership_prod, membership_prod, div;
# 		# // counter for the index of each variable
# 		# int[] count = new int[nv];
#
# 		if (nv <= 0):
# 			raise ValueError("The number of variables {} (<= 0): can not compute the index".format(nv))
#
# 		# gets the maximum number of membership functions among all variables
# 		maxMF = self.getMaxNumberOfMF()
#
# 		# # indexes of the active MFs in each variable
# 		# # an active MF is one MF having output != 0 for the given input value
# 		# int activeMF[][] = new int[nv][maxMF]
# 		#
# 		# # number of active functions for each variable
# 		# int[] naf = new int[nv]
# 		#
# 		# # resets the content of arrays
# 		# for (i = 0; i < nv; i++):
# 		#     naf[i] = 0
# 		#     count[i] = 0
# 		#     for (j = 0; j < maxMF; j++):
# 		#         activeMF[i][j] = -1
#
# 		# number of active functions for each variable
# 		naf = np.zeros(nv)
# 		# counter for the index of each variable
# 		count = np.zeros(nv)
# 		# indexes of the active MFs in each variable
# 		# an active MF is one MF having output != 0 for the given input value
# 		activeMF = -1 * np.ones(nv * maxMF).reshape(nv, maxMF)
#
# 		membership = np.zeros(nv)
#
# 		# initialize the arrays
# 		# for (i = 0; i < nv; i++):
# 		for i, var in enumerate(self.variables):
# 			# Variable currVar = v.get(i);
# 			# for (j = 0; j < currVar.getFuncNumber(); j++):
# 			for j, mf in enumerate(var.membership_functions):
# 				if mf.outputIsNull(var.input):
# 					# if mf.outputIsNull(var.getInput()):
# 					# if (mf.f(var.getInput()) != 0.0):   # TODO: a isNull() method may help here
# 					activeMF[i][naf[i]] = j
# 					naf[i] += 1
#
# 		# calculate the total number of rules
# 		n_rules = 1
# 		# for (i = 0; i < nv; i++):
# 		for val in naf:
# 			n_rules *= val
#
# 		n_exit_functions = len(self.defuzzify.membership_functions)
#
# 		fuzzyOut = np.zeros(n_exit_functions)
# 		var = np.zeros(n_exit_functions)
#
# 		# for (i = 0; i < ef.getFuncNumber(); i++):
# 		#     fuzzyOut[i] = 0.0
# 		#     var[i] = 0.
#
# 		# one loop for each rule
# 		sum_membership_prod = 0.0
# 		# for (i = 0; i < n_rules; i++):
# 		# for i in xrange(n_rules):
# 		for i in np.arange(n_rules):
# 			weight_sum = 0.0
# 			membership_prod = 1.0
#
# 			# one loop for each value of the rule
# 			# for (j = 0; j < nv; j++):
# 			for j, var in enumerate(self.variables):
# 				# Variable currVar = v.get(j)
#
# 				# mf = var.getMF(activeMF[j][count[j]])
# 				mf = var.membership_functions[int(activeMF[j][count[j]])]
#
# 				# sum the contribution of the j-th variable
# 				# weight_sum += mf.getNormalizedWeight()
# 				weight_sum += mf.normalized_weight
#
# 				# calculate the membership grade of j-th variable
# 				membership[j] = mf.f(var.getInput())
#
# 				# calculate the AND operator among membership grades
# 				membership_prod *= membership[j]
#
# 			# sum the column of ANDs
# 			sum_membership_prod += membership_prod
#
# 			# for (j = 0; j < ef.getFuncNumber(); j++):
# 			for j in np.arange(n_exit_functions):
# 				var[j] += self.ef.getMF(j).f(weight_sum) * membership_prod
#
# 			# update the counters to evaluate the next rule
# 			count[0] += 1
# 			# for (j = 0; j < nv - 1; j++):
# 			for j in np.arange(nv - 1):
# 				count[j + 1] += count[j] / naf[j]
# 				count[j] %= naf[j]
#
# 		# double es_n_func = ef.getFuncNumber()
# 		es_n_func = n_exit_functions
# 		div = 1.0 / (es_n_func - 1.0)
# 		indexValue = 0.0
# 		# for (i = 0; i < ef.getFuncNumber(); i++):
# 		for i in np.arange(es_n_func):
# 			fuzzyOut[i] = var[i] / sum_membership_prod
# 			indexValue += div * i * fuzzyOut[i]
#
# 		indexValue = 100 * indexValue
#
# 		return indexValue
#
#
# 	def computeNormalizedWeights(self):
# 		"""
# 		Compute and assign the normalized weights of the functions. First add the
# 		weights of all the best functions of all the variables, then divide the
# 		weight of all the functions of all the variables by this sum.
# 		"""
# 		# int nv, nf;
# 		# int i, j;
# 		# double sum, w;
#
# 		# get the sum of all the weights of the best cases
# 		sum = 0.0
# 		for var in self.variables:
# 			sum += var.weight * var.getBestMF().weight
#
# 		for var in self.variables:
# 			nf = var.getFuncNumber()
#
# 			# compute and assign the normalized weights
# 			# for (j = 0; j < nf; j++):
# 			#     w = var.getMF(j).getWeight()
# 			#     var.getMF(j).setNormalizedWeight(var.getWeight() * w / sum)
#
#
# 			for mf in var.membership_functions:
# 				w = mf.weight
# 				mf.normalized_weight = var.weight * w / sum
#
# 	def computeVariables(self, step):
# 		"""
# 		First computes the weights for each variable; afterwards calculates the normalized weights
# 		of all the functions for all the variables in the model
#
# 		:param step: the number of integration steps used to calculate the distances between membership functions.
# 		"""
#
# 		# nv = getVarNumber()
# 		# for (i = 0; i < nv; i++) {
# 		#     v.get(i).computeWeights(step)
# 		# computeNormalizedWeights()
#
# 		for var in self.variables:
# 			computeWeights(var, step)
# 			self.computeNormalizedWeights(self)
