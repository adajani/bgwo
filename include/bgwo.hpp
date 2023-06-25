//  bgwo.hpp
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
#ifndef __BGWO_HPP
    #define __BGWO_HPP
    #include <fitness.hpp>
    #include <array.hpp>

    class BGWO {
        private:
            long double executionTime_m;
            Fitness *fitness_m;
            int SearchAgentsCount_m;
            int MaxIter_m;            
            int dim_m;

            //initialize alpha, beta, and delta_pos
            long double *AlphaPos_m;
            long double AlphaScore_m;

            long double *BetaPos_m;
            long double BetaScore_m;

            long double *DeltaPos_m;
            long double DeltaScore_m;

            //Initialize the positions of search agents
            Array *Positions_m;

            long double *ConvergenceCurve_m;

            void calculateFitness();
            void updateWolves(long double a);
            long double crossOver(long double x1, long double x2, long double x3);

            friend std::ostream& operator<<(std::ostream &s, const BGWO &bgwo);
        public:
            BGWO(Fitness *fitness, int SearchAgentsCount, int MaxIter);
            ~BGWO();
            long double *evaluate(bool debug=false);
            long double *getAlphaPos();
            long double *getBetaPos();
            long double *getDeltaPos();
            long double getExecutionTime();
    };
#endif