#pragma once

#include <iostream>

#include "Sorter.hpp"

/**
 * @brief Sort array by MergeSort algorithm
 * 
 * @tparam T type of data to sort
 */
template <class T>
class MergeSort : public Sorter<T>
{
private:
    /**
     * @brief The main function of sorting by MergeSort
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void m_mergeSort(std::vector<T> &array, int first, int r);

    /**
     * @brief Merges two subarrays
     * 
     * @param array reverence to array
     * @param first index of first item to be sorted
     * @param q index of midle or midle left item
     * @param last index of last item to be sorted
     */
    void m_merge(std::vector<T> &array, int first, int q, int last);

public:
    /**
     * @brief Construct a new Merge Sort object
     * If not specified, sort in ascending order.
     */
    MergeSort() : Sorter<T>() {}

    /**
     * @brief Construct a new Merge Sort object with specific order
     * 
     * @param order sort order (ASC or DES)
     */
    MergeSort(SortOrder order) : Sorter<T>(order) {}

    /**
     * @brief Sort array in specified order
     * 
     * @param array reverence to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    void Sort(std::vector<T> &array, int first, int last) override;
};

template <class T>
void MergeSort<T>::m_mergeSort(std::vector<T> &array, int first, int last)
{
    if (first < last)
    {
        int q = (first + last) / 2;

        m_mergeSort(array, first, q);
        m_mergeSort(array, q + 1, last);
        m_merge(array, first, q, last);
    }
}

template <class T>
void MergeSort<T>::m_merge(std::vector<T> &array, int first, int q, int last)
{
    const int n = q - first + 1; //number of left elements
    const int m = last - q; //number of riht elements
    std::vector<T> temp_L(&array[first], &array[q + 1]);
    std::vector<T> temp_R(&array[q + 1], &array[last + 1]);

    int i = 0, j = 0, k = first;

    do
    {
        if (i == n) //if all items from left vector inserted, push back the rest of right vector
        {
            do
            {
                array[k++] = temp_R[j++];
            } while (j < m);
        }
        else if (j == m) //if all items from right vector inserted, push back the rest of left vector
        {
            do
            {
                array[k++] = temp_L[i++];
            } while (i < n);
        }
        else
        {
            if (this->m_order == ASC)
                temp_L[i] <= temp_R[j] ? array[k++] = temp_L[i++] : array[k++] = temp_R[j++];
            else
                temp_L[i] <= temp_R[j] ? array[k++] = temp_R[j++] : array[k++] = temp_L[i++];
        }
    } while (k <= last);
}

template <class T>
void MergeSort<T>::Sort(std::vector<T> &array, int first, int last)
{
    if (first < 0 || last >= (int)array.size())
        std::invalid_argument("Invalid array index value");
    m_mergeSort(array, first, last);
}

