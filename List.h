//
//  List.hpp
//  mlg236_P1
//
//  Created by Michah Griffin on 2/2/18.
//  Copyright © 2018 Michah Griffin. All rights reserved.
//

#ifndef List_hpp
#define List_hpp
//#include "Vector.h"
#include "DLL.h"
#include <stdio.h>

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class List declaration                                 **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
template <typename T, typename T2>
class List : public DLL<T> //, public Vector<T>
{
public:
    List();
    List( List &otherList);
    
    void load_frontL(T2 a)  {container.Insert_front(a);}
    void load_rearL(T2 a)   {container.Insert_rear(a);}
    
    void printL();
    
    T2 atL(long pos)  const {return container.at(pos);}
    long sizeL()     const {return container.size();}
    
    void emptyL();
    
private:
    
    T container;
    
};

template <typename T, typename T2>
void List<T,T2>::emptyL()
{
    for (long i = 0; i > container.size(); i++)
        container.erase_rearLL();
}

template <typename T, typename T2>
List<T,T2>::List()
{
    //std::cout << "\nEnter List() - Constructor\n";
    
}

template <typename T, typename T2>
List<T,T2>::List( List &otherList)
{
    //std::cout << "\nEnter List() - Copy Constructor\n";
    
    for (long i = otherList.sizeL(); i>0; i--)
    {
        container.Insert_front(otherList.atL(i));
    }
    
}

template <typename T, typename T2>
void List<T,T2>::printL()
{
    for(int i=container.size(); i>0; i--)
        std::cout << container.at(i);
}




#endif /* List_hpp */
