

<img src="doc/img/pyfuzzy_logo_with_text.png" height="300" />

## Overview

pyFUZZYgenerator is a framework to automatically generate the code to evaluate a fuzzy system in ANSI C.
It uses configuration files to define the characteristics of the fuzzy system.

## Usage

To generate a fuzzy library, a configuration file is required.
Configuration files are in [TOML](https://github.com/toml-lang/toml) format.

In the `examples` directory there is an example configuration file that includes all the available fuzzy types.

In the following, the default example for the F-IND model `examples/sampleFIND.toml` will be used.

To create the set of C source files using the sample file, run the `main.py` script as follows:

```bash
python3 main.py examples/sampleFIND.toml -d sample
```

The generated C source files composing the fuzzy evaluator are placed in the `sample` directory.

More details on the options and arguments can be obtained with the command:

```bash
python3 main.py --help
```

The generated source files include a `Makefile`, so that the executable can be generated as follows:

```bash
cd sample
make
```

These commands generated the `sample` executable that can be ran with

```bash
./sample
```

If the model is run without the necessary input parameters, a warning is printed on standard error, and the model uses default values equal to `0` for all the input variables.

The input values for the variables of a model can be specified on the command line as follows:

```bash
./sample --Test=0.5,1,0.3
```

This means that the model `Test` requires 3 input values, which are 3 comma-separated numerical values.

The generated fuzzy evaluator supports basic help:

```bash
./sample --help
Usage: test [OPTION...]

      --Test=VALUES          Input of model Test: A B C 
  -?, --help                 Give this help list
      --usage                Give a short usage message
```

## Dependencies

The Python (python3) library requires the following packages:

- pytoml
- jinja2
- numpy

To simplify the requirements installation, we provide an [Anaconda](https://www.continuum.io/) environment, that can be imported with:

```bash
conda env create -f environment.yaml
```

## TODOs

- Implement the C evaluator for a general fuzzy system
- Optimize the general fuzzy library
- Make pyFUZZYgenerator a program installable with pip

