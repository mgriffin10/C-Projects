//
//  Bigint.hpp
//  mlg236_P1
//
//  Created by Michah Griffin on 1/29/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//

#ifndef Bigint_hpp
#define Bigint_hpp

#include <stdio.h>
#include <iostream>
#include "DLL.h"
#include "List.h"

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class bigInt declaration                               **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
class bigInt
{
    friend std::istream& operator>> (std::istream &is, bigInt &newNum);
    
public:
    bigInt();
    bigInt(bigInt &otherBI);
    
    char findComplement(int a);
    
    long sizeBI()       const    { return digList.sizeL();}
    char atBI(long pos) const   { return digList.atL(pos);}
    
    void load_frontBI(char dig)     {digList.load_frontL(dig);}
    void load_rearBI(char dig)      {digList.load_rearL(dig);}
    
    void neg()    { negative = true;}
    void posSym() { postiveSym = true;}
    
    void printBI();
    
    void emptyBI() { digList.emptyL();}
    
    bigInt operator+(const bigInt &rh) ;
    bigInt operator-(const bigInt  &rh) ;
    bigInt operator=(bigInt &rh) ; 
    void   copy( const bigInt &rh);
    
    bigInt buffer( const bigInt &rh);
    std::string compare( const bigInt &rh);
    
private:
    
    bool negative;
    bool postiveSym;                    // check for positive symbol
    List< DLL<char>, char> digList;
    
};


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class List implementation                              **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *              bigInt() - CONSTRUCTOR                                      *
 ****************************************************************************/
bigInt::bigInt()
{
    //std::cout << "\nEntering the bigInt Constructor\n";
    
    negative = false;
    postiveSym = false;
}
/****************************************************************************
 *              bigInt() - COPY CONSTRUCTOR                                 *
 ****************************************************************************/
bigInt::bigInt( bigInt &otherBI)
{
    //std::cout << "\nEntering the bigInt Copy Constructor\n";
    
    negative = false;
    postiveSym = false;
    
    copy(otherBI);
}

/****************************************************************************
 *              findComplement(int a)                                       *
 ****************************************************************************/
char bigInt::findComplement(int a)
{
    char complement;
    int tempComplement;
    
    tempComplement = (9 - a);
    complement = tempComplement + '0';
    
    //std::cout << "\n" << complement << "\n";
    
    return complement;
}
/****************************************************************************
 *              friend function overloaded operator>> - Input               *
 ****************************************************************************/
std::istream& operator>>( std::istream &is, bigInt &newList )
{
    //std::cout << "\nYou are now entering OVERLOADED OPERATOR >> " << std::endl;

    // Failed istream error check
    if (!is)
        std::cout << "ERORR:: >> operator:: Stream in failed state, returning to main\n";
    
    else
    {   // Creating Variables
        char ch = '?';
        std::string num;

        // Reading the whole line of digit into a string
        getline(is, num);

        // Check for negative or positive sign
        ch = num[0];
        if (num[0] == '-')
            newList.neg();
        else if (num[0] == '+')
            newList.posSym();
        else
            newList.load_frontBI(ch);

        // Reading the rest of the digits
        for(int i=1; i<num.length(); i++)
        {
            ch = num[i];
            newList.load_frontBI(ch);
        }
    }

    return is;
}

/****************************************************************************
 *              printBI()                                                     *
 ****************************************************************************/
void bigInt::printBI()
{
    std::cout << std::endl;

    // Printing Dash if Num is negative
    if (negative == true)
        std::cout << "-";
    if (postiveSym == true)
        std::cout << "+";

    // Reading List from back to front
    for(long i=digList.sizeL(); i>0; i--)
        std::cout << digList.atL(i);
}

/****************************************************************************
 *             operator+   - ADDING TWO bigInts                             *
 ****************************************************************************/
