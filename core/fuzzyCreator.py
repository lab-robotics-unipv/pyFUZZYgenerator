import shutil

import jinja2 as j2
import os
import pytoml
from pathlib import Path

from core import Model

folders = {
	"f-ind": "F-IND",
}

mfDict = {
	# 'pairwise-linear': ,
	'triangle': 'TRI_MF',
	'trapezoid': 'TRAP_MF',
	# 'gaussian-bell': ,
	# 'gaussian2': ,
	'gaussian': 'GAUSSIAN_MF' ,
	'sigmoid': 'SIGMOID_MF',
	'diff_sigmoid' : 'DIF_SIGMOID_MF',
	'singleton': 'SPIKE_MF',
}

class templateRenderer(object):
	def __init__(self, model):
		self.tmplDir = Path(__file__).parent / '..' / 'templates' / folders[model.type.lower()]
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

		model_types_added = set()

		outDir = self.outDir
		for model in self.models:
			if subfolder:
				outDir = self.outDir / model.name
				if not outDir.exists():
					outDir.mkdir()

			renderer = templateRenderer(model)

			templDir = Path(__file__).parent / '..' / 'templates' / folders[model.type.lower()]
			templateList = templDir.glob('*.j2')
			common = (templDir / 'common').exists()

			for tmpl in templateList:
				tmplSplit = tmpl.split('.')
				if tmplSplit[0] == 'main' or tmplSplit[0] == 'setup' or tmplSplit[0] == 'README' :
					outfile = tmplSplit[0] + '.' + tmplSplit[1]
				else:
					outfile = tmplSplit[0] + '_' + model.name + '.' + tmplSplit[1]
				renderer.write(outDir / outfile, tmpl)

			model_types_added.add(model.type.lower())

		# Check if the model type has any common that should be copied as well
		for mt in model_types_added:
			templDir = Path(__file__).parent / '..' / 'templates' / folders[mt]
			common = (templDir / 'common').exists()

			if common:
				fileDir = templDir / 'common'
				fileList = fileDir.glob('*')
				for f in fileList:
					if f.is_file():
						shutil.copy(f, self.outDir)

		# Copies common model types files
		fileDir = Path(__file__).parent / '..' / 'templates' / "common"
		fileList = fileDir.glob('*')
		for f in fileList:
			if f.is_file():
				shutil.copy(f, self.outDir)