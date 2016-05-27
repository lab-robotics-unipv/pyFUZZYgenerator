import jinja2 as j2
import os

mfDict = {
	# 'pairwise-linear': ,
	'trinagle': 'TRI_MF',
	'trapezoid': 'TRAP_MF',
	# 'gaussian-bell': ,
	# 'gaussian': ,
	# 'gaussian2': ,
	# 'sigmoid': ,
	'singleton': 'SPIKE_MF',
}

templateList = [
	"definitions.h.j2",
	"fuzzyInput.c.j2",
	"fuzzyInput.h.j2",
	"fuzzyLogic.c.j2",
	"fuzzyLogic.h.j2",
	"fuzzyOutput.c.j2",
	"fuzzyOutput.h.j2",
	"init.c.j2",
	"init.h.j2",
	"memFunc.c.j2",
	"memFunc.h.j2",
	"rules.h.j2",
]

class templateRenderer(object):
	def __init__(self, model, directory=os.getcwd()):
		loader = j2.FileSystemLoader(directory)
		self.env = j2.Environment(loader=loader, trim_blocks=True, lstrip_blocks=True)
		self.model = model

	def render(self, template):
		tmpl = self.env.get_template(template)
		return tmpl.render(model=self.model, mfDict=mfDict)

	def write(self, fileOut, template):
		with open(fileOut, 'w') as fo:
			fo.write(self.render(template))
