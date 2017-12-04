//
//  main.cpp
//  patterns
//
//  Created by Андрей Решетников on 19.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

#include "Append+Erase.h"
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

template<typename TL>
struct Length :
std::integral_constant<unsigned int, 0>
{
};

template<typename ...Args>
struct Length<TypeList<Args...>> :
std::integral_constant<unsigned int, IsEmpty<TypeList<Args...>>::value
? 0
: 1 + Length<typename TypeList<Args...>::_tail>::value>
{
};

template<unsigned int N, typename TL>
struct TypeAt
{
    typedef EmptyNode type;
};

template<typename ...Args>
struct TypeAt<0, TypeList<Args...>>
{
    typedef typename TypeList<Args...>::_head type;
};

template<unsigned int N, typename ...Args>
struct TypeAt<N, TypeList<Args...>>
{
    typedef typename TypeAt<N - 1, typename TypeList<Args...>::_tail>::type type;
};

template<typename ...Args>
std::ostream& operator<<(std::ostream& ostr, TypeList<Args...> tl)
{
    ostr << '{';
    PrintTypeListHelper(tl, ostr);
    ostr << '}';
    return ostr;
}

template<class T, int n>
class LineSize {
public:
    static const int size = LineSize<Erase<T, TypeAt<0, T>>, n - 1>::size + sizeof(typename TypeAt<0, T>::type);
};

template<class T>
class LineSize<T, 0> {
public:
    static const int size = 0;
};

template<class TList>
void ReadData(void* data) {
    typename TypeAt<0, TList>::type type;
    void* source;
    std::cin >> type;
    source = &type;
    memcpy(data, source, sizeof(typename TypeAt<0, TList>::type));
    data = (typename TypeAt<0, TList>::type*)data + sizeof(typename TypeAt<0, TList>::type);
    ReadData<Erase<TList, TypeAt<0, TList>>>(data);
};

template<>
void ReadData<EmptyNode>(void* data)
{};

template<class T>
class Reader {
public:
    void* readNextLine() {
        void* data = malloc(8);
        ReadData<T>(data);
        return data;
    };
    
    static const int size = LineSize<T, Length<T>::value>::size;
};

int main(int argc, const char * argv[]) {
    typedef TypeList<char, char, char> TL1;
    typedef TypeList<char, short> TL2;
    
    std::cout << TL1() << ", " << TL2() << std::endl;
    std::cout << Append<TL2, TL1>::type() << std::endl;
    
    void* data;
    Reader<TL1> reader;
    data = reader.readNextLine();
    
    return 0;
}
