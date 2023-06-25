//  BGWOexception.hpp
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

#ifndef __BGWO_EXCEPTION_H
    #define __BGWO_EXCEPTION_H
    #include <iostream>

    enum BGWOExceptionId {
        //Parse arguments
        MISSING_CSV,
        MISSING_POPULATION,
        INVALID_POPULATION,
        MISSING_ITERATIONS,
        INVALID_ITERATIONS,
        MISSING_SPLIT,
        INVALID_SPLIT,

        //dataset
        CANT_OPEN_CSV,
        
        //BGWO

        //Else
        UNKNOWN_ARGUMENT
    };

    struct BGWOExceptionDict {
        unsigned int exceptionId;
        const char *exceptionName;
    };

    class BGWOException : public std::exception {
        public:
            BGWOException(BGWOExceptionId exceptionId);
            const char* what() const throw();
        private:
            BGWOExceptionId exceptionId_m;
            static struct BGWOExceptionDict exceptionDict_m[];
    };
#endif
