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

#define ROUND_TO(value, precision) std::round(value / precision) * precision
#define ROUND_TO_4_DECIMAL(value) ROUND_TO(value, 0.0001)

TEST_F(KnnTest, TestEuclideanDistance) {
    SetUp("./unittest/5x6dataset.dat");
    long double features[] = {1,0,1,0,0,0};
    long double distance = Utils::euclideanDistance(training->getData()[0],
                                                    testing->getData()[0],
                                                    features,
                                                    training->getCol()-1);
    EXPECT_NEAR(distance, 1.41421, 0.001L);
}

TEST_F(KnnTest, TestDifferentNeighbors) {
    SetUp("./unittest/5x6dataset.dat");
    const int knn_k = 2;
    long double features[] = {1,0,1,0,0,0};
    long double *predictions = new long double[testing->getRow()];
    std::vector<Distance> neighbors;
    for(int index=0; index<testing->getRow(); index++) {
        neighbors = Knn::getNeighbors(training, 
                                      testing->getData()[index], 
                                      (long double*)features,
                                      knn_k);
        long double c = Knn::getResponse(neighbors);
        predictions[index] = c;
    }

    float accuracy = Knn::getAccuracy(testing, predictions);
    EXPECT_FLOAT_EQ(ROUND_TO_4_DECIMAL(accuracy), ROUND_TO_4_DECIMAL(0.6667L));
    delete predictions;
}

TEST_F(KnnTest, TestSameNeighbors) {
    SetUp("./unittest/5x2dataset.dat");
    const int knn_k = 2;
    long double features[] = {1, 1};
    long double *predictions = new long double[testing->getRow()];
    for(int index=0; index<testing->getRow(); index++) {
        std::vector<Distance> neighbors = Knn::getNeighbors(training, 
                                                            testing->getData()[index], 
                                                            (long double*)features,
                                                            knn_k);
        long double c = Knn::getResponse(neighbors);
        predictions[index] = c;
    }

    float accuracy = Knn::getAccuracy(testing, predictions);
    EXPECT_FLOAT_EQ(ROUND_TO_4_DECIMAL(accuracy), ROUND_TO_4_DECIMAL(0.3333L));
    delete predictions;
}