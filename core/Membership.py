import numpy as np
import logging

def getExternalDiff(f1, f2, x_min, x_max, scale, step):
    """
    Compute the "external" difference between f1 and f2.

    The external difference goes from
    x_min to x1 and from x2 to x_max, where x1 is the max x of f1 and x2 is
    the min x of f2. The difference is computed as delta on the two functions y
    coordinate values corresponding to the same x coordinate. Then all these differences are added
    into sum1 starting from x_min to x1 and then from x2 to x_max in sum2.
    Finally the integral is computed by multiplying the 2 sums by the 2
    differentials dx1 and dx2.

    IMPORTANT: membership function f1 MUST be on the left w.r.t. f2.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min: min x value from which the distance is computed
    :param x_max: max x value from which the distance is computed
    :param scale: scale factor that divides the final result
    :param step: number of steps for the computation
    :return: the external difference between f1 and f2
    """
    sum1 = 0.0
    sum2 = 0.0

    x1 = f1.getMaxX()
    x2 = f2.getMinX()
    dx1 = 0.5 * (x1 - x_min) / step
    if dx1 > 0.0:
        # for (x = x2; x < x_max; x += dx1):
        for x in np.linspace(x2, x_max, step):
            sum1 += abs(f1.y(x) - f2.y(x))

    dx2 = 0.5 * (x_max - x2) / step;
    if dx2 > 0.0:
        # for (x = x_min; x < x1; x += dx2):
        for x in np.linspace(x_min, x1, step):
            sum2 += abs(f1.y(x) - f2.y(x))

    return ((sum1 * dx1) + (sum2 * dx2)) / scale


def getInternalDiff(f1, f2, scale, step):
    """
    Compute the "internal" difference between f1 and f2, which goes from x1
    to x2, where x1 is the max x of f1 and x2 is the min x of f2. The
    difference is computed as delta on the 2 function y coordinate on the
    same x coordinate. Then all these differences are added into sum. Finally
    the integral is computed by multiplying the sum by the differential dx.

    IMPORTANT: membership function f1 MUST be on the left w.r.t. f2.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the internal difference between f1 and f2
    """
    sum = 0.0;

    x1 = f1.getMinX()
    x2 = f2.getMaxX()
    dx = (x2 - x1) / step;
    # for (x = x1; x <= x2; x += dx):
    for x in np.linspace(x1, x2, step):
        sum += abs(f1.f(x) - f2.f(x))
    return (sum * dx) / scale

def getInternalHoleSize(f1, f2, scale, step):
    """
    Compute the "internal" hole size between f1 and f2, which goes from x1 to
    x2, where x1 is the top right x of f1 and x2 is the top left x of f2. A
    difference is computed: 1-y of f1 and f2 starting from x1 and ending into
    x2. This difference is added into sum and finally the integral is
    computed by multiplying the sum by the differential dx.

    IMPORTANT: membership function f1 MUST be on the left w.r.t. f2.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the internal hole size between f1 and f2
    """
    sum = 0.0

    x1 = f1.getTopRightX()
    x2 = f2.getTopLeftX()
    dx = (x2 - x1) / step
    if dx > 0.0:
        # for (x = x1; x <= x2; x += dx):
        for x in np.linspace(x1, x2, step):
            y1 = f1.f(x)
            y2 = f2.f(x)
            if y1 > y2:
                sum += 1.0 - y1
            else:
                sum += 1.0 - y2
    return (sum * dx) / scale


