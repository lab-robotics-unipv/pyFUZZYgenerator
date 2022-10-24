from core.fuzzyCreator import fuzzyCreator
import argparse
import sys
from pathlib import Path


def tomlFile(string):
    f = Path(string)
    ext = f.suffix
    if ext != '.toml':
        raise argparse.ArgumentTypeError(
            "{} should have .toml extension".format(string))
    return f


def outputDir(string):
    p = Path(string)
    if p.exists() and not p.is_dir():
        raise argparse.ArgumentError(
            "{} exists and it is not a directory".format(string))
    return p


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Translate TOML files into ANSI C Fuzzy library', prog=sys.argv[0])
    parser.add_argument(metavar='TOML', type=tomlFile, nargs='+',
                        help='a TOML file to translate', dest='toml')
    parser.add_argument('-p', '--plain', action='store_false',
                        help='plain output - disable the subfolder splitting')
    parser.add_argument('-o', '--output-dir', type=outputDir,
                        default='./output', help='output directory')
    parser.add_argument('-is', '--include_strings', action="store_true",
                        help='Include names in input and output (models require more memory)')

    args = parser.parse_args()

    for toml in args.toml:
        with toml.open('r') as t:
            try:
                fuzzyCreator(t.read(), args.output_dir).render(
                    args.no_subforlder, args.include_strings)
            except:
                raise
