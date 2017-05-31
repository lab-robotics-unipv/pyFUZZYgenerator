import numpy as np
import math
import logging
import pdb

class MembershipFunction(object):
	def __init__(self, name, data):
		"""
		This method is called by child classes to initialize name, description and type from provided data,
		plus the index indicating the order, increasing from left to right.
		"""
		self.name = name
		self.description = data.get('description', '')
		self.type = data['type']
		self.centroid_x = None
		self.index = None
			 
		self.weight = None
		self.nWeight = None

	def __str__(self):
		return self.name

	@property
	def type(self):
		return self.__type

	@type.setter
	def type(self, value):
		if value != self.required_type:
			raise TypeError("{} type is '{}', not '{}'".format(self.printable_type_name, value, self.required_type))
		self.__type = value

	def check_parameters_number(self, param):
		if self.required_parameters_min_number is not None and len(param) < self.required_parameters_min_number:
			raise ValueError('{} requires at least {} parameters, {} given : {}'.format(self.printable_type_name,
																			   self.required_parameters_min_number,
																			   str(len(param)), str(param)))
		if self.required_parameters_max_number is not None and len(param) > self.required_parameters_max_number:
			raise ValueError('{} requires at most {} parameters, {} given : {}'.format(self.printable_type_name,
																			  self.required_parameters_max_number,
																			  str(len(param)), str(param)))

	def check_distinct_parameters(self, param):
                pass
		#if len(set(param)) != len(param):
		#	raise ValueError('{} parameters must be distinct (given {})'.format(self.printable_type_name, str(param)))

	def check_parameters_scalar_order(self, param):
		ordered = sorted(param)
		if ordered != param:
			raise ValueError("{} parameters must sorted in increasing order (given '{}')".format(self.printable_type_name, str(param)))

	def check_parameters_pairwise_order(self, param):
		"""
		Checks that the list of pairwise elements is sorted.

		We want to check the correct ordering of the list of X coordinate components.

		:param param: list of parameters to be checked
		:return: raises a ValueError in case of issues
		"""
		x_components = [x[0] for x in param]
		self.check_parameters_scalar_order(x_components)

	def getMinX(self):
		raise NotImplementedError("To be overriden in child classes")

	def getMaxX(self):
		raise NotImplementedError("To be overriden in child classes")

	def getTopLeftX(self):
		raise NotImplementedError("To be overriden in child classes")

	def getTopRightX(self):
		raise NotImplementedError("To be overriden in child classes")

	def f(self, value):
		raise NotImplementedError("To be overriden in child classes")

	def outputIsNull(self, value):
		raise NotImplementedError("To be overriden in child classes")

	def getCentroidX(self):
		"""
		Returns the X coordinate of the function centroid.

		The value is calculated using calcCentroidX if self.centroid_x is None, otherwise it returns the stored value.
		The integration step of the calculation is set to 10000 points.
		:return: Floating point value.
		"""
		if self.centroid_x is not None:
			return self.centroid_x
		else:
			return self.__calcCentroidX(10000)

	def __calcCentroidX(self, n):
		"""
		Calculates the X coordinate of the function centroid by integration.

		:param n: Number of integration steps.
		:return: Result of the integration, as a floating point value.
		"""
		sum_fx = 0.0
		sum_xfx = 0.0;
		dx = (self.getMaxX() - self.getMinX()) / n

		x = self.getMinX()
		max_x = self.getMaxX()
		while (x < max_x):
			value = self.f(x)
			sum_fx += value
			sum_xfx += x * value
			x += dx
			return sum_xfx / sum_fx
			
	def getMFindex(self):
		return self.data['index']
		
	def setWeight(self, weight):
		self.weight = weight
	
	def getWeight(self):
		return self.weight
	
	def setNormalizedWeight(self,weight):
		self.nWeight = weight
	
	def getNormalizedWeight(self):
		return self.nWeight
		


class Triangle(MembershipFunction):
	"""
	Triangle membership function.

	The Triangle membership function is defined by exactly 3 parameters: the left lower corner (y = 0),
	the middle corner (y = 1) and the right lower corner (y = 0).
	"""
	def __init__(self, name, data):
		self.required_type = 'triangle'
		self.printable_type_name = 'Triangle'
		self.required_parameters_min_number = 3
		self.required_parameters_max_number = 3
		self.parameters = [float(x) for x in data['parameters']]
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, values):
		self.check_parameters_number(values)
		self.check_distinct_parameters(values)
		self.check_parameters_scalar_order(values)
		self.__parameters = [float(x) for x in values]
		self.centroid_x = None

	def getMinX(self):
		return self.parameters[0]

	def getMaxX(self):
		return self.parameters[2]

	def getTopLeftX(self):
		return self.parameters[1]

	def getTopRightX(self):
		return self.parameters[1]

	def f(self, x):
		p = self.parameters
		
		#Special case of Triangle with 2 equal points ( Triangle Rectangle ) 
		if p[0] == p[1]:
			if x == p[0]:
				return 1
		if p[1] == p[2]:
			if x == p[1]:
				 return 1
		if x <= p[0]:
			return 0
		if x <= p[1]:
			return (p[0] - x) / (p[0] - p[1])
		if x < p[2]:
			return (x - p[2]) / (p[1] - p[2])
		return 0

	def outputIsNull(self, value):
		p = self.parameters
		if value <= p[0] or value >= p[2]:
			return True
		else:
			return False


