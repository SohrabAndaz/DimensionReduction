//
//  ExposureMatrix.cpp
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/11/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//

#include "ExposureMatrix.h"
#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <cstring>
//#include <stdio.h>
#include <math.h>

const double Max = 10000;
const double Min = -10000;
const int numfacts=2;

double *matrix;
double start;
double stop;
double squares;
double* meanOfData;
double meanOfFactor;
double mainfactor;
DataOrganizer *theMarket;
FactorOrganizer* theFactor;
int numVariables;
int numFactors;


ExposureMatrix::ExposureMatrix(int numparam, DataOrganizer* theOrganizer, FactorOrganizer *theFactorOrg)
{
    
    theMarket=theOrganizer;
    theFactor=theFactorOrg;
    numVariables=numparam;
    numFactors=numfacts;
    start=Min;
    stop= Max;
    squares=1;
    matrix= new double[(numfacts)*numparam];
    meanOfData= new double[numVariables];
    meanOfFactor=0;
    
    findVarMean();
    findFactMean();
    sumOfSquares();
}

ExposureMatrix::~ExposureMatrix()
{
    delete [] matrix;
    delete [] meanOfData;
}

double ExposureMatrix::getExposure(int row, int column)
{
    return matrix[(row-1)*column+column-1];
}

void ExposureMatrix::setExposure(int row, int column, double num)
{
    matrix[(row-1)*column+column-1]=num;
}

void ExposureMatrix::findVarMean()
{
    double sum=0;
    for(int j=0; j<numVariables; j++)
    {
        for(int i=1; i<theMarket[j].getInvariantLength(); i++)
        {
            sum+=theMarket[j].getInvariant(i);
        }
        meanOfData[j]=(sum/theMarket[j].getInvariantLength());
        sum=0;
    }
}

void ExposureMatrix::findFactMean()
{
    double sum=0;
    for(int i=1; i<theFactor->getInvariantLength(); i++)
    {
        sum+=theFactor[0].getInvariant(i);
    }
    meanOfFactor=(sum/theFactor->getInvariantLength());
}

void ExposureMatrix::sumOfSquares()
{

    double sum=0;
    for(int i=1; i<theMarket[0].getInvariantLength(); i++)
    {
        
        for(int j=0; j<numVariables; j++)
        {
            
            sum+=pow(theMarket[j].getInvariant(i)-meanOfData[i],2);

        }
    }
    squares=sum;
}

double ExposureMatrix::resSumofSquares()
{
    double sum=0;
    double *eval =new double[numVariables];
    for(int i=0; i<theMarket->getInvariantLength(); i++)
    {
        evaluate(i,eval);
        for(int j=0; j<numVariables; j++)
        {
            sum+= pow(theMarket[j].getInvariant(i)-eval[j],2);
        }
    }
    delete [] eval;
    return sum;
}

                          
void ExposureMatrix::evaluate(int invariantNum, double *ans)
{
    double *eq =new double[numVariables];
    double matrixproduct=0;

    for(int k=0; k<numVariables; k++)
    {
        matrixproduct+=theFactor->getInvariant(invariantNum)* matrix[(k)*(2)+(1)]+matrix[(k*2)];
        eq[k]=matrixproduct;
        matrixproduct=0;
    }
    for(int i=0; i<numVariables; i++)
    {
        ans[i]=eq[i];
    }
    delete [] eq;
}

double ExposureMatrix::getsumOfSqares()
{
    return squares;
}

double ExposureMatrix::rSquare()
{
    return (1-(resSumofSquares()/squares));
}

double ExposureMatrix::DerivatieWRTFactor(int varNum)
{
    double stepsize=0.0000001;
    double currResidual = resSumofSquares();
    double currFact= getExposure(varNum+1,2);
    setExposure(varNum+1,2, currFact+stepsize);
    double nextResidual= resSumofSquares();
    setExposure(varNum+1,2, currFact);
    return ((nextResidual-currResidual)/stepsize);
}

double  ExposureMatrix::DerivativeWRTCosnt(int varNum)
{
    double stepsize=0.0000001;
    double currResidual = resSumofSquares();
    double currFact= getExposure(varNum+1,1);
    setExposure(varNum+1,1, currFact+stepsize);
    double nextResidual= resSumofSquares();
    setExposure(varNum+1,1, currFact);
    return ((nextResidual-currResidual)/stepsize);
}

 void ExposureMatrix::optimize()
{
    
    double alpha=0.0003;
    double bounds=0.001;
    double* dJdF= new double[numVariables];
    double* dJdk= new double[numVariables];
    int isDone=1;
    for(int i=0; i<numVariables;i++)
    {
        dJdF[i]=DerivatieWRTFactor(i);
        dJdk[i]=DerivativeWRTCosnt(i);
        
        if(dJdF[i]>bounds or dJdk[i]>bounds or dJdF[i]<-1*bounds or dJdk[i]<-1*bounds)
        {
            isDone=isDone*0;
        }
        else
        {
            isDone=isDone*1;
        }

    }
    
    
    if(isDone==1)
    {
        delete [] dJdF;
        delete [] dJdk;
        return;
    }
    else
    {
        for (int i=0; i<numVariables; i++)
        {
            setExposure(i+1, 1, getExposure(i+1, 1)-alpha*dJdk[i]);
            setExposure(i+1, 2, getExposure(i+1, 2)-alpha*dJdF[i]);
        }
        delete [] dJdF;
        delete [] dJdk;
        optimize();
    }
}





