# pyFUZZYgenerator

## Overview
pyFUZZYgenerator is a framework to automatically generate a fuzzy systems in ANSI C using configuration files.

## Usage
To generate a fuzzy library, you have to create a configuration file.
The files are written in [TOML](https://github.com/toml-lang/toml) syntax.

In the `examples` directory some examples are provided for each fuzzy type.

In the followings, we will use the default example for the F-IND model: `examples/sampleFIND.toml`.

To create a C library usng the FIND file, you have to run the `main.py` script:
```bash
python3 main.py examples/sampleFIND.toml -d outputDir
```
More details on the options and arguments can be seen in the help:
```bash
python3 main.py -h
```

The generated code can already be compiled using `gcc *c -lm` in the output folder.
A sample `main.c` is automatically generated and can be adjusted to fit user needs.

## Requirements
The Python (python3) library requires the following packages:
- pytoml
- jinja2
- numpy

To simplify the requirements installation, we provide an [Anaconda](https://www.continuum.io/) environment, that can be imported with:
```bash
conda env create -f environment.yaml
```

## TODOs
- Upload the C library of a general fuzzy system
- Optimize the general fuzzy library
- Add pip installation for the package

## Contact
If you find any problem, please open an issue and we'll try to help.
