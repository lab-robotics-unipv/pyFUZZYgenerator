import logging
import numpy as np
# TODO: Remove the following input when the code will be completed

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

        # TODO chiedere a Daniele come risolvere in modo furbo
        i = 0
        for mf in self.membership_functions:
            mf.index = i
            i += 1

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

    def getMFfromIndex(self, index):
        """
        Return the MF corresponding to the index given as input

        input : index

        return: a MF
        """
        for mf in self.membership_functions:
            tmp_index = mf.index
            if tmp_index == index:
                return mf

        raise ValueError(
            '{} is not a valid index, probably is mayor than the maximum one'.format(index))


class VariableFstd(Variable):
    def __init__(self, data):
        super().__init__(data)


class VariableFeq(Variable):
    def __init__(self, data, input=True):
        super().__init__(data)
        self.equilibrium = data['equilibrium']
        self.rules = data.get('rules', None)
        if self.rules == None and input:
            raise ValueError(
                "{} is input but does not contain the rules!".format(self.name))

    @property
    def equilibrium(self):
        return self.__equilibrium

    @equilibrium.setter
    def equilibrium(self, eq):
        equil = next((i for i, mf in enumerate(
            self.membership_functions) if mf.name == eq), None)
        if equil is None:
            raise ValueError(
                "{} not contained in variable {}".format(eq, self.name))
        self.__equilibrium = equil


