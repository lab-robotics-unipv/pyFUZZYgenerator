import re


class ModelValidator(object):
    def __init__(self, models):
        self.models = models
        self.regex_to_validate_c_variables = r"[a-zA-Z_][a-zA-Z0-9_]*"
        self.regex_to_validate_c_variables_end = r"[a-zA-Z0-9_]*"

        # List of reserved words from https://beginnersbook.com/2014/01/c-keywords-reserved-words/
        self.c_reserved_words = [
            "if", "else", "switch", "case", "default",
            "break",
            "int", "float", "char", "double", "long",
            "for", "while", "do",
            "void",
            "goto",
            "auto", "signed", "const", "extern", "register", "unsigned",
            "return",
            "continue",
            "enum",
            "sizeof",
            "struct", "typedef",
            "union",
            "volatile"
        ]

    def validate_c_variable_name(self, variable):
        # First thing: check if any space is present in the string, if it is replace it with underscores
        variable = variable.replace(" ", "_")

        # Check for non valid character, if any is found raise exception
        tmp = re.search(self.regex_to_validate_c_variables, variable).group(0)
        if str(tmp) != variable:
            print("%s: invalid variable name" % variable)
            raise NameError()

        if variable in self.c_reserved_words:
            print("%s: is a C reserved word" % variable)
            raise NameError()

        return variable


    def validate_c_end_of_variable_name(self, variable):
        """"Validate those variable names that are appended to other variables.
            Therefore, there are no problems in using reserved words and numbers
            at the beginning.
        """
        # First thing: check if any space is present in the string, if it is replace it with underscores
        variable = variable.replace(" ", "_")

        # Check for non valid character, if any is found raise exception
        tmp = re.search(self.regex_to_validate_c_variables_end, variable).group(0)
        if str(tmp) != variable:
            print("%s: invalid variable name" % variable)
            raise NameError()

        return variable

    def validate(self):
        models = self.models

        for model in models:
            model.name = self.validate_c_variable_name(model.name)

            for var in model.input_var:
                var.name = self.validate_c_variable_name(var.name)
                var.best.name = self.validate_c_end_of_variable_name(var.best.name)
                var.worst.name = self.validate_c_end_of_variable_name(var.worst.name)

                for mf in var.membership_functions:
                    mf.name = self.validate_c_end_of_variable_name(mf.name)

            for var in model.output_var:
                var.name = self.validate_c_variable_name(var.name)
                var.best.name = self.validate_c_end_of_variable_name(var.best.name)
                var.worst.name = self.validate_c_end_of_variable_name(var.worst.name)

                for mf in var.membership_functions:
                    mf.name = self.validate_c_end_of_variable_name(mf.name)