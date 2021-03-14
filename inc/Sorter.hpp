#pragma once

#include <iostream>


enum SortType{
    ASC,
    DES
};

template<class T>
class Sorter
{
protected:
    SortType m_type;

public:
    Sorter() : m_type(ASC){}
    Sorter(SortType type) : m_type(type){}

    virtual void sort(T *array, int l, int r) = 0;
};

void printArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
}