def getExternalHoleSize(f1, f2, x_min, x_max, scale, step):
    """
    Compute the "external" hole size between f1 and f2, which goes from x_min
    to x1 and from x2 to x_max, where x1 is the top left x of f1 and x2 is
    the top right x of f2. 2 differences are computed: 1-y of f1 starting
    from x_min and ending into x1 and 1-y of f2 starting from x2 and ending
    into x_max. These 2 differences are added into sum1 and sum2 and finally
    the integral is computed by multiplying the 2 sums by the 2 differentials
    dx1 and dx2.

    IMPORTANT: membership function f1 MUST be on the left w.r.t. f2

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min :min value from which the distance is being computed
    :param x_max: max value to which the distance is being computed
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the external hole size between f1 and f2
    """
    sum1 = 0.0
    sum2 = 0.0

    x1 = f1.getTopLeftX()
    x2 = f2.getTopRightX()
    dx1 = (x1 - x_min) / step   # TODO: remove this
    if dx1 > 0.0:
        # for (x = x_min; x < x1; x += dx1):
        for x in np.linspace(x1 - x_min, x1, step):
            sum1 += 1.0 - f1.f(x)   # TODO: 1.0 - in the expression can be replaced by size(range) - integral(f)
    dx2 = (x_max - x2) / step
    if dx2 > 0.0:
        # for (x = x2; x < x_max; x += dx2):
        for x in np.linspace(x2, x_max, step):
            sum2 += 1.0 - f2.f(x)
    return ((sum1 * dx1) + (sum2 * dx2)) / scale


def getExternalCentroidDist(f1, f2, x_min, x_max, scale, step):
    """
    Compute the "external" distance between the centroids of f1 and f2
    membership functions. The distance is obtained by substracting the real
    distance to the size of the range of definition of the corresponding
    variable.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min :min value from which the distance is being computed
    :param x_max: max value to which the distance is being computed
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the external distance between of f1 and f2 centroids
    """
    dist = abs(f1.getCentroidX(step) - f2.getCentroidX(step))
    return (abs(x_max - x_min) - dist) / scale


def getInternalCentroidDist(f1, f2, x_min, x_max, scale, step):
    """
    Compute the "internal" distance between the centroids of f1 and f2
    membership functions.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min :min value from which the distance is being computed
    :param x_max: max value to which the distance is being computed
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the internal distance between of f1 and f2 centroids
    """
    dist = abs(f1.getCentroidX(step) - f2.getCentroidX(step))
    return dist / scale


def getExternalDistance(f1, f2, x_min, x_max, scale, step):
    """
    Compute the external distance between f1 and f2 membership functions.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min :min value from which the distance is being computed
    :param x_max: max value to which the distance is being computed
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the external distance between of f1 and f2 centroids
    """
    return getExternalDiff(f1, f2, x_min, x_max, scale, step) + getExternalHoleSize(f1, f2, x_min, x_max, scale, step)


def getInternalDistance(f1, f2, x_min, x_max, scale, step):
    """
    Compute the internal distance between f1 and f2 membership functions.

    :param f1: membership function on the left
    :param f2: membership function on the right
    :param x_min :min value from which the distance is being computed
    :param x_max: max value to which the distance is being computed
    :param scale: scale factor that divides the final result
    :param step: the number of steps for the computation
    :return: the internal distance between of f1 and f2 centroids
    """
    return getInternalDiff(f1, f2, x_min, x_max, scale, step) + getInternalHoleSize(f1, f2, x_min, x_max, scale, step)


