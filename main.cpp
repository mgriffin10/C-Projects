//
//  main.cpp
//  Calculator
//
//  Created by Michah Griffin on 1/24/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//

/**
 * Simple Example program to demonstrate J. Montgomery
 * 1. reading or populating arbitrary long int (BIGINT) from file
 *
 * 2. adding/subtracting two BIGINT
 *
 * 3. printing out two BIGINT
 *
 * NOTE: BIGINT has-a List member variable
 * List is templated using your Vector or DLL classes
 * i.e. List<DLL<char>, char> or List<Vector<char>, char>
 *
 * Since you are storing digits, it makes sense to use char's
 *
 * Below is to put into context how you should think about designing
 * your classes and how they will be use.
 */

#include <iostream>
#include <fstream>
#include "bigInt.h"


//std::ifstream inputFile(std::string file);

int main(int argc, char *argv[])
{
    std::string fileName = "";
    std::string outputFile = "/Users/michahgriffin/Desktop/CalcTest_Add_SL.txt";
    fileName = argv[1];
    
    
    // Opening the File
    std::ifstream inputFile;
    inputFile.open(fileName.c_str());
    
    while (!inputFile.eof()) //iterate through loop until the end of file is reached
    {
        // Big Int Testing
        bigInt i1;
        bigInt i2;
        
        char operatorSymbol;
        
        // read in digits for 1st pseudo infinite int
        inputFile >> i1;
        
        // read in digits for 2nd pseudo infinite int
        inputFile >> i2;
        
        // read in arithmetic operator
        inputFile >> operatorSymbol;
        
        // Compare and Buffering Testing
        //std::cout <<"\n" << i1.compare(i2) <<"\n";
        
        // printing the problem
        i1.printBI();
        i2.printBI();
        std::cout <<std::endl << operatorSymbol <<std::endl ;
        std::cout <<"---------------------------------------";
        
        // Addition
        if (operatorSymbol == '+')
            (i1 + i2).printBI();
        
        // Subtraction
        if (operatorSymbol == '-')
            (i1 - i2).printBI();
        
        i1.emptyBI();
        i2.emptyBI();
        
        std::cout <<"\n\n";
    }
    
    return 0;
}



