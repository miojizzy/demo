#pragma once

#include <ostream>
#include <vector>
#include <deque>
#include <set>
//#include <multiset>
#include <map>
//#include <multimap>


template<typename T,typename... Types>
struct IsContainerType{
    static const bool value = false;
};
 
template<typename T,typename... Types>
struct IsContainerType<std::vector<T, Types...>>{
    static const bool value = true;
};

template<typename T,typename... Types>
struct IsContainerType<std::deque<T, Types...>>{
    static const bool value = true;
};
 
template<typename T,typename... Types>
struct IsContainerType<std::set<T, Types...>>{
    static const bool value = true;
};
 
template<typename T,typename... Types>
struct IsContainerType<std::multiset<T, Types...>>{
    static const bool value = true;
};
 
template<typename K,typename V,typename... Types>
struct IsContainerType<std::map<K, V, Types...>>{
    static const bool value = true;
};
 
template<typename K,typename V,typename... Types>
struct IsContainerType<std::multimap<K, V, Types...>>{
    static const bool value = true;
};

template<typename T,typename... Types>
constexpr bool is_container = IsContainerType<T, Types...>::value;


// we define operator << for std::pair used in the std::map
template<typename F,typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<F, S>& p){
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}


//template<typename,typename...> class Cntr 
template< template<typename,typename...> class Cntr,typename T,typename... Types>
std::enable_if_t<is_container<Cntr<T,Types...>>,std::ostream&>
operator<<(std::ostream& os, const Cntr<T, Types...>& cntr){
    if (!cntr.empty()){
        auto last_element = std::prev(cntr.end());
        os << "{";
        for (auto itr = cntr.begin(); itr != last_element; itr = std::next(itr)){
            os << *itr << ", ";
        }
        os << *last_element << "}";
    }
    return os;
}

