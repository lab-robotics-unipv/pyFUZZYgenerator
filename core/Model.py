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

		# for r in self.rules:
		# 	print(r)
		# print("")

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
			
		#TODO: Creare le regole 
		self.parseRules() 
   
   
	def parseRules(self): 
     
		#TODO: Decidere come verrà dato lo step di integrazione 
		step = 1 
		self.computeVariables(step) 
         
	def computeVariables(self, step): 
		""" 
		First computes the weights for each variable; afterwards calculates the normalized weights 
		of all the functions for all the variables in the model 

		:param step: the number of integration steps used to calculate the distances between membership functions. 
		""" 
		pdb.set_trace() 
		for var in self.input_var: 
		  var.computeWeights(step) 

		self.computeNormalizedWeights() 
	  
	def computeNormalizedWeights(self): 
		""" 
		Compute and assign the normalized weights of the functions. First add the 
		weights of all the best functions of all the variables, then divide the 
		weight of all the functions of all the variables by this sum. 
		""" 

		#TODO: Add the function getWeight for the Variables! **IMPORTANT** 

		# get the sum of all the weights of the best cases 
		sum = 0.0 
		for var in self.input_var: 
		  #sum += var.getWeight() * var.getBestMF().getWeight() 
		  sum += 1 * var.getBestMF().getWeight() 
		 
		for var in self.input_var: 
		  for mf in var.membership_functions: 
			w = mf.getWeight() 
			#mf.setNormalizedWeight(var.getWeight * w / sum) 
			mf.setNormalizedWeight( 1 * w / sum)    
