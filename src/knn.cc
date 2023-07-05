//  knn.cc
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

#include <knn.hpp>
#include <utils.hpp>

/* Returns k most similar neighbors from the training set for a given 
 * test instance (using the already defined euclideanDistance function) */
std::vector<Distance> Knn::getNeighbors(Array *training, long double *testing, long double *features, int k) {
    std::vector<Distance> distances(training->getRow());
    std::vector<Distance> neighbors(k);

    for(int y=0; y<training->getRow(); y++) {
        long double dist = Utils::euclideanDistance(training->getData()[y],
                                                    testing,
                                                    features,
                                                    training->getCol()-1);
        distances.at(y) = {dist, training->getData()[y][training->getCol()-1]};
    }

    std::sort(distances.begin(), distances.end());
    std::copy(distances.begin(), distances.begin()+k, neighbors.begin());
    
    return neighbors;
}

std::pair<long double, VoteInformation> Knn::getMaxVoteCount(const std::map<long double, VoteInformation> &x) {
    using pairtype=std::pair<long double, VoteInformation>; 
    return *std::max_element(x.begin(), x.end(), [] (const pairtype &p1, const pairtype &p2) {
        return p1.second.voteCount < p2.second.voteCount;
    });
}

std::pair<long double, VoteInformation> Knn::getMinDistance(const std::map<long double, VoteInformation> &x) {
    using pairtype=std::pair<long double, VoteInformation>; 
    return *std::max_element(x.begin(), x.end(), [] (const pairtype &p1, const pairtype &p2) {
        return p1.second.distance > p2.second.distance;
    });
}

/* Function for getting the majority voted response from a number of neighbors. */
long double Knn::getResponse(std::vector<Distance> neighbors) {
    std::map<long double, VoteInformation> class_votes;

    //count the label frequency 
    for(auto &neighbor : neighbors) {
        long double response = neighbor.label;
        if(class_votes.find(response) == class_votes.end()) { //not found
            class_votes[response] = {.voteCount=1, .distance=neighbor.distanceValue};
        } else {
            class_votes[response].voteCount += 1;
        }
    }

    auto firstMax = Knn::getMaxVoteCount(class_votes);
    if(class_votes.size() > 1) {//at least two keys
        //remove the highest rated label
        class_votes.erase(firstMax.first);
        //get the second heightst label count
        auto secondMax = Knn::getMaxVoteCount(class_votes);
        //if the first two labels share the same count
        if(firstMax.second.voteCount == secondMax.second.voteCount) {
            //return the first voted label to the map
            class_votes.insert({firstMax.first, firstMax.second});
            //return the label with lowest distance
            return Knn::getMinDistance(class_votes).first;
        }
    }
    //return the heightst label count
    return firstMax.first;
}

/* Function that sums the total correct predictions and returns the accuracy 
   as a percentage of correct classifications. */
float Knn::getAccuracy(Array *test_set, long double *predictions) {
    float correct = 0;

    for(int y=0; y<test_set->getRow(); y++) {
        if(test_set->getData()[y][test_set->getCol()-1] == predictions[y]) {
            correct += 1.0;
        }
    }

    return correct / (float)test_set->getRow();
}
