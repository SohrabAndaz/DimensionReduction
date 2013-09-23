//
//  FactorOrganizer.h
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/11/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//

#ifndef __DimensionReduction__FactorOrganizer__
#define __DimensionReduction__FactorOrganizer__


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "Organizer.h"
/*
 FactorOrganizer
 
 
 A derived class of Organizer, the FactorOrganizer is used to extract and store market invariants from a times series of stock prices. These market invariants are the natural log of the returns.
 
 */
using namespace std;
class FactorOrganizer: public Organizer
{
    
    
public:
    /*
     The constructor for this class builds a FactorOrganizer object.
     It takes in two parameters:
     1) An integer, size, which asks for the number of data points you have in your stock price v. time curve.
     2) A string, filename, which asks for the filename where the data is stored. The data must be seperated by commas.
     After it has been fed these arguments it, strips the data, computes the market invariants, and stores the invariants in an array.
     */
    FactorOrganizer(int, string);
    
    //  ~DataOrganizer();
    
    void fill(char*, int, string);
    /*
     This is the custom fill function for the FactorOrganizer. It is used by the constructor to fill in a string with the data from the file given the correct file formatting. Files must be formatted so that on every line there are two entries, first the date (and/or time) and then the price at that data at that data and/or time. So an example of a line would be:
    
     3/12/12, 19.90
     
     The resason for this particular format is becuase this is how "https://www.google.com/finance?ei=qzU7UtDfD-aL0QGRew", Google's free source of historical quotes, formats it's data.
     
     
     */
    
};



#endif /* defined(__DimensionReduction__FactorOrganizer__) */