class Trapezoid(MembershipFunction):
	"""
	Trapezoid membership function.

	The Trapezoid membership function is defined by exactly 4 parameters: the left lower corner (y = 0),
	the middle left corner (y = 1), the middle right corner (y = 1) and the right lower corner (y = 0).
	"""
	def __init__(self, name, data):
		self.required_type = 'trapezoid'
		self.printable_type_name = 'Trapezoid'
		self.required_parameters_min_number = 4
		self.required_parameters_max_number = 4
		self.parameters = [float(x) for x in data['parameters']]
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, values):
		self.check_parameters_number(values)
		self.check_distinct_parameters(values)
		self.check_parameters_scalar_order(values)
		self.__parameters = [float(x) for x in values]
		self.centroid_x = None

	def getMinX(self):
		return self.parameters[0]

	def getMaxX(self):
		return self.parameters[3]

	def getTopLeftX(self):
		return self.parameters[1]

	def getTopRightX(self):
		return self.parameters[2]

	def f(self, x):
		p = self.parameters
		if x <= p[0]:
			return 0
		if x <= p[1]:
			return (p[0] - x) / (p[0] - p[1])
		if x < p[2]:
			return 1
		if x < p[3]:
			return (p[3] - x) / (p[3] - p[2])
		return 0

	def outputIsNull(self, value):
		p = self.parameters
		if value <= p[0] or value >= p[3]:
			return True
		else:
			return False

# TODO: maybe a singleton type with variable height different from 1 may be of interest
class Singleton(MembershipFunction):
	def __init__(self, name, data):
		self.required_type = 'singleton'
		self.printable_type_name = 'Singleton'
		self.required_parameters_min_number = 1
		self.required_parameters_max_number = None
		self.parameters = [data['parameters']]   # set as one-element list to allow iteration on checking
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, param):
		self.check_distinct_parameters(param)
		self.check_parameters_scalar_order(param)
		self.__parameters = [float(x) for x in param]
		self.centroid_x = None   # invalidates the stored centroid value

	def getMinX(self):
		return self.parameters[0]

	def getMaxX(self):
		return self.parameters[-1]

	def f(self, value):
		if value in self.parameters:
			return 1
		else:
			return 0

	def outputIsNull(self, value):
		if value not in self.parameters:
			return True
		else:
			return False

#TODO : Implement also Product and difference of Sigmoids
class Sigmoid(MembershipFunction):
	def __init__(self, name, data):
		self.required_type = 'sigmoid'
		self.printable_type_name = 'Sigmoid'
		self.required_parameters_min_number = 2
		self.required_parameters_max_number = 2
		#First value is the slope, the second is the center
		self.parameters = [float(x) for x in data['parameters']]
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, param):
		self.check_parameters_number(param)
		self.__parameters = [float(x) for x in param]
		self.centroid_x = None  # invalidates the stored centroid value

	def getMinX(self):
		#When the Sigmoid reaches the value 0.001
		value = - math.fabs(self.parameters[0] * 4)
		if self.parameters[0] > 0:
			while ( 1.0 / (1.0 + math.exp(-self.parameters[0] * (value))) < 0.001 ):
				value += 0.01
			return value + self.parameters[1]
		
		else:
			while ( (1.0 / (1.0 + math.exp(-self.parameters[0] * (value)))) > 0.999 ):
				value += 0.01
			return value + self.parameters[1]	

	def getMaxX(self):
		#When the Sigmoid reaches the value 0.001
		value = - math.fabs(self.parameters[0] * 4)
		if self.parameters[0] > 0:
			while ( 1.0 / (1.0 + math.exp(-self.parameters[0] * (value))) < 0.999  ):
				value += 0.01
			return value + self.parameters[1]
		
		else:
			while ( 1.0 / (1.0 + math.exp(-self.parameters[0] * (value))) > 0.001 ):
				value += 0.01
			return value + self.parameters[1]	

	def getTopLeftX(self):
		return self.parameters[1]

	def getTopRightX(self):
		return self.parameters[1]
		
	def f(self, value):
		return 1.0 / (1.0 + math.exp(-self.parameters[0] * (value - self.parameters[1])))

	def outputIsNull(self, value):
		if self.f(value) <= 0.0000001:
			return True
		else:
			return False
			
