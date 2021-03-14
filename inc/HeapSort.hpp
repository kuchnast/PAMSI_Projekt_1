#pragma once

#include <iostream>
#include <algorithm>
#include "Sorter.hpp"

template <class T>
class HeapSort : public Sorter<T>
{
private:
    void m_heapSort(T *array, int l, int r);
    void m_max_heapify(T *array, int l, int r, int i);
    void m_min_heapify(T *array, int l, int r, int i);
    void m_build_max_heap(T *array, int l, int r);
    void m_build_min_heap(T *array, int l, int r);

public:
    using Sorter<T>::Sorter;
    void sort(T *array, int l, int r) override;
};

template <class T>
void HeapSort<T>::m_heapSort(T *array, int l, int r)
{   
    switch (this->m_type)
    {
    case ASC:
        m_build_max_heap(array, l, r);
        for (int i = r; i >= l && i > 0; --i)
        {
            std::swap(array[l], array[i]);
            m_max_heapify(array, l, --r, l);
        }
        break;
    
    case DES:
        m_build_min_heap(array, l, r);
        for (int i = r; i >= l && i > 0; --i)
        {
            std::swap(array[l], array[i]);
            m_min_heapify(array, l, --r, l);
        }
        break;
    }
    

}

template<class T>
void HeapSort<T>::m_max_heapify(T *array, int l, int r, int i) 
{
    int child_l = 2 * i + 1 - l;
    int child_r = 2 * i + 2 - l;
    int largest;

    (child_l <= r && array[child_l] > array[i]) ? largest = child_l : largest = i;

    if(child_r <= r && array[child_r] > array[largest])
        largest = child_r;
    
    if(largest != i)
    {
        std::swap(array[i], array[largest]);
        m_max_heapify(array, l, r, largest);
    }
}


template<class T>
void HeapSort<T>::m_min_heapify(T *array, int l, int r, int i) 
{
    int child_l = 2 * i + 1 - l;
    int child_r = 2 * i + 2 - l;
    int smallest;

    (child_l <= r && array[child_l] < array[i]) ? smallest = child_l : smallest = i;

    if(child_r <= r && array[child_r] < array[smallest])
        smallest = child_r;
    
    if(smallest != i)
    {
        std::swap(array[i], array[smallest]);
        m_min_heapify(array, l, r, smallest);
    }
}

template<class T>
void HeapSort<T>::m_build_max_heap(T *array, int l, int r) 
{
    for (int i = (r - 1) / 2 + l; i >= l; --i)
    {
        m_max_heapify(array, l, r, i);
    }
}

template<class T>
void HeapSort<T>::m_build_min_heap(T *array, int l, int r) 
{
        for (int i = (r - 1) / 2 + l; i >= l; --i)
    {
        m_min_heapify(array, l, r, i);
    }
}

template <class T>
void HeapSort<T>::sort(T *array, int l, int r)
{
    m_heapSort(array, l, r);
}