bigInt bigInt::operator+(const bigInt &rh)
{
    bigInt product;

    int  newNumInt;
    char newNumChar;
    int  carry = 0;
    
    long maxDigs;
    long minDigs;
    
    int minu;
    long minuSz = digList.sizeL();              // seting size before buffer
    int subtra;
    long subtraSz = rh.sizeBI();                // setting size before buffer
    
    bigInt buffered;                            
    
    if ( minuSz > subtraSz )
    {
        maxDigs = minuSz;
        minDigs = subtraSz;
        buffered.copy(buffer(rh));                  // compares sizes and buffers zeros to shorter list
        
        for ( int i = 1; i <= maxDigs; i++)
        {
            minu = digList.atL(i) - '0';
            subtra = buffered.atBI(i) - '0';
            
            newNumInt = minu + subtra + carry;                 // Addition of minu, subtra and carry
            
            // Check if carry newNum larger than 10
            if (newNumInt > 9)
            {
                //std::cout << "\nEntering carry if loop \n " ;
                newNumInt = newNumInt - 10;
                carry = 1;
            }
            else
                carry = 0;
            
            
            newNumChar = (newNumInt + '0');                   // changing newNum into char
            product.load_rearBI(newNumChar);                 // loading each digit
            
            //std::cout << "\n i = " << i << "\n";        // Error checking cout
        }
    }
    else if (minuSz < subtraSz )
    {
        maxDigs = subtraSz;
        minDigs = minuSz;
        buffered.copy(buffer(*this));             // compares sizes and buffers zeros to shorter list
        
        for ( int i = 1; i <= maxDigs; i++)
        {
            minu = buffered.atBI(i) - '0';
            subtra = rh.atBI(i) - '0';
            
            newNumInt = minu + subtra + carry;                 // Addition of minu, subtra and carry
            
            // Check if carry newNum larger than 10
            if (newNumInt > 9)
            {
                //std::cout << "\nEntering carry if loop \n " ;
                newNumInt = newNumInt - 10;
                carry = 1;
            }
            else
                carry = 0;
            
            
            newNumChar = (newNumInt + '0');                   // changing newNum into char
            product.load_rearBI(newNumChar);                 // loading each digit
            
            //std::cout << "\n i = " << i << "\n";        // Error checking cout
        }
    }
    // else catches same number of digits so max and min eqaul
    else
    {
        maxDigs = minDigs = minuSz;
        
        for ( int i = 1; i <= maxDigs; i++)
        {
            minu = digList.atL(i) - '0';
            subtra = rh.atBI(i) - '0';
            
            newNumInt = minu + subtra + carry;                 // Addition of minu, subtra and carry
            
            // Check if carry newNum larger than 10
            if (newNumInt > 9)
            {
                //std::cout << "\nEntering carry if loop \n " ;
                newNumInt = newNumInt - 10;
                carry = 1;
            }
            else
                carry = 0;
            
            
            newNumChar = (newNumInt + '0');                   // changing newNum into char
            product.load_rearBI(newNumChar);                 // loading each digit
            
            //std::cout << "\n i = " << i << "\n";        // Error checking cout
        }
    }
   
    // Adds additional place if carry remains after for loop
    if (carry > 0)
        product.load_rearBI(carry + '0');
    
    //return product
    return product;
}
/****************************************************************************
 *             operator-   - Subtracting TWO bigInts                        *
 ****************************************************************************/
bigInt bigInt::operator-(const bigInt &rh)
{
    bigInt minu;
    bigInt subtra;
    bigInt minuComplement;
    bigInt productComplement;
    bigInt product;
    
    char minuCompChr;
    
    char prodctCompChr;
    
    long minuDigs;
    
    if ( compare(rh) == "lss")
    {
        product.neg();
        minu.copy(rh);
        subtra.copy(*this);
    
    }
    else if ( compare(rh) == "gtr")
    {
        minu.copy(*this);
        subtra.copy(rh);
    }
    else // The Numbers are eqaul return 0
        product.load_rearBI('0');

    minuDigs = minu.sizeBI();
    
    // For Loop creating minu complement
    for (int i = 1; i <= minuDigs; i++)
    {
        minuCompChr = findComplement(minu.atBI(i) - '0');     // finding complement for each digit of minu
    
        minuComplement.load_rearBI(minuCompChr);                // loading to bigInt
    }
    
    productComplement.copy(minuComplement + subtra);      // Adding minuComplent to subtrahand and seting to productComp

    // For Loop creating product from product complement
    for (int i = 1; i <= minuDigs; i++)
    {
        prodctCompChr = findComplement(productComplement.atBI(i) - '0');     // finding complement for each digit of productComplement
        
        product.load_rearBI(prodctCompChr);                                  // loading to prodctCompChr to product bigInt
    }
    
    return product;

}
/*************************************************s***************************
 *                    overloaded assignment operator                        *
 ****************************************************************************/
bigInt bigInt::operator=( bigInt &rhs)
{
    copy(rhs);
    
    return *this;
    
}; // END overloaded assignment operator for Date class
/****************************************************************************
 *             copy ()  - copys rhs BigInt to empty lsh BigInt              *
 ****************************************************************************/
void bigInt::copy( const bigInt &rh)
{
    for (long i=1; i <= rh.sizeBI(); i++)
        digList.load_rearL(rh.atBI(i));
}
/****************************************************************************
 *             compare   - comparing and buffering bigInts                  *
 ****************************************************************************/
std::string bigInt::compare(const bigInt &rh)
{
    std::string gtr = "gtr";
    std::string lss = "lss";
    std::string equ = "equ";
    
    // Check for more digits and adds zeros to shorter List
    long digDif = digList.sizeL() - rh.sizeBI();
    // lhs List larger
    if (digDif > 0)
        return gtr;

    // lhs List smaller
    else if (digDif < 0)
        return lss;

    // Same amount of digits check each digit starting in largest place
    else
    {
        for (long i = rh.sizeBI(); i > 0; i--)
        {
            int a = digList.atL(i) - '0';
            int b = rh.atBI(i) - '0';
            
            if (a>b)
                return gtr;
            if (b>a)
                return lss;
        }
    }
    return equ;       // No difference
}

/****************************************************************************
 *             buffer   - comparing and buffering bigInts and returning temp BigInt to be used    *
 ****************************************************************************/
bigInt bigInt::buffer(const bigInt &rh)
{
    bigInt bufferedBI;
    
    // Check for more digits and adds zeros to shorter List
    long digDif = digList.sizeL() - rh.sizeBI();
    
    // lhs List larger
    if (digDif > 0)
    {
        bufferedBI.copy(rh);
        for (long i=0; i < digDif; i++)
            bufferedBI.load_rearBI('0');
        
    }
    // lhs List smaller
    else if (digDif < 0)
    {
        bufferedBI.copy(rh);
        for (long i=0; i < digDif; i++)
            bufferedBI.load_rearBI('0');
    }
    else
        bufferedBI.load_rearBI('E');         // if digit size is eqaul return List with a single char 'E';
    
    return bufferedBI;

}

#endif /* Bigint_hpp */
