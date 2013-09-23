//
//  FactorOrganizer.cpp
//  DimensionReduction
//
//  Created by Sohrab Andaz on 9/11/13.
//  Copyright (c) 2013 Sohrab Andaz. All rights reserved.
//


#include "FactorOrganizer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <math.h>

using namespace std;



FactorOrganizer::FactorOrganizer(int sz, string filename):Organizer(sz,filename)
{
    fill(dataPriceString, sz*20, filename);
    convert(dataPriceString, sz*20, dataprices, sz);
    extractInvariants(dataprices, datasize, datainvariants, datasize-1);
}



void FactorOrganizer::fill(char openPriceString[], int size, string filename)
{
    int counter=0;
    int commacounter=0;
    for( int i=0; i<size; i++)
    {
        openPriceString[i]='0';
    }
    
    int priceStringCounter=1;
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            commacounter=0;
            counter++;
            for(int i=0; i<line.length(); i++)
            {
                
                if(commacounter==1 && line[i]!=',')
                {
                    openPriceString[priceStringCounter]=line[i];
                    priceStringCounter++;
                }
                else
                {
                    if(line[i]==',')
                    {
                        commacounter++;
                    }
                }
            }
            openPriceString[priceStringCounter]='"';
            priceStringCounter++;
            
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    
}
