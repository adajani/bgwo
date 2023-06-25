//  dataset.hpp
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

#ifndef __DATASET_HPP
    #define __DATASET_HPP

    #include <fstream>
    #include <sstream>
    #include <algorithm>
    #include <random>
    #include <cstdlib>
    #include <ctime>
    #include <cmath>
    #include <array.hpp>
    #include <BGWOexception.hpp>

    class DataSet {
        private:
            std::string fileName_m;
            bool shuffleFlag_m = false;
            Array *dataset_m = nullptr;
            Array *training_m = nullptr;
            Array *testing_m = nullptr;

        public:
            DataSet(const std::string &fileName) : fileName_m(fileName) {};
            ~DataSet();
            void load();
            std::string getFileName();
            bool isDataShuffled();
            void shuffle();
            void split(float training_percent);
            Array *getData();
            Array *getTraining();
            Array *getTesting();
    };
#endif