class VariableFind(Variable):
    def __init__(self, data):
        super().__init__(data)

        try:
            # TODO: It could be added a Weight associated to each input variable.
            #self.weight = data['weight']
            self.best = data['best']
            self.worst = data['worst']
        except:
            raise

    @property
    def best(self):
        return self.__best

    @best.setter
    def best(self, bst):
        best = next(
            (mf for mf in self.membership_functions if mf.name == bst), None)
        if best is None:
            raise ValueError(
                "{} not contained in variable {}".format(bst, self.name))
        elif hasattr(self, 'worst') and best == self.worst:
            raise ValueError("Best can not be same as worst")
        self.__best = best

    @property
    def worst(self):
        return self.__worst

    @worst.setter
    def worst(self, wst):
        worst = next(
            (mf for mf in self.membership_functions if mf.name == wst), None)
        if worst is None:
            raise ValueError(
                "{} not contained in variable {}".format(wst, self.name))
        elif hasattr(self, 'best') and worst == self.best:
            raise ValueError("Worst can not be same as best")
        self.__worst = worst

    def getBestMF(self):
        for mf in self.membership_functions:
            if mf.name == self.best.name:
                return mf

    def getWorstMF(self):
        for mf in self.membership_functions:
            if mf.name == self.worst.name:
                return mf

    def getBestMFindex(self):
        return self.getBestMF().index

    def getWorstMFindex(self):
        return self.getWorstMF().index

    # TODO : Refactoring of the following method is needed
    def getExternalDiff(self, f1, f2, x_min, x_max, scale, step):
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

        mf1 = self.getMFfromIndex(f1)
        mf2 = self.getMFfromIndex(f2)
        x1 = mf1.getMaxX()
        x2 = mf2.getMinX()
        dx1 = 0.5 * (x1 - x_min) / step
        if dx1 > 0.0:
            x = x2
            while x < x_max:
                # for (x = x2; x < x_max; x += dx1):
                # for x in np.linspace(x2, x_max, step):
                sum1 += abs(mf1.f(x) - mf2.f(x))
                x += dx1

        dx2 = 0.5 * (x_max - x2) / step
        if dx2 > 0.0:
            x = x_min
            # for (x = x_min; x < x1; x += dx2):
            # for x in np.linspace(x_min, x1, step):
            while x < x1:
                sum2 += abs(mf1.f(x) - mf2.f(x))
                x = x + dx2

        return ((sum1 * dx1) + (sum2 * dx2)) / scale

    def getInternalDiff(self, f1, f2, scale, step):
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
        sum = 0.0
        mf1 = self.getMFfromIndex(f1)
        mf2 = self.getMFfromIndex(f2)
        x1 = mf1.getMinX()
        x2 = mf2.getMaxX()
        dx = (x2 - x1) / step

        for x in np.linspace(x1, x2, step+1):
            sum += abs(mf1.f(x) - mf2.f(x))
            x += dx

        return (sum * dx) / scale

    def getInternalHoleSize(self, f1, f2, scale, step):
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
        mf1 = self.getMFfromIndex(f1)
        mf2 = self.getMFfromIndex(f2)
        x1 = mf1.getTopRightX()
        x2 = mf2.getTopLeftX()
        dx = (x2 - x1) / step
        if dx > 0.0:
            for x in np.linspace(x1, x2, step+1):
                y1 = mf1.f(x)
                y2 = mf2.f(x)
                if y1 > y2:
                    sum += 1.0 - y1
                else:
                    sum += 1.0 - y2

        return (sum * dx) / scale

    # TODO: the following method needs to be refactored
    def getExternalHoleSize(self, f1, f2, x_min, x_max, scale, step):
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
        mf1 = self.getMFfromIndex(f1)
        mf2 = self.getMFfromIndex(f2)
        x1 = mf1.getTopLeftX()
        x2 = mf2.getTopRightX()
        dx1 = (x1 - x_min) / step   # TODO: remove this
        if dx1 > 0.0:
            # for (x = x_min; x < x1; x += dx1):
            # TODO : Cambiare questi loop for con dei while, siccome funzionano
            # for x in np.linspace(x1 - x_min, x1, step):
            x = x_min
            while x < x1:
                # TODO: 1.0 - in the expression can be replaced by size(range) - integral(f)
                sum1 += 1.0 - mf1.f(x)
                x = x + dx1

        dx2 = (x_max - x2) / step
        if dx2 > 0.0:
            # for (x = x2; x < x_max; x += dx2):
            # for x in np.linspace(x2, x_max, step):
            x = x2
            while x < x_max:
                sum2 += 1.0 - mf2.f(x)
                x = x + dx2

        return ((sum1 * dx1) + (sum2 * dx2)) / scale

    def getExternalDistance(self, f1, f2, x_min, x_max, scale, step):
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
        return self.getExternalDiff(f1, f2, x_min, x_max, scale, step) + self.getExternalHoleSize(f1, f2, x_min, x_max, scale, step)

    def getInternalDistance(self, f1, f2, scale, step):
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
        return self.getInternalDiff(f1, f2, scale, step) + self.getInternalHoleSize(f1, f2, scale, step)

    def sumVect(self, d, nf, worst, best, internal):
        """
        Compute the sum of a vector from worst to best, i think it could me changed

        worst and best are passed as index of the respective MFs
        """
        distance = 0.0
        i = 0

        if worst == best:
            return 0.0

        # We want te worst MF before best MF
        if (best < worst):
            tmp = best
            best = worst
            worst = tmp

        if (internal):
            while worst < best:
                distance = distance + d[worst]
                worst = worst + 1
        else:
            while best < (nf):  # TODO : Controllare se ci va nf - 1
                distance = distance + d[best]
                best = best + 1
            while i < worst:
                distance = distance + d[worst]
                i = i + 1

        return distance

    # TODO: the following method needs to be refactored
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
        minX = self.getMinX()
        maxX = self.getMaxX()
        logging.debug(self)
        logging.debug(self.best)
        logging.debug(self.worst)

        if (self.worst == self.best):
            raise ValueError(
                "{}: worst and best membership functions are the same.".format(self.name))

        nf = len(self.membership_functions)
        interval = maxX - minX

        worstIndex = self.getWorstMFindex()
        bestIndex = self.getBestMFindex()

        i = 0
        while i < (nf-1):
            f1 = self.getMFfromIndex(i)
            f2 = self.getMFfromIndex(i+1)
            d.append(self.getInternalDistance(
                f1.index, f2.index, interval, step))
            i = i + 1
        d.append(self.getExternalDistance(self.getMFfromIndex(0).index,
                                          self.getMFfromIndex(nf - 1).index, minX, maxX, interval, step))
        """
		for mf in self.membership_functions:    # TODO: fix since we need to address i-th and (i+1)-th mf
			d.append(getInternalDistance(self, getMF(i), getMF(i + 1), interval, step))
			d.append(getExternalDistance(self, getMF(0), getMF(nf - 1), getMinX(), getMaxX(), interval, step))
		"""
        self.getWorstMF().setWeight(0.0)
        # pdb.set_trace()
        # TODO : fare in modo furbo la somma di questi vettori
        # Qua sto calcolando la distanza massima tra worst e best, sia nel caso interno che esterno

        d1 = self.sumVect(d, nf, worstIndex, bestIndex, True)
        d2 = self.sumVect(d, nf, worstIndex, bestIndex, False)

        if (d1 > d2):
            self.getBestMF().setWeight(d1)
            internal = True
        else:
            self.getBestMF().setWeight(d2)
            internal = False

        # for (i = 0; i < nf; i++):
        i = 0
        while i < nf:
            if (i != worstIndex) and (i != bestIndex):
                d1 = self.sumVect(d, nf, worstIndex, i, True)
                d2 = self.sumVect(d, nf, worstIndex, i, False)

                # it seems independent from the value of the "internal" flag
                if (internal):
                    if (worstIndex < bestIndex):
                        if (i < bestIndex):
                            self.getMFfromIndex(i).setWeight(d1)
                        else:
                            self.getMFfromIndex(i).setWeight(d2)
                    else:
                        if (i > bestIndex):
                            self.getMFfromIndex(i).setWeight(d1)
                        else:
                            self.getMFfromIndex(i).setWeight(d2)
                else:
                    if (worstIndex < bestIndex):
                        if (i < bestIndex):
                            self.getMFfromIndex(i).setWeight(d1)
                        else:
                            self.getMFfromIndex(i).setWeight(d2)
                    else:
                        if (i > bestIndex):
                            self.getMFfromIndex(i).setWeight(d1)
                        else:
                            self.getMFfromIndex(i).setWeight(d2)

            i = i + 1
        # pdb.set_trace()
