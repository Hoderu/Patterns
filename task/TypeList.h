//
//  TypeList.h
//  patterns
//
//  Created by Андрей Решетников on 24.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

#include <iostream>

class EmptyNode
{
};

template <typename ...Arg>
class TypeList {
public:
    typedef EmptyNode _head;
    typedef EmptyNode _tail;
};

typedef TypeList<> EmptyTypeList;

template <typename H, typename ...Args>
class TypeList<H, Args...> {
public:
    typedef H _head;
    typedef TypeList<Args...> _tail;
};
