import jinja2 as j2
import os

mfDict = {
	# 'pairwise-linear': ,
	'triangle': 'TRI_MF',
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

class fuzzyCreator(object):
	def __init__(self, models, tmplDir=os.getcwd(), outDir=os.getcwd()):
		self.models = models
		self.tmplDir = tmplDir
		self.outDir = outDir

	def render(self, inFolder=True):
		for model in self.models:
			outDir = self.outDir

			if inFolder:
				outDir = os.path.join(outDir, model.name)
				os.mkdir(outDir)

			renderer = templateRenderer(model, self.tmplDir)

			for tmpl in templateList:
				tmplSplit = tmpl.split('.')
				outfile = tmplSplit[0] + '_' + model.name + '.' + tmplSplit[1]
				renderer.write(os.path.join(outDir, outfile), tmpl)
