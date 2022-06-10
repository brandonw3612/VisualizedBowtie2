# VisualizedBowtie2

## About

A Linux and macOS CLI-based visualization of [BenLangmead/bowtie2](https://github.com/BenLangmead/bowtie2).

## Before Building

You need bowtie2 downloaded on your device, which you can access [here](http://bowtie-bio.sourceforge.net/bowtie2/index.shtml).

Select the binary zip pack that matches your system and architecture and put it in the `bin` subdirectory in the project folder, right next to `bowtie2.sh`.

## Building

The project files are managed by CMake (Ver. 3.22+).
Developer toolchain programs are required to build the project.

To build the project, you can either

1) open the project directory with your IDE supporting CMake (JetBrains CLion recommended, for its brilliant cross-platform availability and performance). Simply build the project in the IDE and run the project with terminal.

2) install all developer tools needed and CMake on your device. Make sure you have the latest CMake version. Version 3.22 is required. <br />
   After configuring the development environment, you can follow the steps below: <br />
   + Change the directory to the project folder.
   + Run `cmake .` in the terminal.
   + Run `make` to build the project.

## Running

+ Change the directory to the `bin` subdirectory in the project folder.
+ Run `./VisualizedBowtie2 "InputFastaFile" "FastaqFile"` with terminal.