//  argument.cpp
//
//  Author:
//       Ahmed Dajani <adajani@iastate.edu>
//
//  Copyright (c) 2023 Ahmad Dajani
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cstring> //strcasecmp
#include <cstdlib> //exit
#include <iostream> //cout
#include <argument.hpp>
#include <BGWOexception.hpp>

Argument::Argument(int argc, char **argv) {
    argc_m = argc;
    argv_m = argv;
    populationSize_m = 8;
    iterations_m = 70;
    trainingPercent_m = 0.5;
    debug_m = false;
    shuffle_m = false;
}

void Argument::showUsage() {
    std::cout << "Binary grey wolf optimizer for feature selection"  << std::endl
              << "./bgwo -file [-population_size] [-iterations] [-split] [-debug]" << std::endl
              << "where:" << std::endl
              << "    -file               [required]    Input csv file." << std::endl
              << "    -population_size    [optinal ]    Search agents size, integer >= 0, default(" << populationSize_m << ")" << std::endl
              << "    -iterations         [optinal ]    Number of iterations, integer >= 0, defualt(" << iterations_m << ")" << std::endl
              << "    -split              [optinal ]    Training data percent, float >= 0, defualt(" << trainingPercent_m << ")" << std::endl
              << "    -shuffle            [optinal ]    Shuffle the input csv file , defualt(false)" << std::endl
              << "    -debug              [optinal ]    Show debugging info, defualt(false)" << std::endl;
    exit(EXIT_SUCCESS);
}

void Argument::parse() {
    if(argc_m < 2) {
        showUsage();
    }

    for(int index=1; index<argc_m; index++) {
        if(strcasecmp(argv_m[index], "-help") == 0) {
            showUsage();
        } else if(strcasecmp(argv_m[index], "-file") == 0) {
            index += 1;
            char *file_name = argv_m[index];
            if(file_name == NULL) {
                throw BGWOException(MISSING_CSV);
            } 
            fileName_m.assign(file_name);
        } else if(strcasecmp(argv_m[index],"-population_size")==0) {
            index += 1;
            char *size=argv_m[index];
            if(size == NULL) {
                throw BGWOException(MISSING_POPULATION);
            }
            populationSize_m = atoi(size);
            if(populationSize_m < 0 ) {
                throw BGWOException(INVALID_POPULATION);
            }
        } else if(strcasecmp(argv_m[index],"-iterations")==0) {
            index += 1;
            char *itr=argv_m[index];
            if(itr == NULL) {
                throw BGWOException(MISSING_ITERATIONS);
            }
            iterations_m = atoi(itr);
            if(iterations_m < 0 ) {
                throw BGWOException(INVALID_ITERATIONS);
            }
        } else if(strcasecmp(argv_m[index],"-split")==0) {
            index += 1;
            char *split=argv_m[index];
            if(split == NULL) {
                throw BGWOException(MISSING_SPLIT);
            }
            trainingPercent_m = atof(split);
            if(trainingPercent_m < 0 ) {
                throw BGWOException(INVALID_SPLIT);
            } 
        } else if(strcasecmp(argv_m[index],"-debug")==0) {
            debug_m = true;
        } else if(strcasecmp(argv_m[index],"-shuffle")==0) {
            shuffle_m = true;
        } else {
            throw BGWOException(UNKNOWN_ARGUMENT);
        }
    }
}

unsigned int Argument::getPopulationSize() {
    return populationSize_m;
}

unsigned int Argument::getIterations() {
    return iterations_m;
}

std::string Argument::getFileName() {
    return fileName_m;
}

float Argument::getTrainingPercent() {
    return trainingPercent_m;
}

bool Argument::isDebug() {
    return debug_m;
}

bool Argument::isShuffled() {
    return shuffle_m;
}
