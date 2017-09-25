//
//  IsEmpty.h
//  patterns
//
//  Created by Андрей Решетников on 24.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

#include "TypeList.h"

template<typename TL>
struct IsEmpty :
std::true_type
{
};

template<>
struct IsEmpty<TypeList<EmptyNode, EmptyNode>> :
std::true_type
{
};

template <typename ...Args>
struct IsEmpty<TypeList<Args...>> :
    std::integral_constant<bool,
        std::is_same<typename TypeList<Args...>::_head, EmptyNode>::value &&
        IsEmpty<typename TypeList<Args...>::_tail>::value>
{
};
