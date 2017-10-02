//
//  main.cpp
//  patterns
//
//  Created by Андрей Решетников on 19.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

#include "Append.h"
#include "IsEmpty.h"
#include <list>

std::ostream& operator<<(std::ostream& ostr, EmptyTypeList)
{
    ostr << "{}";
    return ostr;
}

template<typename TL>
void PrintTypeListHelper(TL, std::ostream& ostr)
{
}

template<typename T>
void PrintTypeListHead(T, std::ostream& ostr)
{
    ostr << typeid(T).name();
}

template<typename ...Args>
void PrintTypeListHead(TypeList<Args...> tl, std::ostream& ostr)
{
    ostr << tl;
}

template<typename Head, typename ...Args>
void PrintTypeListHelper(TypeList<Head, Args...>, std::ostream& ostr)
{
    PrintTypeListHead(Head(), ostr);
    if(!IsEmpty<TypeList<Args...>>::value)
    {
        ostr << ' ';
        PrintTypeListHelper<Args...>(TypeList<Args...>(), ostr);
    }
}

template<typename ...Args>
std::ostream& operator<<(std::ostream& ostr, TypeList<Args...> tl)
{
    ostr << '{';
    PrintTypeListHelper(tl, ostr);
    ostr << '}';
    return ostr;
}

template <typename ...Args>
class objList {
public:
    typedef TypeList<Args...> _types;
    std::list<void *> _data;
    
    template <typename T, typename ...Arg>
    friend objList<Arg..., T>* push(T*, objList<Arg...>*);
    template <typename T, typename ...Arg>
    friend objList<Arg...>* pop_back(objList<Arg..., T>*);
};

template <typename T, typename ...Args>
objList<Args..., T>* push(T* pointer, objList<Args...>* obj_list) {
    obj_list->_data.push_back(pointer);
    objList<Args..., T>* new_list = new objList<Args..., T>();
    new_list->_data = obj_list->_data;
    return new_list;
}

template <typename T, typename ...Args>
objList<Args...>* pop_back(objList<Args..., T>* obj_list) {
    obj_list->_data.pop_back();
    objList<Args...>* new_list = new objList<Args...>();
    new_list->_data = obj_list->_data;
    return new_list;
}


int main(int argc, const char * argv[]) {
    typedef TypeList<int> TL1;
    typedef TypeList<char, short> TL2;
    
    std::cout << TL1() << ", " << TL2() << std::endl;
    std::cout << Append<TL2, TL1>::type() << std::endl;
    
    int d = 2;
    int* c = &d;
    objList<int> a;
    objList<int, int>* b = new objList<int, int>();
    b = push(c, &a);
    objList<int, int, int>* f = new objList<int, int, int>();
    f = push(c, b);
    objList<int, int>* e = new objList<int, int>();
    e = pop_back<int, int, int>(f);
    
    return 0;
}
