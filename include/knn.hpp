//  knn.hpp
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

#ifndef __KNN_HPP
    #define __KNN_HPP
    #include <iostream>
    #include <algorithm>
    #include <dataset.hpp>
    #include <vector>
    #include <map>

    typedef struct VoteInformation {
        int voteCount;
        long double distance;
    } VoteInformation;

    typedef struct Distance{
        long double distanceValue;
        long double label;
        Distance() = default;
        Distance(long double distanceValue, long double label) :
            distanceValue(distanceValue), label(label){}
        Distance(const Distance &distance) :
            distanceValue(distance.distanceValue), label(distance.label){}            
        bool operator < (const Distance& rhs) const {
            return distanceValue < rhs.distanceValue;
        }
    } Distance;

    class Knn {
        public:
            /* Returns k most similar neighbors from the training set for a given 
             * test instance (using the already defined euclideanDistance function) */
            static std::vector<Distance> getNeighbors(Array *training, long double *testing, long double *features, int k);

            /* Function for getting the majority voted response from a number of neighbors. 
               It assumes the class is the last attribute for each neighbor. */
            static long double getResponse(std::vector<Distance> neighbors);

            /* Function that sums the total correct predictions and returns the accuracy 
               as a percentage of correct classifications. */
            static float getAccuracy(Array *test_set, long double *predictions);

            /* Function that returns the voted label based on the maximum voted count from the VoteInformation structure. */
            static std::pair<long double, VoteInformation> getMaxVoteCount(const std::map<long double, VoteInformation> &x);
            
            /* Function that returns the voted label based on the minimum distance from the VoteInformation structure. */
            static std::pair<long double, VoteInformation> getMinDistance(const std::map<long double, VoteInformation> &x);
    };
#endif