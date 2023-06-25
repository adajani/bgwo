//  main.cc
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

#include <cstdlib> //atexit
#include <iostream> //cerr, cout
#include <argument.hpp>
#include <bgwo.hpp>
#include <BGWOexception.hpp>
#include <dataset.hpp>
#include <fitness.hpp>
#include <bgwo.hpp>

Argument *argument = nullptr;
DataSet *dataset = nullptr;
Fitness *fitness = nullptr;

Array *entireDataset = nullptr;
Array *training = nullptr;
Array *testing = nullptr;
BGWO *bgwo = nullptr;

int main(int argc, char **argv) {
    try {
        argument = new Argument(argc, argv);
        argument->parse();

        dataset = new DataSet(argument->getFileName());
        dataset->load();
        if(argument->isShuffled()) {
            dataset->shuffle();
        }

        dataset->split(argument->getTrainingPercent());
        training = dataset->getTraining();
        testing = dataset->getTesting();

        fitness = new Fitness(training, testing);
        bgwo = new BGWO(fitness, argument->getPopulationSize(), argument->getIterations());
        (void)bgwo->evaluate(argument->isDebug());

        std::cout << *bgwo << std::endl;

        delete argument;
        delete dataset;
        delete fitness;
        delete bgwo;
    }
    catch (BGWOException &e) {
        std::cerr << "Binary Grey wolf optimizer exception : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
