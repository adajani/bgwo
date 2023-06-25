//  utils.cc
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

#include <utils.hpp>

// Calculate the similarity between any two given data instances. 
long double Utils::euclideanDistance(long double *instance1, long double *instance2, long double *features, int length) {
    long double distance = 0.0;
    for(int x=0; x<length; x++) {
        if(features[x] == 1) {
            distance += powl(instance1[x] - instance2[x], 2.0);
        }
    }
    return sqrtl(distance);
}

// Get max value in hashmap
std::pair<long double, int> Utils::hashmapGetMax(const std::map<long double, int> &x) {
    using pairtype=std::pair<long double, int>; 
    return *std::max_element(x.begin(), x.end(), [] (const pairtype &p1, const pairtype &p2) {
        return p1.second < p2.second;
    });
}

// Convert array into binary, where each item >0.5 will be 1 else 0
long double *Utils::convertArrayToBinary(long double *array, int size) {
    long double *binary = new long double[size];

    for(int index=0; index<size; index++) {
        binary[index] = (array[index] > 0.5) ? 1.0 : 0.0;
    }

    return binary;
}

// Array elements summation
long double Utils::arraySum(long double *array, int size) {
    long double sum=0.0;
    for(int index=0; index<size; index++) {
        sum += array[index];
    }
    return sum;
}

// create 1D long double array with value zero
long double* Utils::doubleZeros(int size) {
    long double *array = new long double[size];
    std::fill_n(array,size,0);
    return array;
}

// random number between 0 and 1
long double Utils::randomNumber() {
    static bool init=false;
    if(!init) {
        init=true;
        srand(time(NULL));
    }
    return (long double)rand() / ((long double)RAND_MAX + 1);
}

/*
    The sigmoidal function, sigmf(x,[a c]), as given in the following equation by f(x,a,c)
    is a mapping on a vector x, and depends on two parameters a and c.
*/
long double Utils::sigmld(long double x, long double a, long double c) {
    return 1.0 / (1.0 + exp(-a * (x-c)));
}