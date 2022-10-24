import shutil

import jinja2 as j2
import pytoml
from pathlib import Path

from core import Model, ModelType

from core.ModelValidator import ModelValidator

folders = {
        "F-IND": "F-IND",
}

mfDict = {
        # 'pairwise-linear': ,
        'triangle': 'TRI_MF',
        'trapezoid': 'TRAP_MF',
        # 'gaussian-bell': ,
        # 'gaussian2': ,
        'gaussian': 'GAUSSIAN_MF',
        'sigmoid': 'SIGMOID_MF',
        'diff_sigmoid': 'DIF_SIGMOID_MF',
        'singleton': 'SPIKE_MF',
}


class templateRenderer(object):
    def __init__(self, model, path):
        #self.tmplDir = Path(__file__).parent / '..' / 'templates' / folders[model.type.lower()]
        self.tmplDir = path
        self.tmplDir.resolve()

        loader = j2.FileSystemLoader(str(self.tmplDir))
        self.env = j2.Environment(
            loader=loader, trim_blocks=True, lstrip_blocks=True)
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

    def __process_template__(self, renderer, template_name, out_dir, add_model_name=None):
        try:
            tmplSplit = template_name.split('.')
            if add_model_name is None:
                outfile = tmplSplit[0] + '.' + tmplSplit[1]
            else:
                outfile = tmplSplit[0] + '_' + \
                    add_model_name + '.' + tmplSplit[1]
            renderer.write(out_dir / outfile, template_name)
        except j2.TemplateSyntaxError as e:
            print("Exception in ", template_name, ":")
            raise e


    def render(self, subfolder=True, include_strings=False):
        if not self.outDir.exists():
            self.outDir.mkdir(parents=True)

        # Validate the models
        validator = ModelValidator(self.models)
        validator.validate()

        model_types_added = ModelType.ModelTypeSet()

        outDir = self.outDir
        i = 0
        for model in self.models:
            # this is required to have unique numbers for each model
            # to be used by argp in the main C file for reading
            # from command line (the starting value must be > 256)
            model.id_for_cli = 1000 + i

            model.include_strings = include_strings
            if subfolder:
                outDir = self.outDir / model.name
                if not outDir.exists():
                    outDir.mkdir()
                model.subfolder = model.name + '/'
                model.include_path_for_models = '../'
            else:
                model.subfolder = ""
                model.include_path_for_models = ""

            templ_dir = Path(__file__).parent / '..' / \
                'templates' / folders[model.type.upper()]

            renderer = templateRenderer(model, templ_dir)

            template_list = templ_dir.glob('*.j2')
            template_list = [x.name for x in template_list]

            for tmpl in template_list:
                self.__process_template__(renderer, tmpl, outDir, model.name)

            model_types_added.update(model)
            i += 1

        # Check if the model type has any common that should be copied as well
        for mt in model_types_added:
            mt.include_strings = include_strings
            templ_dir = Path(__file__).parent / '..' / \
                             'templates' / folders[mt.type]
            common = (templ_dir / 'common').exists()
            if common:
                renderer = templateRenderer(mt, templ_dir / "common")
                fileDir = templ_dir / 'common'
                fileList = fileDir.glob('*')
                for f in fileList:
                    if f.is_file():
                        if f.suffix == ".j2":
                            self.__process_template__(
                                renderer, f.name, self.outDir)
                        else:
                            shutil.copy(str(f), str(self.outDir))

        # Copies common model types files
        fileDir = Path(__file__).parent / '..' / 'templates' / "common"
        fileList = fileDir.glob('*')
        renderer = templateRenderer(model_types_added, fileDir)
        for f in fileList:
            if f.is_file():
                if f.suffix == ".j2":
                    self.__process_template__(renderer, f.name, self.outDir)
                else:
                    shutil.copy(str(f), str(self.outDir))
