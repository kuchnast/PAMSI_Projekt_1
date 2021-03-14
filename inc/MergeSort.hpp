#pragma once

#include <iostream>
#include "Sorter.hpp"

template <class T>
class MergeSort : public Sorter<T>
{
private:
    void m_mergeSort(T *array, int l, int r);

    void m_merge(T *array, int l, int q, int r);

public:
    using Sorter<T>::Sorter;
    void sort(T *array, int l, int r) override;
};

template <class T>
void MergeSort<T>::m_mergeSort(T *array, int l, int r)
{
    if (l < r)
    {
        int q = (l + r) / 2;

        m_mergeSort(array, l, q);
        m_mergeSort(array, q + 1, r);
        m_merge(array, l, q, r);
    }
}

template <class T>
void MergeSort<T>::m_merge(T *array, int l, int q, int r)
{
    const int n = q - l + 1;
    const int m = r - q;
    int *temp_L = new int[n], *temp_R = new int[m];

    for (int i = 0; i < n; i++)
        temp_L[i] = array[l + i];

    for (int i = 0; i < m; i++)
        temp_R[i] = array[q + 1 + i];

    int i = 0, j = 0, k = l;

    do
    {
        if (i == n)
        {
            do
            {
                array[k++] = temp_R[j++];
            } while (j < m);
        }
        else if (j == m)
        {
            do
            {
                array[k++] = temp_L[i++];
            } while (i < n);
        }
        else
        {
            switch (this->m_type)
            {
            case ASC:
                temp_L[i] <= temp_R[j] ? array[k++] = temp_L[i++] : array[k++] = temp_R[j++];
                break;

            case DES:
                temp_L[i] <= temp_R[j] ? array[k++] = temp_R[j++] : array[k++] = temp_L[i++];
                break;
            }
        }
    } while (k < r + 1);

    delete[] temp_L;
    delete[] temp_R;
}

template <class T>
void MergeSort<T>::sort(T *array, int l, int r)
{
    m_mergeSort(array, l, r);
}

