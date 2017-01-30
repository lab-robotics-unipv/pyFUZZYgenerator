import jinja2 as j2
import os
import pytoml
from pathlib import Path

from core import Model

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
	"rules.c.j2",
	"MFShapes.h.j2",
	"MFShapes.c.j2",
]

commonFileList = [
	"MFShapes.h.j2",
	"MFShapes.c.j2",
]

class templateRenderer(object):
	def __init__(self, model):
		self.tmplDir = Path(__file__).parent / '..' / 'templates'
		self.tmplDir.resolve()

		loader = j2.FileSystemLoader(str(self.tmplDir))
		self.env = j2.Environment(loader=loader, trim_blocks=True, lstrip_blocks=True)
		self.model = model

	def render(self, template):
		tmpl = self.env.get_template(template)
		return tmpl.render(model=self.model, mfDict=mfDict)

	def write(self, fileOut, template):
		with fileOut.open('w') as fo:
			fo.write(self.render(template))

class fuzzyCreator(object):
	def __init__(self, modelString, outDir):
		conf = pytoml.loads(modelString)
		
		self.models = []
		for m in conf['model']:
			if m['type'].upper() == 'F-IND':
				self.models.append(Model.ModelFIND(m))
			if m['type'].upper() == 'FEQ':
				self.models.append(Model.ModelFeq(m))
			if m['type'].upper() != 'F-IND' and m['type'].upper() != 'FEQ':
				self.models.append(Model.ModelFis(m))

		self.outDir = outDir

	def render(self, subfolder=True):
		if not self.outDir.exists():
			self.outDir.mkdir(parents=True)

		outDir = self.outDir
		for model in self.models:
			if subfolder:
				outDir = self.outDir / model.name
				if not outDir.exists():
					outDir.mkdir()

			renderer = templateRenderer(model)

			for tmpl in templateList:
				tmplSplit = tmpl.split('.')
				outfile = tmplSplit[0] + '_' + model.name + '.' + tmplSplit[1]
				renderer.write(outDir / outfile, tmpl)
