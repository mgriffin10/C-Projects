//
//  DLL.hpp
//  DS_HW_#0
//
//  Created by Michah Griffin on 1/21/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//

#ifndef DLL_h
#define DLL_h

#include <stdio.h>

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Node declaration                                 **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
template <typename T>
class Node
{
public:
    T info;
    Node<T>* next;
    Node<T>* previous;
    
    Node(T val = T(), Node<T>* nextPointer = NULL, Node<T>* previousPointer = NULL);
    
}; //END declaration template class Node

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class DLL declaration                                  **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template <typename T>
class DLL
{
private:
    Node<T> *current;
    Node<T> *header;
    long count;
    
    void Insert_before(T val );
    void Insert_after(T val );
    
    T& find(T val);
    
public:
    DLL();
    ~DLL();
    
    void Insert_front(T val);
    void Insert_rear(T val);
    void Insert( int pos, T val);
    
    void erase(int pos);
    void eraseV(T val);             // Deletes first instance of val
    void erase_rearLL();
    void erase_front();
    
    // Accessor Functions
    
    long findT(T val);
    T& front();
    T& back();
    T& at(long pos) const ;
    long size() const;
    
};

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Node implementation                              **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template <typename T>
Node<T>::Node(T val, Node<T>* nextPointer, Node<T>* previousPointer)
{
    info = val;
    next = nextPointer;
    previous = previousPointer;
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class DLL implementation                               **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/**************************************************************************
 *            DLL() - Constructor                                         *
 **************************************************************************/
template <typename T>
DLL<T>::DLL()
{
    //std::cout << "\nEntering the DLL Constructor\n";
    
    count = 0; // Seting the size of the new DLL to zero
    
    // Creating Sentinal Node and pointing next and previous to itself meaning empty DLL
    header = new Node<T>;
    header->next = header->previous = header;
    
    current = header;       // setting the current to header
}

/**************************************************************************
 *            ~DLL() - Destructor                                         *
 **************************************************************************/
template <typename T>
DLL<T>::~DLL()
{
    //std::cout << "\nEntering Destructor\n";
    
    while (count > 0)
    {
        erase_rearLL();
        //std::cout << "\n\n Size is now " << count <<" \n\n";
    }

    current = nullptr;
    delete current;
}

/**************************************************************************
 *            Insert_front(val)                                           *
 **************************************************************************/
template <typename T>
void DLL<T>::Insert_front(T val)
{
    current = header;               // point the current pointer to header
    
    Insert_after(val);              // inserting new node after header
    
    count++;                        // increasing the count by 1
}

/**************************************************************************
 *            Insert_rear(val)                                           *
 **************************************************************************/
template <typename T>
void DLL<T>::Insert_rear(T val)
{
    current = header;           // point the current pointer to header
    
    Insert_before(val);         // inserting new node before header

    count++;                    // increasing the count by 1
}

/**************************************************************************
 *            Insert(pos, val)                                      *
 **************************************************************************/
template <typename T>
void DLL<T>::Insert(int pos, T val)
{
    current = header;               // point the current pointer to header
    
    for (int i=0; i < pos; i++)     // push current pointer to desired position
        current = current->next;
    
    Insert_before(val);             // inserting new node before current

    count++;                        // increasing the count by 1
}

/**************************************************************************
 *            at(pos)                                                     *
 **************************************************************************/
template <typename T>
T& DLL<T>::at(long pos) const
{
    Node<T> * curr = header;            // set current pointer to header to begin search
    
    if ( pos > count || pos <= 0)
    {
        std::cout << "\n\nERROR::at(pos):: The given position is invailed\n";
        std::cout << "Returning zero\n\n";
    }
    
    else
    {
        for(long i=0; pos != i;i++)
            curr = curr->next;
    }
    
    return curr->info;
}

/**************************************************************************
 *            size()                                                     *
 **************************************************************************/
template <typename T>
long DLL<T>::size() const
{
    return count;
}

/**************************************************************************
 *            erase(pos)                                                  *
 **************************************************************************/
template <typename T>
void DLL<T>::erase(int pos)
{
    if ( pos > count || pos <= 0 )
        std::cout << "\nERROR::erase(pos):: The given position is invailed\n";
    
    else
    {
        
        current = header;            // current pointer to header
        
        for (int i=0; i<=pos; i++)
        {
            current = current->next;
        }
        
        current->previous->next = current->next;
        current->next->previous = current->previous;
        
        delete current;
        
        count--;
        
    } // end of else
    
}

/**************************************************************************
 *            eraseV(val)                                                  *
 **************************************************************************/
template <typename T>
void DLL<T>::eraseV(T val)
{
    
    find(val);                  // call private function find which places current pointer at location of val
                                // if unfound places pointer at last node in list
    
    // Error Message for unfound values
    if (val != current->info)
        std::cout << "\nERROR::erase(val):: Value " <<val << " not found in DLL\n";
    
    else
    {
        current->previous->next = current->next;
        current->next->previous = current->previous;
    
        delete current;         // deleting the node pointed to by current
        
        current = header;       // pointing current back to header
    
        count--;                // subtracting 1 from size count

    }

}

/**************************************************************************
 *            erase_front()                                               *
 **************************************************************************/
template <typename T>
void DLL<T>::erase_front()
{
    // If statement to catch empty DLL
    if (count == 0)
        std::cout << "\nERROR::erase_front():: The LL is empty \n";
    
    else
    {
        current = header->next;            // currenter pointer to position after header
        
        header->next = current->next;
        current->next->previous = header;
        
        delete current;
        
        count--;
    }
    
    current = header;
}

/**************************************************************************
 *            erase_rear()                                               *
 **************************************************************************/
template <typename T>
void DLL<T>::erase_rearLL()
{
    // If statement to catch empty DLL
    if (count == 0)
        std::cout << "\nERROR::erase_rear():: The LL is empty \n";
    
    else
    {
        current = header->previous;         // currenter pointer to position before header
        
        current->previous->next = current->next;
        header->previous = current->previous;
        
        delete current;
        
        count--;
    }
    
    current = header;
}

/**************************************************************************
 *            back()                                               *
 **************************************************************************/
template <typename T>
T& DLL<T>::back()
{
    // If statement to catch empty DLL
    if (count == 0)
        std::cout << "\nERROR::erase_rear():: The LL is empty \n";
    
    return header->previous->info;
}

/**************************************************************************
 *            front()                                               *
 **************************************************************************/
template <typename T>
T& DLL<T>::front()
{
    // If statement to catch empty DLL
    if (count == 0)
        std::cout << "\nERROR::front():: The LL is empty \n";
    
    return header->next->info; 
}

/**************************************************************************
 *            private function - Insert_before()                          *
 **************************************************************************/
template <typename T>
void DLL<T>::Insert_before(T val)
{
    Node<T> *temp;
    temp = new Node<T>(val);        // Created new node

    temp->previous = current->previous; // setting new node behind current pointer
    temp->next = current;
    
    current->previous->next = temp;
    current->previous = temp;
}

/**************************************************************************
 *            private function - Insert_after()                          *
 **************************************************************************/
template <typename T>
void DLL<T>::Insert_after(T val)
{
    Node<T> *temp;
    temp = new Node<T>(val);        // Created new node
    
    temp->previous = current;       // setting new node behind current pointer
    temp->next = current->next;
    
    current->next->previous = temp;
    current->next = temp;
}
/**************************************************************************
 *            public function - find(val)                                  *
 **************************************************************************/
template <typename T>
long DLL<T>::findT(T val)
{
    current = header->next;
    long position = 1;
    
    while(val != current->info)
    {
        // If loop to display missing value error - returns postion as 0
        if (current->next == header)
        {
            std::cout << "\nERROR::private function &find(val):: Value " <<val << " not found in DLL\n";
            position = 0;
            break;
        }
    
        current = current->next;
        position++;
    }
    
    return position;
}

/**************************************************************************
 *            private function - &find(val)                                  *
 **************************************************************************/
template <typename T>
T& DLL<T>::find(T val)
{
    current = header->next;
    
    while(val != current->info)
    {
        // If loop to display invalid value error - returns value of header->info
        if (current->next == header)
        {
            std::cout << "\nERROR::private function &find(val):: Value " << val << " not found in DLL\n";
            std::cout << "\nReturning the value held in final node in list\n";
            break;
        }
        
        current = current->next;
    }
    
    return current->info;
}
    

#endif /* DLL_h */
