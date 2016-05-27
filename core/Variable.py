import logging

from core.Membership import MembershipFactory

class Variable:
	def __init__(self, data):
		try:
			self.name = data['name']
		except:
			raise

		self.description = data.get('description', None)

		self.membership_functions = []
		for mf in data['mf']:
			self.add_membership_function(mf)

	def add_membership_function(self, data):
		factory = MembershipFactory(data)
		mf = factory.getMF()
		self.membership_functions.append(mf)

	def getMinX(self):
		"""
		Returns the minimum X value among all the membership functions belonging to the variable.

		:return: a floating point value.
		"""
		return min([mf.getMinX() for mf in self.membership_functions])


	def getMaxX(self):
		"""
		Returns the maximum X value among all the membership functions belonging to the variable.

		:return: a floating point value.
		"""
		return max([mf.getMaxX() for mf in self.membership_functions])

	def __str__(self):
		return self.name + ': ' + ', '.join([str(mf) for mf in self.membership_functions])

class VariableFis(Variable):
	def __init__(self, data):
		super().__init__(data)


class VariableFIND(Variable):
	def __init__(self, name=None, data=None):
		super().__init__(name, data)
		try:
			self.weight = data['weight']
			self.best = data['best']
			self.worst = data['worst']
		except:
			raise

	@property
	def best(self):
		return self.__best

	@best.setter
	def best(self, bst):
		best = next((mf for mf in self.membership_functions if mf.name == bst), None)
		if best is None:
			raise ValueError("{} not contained in variable {}".format(bst, self.name))
		elif hasattr(self, 'worst') and best == self.worst:
		    raise ValueError("Best can not be same as worst")
		self.__best = best

	@property
	def worst(self):
		return self.__worst

	@worst.setter
	def worst(self, wst):
		worst = next((mf for mf in self.membership_functions if mf.name == wst), None)
		if worst is None:
			raise ValueError("{} not contained in variable {}".format(wst, self.name))
		elif hasattr(self, 'best') and worst == self.best:
		    raise ValueError("Worst can not be same as best")
		self.__worst = worst

	def getBestMF(self):
		return self.membership_functions[self.best]

	def getWorstMF(self):
		return self.membership_functions[self.worst]
