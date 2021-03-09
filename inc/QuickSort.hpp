#pragma once

#include <iostream>
#include <algorithm>
#include <Sorter.hpp>

template <class T>
class QuickSort : public Sorter<T>
{
private:
    void m_quickSort(T *array, int l, int r, SortType type);

public:
    void sort(T *array, int l, int r, SortType type = ASC) override;
};

template <class T>
void QuickSort<T>::m_quickSort(T *array, int l, int r, SortType type)
{
    if(l < r)
    {
       q= 
    }
}

template <class T>
void QuickSort<T>::sort(T *array, int l, int r, SortType type = ASC)
{
    m_quickSort(array, l, r, type);
}