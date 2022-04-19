# svg2cpp

Circle CI Status: [![BrantKyser](https://circleci.com/gh/BrantKyser/svg2cpp.svg?style=svg)](https://app.circleci.com/pipelines/github/BrantKyser/svg2cpp)

## What is svg2cpp?

svg2cpp is a tool that enables 2d graphics artifacts saved as SVG files to be integrated into C++ projects. The tool parses the specified SVG file and applies templates to the parsed elements from the SVG file to generate source code that can then be integrated into a project. The current templates provided generate C++ code for the QGraphics 2d graphics library that is part of Qt. 

## Building
The svg2cpp tool is developed on MacOS. Simply run ```make``` in the root directory of the repository after cloning the repository to build the tool. The tool can be built on other Unix platforms with minor modifications to the Makefile.

## Running

The svg2cpp tool is a CLI tool. When invoked, the directory containing the templates to apply to the elements parsed from the SVG file as well as the SVG file to be parsed must be specified. Additionally, the output directory to which to write the generated source code should usually be specified. Not specifiying an output directory results in the generated code being written to the current working directory and results in the tool issuing a warning.

```
$ ./svg2cpp -h
Allowed options:
  -h [ --help ]            Print help message to stdout and exit
  -o [ --outDir ] arg      Directory to which generated code should be written.
  -t [ --templateDir ] arg Directory containing the code generation templates.
  --inputFile arg          SVG file to process.
```
