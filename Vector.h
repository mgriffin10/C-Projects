//
//  Vector.cpp
//  mlg236_P1
//
//  Created by Michah Griffin on 2/2/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//
//
//  Vector.hpp
//  DS_HW_#0
//
//  Created by Michah Griffin on 1/15/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <stdio.h>

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Vector declaration                               **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template <typename T>
class Vector
{
public:
    Vector();
    ~Vector();
    
    void Insert_front(T val);
    void Insert_rear(T val);
    void Insert( int index, T val);
    void erase(int index);
    void erase_rear();
    void erase_front();
    
    // Accessor Functions
    
    T& operator[](int index);
    T& front();
    T& back();
    T& at(int index);
    int size();
    int cap();
    bool moveCursorTo(int index);
    int getCursorTo(int index);
    
private:
    int n;              // spaces in array
    int count;          // values in array
    T *container;       // a pointer to the array
    
    
};

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Vector implementation                            **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/**************************************************************************
 *            Vector() - Constructor                                      *
 **************************************************************************/
template <typename T>
Vector<T>::Vector()
{
    std::cout << "Entering Vector Constructor\n";
    
    n = 10;                                 // Size of Array
    char zero = '0';
    
    container = new T[n];
    for (int i=0; i<=n; i++)
        container[i] = zero;                // Initialize all elements to zero.
    
    count = 0;                              // Ammount of values entered in array
    
}

/**************************************************************************
 *            ~Vector() - Destructor                                      *
 **************************************************************************/
template <typename T>
Vector<T>::~Vector()
{
    std::cout << "Entering Vector Destructor \n";
    
    delete [] container;
    
}

/**************************************************************************
 *            Overload operrator[] - no bounds checking                    *
 **************************************************************************/
template <typename T>
T& Vector<T>::operator[](int index)
{
    return *(container + index); // a reference to the element
}


/**************************************************************************
 *            Insert_front(val)                                              *
 **************************************************************************/
template <typename T>
void Vector<T>::Insert_front(T val)
{
    //std::cout << "\nEntering insert_front with size: " << count << std::endl;
    
    // While Loop to enlarge array if nessary
    T *temp;
    if (count+1 > n)
    {
        while (count+1 > n)
            n = n * 2;                  // double the size of the array
        
        temp = new T[n];                // create new larger array
        
        for (int i = 0; i < count; i++) // copy container to temp
            temp[i] = container[i];
        
        for (int j = count; j < n; j++)
            temp[j] = 0;
        
        delete [] container;
        
        container = temp;
        
        //std::cout << "\nArray space doubled to: " << n << std::endl;
    }
    
    // Shifting array over 1
    T *shift;
    shift = new T[n];                   // creating new array
    
    shift[0] = val;                     // setting the shift first location to new value
    
    for (int j = 0; j < (n-1); j++)         // copy rest of the container to shift
        shift[j+1] = container[j];
    
    delete [] container;
    container = shift;                  // pointing container to shifted array
    count++;                            // add to count
    
}

/**************************************************************************
 *            Insert_rear(val)                                              *
 **************************************************************************/
template <typename T>
void Vector<T>::Insert_rear(T val)
{
    //std::cout << "Entering Insert_rear, with size:" << count << "\n";
    
    int *temp;
    while (count+1 > n)
    {
        n = n * 2;                      // double the size of the array
        temp = new T[n];                // create new larger array
        
        for (int i = 0; i <= (count); i++)
            temp[i] = container[i];
        for (int j = count; j < n; j++)
            temp[j] = 0;
        delete [] container;
        container = temp;
    }
    
    container[count] = val;
    count++;
    
}

/**************************************************************************
 *            Insert(index, val)                                          *
 **************************************************************************/
template <typename T>
void Vector<T>::Insert(int index, T val)
{
    std::cout << "Entering Insert, with size:" << count << "\n";
    
    // Check if index is invaild location
    if ( index > count )
    {
        std::cout << "\nERROR::Insert(index, val):: The imputed index is not a valid location\n";
    }
    
    else
    {
        
        // While Loop to enlarge array if nessary
        T *temp;
        while (index > n)
        {
            
            n = n * 2;                      // double the size of the array
            temp = new T[n];                // create new larger array
            
            for (int i = 0; i <= (count); i++)
                temp[i] = container[i];
            for (int j = count; j < n; j++)
                temp[j] = 0;
            delete [] container;
            container = temp;
        }
        
        // If to shift array over if not the final location
        T *shift;
        if (index < count)
        {
            
            shift = new T[n];                // creating new array
            
            for (int i = 0; i < index; i++) // copying old array up to index
                shift[i] = container[i];
            
            shift[index] = 0;               // setting the shift index location to zero
            
            for (int j = index; j < n; j++) // copy rest of the container 1 spot past the index
                shift[j+1] = container[j];
            
            delete [] container;
            container = shift;               // pointing container to shifted array
        }
        
        container[index] = val;             // replacing the indexed location with val
        count++;                            // add to count
        
    } // end of else
    
}

/**************************************************************************
 *            erase(index)                                                *
 **************************************************************************/
template <typename T>
void Vector<T>::erase(int index)
{
    // Check if index is filled with value
    if ( index >= count )
        std::cout << "\nERROR in erase(index) there is no value stored in this index\n";
    
    else
    {
        // If loop for erasing location that is not the final value
        T *shift;
        if (index < count)
        {
            shift = new T[n];                // creating new array
            
            for (int i = 0; i < index; i++) // copying old array up to index
                shift[i] = container[i];
            
            for (int j = index; j < n; j++) // copy rest of the container 1 spot past the index
                shift[j] = container[j+1];
            
            delete [] container;
            container = shift;               // pointing container to shifted array
        }
        
        container[n-1] = 0;             // filling the empty location with a zero
        count--;                            // remove from the count
        
    }
    
}

/**************************************************************************
 *            erase_rear()                                                *
 **************************************************************************/
template <typename T>
void Vector<T>::erase_rear()
{
    container[count-1] = 0;         // filling the empty location with a zero
    count--;                        // remove from the count
}

/**************************************************************************
 *            erase_front()                                                *
 **************************************************************************/
template <typename T>
void Vector<T>::erase_front()
{
    T *shift;
    
    shift = new T[n];               // creating new array
    
    for (int i = 0; i < n; i++)    // copying old array up to index starting one past start
        shift[i] = container[i+1];
    
    delete [] container;
    container = shift;               // pointing container to shifted array
    
    
    container[n-1] = 0;                // filling the empty location with a zero
    count--;                            // remove from the count
}



/**************************************************************************
 *            size()                                                      *
 **************************************************************************/
template <typename T>
int Vector<T>::size()
{
    return count;
}

/**************************************************************************
 *            cap()                                                       *
 **************************************************************************/
template <typename T>
int Vector<T>::cap()
{
    return n;
}

/**************************************************************************
 *            at(index) function - bounds checking                        *
 **************************************************************************/
template <typename T>
T& Vector<T>::at(int index)
{
    
}


#endif /* Vector_h */

