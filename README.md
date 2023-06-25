# Binary Grey Wolf Optimizer 

This repository contains the implementation of the novel binary version of the grey wolf optimization (BGWO1) to select optimal feature subset for classification purposes.

# Development toolchains:
The proposed algorithm was developed under Debian Linux 64bit operating system(version 11.6), with the following  toolchains:

| Tool name | Version  | Description  |
| :---:   | :-: | :-: |
| g++ | 10.2.1 | C++ compiler (standard 0x11) |
| ld | 2.35.2 | GNU linker |
| make | 4.3 |  GNU make (builder) |

# How to compile:
Locate the root source code, then type the folowing:
```
$ make clean
$ make -j4
```
If the compilation process proceeds successfully, you will see "bgwo" binary under build directory.

# Benchmark usage:
```
Binary grey wolf optimizer for feature selection
./bgwo -file [-population_size] [-iterations] [-split] [-debug]
where:
    -file               [required]    Input csv file.
    -population_size    [optinal ]    Search agents size, integer >= 0, default(8)
    -iterations         [optinal ]    Number of iterations, integer >= 0, defualt(70)
    -split              [optinal ]    Training data percent, float >= 0, defualt(0.5)
    -shuffle            [optinal ]    Shuffle the input csv file , defualt(false)
    -debug              [optinal ]    Show debugging info, defualt(false)
```

## Example
```
$ build/bgwo -file dataset/zoo.dat -population_size 100 -iterations 1000
```

# Author
Ahmed Dajani
Email: adajani@iastate.edu

# Reference
+ Binary Grey Wolf Optimizer: https://www.sciencedirect.com/science/article/pii/S0925231215010504