import logging

from core.Membership import MembershipFactory

class Variable:
    def __init__(self, name=None, data=None):
        logging.debug(data)
        self.name = name
        self.description = data.get('description', None)
        self.weight = data.get('weight', None)
        self.membership_functions = []
        for mf_name in data['membership_functions']:
            self.add_membership_function(name=mf_name, data=data[mf_name])
        self.input = None

    def __str__(self):
        s = str(self.name) + ': '
        for mf in self.membership_functions:
            if mf is None:
                s += ' None'
            else:
                s += ' ' + mf.name
        return s

    def add_membership_function(self, name=None, data=None):
        factory = MembershipFactory(name=name, data=data)
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


class VariableFIND(Variable):
    def __init__(self, name=None, data=None):
        super().__init__(name, data)
        self.best = None
        self.worst = None

    @property
    def best(self):
        return self.__best

    @best.setter
    def best(self, value):
        if value is None:
            pass  # will assign the value in the end
        elif hasattr(self, 'worst') and value == self.worst:
            raise ValueError("Best can not be same as worst")
        elif value < 0 or value > len(self.membership_functions):
            raise ValueError("Best value is {}, allowed range is [{},{}]".format(value, 0, len(self.membership_functions)))
        self.__best = value

    @property
    def worst(self):
        return self.__worst

    @worst.setter
    def worst(self, value):
        if value is None:
            pass   # will assign the value in the end
        elif hasattr(self, 'best') and value == self.best:
            raise ValueError("Wosrt can not be same as best")
        elif value < 0 or value > len(self.membership_functions):
            raise ValueError("Worst value is {}, allowed range is [{},{}]".format(value, 0, len(self.membership_functions)))
        self.__worst = value
