//  knn_unittest.cc
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

#include <knn_fixture.hpp>

TEST_F(KnnTest, TestEuclideanDistance) {
    long double features[] = {1,0,1,0,0,0};
    long double distance = Utils::euclideanDistance(training->getData()[0],
                                                    testing->getData()[0],
                                                    features,
                                                    training->getCol()-1);
    EXPECT_NEAR(distance, 1.41421, 0.0001L);
}

TEST_F(KnnTest, TestNeighbors) {
    const int knn_k = 2;
    long double features[]= {1,0,1,0,0,0};
    long double *predictions = new long double[testing->getRow()];
    Array *neighbors;
    for(int index=0; index<testing->getRow(); index++) {
        neighbors = Knn::getNeighbors(training, 
                                      testing->getData()[index], 
                                      (long double*)features,
                                      knn_k);
        long double c = Knn::getResponse(neighbors);
        predictions[index] = c;
        delete neighbors;
    }

    float accuracy = Knn::getAccuracy(testing, predictions);
    EXPECT_NEAR(accuracy, 0.666667, 0.0001L);
    delete predictions;
}