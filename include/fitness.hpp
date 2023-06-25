//  fitness.hpp
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

#ifndef __FITNESS_HPP
    #define __FITNESS_HPP
    #include <dataset.hpp>
    #include <utils.hpp>

    class Fitness {
        private:
            Array *training_m;
            Array *testing_m;
            const long double SzW_m=0.01;
            const int k_m=5;
            int dim_m;
            long double *predictions_m;
            float accuracy_m=0.0;
        public:
            Fitness(Array *training, Array *testing);
            ~Fitness();
            float getAccuracy();
            int getDim();
            long double calculate(long double *x);
    };
#endif