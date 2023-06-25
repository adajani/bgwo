//  dataset_fixture.hpp
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

#ifndef __DATASET_FIXTURE_HPP
    #define __DATASET_FIXTURE_HPP

    #include <gtest/gtest.h>
    #include <dataset.hpp>

    using ::testing::Test;  // GTest test fixture

    class DatasetTest : public Test {
        protected:
            DataSet *dataset = nullptr;
            const std::string fileName = "./dataset/zoo.dat";

        public:
            void SetUp() override {
                dataset = new DataSet(this->fileName);
            }

            void TearDown() override {
                delete dataset;
            }
    };
#endif