#pragma once

#include <iostream>


enum SortType{
    ASC,
    DES
}

template<class T>
class Sorter
{
public:

    virtual void sort(T *array, int size, SortType type = ASC) = 0;
};
