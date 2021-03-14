#pragma once

#include <iostream>
#include <algorithm>
#include <math.h>
#include "Sorter.hpp"
#include "HeapSort.hpp"
#include "QuickSort.hpp"

template <class T>
class IntroSort : public Sorter<T>
{
private:
    void m_introSort(T *array, int maxdepth, int l, int r);
    int m_partition(T *array, int l, int r);

public:
    using Sorter<T>::Sorter;
    void sort(T *array, int l, int r) override;
};

template <class T>
void IntroSort<T>::m_introSort(T *array, int maxdepth, int l, int r)
{
    if (l < r)
    {
        if(maxdepth == 0)
        {
            HeapSort<T> H(this->m_type);
            H.sort(array, l, r);
        }
        else
        {
                int q = m_partition(array, l, r);
                m_introSort(array, maxdepth - 1, l, q - 1);
                m_introSort(array, maxdepth - 1, q + 1, r);
        }
    }
}

template <class T> 
int IntroSort<T>::m_partition(T *array, int l, int r)
{
    int q = array[r];
    int i = l - 1;

    for (int j = l; j < r; ++j)
    {
        switch (this->m_type)
        {
        case ASC:
            if(array[j] <= q)
            {
                std::swap(array[++i], array[j]);
            }
            break;
        
        case DES:
            if(array[j] >= q)
            {
                std::swap(array[++i], array[j]);
            }
            break;
        }
    }

    std::swap(array[++i], array[r]);
    return i;
}

template <class T>
void IntroSort<T>::sort(T *array, int l, int r)
{
    int maxdepth = (int)(2 * floor(log(r - l + 1)));
    m_introSort(array, maxdepth, l, r);
}