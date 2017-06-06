class ModelType:
    def __init__(self):
        self.type = None
        self.properties = {}

    def __eq__(self, other):
        if other.type == self.type:
            return True
        return False

    def update(self, model):
        raise NotImplementedError


class TooBigDimensionsException(Exception):
    pass


class ModelNotFoundException(Exception):
    pass


class FINDModelType(ModelType):
    def __init__(self):
        super().__init__()
        self.type = "F-IND"
        self.properties["max_input_n"] = 0

    def update(self, model):
        self.properties["max_input_n"] = max(len(model.input_var), self.properties["max_input_n"])

    def get_squaredint_t(self):
        ninput = self.properties["max_input_n"]
        if ninput < 8:
            return "uint8_t"
        elif ninput < 16:
            return "uint16_t"
        elif ninput < 32:
            return "uint32_t"
        else:
            raise TooBigDimensionsException


class FISModelType(ModelType):
    def __init__(self):
        super().__init__()
        self.type = "FIS"

    def update(self, model):
        pass


class FEQModelType(ModelType):
    def __init__(self):
        super().__init__()
        self.type = "FIS"

    def update(self, model):
        pass


class ModelTypeSet:
    def __init__(self):
        self.list = []

    def update(self, model):
        model_type = None
        if model.type.upper() == 'F-IND':
            model_type = FINDModelType()
        elif model.type.upper() == 'FEQ':
            model_type = FEQModelType()
        elif model.type.upper() != 'FIS':
            model_type = FISModelType()
        else:
            raise ModelNotFoundException

        if model_type not in self.list:
            self.list.append(model_type)

        actual_model_type = self.list[self.list.index(model_type)]
        actual_model_type.update(model)

    def __iter__(self):
        return self.list.__iter__()
