//  fitness.cc
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

#include <fitness.hpp>
#include <knn.hpp>

Fitness::Fitness(Array *training, Array *testing) {
    this->training_m = training;
    this->testing_m = testing;
    this->dim_m = training->getCol();
    this->predictions_m = new long double[this->training_m->getRow()];
}

Fitness::~Fitness() {
    delete this->predictions_m;
}

float Fitness::getAccuracy() {
    return this->accuracy_m;
}

long double Fitness::calculate(long double *x) {
    long double c;
    Array *neighbors;

    long double *array = Utils::convertArrayToBinary(x, this->dim_m);
    long double sum = Utils::arraySum(array, this->dim_m);
    if( sum == 0.0 ) {
        return std::numeric_limits<long double>::infinity();
    }
    delete []array;

    for(int index=0; index<this->testing_m->getRow(); index++) {
        neighbors = Knn::getNeighbors(this->training_m, 
                                       this->testing_m->getData()[index], 
                                       x,
                                       this->k_m);
        c = Knn::getResponse(neighbors);
        delete neighbors;
        this->predictions_m[index] = c;
    }

    this->accuracy_m = Knn::getAccuracy(this->testing_m, this->predictions_m);

    return (1.0- this->SzW_m) * (1.0 - this->accuracy_m) + this->SzW_m * 
            sum / (long double)this->dim_m;
}

int Fitness::getDim() {
    return this->dim_m;
}