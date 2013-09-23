//
//  Organizer.cpp
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/19/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//

#include "Organizer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>

using namespace std;



int datasize;
char *dataPriceString;
double *dataprices;
double *datainvariants;


Organizer::Organizer(int sz, string filename)
{
    datasize=sz;
    dataPriceString= new char[sz*20];
    dataprices= new double[sz];
    datainvariants= new double[sz-1];
}

/*
 Organizer::~Organizer()
 {
 delete [] dataPriceString;
 delete [] dataprices;
 delete [] datainvariants;
 }*/



void Organizer::print(char input[], int len)
{
    for(int i=0; i<len; i++)
    {
        if(input[i]=='"')
        {
            cout << ""<< endl;
        }
        cout<< input[i];
    }
}

void Organizer::print(double input[], int len)
{
    for(int i=0; i<len; i++)
    {
        
        cout<< input[i]<<endl;
    }
}

void Organizer::convert(string input, int size, double convert[], int convsize)
{
    int quoteCounter=0;
    int inputCounter=0;
    int outputcounter=0;
    double sample;
    string str= "";
    
    for(int i=1; i<convsize; i++)
    {
        while (quoteCounter==0)
        {
            if(input[inputCounter]=='"')
            {
                inputCounter++;
                quoteCounter++;
                break;
            }
            else
            {
                str+=input[inputCounter];
                inputCounter++;
            }
            if(str=="000000000000000000000")
            {
                break;
            }
            
        }
        if(str=="000000000000000000000")
        {
            break;
        }
        quoteCounter=0;
        stringstream ss(str);
        if(ss >> sample)
        {
            outputcounter++;
            if(sample!=0)
            {
                convert[outputcounter]=sample;
            }
            
        }
        else{break;}
        str="";
        
    }
    
}

void Organizer::extractInvariants(double data[], int theDatasize, double invariants[], int invariantSize)
{
    for( int i=0; i<invariantSize; i++)
    {
        if(i>theDatasize){break;}
        invariants[i]= log(data[i]/data[i+1]);
    }
}

double Organizer::getInvariant(int num)
{
    if(0<=num && num<datasize-1)
    {
        return datainvariants[num+1];
    }
    else{
        return 100000000000;
    }
}

double Organizer::getInvariantLength()
{
    return datasize-3;
}

void Organizer::printInvariants()
{
    print(datainvariants, datasize/20-1);
}

