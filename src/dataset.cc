//  dataset.cc
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

#include <dataset.hpp>

DataSet::~DataSet() {
    delete dataset_m;
}

void DataSet::load() {
    std::string line;
    std::ifstream file(this->fileName_m);

    //can't open file
    if(!file.is_open()) {
        throw BGWOException(CANT_OPEN_CSV);
    }

    //get row,col dynamically 
    int col = 0;
    int row = 0;
    while(!file.eof()) {
        getline(file, line);

        if( col == 0) {
            // Insert the line string into a stream
            std::string buffer;
            std::stringstream ss(line);
            while (ss >> buffer) {
                col++;
            }
        }

        //trim line
        std::stringstream trimmer;
        trimmer << line;
        line.clear();
        trimmer >> line;
        if(line.length() > 0) {
            row++;
        }
    }

    //rewind file
    file.clear();
    file.seekg(0, std::ios::beg);

    //allocate dataest
    dataset_m = new Array(row, col);

    //fill array with datafrom file
    int row_index=0;
    int col_index=0;
    while ( getline (file,line) ) {	  
        //trim line
        std::string trim_line;
        std::stringstream trimmer;
        trimmer << line;
        trim_line.clear();
        trimmer >> trim_line;

        if(trim_line.length()>0) {
            // Insert the line string into a stream
            std::string buffer;
            std::stringstream ss(line);
            col_index=0;
            while (ss >> buffer) {
                //note class must be long double, else will be zero
                dataset_m->getData()[row_index][col_index] = strtold(buffer.c_str(), NULL);
                col_index++;
            }
            row_index++;
        }
    }

    file.close();
}

std::string DataSet::getFileName() {
    return fileName_m;
}

bool DataSet::isDataShuffled() {
    return shuffleFlag_m;
}

void DataSet::shuffle() {
    shuffleFlag_m = true;
    std::srand(unsigned(std::time(NULL)));
	std::random_shuffle(&dataset_m->getData()[0],
                        &dataset_m->getData()[dataset_m->getRow()],
                        [](int i)->int{return(std::rand() % i);}
                        );
}

void DataSet::split(float training_percent) {
    //training
    training_m = new Array(floorl((long double)dataset_m->getRow()*training_percent),
                           dataset_m->getCol());

    std::copy(&dataset_m->getData()[0],
              &dataset_m->getData()[training_m->getRow()],
              &training_m->getData()[0]);

    //testing
    testing_m = new Array(dataset_m->getRow() - training_m->getRow(),
                          dataset_m->getCol());

    std::copy(&dataset_m->getData()[training_m->getRow()],
              &dataset_m->getData()[dataset_m->getRow()],
              &testing_m->getData()[0]);
}

Array *DataSet::getData() {
    return dataset_m;
}

Array *DataSet::getTraining() {
    return training_m;
}
Array *DataSet::getTesting() {
    return testing_m;
}