class DiffSigmoid(MembershipFunction):
	def __init__(self, name, data):
		self.required_type = 'diff_sigmoid'
		self.printable_type_name = 'DiffSigmoid'
		self.required_parameters_min_number = 4
		self.required_parameters_max_number = 4
		#First value is the slope, the second is the center of the first Sigmoid
		self.parameters = [float(x) for x in data['parameters']]
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, param):
		self.check_parameters_number(param)
		self.__parameters = [float(x) for x in param]
		self.centroid_x = None  # invalidates the stored centroid value

	def getMinX(self):
		#When the Sigmoid reaches the value 0.001
		value = - math.fabs(self.parameters[0] * 4)
		while ( 1.0 / (1.0 + math.exp(-self.parameters[0] * (value))) < 0.001 ):
			value += 0.01
		return value + self.parameters[1]	

	def getMaxX(self):
		#When the Sigmoid reaches the value 0.001
		value = - math.fabs(self.parameters[0] * 4)
		while ( 1.0 / (1.0 + math.exp(-self.parameters[0] * (value))) > 0.001 ):
			value += 0.01
		return value + self.parameters[1]	
		
	def getTopLeftX(self):
		return self.parameters[1]

	def getTopRightX(self):
		return self.parameters[3]
		
	def f(self, value):
		slope = math.exp( -self.parameters[0] * ( value - self.parameters[1]));
		slope1 = math.exp( -self.parameters[2] * ( value - self.parameters[3]));
		return math.fabs( (1 / (1 + slope)) - ( 1 / ( 1 + slope1)));

	def outputIsNull(self, value):
		if self.f(value) <= 0.0000001:
			return True
		else:
			return False
					
class Gaussian(MembershipFunction):
	def __init__(self, name, data):
		self.required_type = 'gaussian'
		self.printable_type_name = 'Gaussian'
		self.required_parameters_min_number = 2
		self.required_parameters_max_number = 2
		#First value is the slope, the second is the center
		self.parameters = [float(x) for x in data['parameters']]
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, param):
		self.check_parameters_number(param)
		self.__parameters = [float(x) for x in param]
		self.centroid_x = None  # invalidates the stored centroid value

	def getMinX(self):
		#TODO: check if this value is correct
		return self.parameters[1] - math.fabs( 3 * self.parameters[0])

	def getMaxX(self):
		#TODO: check if this value is correct
		return self.parameters[1] + math.fabs( 3 * self.parameters[0])
		
	def getTopLeftX(self):
		return self.parameters[1]

	def getTopRightX(self):
		return self.parameters[1]
		
	def f(self, value):
		return math.exp( - ( value - pow(self.parameters[1],2) )  / ( 2 * pow(self.parameters[0],2)) )

	def outputIsNull(self, value):
		if self.f(value) <= 0.0000001:
			return True
		else:
			return False
			
#TODO: This class can be removed, sine a Pairwise function can be approximated by a rectangle triangle.
class PairwiseLinear(MembershipFunction):
	def __init__(self, name, data):
		self.required_type = 'pairwise-linear'
		self.printable_type_name = 'Pairwise-linear'
		self.required_parameters_min_number = 2
		self.required_parameters_max_number = None
		self.parameters = data['parameters']
		super().__init__(name, data)

	@property
	def parameters(self):
		return self.__parameters

	@parameters.setter
	def parameters(self, param):
		# self.check_distinct_parameters(param)
		self.check_parameters_pairwise_order(param)
		self.__parameters = param
		self.centroid_x = None  # invalidates the stored centroid value

	def getMinX(self):
		return self.parameters[0][0]

	def getMaxX(self):
		return self.parameters[-1][0]

	def f(self, x):
		logging.debug(self.parameters)
		if x <= self.parameters[0][0]:
			return self.parameters[0][1]
		elif x >= self.parameters[-1][0]:
			return self.parameters[-1][1]
		else:
			# TODO: logic to be implemented
			return None

	def outputIsNull(self, value):
		# NOTE: this safe in case the function goes to 0
		if self.f(value) <= 0.0000001:
			return True
		else:
			return False


class MembershipFactory():
	def __init__(self, data):
		self.data = data
		
		if self.data is None:
			raise ValueError("data is None in MF {}".format(self.data['name']))

		try:
			self.name = self.data['name']
		except:
			raise ValueError("name is None in MF {}".format(self.data['name']))

	def getMF(self):
		if 'type' not in self.data:
			raise ValueError("Missing type field in MF {}".format(self.name))

		type_name = self.data['type']
		if type_name == 'pairwise-linear':
			mf = PairwiseLinear(self.name, self.data)
		elif type_name == 'triangle':
			mf = Triangle(self.name, self.data)
		elif type_name == 'trapezoid':
			mf = Trapezoid(self.name, self.data)
		elif type_name == 'gaussian-bell':
			pass
		elif type_name == 'gaussian':
			mf = Gaussian(self.name, self.data)
		elif type_name == 'gaussian2':
			pass
		elif type_name == 'sigmoid':
			mf = Sigmoid(self.name, self.data)
		elif type_name == 'singleton':
			mf = Singleton(self.name, self.data)
		elif type_name == 'diff_sigmoid':
			mf = DiffSigmoid(self.name, self.data)
		else:
			raise ValueError("Invalid type {} in MF {}".format(type_name, self.name))
		return mf
	

	

