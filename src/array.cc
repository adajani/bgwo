//  array.cc
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
#include <array.hpp>

Array::Array(int row, int col) {
    this->row_m = row;
    this->col_m = col;
    this->data_m = new long double*[this->row_m];
    for(int row_index=0; row_index<this->row_m; row_index++) {
        this->data_m[row_index] = new long double[this->col_m];
    }
}

Array::~Array() {
    for(int row_index=0; row_index<this->row_m; row_index++) {
        delete[] this->data_m[row_index];
    }
    delete[] this->data_m;
}

int Array::getCol() {
    return this->col_m;
}

int Array::getRow() {
    return this->row_m;
}

long double ** Array::getData() {
    return this->data_m;
}