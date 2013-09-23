//
//  main.cpp
//  Dimension Reduction
//
//  Created by Sohrab Andaz on 8/28/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//


/*
In quantitaive finance, many times the dimension of the problem is simply to large to solve.
For example, if you tried to optimize a porfolio using CAPM, or tried to minimize risk, if your portfolio contains a thousand different stocks, it can be computationally impossible to resolve the problem. So there are certain methods that are used to try and reduce the dimension of the problem. One is shrinkage. Another is Principal Component Analysis. And another is Dimension Reduction.
 
    In Dimension Reduction you try and estimate a set of IID random variables by using a much smaller different set of IID random variables, called factors. Note: the IID-ness is crucial. Dimension Reduction will not work if your variables and factos are not IID.
 
    In this program we are trying to reduce the dimension of a vector of IID random variables by regressing them against a single factor. (This could easily be generalized to include more factors)
    
    In this case, the IID random variables we are trying to estimate are log returns on a stock over a one week period. The price data runs from 09/04/2013 to 09/03/2003: ten years. The program massages the data and extracts the invariants — IID random variables.  These invariants are stores in DataOrganizers, which are composed into an array.
 
    The program performs a simmilar action for the factor. The factor, which in this case is the Nasdaq Composite runs from the same range. One again the program massages the data and extracts the invarants — log returns, which are IID random variables. In this case the invariants are stored in a FacotrOrganier object.
 
    Then the array of DataOrganizers and the FactorOrganizer is fed into a ExposureMatrix object. The ExposureMatrix data structure allows users to set the matrix components, or just optimize the matrix. 
 
 
    Because there are thousands of data points, the regression is overdetermined. So the best solution that can be given is one that maximizes the coeffiencent of determination, the R Squared. The technique used for optimization is gradient descent. The step size and bounds(a measure of exactitude, the smaller the more exact) can be changed in the code. Currently the step size and bounds require a few minutes of computation.
 
    In main, an array of DataOrganizers are created. It, along with the factor organizer, is fed into an Exposure Matrix object. Certain unoptimized paramaters are displayed. Note the R-Squared is negative, and this is okay. In situations where the data does not have an y-intercept of 0, the data can have an negative R squared value if the additive constant is not specified (Ax+b=y, b is the additive constant).
 
    Then the program optimizes the Exposure Matrix and the optimized valeus are displayed.
 
    For more information on Dimension Reduction see "Meucci, Attilio. Risk and Asset Allocation. Berlin: Springer, 2005."
 
 
 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "DataOrganizer.h"
#include "FactorOrganizer.h"
#include "ExposureMatrix.h"


using namespace std;


int main ()
{
    int size=2520;
    DataOrganizer Historical (size, "aapl.txt");
    DataOrganizer Historical2 (size, "arw.txt");
    DataOrganizer theDatas[2]= {Historical, Historical2};
    FactorOrganizer Nasdaq(size, "NASDAQComposite.txt");

    FactorOrganizer* theFactor= &Nasdaq;
    ExposureMatrix sample (2, theDatas, theFactor);
    sample.setExposure(1, 2, 10);
    sample.setExposure(2, 2, 10);
    cout << "Current R Squared Value is: "<< sample.rSquare()  <<  endl;
    cout <<"Where the sum of squares of residuals is: " << sample.resSumofSquares() << endl;
    cout <<"And the total sum of squares is: " << sample.getsumOfSqares() <<endl;
    cout << "Optimizing..." << endl;
    sample.optimize();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "After optimizing, the R Squared Value is: "<< sample.rSquare()  <<  endl;
    cout <<"Where the sum of squares of residuals is: " << sample.resSumofSquares() << endl;
    cout <<"And the total sum of squares is: " << sample.getsumOfSqares() <<endl;

    
  return 0;
}