//
//  main.cpp
//  patterns
//
//  Created by Андрей Решетников on 19.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

//#include "Append.h"
//#include "IsEmpty.h"
#include <iostream>
#include <list>
#include "EmptyType.h"
#include "Typelist.h"

template<class T, int n>
class LineSize {
public:
    static const int size = LineSize<typename Loki::TL::Erase<T, typename Loki::TL::TypeAt<T, 0>::Result>::Result, n - 1>::size + sizeof(typename Loki::TL::TypeAt<T, 0>::Result);
};

template<class T>
class LineSize<T, 0> {
public:
    static const int size = 0;
};

template<class TList>
void ReadData(void* data) {
    typename Loki::TL::TypeAt<TList, 0>::Result type;
    void* source;
    std::cin >> type;
    source = &type;
    memcpy(data, source, sizeof(typename Loki::TL::TypeAt<TList, 0>::Result));
    data = (typename Loki::TL::TypeAt<TList, 0>::Result*)data + sizeof(typename Loki::TL::TypeAt<TList, 0>::Result);
    ReadData<typename Loki::TL::Erase<TList,typename Loki::TL::TypeAt<TList, 0>::Result>::Result>(data);
};

template<>
void ReadData<Loki::NullType>(void* data)
{};

template<class TList>
void PrintData(void* data, int writedSize)
{
    if (writedSize == 0) {
        writedSize = sizeof(typename Loki::TL::TypeAt<TList, 0>::Result);
    }
    std::cout << *((typename Loki::TL::TypeAt<TList, 0>::Result*)data);
    data = (typename Loki::TL::TypeAt<TList, 0>::Result*)data + writedSize;
    writedSize = sizeof(typename Loki::TL::TypeAt<TList, 0>::Result);
    PrintData<typename Loki::TL::Erase< TList,typename Loki::TL::TypeAt< TList, 0 >::Result >::Result>(data, writedSize);
};

template<>
void PrintData<Loki::NullType>(void* data,int writedSize)
{
};

template<class T>
class Reader {
public:
    void* readNextLine() {
        void* data = malloc(size);
        ReadData<T>(data);
        return data;
    };
    
    void print(void* data) {
        PrintData<T>(data, 0);
    }
    
    static const int size = LineSize<T, Loki::TL::Length<T>::value>::size;
};

int main(int argc, const char * argv[]) {
//    typedef TypeList<char, char, char> TL1;
//    typedef TypeList<char, short> TL2;
//
//    std::cout << TL1() << ", " << TL2() << std::endl;
//    std::cout << Append<TL2, TL1>::type() << std::endl;
    
    freopen("/Users/Hoderu/Desktop/Projects/patterns/patterns/input.txt", "r", stdin);
    void* data;
    Reader<Loki::TL::MakeTypelist<char, char, char>::Result> reader;
    data = reader.readNextLine();
    reader.print(data);
    data = reader.readNextLine();
    reader.print(data);
    
    return 0;
}
