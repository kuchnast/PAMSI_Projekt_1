#pragma once

#include <iostream>
#include <algorithm>

#include "Sorter.hpp"

/**
 * @brief Sort array by HeapSort algorithm
 * 
 * @tparam T type of data to sort
 */
template <class T>
class HeapSort : public Sorter<T>
{
private:
    /**
     * @brief The main function of sorting by HeapSort
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_heapSort(std::vector<T> &array, int first, int last);

    /**
     * @brief Procedure for restoring max heap structure
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     * @param i index of parent in heap structure
     */
    void m_max_heapify(std::vector<T> &array, int first, int last, int i);

    /**
     * @brief Procedure for restoring min heap structure from specified parent
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     * @param i index of parent in heap structure
     */
    void m_min_heapify(std::vector<T> &array, int first, int last, int i);

    /**
     * @brief Build max heap structure
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_build_max_heap(std::vector<T> &array, int first, int last);

    /**
     * @brief Build min heap structure
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_build_min_heap(std::vector<T> &array, int first, int last);

public:
    /**
     * @brief Construct a new Heap Sort object
     * If not specified, sort in ascending order.
     */
    HeapSort() : Sorter<T>() {}

    /**
     * @brief Construct a new Heap Sort object with specific order
     * 
     * @param order sort order (ASC or DES)
     */
    HeapSort(SortOrder order) : Sorter<T>(order) {}

    /**
     * @brief Sort array in specified order
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void Sort(std::vector<T> &array, int first, int last) override;
};

template <class T>
void HeapSort<T>::m_heapSort(std::vector<T> &array, int first, int last)
{   
    switch (this->m_order)
    {
    case ASC:
        m_build_max_heap(array, first, last);
        for (int i = last; i >= first && i > 0; --i)
        {
            std::swap(array[first], array[i]);
            m_max_heapify(array, first, --last, first);
        }
        break;
    
    case DES:
        m_build_min_heap(array, first, last);
        for (int i = last; i >= first && i > 0; --i)
        {
            std::swap(array[first], array[i]);
            m_min_heapify(array, first, --last, first);
        }
        break;
    }
}

template<class T>
void HeapSort<T>::m_max_heapify(std::vector<T> &array, int first, int last, int i) 
{
    int child_l = 2 * i + 1 - first;
    int child_r = 2 * i + 2 - first;
    int largest;

    (child_l <= last && array[child_l] > array[i]) ? largest = child_l : largest = i;

    if (child_r <= last && array[child_r] > array[largest])
        largest = child_r;
    
    if(largest != i)
    {
        std::swap(array[i], array[largest]);
        m_max_heapify(array, first, last, largest);
    }
}


template<class T>
void HeapSort<T>::m_min_heapify(std::vector<T> &array, int first, int last, int i) 
{
    int child_l = 2 * i + 1 - first;
    int child_r = 2 * i + 2 - first;
    int smallest;

    (child_l <= last && array[child_l] < array[i]) ? smallest = child_l : smallest = i;

    if (child_r <= last && array[child_r] < array[smallest])
        smallest = child_r;
    
    if(smallest != i)
    {
        std::swap(array[i], array[smallest]);
        m_min_heapify(array, first, last, smallest);
    }
}

template<class T>
void HeapSort<T>::m_build_max_heap(std::vector<T> &array, int first, int last) 
{
    for (int i = (last - 1) / 2 + first; i >= first; --i)
    {
        m_max_heapify(array, first, last, i);
    }
}

template<class T>
void HeapSort<T>::m_build_min_heap(std::vector<T> &array, int first, int last) 
{
    for (int i = (last - 1) / 2 + first; i >= first; --i)
    {
        m_min_heapify(array, first, last, i);
    }
}

template <class T>
void HeapSort<T>::Sort(std::vector<T> &array, int first, int last)
{
    if (first < 0 || last >= (int)array.size())
        std::invalid_argument("Invalid array index value");
    m_heapSort(array, first, last);
}