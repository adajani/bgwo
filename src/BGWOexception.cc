//  BGWOexception.cc
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


#include <BGWOexception.hpp>

struct BGWOExceptionDict BGWOException::exceptionDict_m[] = {
    {MISSING_CSV,        "Input CSV file is missing"},
    {MISSING_POPULATION, "Population size is missing"},
    {INVALID_POPULATION, "Invalid population size"},
    {MISSING_ITERATIONS, "Iterations count is missing"},
    {INVALID_ITERATIONS, "Invalid iterations count"},
    {MISSING_SPLIT,      "Training data percentis missing"},
    {INVALID_SPLIT,      "Invalid training data percent"},

    {CANT_OPEN_CSV,      "Can't open CSV file"},

    {UNKNOWN_ARGUMENT,   "Unknown input argument"}
};

BGWOException::BGWOException (BGWOExceptionId exceptionId) {
    exceptionId_m = exceptionId;
}

const char* BGWOException::what() const throw() {
    return exceptionDict_m[exceptionId_m].exceptionName;
}
