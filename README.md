# otdgen

[![Build Status](https://travis-ci.org/ohmtech/otdgen.svg?branch=master)](https://travis-ci.org/ohmtech/otdgen)

Ohm Technologies Documentation Generator.


## Requirements

`otdgen` only works on macOS for now. It requires:
- Apple Xcode 9 or Apple Xcode 10.
- [`Python`](https://www.python.org/downloads/) (version `2.7`).
- [`gyp`](https://gyp.gsrc.io/).
- `librsvg`.


## Install

When you have all the requirements, run the `configure.py` script. This will create a native Xcode Project in a `projects` directory at the root of the `otdgen` repository.

> Xcode 10 users will have to specify the architecture to use to be 64-bit only with the `--archs x86_64` CL option.

You can then build the generated project to get the `otdgen` executable.


## Usage

Run the `otdgen` executable to generate the documentation:

```
otdgen --format=<format> --output=<output> doc_src_root_file.otd
```

##### `--format`

The `--format` option allows to specify the output format of the generated documentation. Available formats are:
- `markdown`
- `html`
- `docset`
- `plain-text`

##### `--output`

The `--output` option allows to specify the output directory of the files that will be generated.


## OTD Syntax

TODO


### Adding Syntax Highlighting for Xcode

Otdgen contains a plug-in that brings syntax highlighting of the OTD language into Xcode. To install it, follow the instructions given [here](scripts/xcode).
