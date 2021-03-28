#pragma once

#include <iostream>
#include <algorithm>

#include "Sorter.hpp"

/**
 * @brief Sort array by QuickSort algorithm
 * 
 * @tparam T type of data to sort
 */
template <class T>
class QuickSort : public Sorter<T>
{
private:
    /**
     * @brief The main function of sorting by QuickSort
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_quickSort(std::vector<T> &array, int first, int last);

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
     * @brief Construct a new Quick Sort object
     * If not specified, sort in ascending order.
     */
    QuickSort() : Sorter<T>() {}

    /**
     * @brief Construct a new Quick Sort object with specific order
     * 
     * @param order sort order (ASC or DES)
     */
    QuickSort(SortOrder order) : Sorter<T>(order) {}

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
void QuickSort<T>::m_quickSort(std::vector<T> &array, int first, int last)
{
    if(first < last)
    {
        int q = m_partition(array, first, last);
        m_quickSort(array, first, q - 1);
        m_quickSort(array, q + 1, last);
    }
}

template <class T>
int QuickSort<T>::m_partition(std::vector<T> &array, int first, int last)
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
void QuickSort<T>::Sort(std::vector<T> &array, int first, int last)
{
    if(first < 0 || last >= (int)array.size())
        std::invalid_argument("Invalid array index value");
    m_quickSort(array, first, last);
}