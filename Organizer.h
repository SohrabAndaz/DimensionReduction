//
//  Organizer.h
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/19/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//

#ifndef __DimensionReduction__Organizer__
#define __DimensionReduction__Organizer__

#include <iostream>


#include "Organizer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>

/*
 The organizer class is an abstract class that can be used to calculate market invariants from given stock prices.
 */

using namespace std;
class Organizer {
    
public:
    int datasize;
    char *dataPriceString;
    double *dataprices;
    double *datainvariants;
/* The constructor takes two arguemnts:
            1) An integer, size, which asks for the number of data points you have in your stock price v. time curve.
            2) A string, filename, which asks for the filename where the data is stored. */

    Organizer(int, string);

/*
 The virtual function fill must be written in a derived class to fill a string with the price data from a file. This fill function must be written correctly so as to properly extract the data given the files unique formatting.
 */
    virtual void fill(char*, int, string)=0;
/*
The function print(char*,int), prints an array of characters for a given length to the console
 */
    void print(char*, int);
/*
The function print(double*,int), prints an array of doubles for a given length to the console
*/
    void print(double*, int);
    
/*
The convert function converts the string of prices to an array of prices using string stream objects
*/
    void convert(string input, int, double*, int);

/*
The Extract Invariants function takes the array of market prices and massages the data to calculate the market invariants. 
*/
    void extractInvariants(double*, int, double*, int);
    
/*
The getInvariantLenght function returns the number of invariants
*/
    double getInvariantLength();
/*
 The getInvariant function returns an invariant from the array of market invariants
 */
    double getInvariant(int num);
/*
 The printInvariants prints the list of invariants to the console screen.
 */
    void printInvariants();
    
    
};

#endif /* defined(__DimensionReduction__Organizer__) */
