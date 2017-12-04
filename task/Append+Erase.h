//
//  Append.h
//  patterns
//
//  Created by Андрей Решетников on 24.09.17.
//  Copyright © 2017 Андрей Решетников. All rights reserved.
//

#import "TypeList.h"

template<typename T, typename TL>
struct Append
{
};

template<typename T, typename ...Args>
struct Append<T, TypeList<Args...>>
{
    typedef TypeList<Args..., T> type;
};

template<typename ...Args1, typename ...Args2>
struct Append<TypeList<Args1...>, TypeList<Args2...>>
{
    typedef TypeList<Args2..., Args1...> type;
};

template <typename TList, typename T>
struct Erase
{};

template <typename T>
struct Erase<EmptyNode, T>
{
    typedef EmptyNode Result;
};

template <typename T, typename Tail>
struct Erase<TypeList<T, Tail>, T>
{
    typedef Tail Result;
};
