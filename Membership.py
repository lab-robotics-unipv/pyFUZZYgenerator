class MembershipFunction():
    pass


class Triangle(MembershipFunction):
    def __init__(self, name, data):
        self.name = name
        self.description = data.get('description', '')
        self.type = data['type']
        self.param = data['param']

    @property
    def _param(self, param):
        if len(param) != 3:
            raise('Triangle membership function requires 3 parameters, ' + len(param) + ' given :' + str(param))
        # TODO: must check that all 3 param are numbers
        # TODO: must check that numbers are distinct
        # TODO: must check that numbers are ordered in increasing order
        self.__param = param

    def f(self, x):
        p = self.param
        if x <= p[0]:
            return 0
        if x <= p[1]:
            return (p[0] - x) / (p[0] - p[1])
        if x < p[2]:
            return (x - p[2]) / (p[1] - p[2])
        return 0


class MembershipFactory():
    def __init__(self, name, data):
        self.name = name
        self.description = data.get('description', '')
        self.type = data['type']
        self.param = data['param']
        self.f = self.calc_functions(self.type)

    def linear(x):
        return -10000

    def triangle(x):
        return -10001

    def trapezoid(x):
        return -10002

    def gaussian_bell(x):
        return -10003

    def gaussian(x):
        return -10004

    def gaussian2(x):
        return -10005

    def sigmoid(x):
        return -10006

    def singleton(x):
        return -10007

    def calc_functions(self, type):
        funcs = {
            'pairwise-linear': self.linear,
            'triangle': self.triangle,
            'trapezoid': self.trapezoid,
            'gaussian-bell': self.gaussian_bell,
            'gaussian': self.gaussian,
            'gaussian2': self.gaussian2,
            'sigmoid': self.sigmoid,
            'singleton': self.singleton
        }
        return funcs[type]

    def __str__(self):
        s = 'MF ' + self.name
        if self.description != '':
            s += ' (' + self.description + ')'
        s += ' ' + self.type + ' ' + str(self.param)
        return s
