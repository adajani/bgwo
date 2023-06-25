//  argument.hpp
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

#ifndef __ARGUMENT_H
    #define __ARGUMENT_H

    class Argument {
        private:
            int argc_m;
            char **argv_m;
            unsigned int populationSize_m;
            unsigned int iterations_m;
            std::string fileName_m;
            float trainingPercent_m;
            bool debug_m;
            bool shuffle_m;
            void showUsage();
        public:
            Argument(int argc, char **argv);
            ~Argument() = default;
            void parse();
            unsigned int getPopulationSize();
            unsigned int getIterations();
            std::string getFileName();
            float getTrainingPercent();
            bool isDebug();
            bool isShuffled();
    };
#endif
