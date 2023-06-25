//  knn.cc
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

#include <knn.hpp>
#include <utils.hpp>

/* Returns k most similar neighbors from the training set for a given 
 * test instance (using the already defined euclideanDistance function) */
Array *Knn::getNeighbors(Array *training, long double *testing, long double *features, int k) {
    Distance *distances = new Distance[training->getRow()];

    Array *neighbors = new Array(k, training->getCol());

    for(int y=0; y<training->getRow(); y++) {
        long double dist = Utils::euclideanDistance(training->getData()[y],
                                                     testing,
                                                     features,
                                                     training->getCol()-1);

        distances[y].distance_value = dist;
        distances[y].array = new long double[training->getCol()];
        std::copy(&training->getData()[y][0], 
                  &training->getData()[y][training->getCol()],
                  distances[y].array);
    }

    std::sort(&distances[0], &distances[training->getRow()], 
              [](Distance left, Distance right){ return left.distance_value < right.distance_value;});

    for(int y=0; y<k; y++) {
        std::copy(&distances[y].array[0],
                  &distances[y].array[training->getCol()],
                  neighbors->getData()[y]);
    }

    //delete temp. distances
    for(int y=0; y<training->getRow(); y++) {
        delete []distances[y].array;
    }
    delete []distances;

    return neighbors;
}

/* Function for getting the majority voted response from a number of neighbors. 
 * It assumes the class is the last attribute for each neighbor. */
long double Knn::getResponse(Array *neighbors) {
    std::map<long double, int> class_votes;

    for(int y=0; y<neighbors->getRow(); y++) {
        long double response = neighbors->getData()[y][neighbors->getCol()-1];
        if(class_votes.find(response) == class_votes.end()) {
            class_votes[response] = 1; //not found
        } else {
            class_votes[response] += 1;
        }
    }

    //get max voted class
    return Utils::hashmapGetMax(class_votes).first;
}

/* Function that sums the total correct predictions and returns the accuracy 
   as a percentage of correct classifications. */
float Knn::getAccuracy(Array *test_set, long double *predictions) {
    float correct = 0;

    for(int y=0; y<test_set->getRow(); y++) {
        if(test_set->getData()[y][test_set->getCol()-1] == predictions[y]) {
            correct += 1.0;
        }
    }

    return correct / (float)test_set->getRow();
}
