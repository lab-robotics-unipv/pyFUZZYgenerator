class ModelType:
    def __init__(self):
        self.type = None
        self.properties = {}
        self.models = []
        self.logic_function_name = None
        self.init_function_name = None
        self.output_function_name = None

    def __eq__(self, other):
        if other.type == self.type:
            return True
        return False

    def update(self, model):
        self.models.append(model)


class TooBigDimensionsException(Exception):
    pass


class ModelNotFoundException(Exception):
    pass


class FINDModelType(ModelType):
    def __init__(self):
        super().__init__()
        self.type = "F-IND"
        self.properties["max_input_n"] = 0
        self.logic_function_name = "findLogic"
        self.init_function_name = "initFindLogic"
        self.output_function_name = "calculateFindIndex"

    def update(self, model):
        super().update(model)
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
        self.logic_function_name = "fisLogic"
        self.init_function_name = "initFisLogic"
        self.output_function_name = "calculateFisOutput"

    def update(self, model):
        super().update(model)


class FEQModelType(ModelType):
    def __init__(self):
        super().__init__()
        self.type = "FIS"
        self.logic_function_name = "feqLogic"
        self.init_function_name = "initFeqLogic"
        self.output_function_name = "calculateFeqOutput"

    def update(self, model):
        super().update(model)


class ModelTypeSet:
    def __init__(self):
        self.model_type_list = []

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

        if model_type not in self.model_type_list:
            self.model_type_list.append(model_type)

        actual_model_type = self.model_type_list[self.model_type_list.index(model_type)]
        actual_model_type.update(model)

    def __iter__(self):
        return self.model_type_list.__iter__()
