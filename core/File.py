import json
import sys
from core.Membership import MembershipFactory


class RulesSet():
    def __init__(self, data):
        pass


class Variable():
    def __init__(self, name, data):
        tag_mf = 'membership_functions'
        self.name = name
        self.description = data.get('description', '')
        if tag_mf in data:
            self.mf = [MembershipFactory(f, data[tag_mf][f]) for f in data[tag_mf]]
        self.data = data

    def __str__(self):
        s = 'VAR ' + self.name
        if self.description != '':
            s += ' (' + self.description + ')'
        s += '\n'
        for f in self.mf:
            s += str(f) + '\n'
        return s


class Model():
    def __init__(self, name, data):
        self.name = name
        self.description = data.get('description', '')
        if 'fuzzify' in data:
            self.input_var = [Variable(v, data['fuzzify'][v]) for v in data['fuzzify']]
        else:
            self.input_var = []
        if 'defuzzify' in data:
            self.output_var = [Variable(v, data['defuzzify'][v]) for v in data['defuzzify']]
        else:
            self.output_var = []
        if 'rules_set' in data:
            self.rules = RulesSet(data['rules_set'])
        else:
            self.rules = []

    def __str__(self):
        s = 'MODEL ' + self.name
        if self.description != '':
            s += ' (' + self.description + ')'
        s += '\n'
        for v in self.input_var:
            s += str(v) + '\n'
        for v in self.output_var:
            s += str(v) + '\n'
        return s


class File():
    def __init__(self, fname):
        self.fname = fname

    def load(self):
        with open(self.fname, 'r') as f:
            self.models = json.load(f)
        models = [Model(m, self.models[m]) for m in self.models]
        return models


f = File(sys.argv[1])
models = f.load()
for m in models:
    print(m)