def computeWeights(self, step):
    """
	/**
	 * Compute and assign a weight of every function. WORST has weight=0, BEST
	 * has weight=max and all the other functions have intermediate weights.
	 * Since the weight is computed as a distance and the distance between worst
	 * and best function must be the largest, if these 2 functions are not on
	 * the opposite sides, the external distance is used. All the other weights
	 * are computed imagining the intermediate function always between best and
	 * worst ones, so that the appropriate distance (internal or external) is
	 * used. Worst-best distance is a special case.
	 *
	 * @param step
	 *            the number of integration steps
	 */
	"""

    d = []

    if (self.isCrisp()):   # TODO: check what this means
        return
    if (self.worst == self.best):
        raise ValueError("Worst and best membership functions are the same.")

    nf = len(self.membership_functions)
    interval = self.getMaxX() - self.getMinX()
    for mf in self.membership_functions:    # TODO: fix since we need to address i-th and (i+1)-th mf
        d.append(getInternalDistance(getMF(i), getMF(i + 1), interval, step))
    d.append(getExternalDistance(getMF(0), getMF(nf - 1), getMinX(), getMaxX(), interval, step))

    self.getWorstMF().setWeight(0.0)

    d1 = sumVect(d, nf, self.worst, self.best, True)
    d2 = sumVect(d, nf, self.worst, self.best, False)

    if (d1 > d2):
        self.getBestMF().setWeight(d1)
        internal = True
    else:
        self.getBestMF().setWeight(d2)
        internal = False

    # for (i = 0; i < nf; i++):
    for i, mf in enumerate(self.membership_functions):
        if (i != worst) and (i != best):
            d1 = sumVect(d, nf, worst, i, true);
            d2 = sumVect(d, nf, worst, i, false);

            # it seems independent from the value of the "internal" flag
            if (internal):
                if (self.worst < best):
                    if (i < best):
                        getMF(i).setWeight(d1)
                    else:
                        getMF(i).setWeight(d2)
                else:
                    if (i > best):
                        getMF(i).setWeight(d1)
                    else:
                        getMF(i).setWeight(d2)
            else:
                if (worst < best):
                    if (i < best):
                        getMF(i).setWeight(d1)
                    else:
                        getMF(i).setWeight(d2)
                else:
                    if (i > best):
                        getMF(i).setWeight(d1)
                    else:
                        getMF(i).setWeight(d2)


class MembershipFunction(object):
    def __init__(self, name, data):
        """
        This method is called by child classes to initialize name, description and type from provided data.
        """
        self.name = name
        self.description = data.get('description', '')
        self.type = data['type']
        self.centroid_x = None

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
        if len(set(param)) != len(param):
            raise ValueError('{} parameters must be distinct (given {})'.format(self.printable_type_name, str(param)))

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
        return self.parameters[0][0]

    def getMaxX(self):
        return self.parameters[2][0]

    def getTopLeftX(self):
        return self.parameters[1][0]

    def getTopRightX(self):
        return self.parameters[1][0]

    def f(self, x):
        p = self.parameters
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
        return self.parameters[0][0]

    def getMaxX(self):
        return self.parameters[3][0]

    def getTopLeftX(self):
        return self.parameters[1][0]

    def getTopRightX(self):
        return self.parameters[2][0]

    def f(self, x):
        p = self.parameters
        if x <= p[0]:
            return 0
        if x <= p[1]:
            return (p[0] - x) / (p[0] - p[1])
        if x < p[2]:
            return 1
        if x < p[3]:
            return (x - p[2]) / (p[1] - p[2])
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


class Sigmoid(MembershipFunction):
    def __init__(self, name, data):
        self.required_type = 'sigmoid'
        self.printable_type_name = 'Sigmoid'
        self.required_parameters_min_number = 2
        self.required_parameters_max_number = 2
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

    def f(self, value):
        return 1. / (1. + np.exp(-self.parameters[0] * (value - self.parameters[1])))

    def outputIsNull(self, value):
        if self.f(value) <= 0.0000001:
            return True
        else:
            return False


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
    def __init__(self, name=None, data=None):
        self.name = name
        self.data = data

    def getMF(self):
        if self.data is None:
            raise ValueError("data is None in MF {}".format(self.name))
        if 'type' not in self.data:
            raise ValueError("Missing type field in MF {}".format(self.name))
        type_name = self.data['type']
        mf = None
        if type_name == 'pairwise-linear':
            mf = PairwiseLinear(self.name, self.data)
        elif type_name == 'triangle':
            mf = Triangle(self.name, self.data)
        elif type_name == 'trapezoid':
            mf = Trapezoid(self.name, self.data)
        elif type_name == 'gaussian-bell':
            pass
        elif type_name == 'gaussian':
            pass
        elif type_name == 'gaussian2':
            pass
        elif type_name == 'sigmoid':
            mf = Sigmoid(self.name, self.data)
        elif type_name == 'singleton':
            mf = Singleton(self.name, self.data)
        else:
            raise ValueError("Invalid type {} in MF {}".format(type_name, self.name))
        return mf

