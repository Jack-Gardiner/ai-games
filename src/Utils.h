#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#pragma once
std::vector<std::string> split(std::string input, std::string splitter);
std::vector<int> splitint(std::string input, std::string splitter);
/*
template<class T>
T vcopy(T vec);
template<class T>
std::vector<T> vcopy(std::vector<T> vec);
*/

template<class T>
T vcopy(T vec){
    static_assert(std::is_copy_constructible_v<T>);
    return *(new T(vec));
}
template<class T>
std::vector<T> vcopy(std::vector<T> vec){
    std::vector<T> ret = std::vector<T>();
    for(int i = 0; i < vec.size();i++){
        ret.push_back(vcopy<T>(vec[i]));
    }
    return ret;
}