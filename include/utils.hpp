//  utils.hpp
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

#ifndef __UTILS_H
#define __UTILS_H
    #include <algorithm>
    #include <iostream>
    #include <cstring>
    #include <dataset.hpp>

    class Utils {
        public:
            // Calculate the similarity between any two given data instances. 
            static long double euclideanDistance(long double *instance1, long double *instance2, long double *features, int length);

            // Convert array into binary, where each item >0.5 will be 1 else 0
            static long double *convertArrayToBinary(long double *array, int size);

            // Array elements summation
            static long double arraySum(long double *array, int size);

            // Create 1D long double array with value zero
            static long double *doubleZeros(int size);

            // Random number between 0 and 1
            static long double randomNumber();

            // Sigmoidal unction
            static long double sigmld(long double x, long double a, long double c);
    };
#endif
