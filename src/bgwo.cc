//  bgwo.cc
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

#include <bgwo.hpp>
#include <chrono>
#include <iomanip> //setprecision

BGWO::BGWO(Fitness *fitness, int SearchAgentsCount, int MaxIter) {
    this->fitness_m = fitness;
    this->SearchAgentsCount_m = SearchAgentsCount;
    this->MaxIter_m = MaxIter;
    this->dim_m = fitness->getDim();

    //initialize alpha, beta, and delta_pos
    this->AlphaPos_m = Utils::doubleZeros(this->dim_m); //zerro array with size dim
    this->AlphaScore_m = std::numeric_limits<long double>::infinity();

    this->BetaPos_m = Utils::doubleZeros(this->dim_m);
    this->BetaScore_m = std::numeric_limits<long double>::infinity();

    this->DeltaPos_m = Utils::doubleZeros(this->dim_m);
    this->DeltaScore_m = std::numeric_limits<long double>::infinity();

    this->ConvergenceCurve_m = Utils::doubleZeros(this->MaxIter_m);

    //Initialize the positions of search agents
    this->Positions_m = new Array(this->SearchAgentsCount_m, this->dim_m);
    //randomize data and apply between (lower,upper) bound
    for(int y=0; y<SearchAgentsCount_m; y++) {
        for(int x=0; x<this->dim_m; x++) {
            this->Positions_m->getData()[y][x] = (Utils::randomNumber() > 0.5) ? 1.0 : 0.0;
        }
    }
}

BGWO::~BGWO() {
    delete Positions_m;
}

void BGWO::calculateFitness() {
    long double fitnessValue;

    for(int i=0; i< this->SearchAgentsCount_m; i++) {
        //Calculate objective function for each search agent
        fitnessValue = this->fitness_m->calculate(this->Positions_m->getData()[i]);

        //Update Alpha, Beta, and Delta
        if( fitnessValue < this->AlphaScore_m ) {
            this->AlphaScore_m = fitnessValue; // Update alpha
            std::copy(&this->Positions_m->getData()[i][0], 
                      &this->Positions_m->getData()[i][this->dim_m],
                      this->AlphaPos_m);
        }

        if( fitnessValue > this->AlphaScore_m && fitnessValue < this->BetaScore_m ) {
            this->BetaScore_m = fitnessValue;  // Update beta
            std::copy(&this->Positions_m->getData()[i][0],
                      &this->Positions_m->getData()[i][this->dim_m],
                      this->BetaPos_m);
        }

        if( fitnessValue > this->AlphaScore_m && fitnessValue > this->BetaScore_m && fitnessValue < this->DeltaScore_m ) {
            this->DeltaScore_m = fitnessValue; //Update delta
            std::copy(&this->Positions_m->getData()[i][0],
                      &this->Positions_m->getData()[i][this->dim_m],
                      this->DeltaPos_m);
        }
    }
}

long double BGWO::crossOver(long double x1, long double x2, long double x3) {
    long double r = Utils::randomNumber();
    if(r < 0.333) {
        return x1;
    } else if(r < 0.6666) {
        return x2;
    } else {
        return x3;
    }
}

void BGWO::updateWolves(long double a) {
    long double v1;
    //Update the Position of search agents including omegas
    for(int i=0; i<this->SearchAgentsCount_m; i++) {
        for(int j=0; j<this->dim_m; j++) {
            long double r1 = Utils::randomNumber();
            long double r2 = Utils::randomNumber();

            long double A1 = 2.0 * a * r1 - a; //Equation (3.3)
            long double C1 = 2.0 * r2; //Equation (3.4)

            long double D_alpha = fabsl(C1 * this->AlphaPos_m[j] - this->Positions_m->getData()[i][j]); //Equation (3.5)-part 1
            v1 = Utils::sigmld(-A1*D_alpha, 10, 0.5) < Utils::randomNumber() ? 0.0 : 1.0;
            long double X1 = (this->AlphaPos_m[j] + v1) >= 1.0 ? 1.0 : 0.0;  //Equation (3.6)-part 1

            r1 = Utils::randomNumber();
            r2 = Utils::randomNumber();

            long double A2 = 2 * a * r1 - a; //Equation (3.3)
            long double C2 = 2 * r2; //Equation (3.4)

            long double D_beta = fabsl(C2 * this->BetaPos_m[j] - this->Positions_m->getData()[i][j]); //Equation (3.5)-part 2
            v1 = Utils::sigmld(-A2*D_beta, 10, 0.5) < Utils::randomNumber() ? 0.0 : 1.0;
            long double X2 = (this->BetaPos_m[j] + v1) >= 1.0 ? 1.0 : 0.0; //Equation (3.6)-part 2

            r1 = Utils::randomNumber();
            r2 = Utils::randomNumber();

            long double A3 = 2.0 * a * r1 - a; //Equation (3.3)
            long double C3 = 2.0 * r2; //Equation (3.4)

            long double D_delta = fabsl(C3 * this->DeltaPos_m[j] - this->Positions_m->getData()[i][j]); //Equation (3.5)-part 3
            v1 = Utils::sigmld(-A3*D_delta, 10, 0.5) < Utils::randomNumber() ? 0.0 : 1.0;
            long double X3 = (this->DeltaPos_m[j] + v1) >= 1.0 ? 1.0 : 0.0; //Equation (3.5)-part 3

            this->Positions_m->getData()[i][j]= this->crossOver(X1, X2, X3);  //Equation (3.7)
        }
    }
}

long double* BGWO::evaluate(bool debug) {
    int l;
    long double a;
    auto start_time = std::chrono::high_resolution_clock::now();

    //Main loop
    for(l=0; l < this->MaxIter_m; l++) {
        calculateFitness();

        //a decreases linearly from 2 to 0
        a=2.0-l*(2.0/this->MaxIter_m);
        updateWolves(a);

        this->ConvergenceCurve_m[l] = this->AlphaScore_m;

        if (debug && (l%1==0) ) {
            std::cout    << "At iteration " << l << " the best fitness is "
                        << std::setprecision(10)
                        << this->AlphaScore_m << std::endl;
        }

    }

    auto finish_time = std::chrono::high_resolution_clock::now();
    this->executionTime_m = std::chrono::duration_cast<std::chrono::nanoseconds>(finish_time-start_time).count() * 1e-9;

    return this->ConvergenceCurve_m;
}

long double BGWO::getExecutionTime() {
    return this->executionTime_m;
}

long double *BGWO::getAlphaPos() {
    return this->AlphaPos_m;
}
long double *BGWO::getBetaPos() {
    return this->BetaPos_m;
}

long double *BGWO::getDeltaPos() {
    return this->DeltaPos_m;
}

std::ostream& operator<<(std::ostream &s, const BGWO &bgwo) {
    std::stringstream stream;
    stream << "convergence:" << bgwo.ConvergenceCurve_m[bgwo.MaxIter_m - 1] << std::endl
           << "execution time (seconds):" << bgwo.executionTime_m << std::endl
           << "accuracy:" << bgwo.fitness_m->getAccuracy() << std::endl
           << "Solution (alpha positions):";

    long double *solution = bgwo.AlphaPos_m;
    for(int i=0; i<bgwo.dim_m; i++) {
        stream << solution[i] << ", ";
    }

    return s << stream.str();
}