//  knn_fixture.hpp
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

#ifndef __KNN_FIXTURE_HPP
    #define __KNN_FIXTURE_HPP

    #include <gtest/gtest.h>
    #include <dataset.hpp>
    #include <knn.hpp>
    #include <utils.hpp>

    using ::testing::Test;

    class KnnTest : public Test {
        protected:
            const std::string fileName = "./unittest/5x6dataset.dat";
            const float trainingPercent = 0.5;
            const int numberOfFeatures = 6;
            DataSet *dataset = nullptr;
            Array *training = nullptr;
            Array *testing = nullptr;            
        public:
            void SetUp() override {
                dataset = new DataSet(this->fileName);
                dataset->load();
                dataset->split(this->trainingPercent);
                training = dataset->getTraining();
                testing = dataset->getTesting();
            }

            void TearDown() override {
                delete dataset;
            }
    };
#endif