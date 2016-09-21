from core.fuzzyCreator import fuzzyCreator
import argparse
import os
from pathlib import Path

def tomlFile(string):
	f = Path(string)
	ext = f.suffix
	if ext != '.toml':
		raise argparse.ArgumentTypeError("{} should have .toml extension".format(string))
	return f

def outputDir(string):
	p = Path(string)
	if p.exists() and not p.is_dir():
		raise argparse.ArgumentError("{} exists and it is not a directory".format(string))
	return p

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Translate TOML files into ANSI C Fuzzy library', prog='fuzzyTranslator')
	parser.add_argument(metavar='TOML', type=tomlFile, nargs='*', help='a TOML file to translate', dest='toml')
	parser.add_argument('-n', '--no-subforlder', action='store_true', help='disable the subfolder division')
	parser.add_argument('-d', '--output-dir', type=outputDir, default='./output', help='output directory')

	args = parser.parse_args()
	
	for toml in args.toml:
		with open(toml, 'r') as t:
			try:
				fuzzyCreator(t.read(), './templates/', args.output_dir).render(args.no_subforlder)
			except:
				raise

