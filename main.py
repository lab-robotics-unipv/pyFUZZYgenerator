from core.fuzzyCreator import fuzzyCreator
import argparse
import os

def tomlFile(string):
		base, ext = os.path.splitext(string)
		if ext != '.toml':
			raise argparse.ArgumentTypeError("{} should have .toml extension".format(string))
		return string

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Translate TOML files into ANSI C Fuzzy library', prog='fuzzyTranslator')
	parser.add_argument(metavar='TOML', type=tomlFile, nargs='*', help='a TOML file to translate', dest='toml')
	parser.add_argument('-n', '--nosubforlder', action='store_true', help='disable the subfolder division')

	args = parser.parse_args()
	
	print(args.toml)

	for toml in args.toml:
		with open(toml, 'r') as t:
			if args.nosubforlder:
				fuzzyCreator(t.read(), './templates/', './output').render(False)
			else:
				fuzzyCreator(t.read(), './templates/', './output').render(False)

