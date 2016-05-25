import jinja2 as j2
import os

class templateRenderer(object):
	def __init__(self, model, directory=os.getcwd()):
		loader = j2.FileSystemLoader(directory)
		self.env = j2.Environment(loader=loader, trim_blocks=True, lstrip_blocks=True)
		self.model = model

	def render(self, template):
		tmpl = self.env.get_template(template)
		return tmpl.render(model=model)

	def write(self, fileOut, template):
		with open(fileOut, 'w') as fo:
			fo.write(self.render(template))
