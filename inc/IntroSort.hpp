#pragma once

#include <iostream>
#include <algorithm>
#include <math.h>

#include "Sorter.hpp"
#include "HeapSort.hpp"

/**
 * @brief Sort array by IntroSort algorithm
 * 
 * @tparam T type of data to sort
 */
template <class T>
class IntroSort : public Sorter<T>
{
private:
    /**
     * @brief The main function of sorting by MergeSort
     * 
     * @param array reference to array
     * @param max_depth max depth counter of recursion
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_introSort(std::vector<T> &array, int max_depth, int first, int last);

    /**
     * @brief Organizes elements in array
     * This function takes last element value, places all smaler elements to left, 
     * all greater elements to right and place chosen element between them as partition.
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     * @return int index where partition was placed
     */
    int m_partition(std::vector<T> &array, int first, int last);

public:
    /**
     * @brief Construct a new Intro Sort object
     * If not specified, sort in ascending order.
     */
    IntroSort() : Sorter<T>() {}

    /**
     * @brief Construct a new Intro Sort object with specific order
     * 
     * @param order sort order (ASC or DES)
     */
    IntroSort(SortOrder order) : Sorter<T>(order) {}

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
void IntroSort<T>::m_introSort(std::vector<T> &array, int max_depth, int first, int last)
{
    if (first < last)
    {
        if(max_depth == 0)
        {
            HeapSort<T> H(this->m_order);
            H.Sort(array, first, last);
        }
        else
        {
            int q = m_partition(array, first, last);
            m_introSort(array, max_depth - 1, first, q - 1);
            m_introSort(array, max_depth - 1, q + 1, last);
        }
    }
}

template <class T> 
int IntroSort<T>::m_partition(std::vector<T> &array, int first, int last)
{
    int q = array[last];
    int i = first - 1;

    switch (this->m_order)
    {
    case ASC:
        for (int j = first; j < last; ++j)
        {
            if (array[j] <= q)
            {
                std::swap(array[++i], array[j]);
            }
        }
        break;

    case DES:
        for (int j = first; j < last; ++j)
        {
            if (array[j] >= q)
            {
                std::swap(array[++i], array[j]);
            }
        }
        break;
    }

    std::swap(array[++i], array[last]);
    return i;
}

template <class T>
void IntroSort<T>::Sort(std::vector<T> &array, int first, int last)
{
    if (first < 0 || last >= (int)array.size())
        std::invalid_argument("Invalid array index value");
    int max_depth = (int)(2 * floor(log(last - first + 1)));
    m_introSort(array, max_depth, first, last);
}