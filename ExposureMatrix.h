//
//  ExposureMatrix.h
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/11/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//

#ifndef __DimensionReduction__ExposureMatrix__
#define __DimensionReduction__ExposureMatrix__


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "DataOrganizer.h"
#include "FactorOrganizer.h"

/*
The Exposure Matrix is a matrix which maps from your factors to your market variabeles. Let y be a vector of market variables, x be a vector comprised of a market factor and a additive constant, and A be the exposure matrix. Then:
 
    Y=Ax
 
    Just for illustration, x is written out as:
    x={1,F}^T, where F is the factor. (The ^T just means transpose. x is a column vector)
 
    The Exposure object is fed  an array of market data (stored as DataOrganizers) and a factor (stored as a factor organizer). The componenets of the exposure matrix can be tweaked and augmented — or they can simply be optimized to maximize the R square value between the actual market distribution and the estimated (or caluclated) distribution given by the matrix product between the matrix and the factor.
 */

class ExposureMatrix
{
    
public:
    
    /*
     The constructor takes in three parameters:
                        1) An int, the number of the market variables
                        2) An array of DataOrganizers that have stores the market variables
                        3) A pointer to a factor organizer, which will be used to try and estimate the market variables
     */
    ExposureMatrix(int, DataOrganizer*, FactorOrganizer*);
    /*
     The destructor deletes the necessary arrays to free up memory
     */
    ~ExposureMatrix();
    /*
     getExposure returns the matrix element at a given (row,column)
     */
    double getExposure(int, int);
    /*
     Set exposure sets the matrix element for a given (row, coulmn)
     */
    void setExposure(int, int, double);
    /*
     The optimze function is a function that uses the technique of gradient descent to minimize the sum of squares of residuals to maximize the R Squared value
     */
    void optimize();
    /*
    The findVarMean fucntion calculates the mean for every variable and stores it in an array
     */
    void findVarMean();
    /*
     The findFactMean function calculates the mean for the factor and stores it in a double
     */
    void findFactMean();
    /*
     The sumOfSquares function calculates and stores the total sum of squares
     */
    void sumOfSquares();
    /*
     The resSumOfSquares functions calculates and returns the sum of squares of residuals given the current set of matrix elements
     */
    double resSumofSquares();
    /*
     The getsumOfSquares function returns the total sum of squares 
     */
    double getsumOfSqares();
    /*
     The evalueate function is used by the ExposureMatrix object to calculate the matrix product between the factor vector and the matrix
     */
    void evaluate(int , double*);
    /*
     The rSquare function calculates and returns the R Squared value for the current matrix
     */
    double rSquare();
    /*
     The derivateWRTFactor calcualtes and returns the partial derivative of the residual sum of squares function at a particular data point
     */
    double DerivatieWRTFactor(int);
    /*
     The derivateWRTFactor calcualtes and returns the partial derivative of the residual sum of squares function at a particular data point
     */
    double DerivativeWRTCosnt(int);
    
    
};


#endif /* defined(__DimensionReduction__ExposureMatrix__) */
