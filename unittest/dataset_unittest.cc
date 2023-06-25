//  dataset_unittest.cc
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

#include <dataset_fixture.hpp>

TEST_F(DatasetTest, TestInit) {
    EXPECT_EQ(dataset->getFileName(), "./dataset/zoo.dat");
    EXPECT_EQ(dataset->getData(), nullptr);
    EXPECT_EQ(dataset->getTraining(), nullptr);
    EXPECT_EQ(dataset->getTesting(), nullptr);
}

TEST_F(DatasetTest, TestZooLoading) {
    dataset->load();
    EXPECT_NE(dataset->getData()->getCol(), 0);
    EXPECT_NE(dataset->getData()->getRow(), 0);

    const int numberOfAttributes = 16 + 1; //attributes + label
    const int numberOfInstances = 101;

    int expectedDatasetSize = numberOfAttributes * numberOfInstances;

    int actualDatasetSize = dataset->getData()->getCol() * 
                            dataset->getData()->getRow();
    
    EXPECT_EQ(expectedDatasetSize, actualDatasetSize);
}

TEST_F(DatasetTest, TestZooSplit) {
    float training_percent = 0.5;
    Array *training = nullptr;
    Array *testing = nullptr;
    
    dataset->load();
    dataset->split(training_percent);
    training = dataset->getTraining();
    testing = dataset->getTesting();

    EXPECT_NE(training, nullptr);
    EXPECT_EQ(training->getRow(), 50);
    
    EXPECT_NE(testing, nullptr);
    EXPECT_EQ(testing->getRow(), 51);
}
