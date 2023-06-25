//  knn.hpp
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

#ifndef __KNN_HPP
    #define __KNN_HPP
    #include <iostream>
    #include <algorithm>
    #include <dataset.hpp>

    typedef struct {
        long double *array;
        long double distance_value;
    } Distance;

    class Knn {
        public:
            /* Returns k most similar neighbors from the training set for a given 
             * test instance (using the already defined euclideanDistance function) */
            static Array *getNeighbors(Array *training, long double *testing, long double *features, int k);

            /* Function for getting the majority voted response from a number of neighbors. 
               It assumes the class is the last attribute for each neighbor. */
            static long double getResponse(Array *neighbors);

            /* Function that sums the total correct predictions and returns the accuracy 
               as a percentage of correct classifications. */
            static float getAccuracy(Array *test_set, long double *predictions);
    };
#endif