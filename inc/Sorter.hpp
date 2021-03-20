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
    explicit Sorter(SortType type) : m_type(type){}

    virtual void sort(T *array, int l, int r) = 0;

    void SetSortType(SortType type);
    SortType GetSortType() const;
};

template<class T>
void Sorter<T>::SetSortType(SortType type) 
{
    m_type = type;
}


template<class T>
SortType Sorter<T>::GetSortType() const
{
    return m_type;
}